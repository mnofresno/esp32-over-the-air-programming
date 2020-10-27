#include "FirmwareUpdater.h"

#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include "UploaderPage.h"

void FirmwareUpdater::setup(const char* username, const char* password) {
  _username = username;
  _password = password;
  setup_root_path();
  setup_update_path();
  ArduinoOTA.begin();
  server.begin(80);
}

void FirmwareUpdater::handle() {
  server.handleClient();
  ArduinoOTA.handle();
}

void FirmwareUpdater::setup_root_path() {
  server.on("/", [&]() {
    authenticate_and_handle([&](){
      server.send(200, "text/html", serverIndex);
    });
  });
}

void FirmwareUpdater::authenticate_and_handle(THandlerFunction handler) {
  if (!server.authenticate(_username, _password)) {
    // FIXME: Maybe we can add a flag: return this or redirect?
    // server.send(200, "Auth error");
    return server.requestAuthentication();
  }
  handler();
}

void FirmwareUpdater::setup_update_path() {
  server.on("/update", HTTP_POST, [&]() {
    finish_update();
  }, [&]() {
    handle_update();
  });
}

void FirmwareUpdater::handle_update() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("Update: %s\n", upload.filename.c_str());
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { //true to set the size to the current progress
      Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
  }
}

void FirmwareUpdater::finish_update() {
  authenticate_and_handle([&](){
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  });
}
