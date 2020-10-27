#ifndef __FIRMWARE_UPDATER_H__
#define __FIRMWARE_UPDATER_H__

#include <WebServer.h>

typedef std::function<void(void)> THandlerFunction;

class FirmwareUpdater {
  public:
    void setup(const char* username, const char* password);
    void handle();
  private:
    void setup_root_path();
    void setup_update_path();
    void authenticate_and_handle(THandlerFunction handler);
    void handle_update();
    void finish_update();
    
    WebServer server;
    const char* _username;
    const char* _password;
};

#endif //ESP8266WEBSERVER_H
