/**************************************************************
   WiFiManager is a library for the ESP8266/Arduino platform
   (https://github.com/esp8266/Arduino) to enable easy
   configuration and reconfiguration of WiFi credentials using a Captive Portal
   inspired by:
   http://www.esp8266.com/viewtopic.php?f=29&t=2520
   https://github.com/chriscook8/esp-arduino-apboot
   https://github.com/esp8266/Arduino/tree/esp8266/hardware/esp8266com/esp8266/libraries/DNSServer/examples/CaptivePortalAdvanced
   Built by AlexT https://github.com/tzapu
   Licensed under MIT license
 **************************************************************/

#ifndef WiFiManager_h
#define WiFiManager_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <memory>

extern "C" {
  #include "user_interface.h"
}

const char HTTP_HEAD[] PROGMEM            = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
const char HTTP_STYLE[] PROGMEM           = "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#c1d72f;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;} .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1em;}</style>";
const char HTTP_SCRIPT[] PROGMEM          = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
const char HTTP_HEAD_END[] PROGMEM        = "</head><body><div style='text-align:left;display:inline-block;min-width:260px;'><div style='margin-bottom:10px'><img src='data:image/png;base64,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'/></div>";
const char HTTP_PORTAL_OPTIONS[] PROGMEM  = "<form action=\"/wifi\" method=\"get\"><button>Configure WiFi</button></form><br/><form action=\"/0wifi\" method=\"get\"><button>Configure WiFi (No Scan)</button></form><br/><form action=\"/i\" method=\"get\"><button>Info</button></form><br/><form action=\"/r\" method=\"post\"><button>Reset</button></form>";
const char HTTP_ITEM[] PROGMEM            = "<div><a href='#p' onclick='c(this)'>{v}</a>&nbsp;<span class='q {i}'>{r}%</span></div>";
const char HTTP_FORM_START[] PROGMEM      = "<form method='get' action='wifisave'><input id='s' name='s' length=32 placeholder='SSID'><br/><input id='p' name='p' length=64 type='password' placeholder='password'><br/>";
const char HTTP_FORM_PARAM[] PROGMEM      = "<br/><input id='{i}' name='{n}' length={l} placeholder='{p}' value='{v}' {c}>";
const char HTTP_FORM_END[] PROGMEM        = "<br/><button type='submit'>save</button></form>";
const char HTTP_SCAN_LINK[] PROGMEM       = "<br/><div class=\"c\"><a href=\"/wifi\">Scan</a></div>";
const char HTTP_SAVED[] PROGMEM           = "<div>Credentials Saved<br />Trying to connect ESP to network.<br />If it fails reconnect to AP to try again</div>";
const char HTTP_END[] PROGMEM             = "</div></body></html>";

#define WIFI_MANAGER_MAX_PARAMS 10

class WiFiManagerParameter {
  public:
    WiFiManagerParameter(const char *custom);
    WiFiManagerParameter(const char *id, const char *placeholder, const char *defaultValue, int length);
    WiFiManagerParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);

    const char *getID();
    const char *getValue();
    const char *getPlaceholder();
    int         getValueLength();
    const char *getCustomHTML();
  private:
    const char *_id;
    const char *_placeholder;
    char       *_value;
    int         _length;
    const char *_customHTML;

    void init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);

    friend class WiFiManager;
};


class WiFiManager
{
  public:
    WiFiManager();

    boolean       autoConnect();
    boolean       autoConnect(char const *apName, char const *apPassword = NULL);

    //if you want to always start the config portal, without trying to connect first
    boolean       startConfigPortal();
    boolean       startConfigPortal(char const *apName, char const *apPassword = NULL);

    // get the AP name of the config portal, so it can be used in the callback
    String        getConfigPortalSSID();

    void          resetSettings();

    //sets timeout before webserver loop ends and exits even if there has been no setup.
    //usefully for devices that failed to connect at some point and got stuck in a webserver loop
    //in seconds setConfigPortalTimeout is a new name for setTimeout
    void          setConfigPortalTimeout(unsigned long seconds);
    void          setTimeout(unsigned long seconds);

    //sets timeout for which to attempt connecting, usefull if you get a lot of failed connects
    void          setConnectTimeout(unsigned long seconds);


    void          setDebugOutput(boolean debug);
    //defaults to not showing anything under 8% signal quality if called
    void          setMinimumSignalQuality(int quality = 8);
    //sets a custom ip /gateway /subnet configuration
    void          setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    //sets config for a static IP
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    //called when AP mode and config portal is started
    void          setAPCallback( void (*func)(WiFiManager*) );
    //called when settings have been changed and connection was successful
    void          setSaveConfigCallback( void (*func)(void) );
    //adds a custom parameter
    void          addParameter(WiFiManagerParameter *p);
    //if this is set, it will exit after config, even if connection is unsucessful.
    void          setBreakAfterConfig(boolean shouldBreak);
    //if this is set, try WPS setup when starting (this will delay config portal for up to 2 mins)
    //TODO
    //if this is set, customise style
    void          setCustomHeadElement(const char* element);
    //if this is true, remove duplicated Access Points - defaut true
    void          setRemoveDuplicateAPs(boolean removeDuplicates);

  private:
    std::unique_ptr<DNSServer>        dnsServer;
    std::unique_ptr<ESP8266WebServer> server;

    //const int     WM_DONE                 = 0;
    //const int     WM_WAIT                 = 10;

    //const String  HTTP_HEAD = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/><title>{v}</title>";

    void          setupConfigPortal();
    void          startWPS();

    const char*   _apName                 = "no-net";
    const char*   _apPassword             = NULL;
    String        _ssid                   = "";
    String        _pass                   = "";
    unsigned long _configPortalTimeout    = 0;
    unsigned long _connectTimeout         = 0;
    unsigned long _configPortalStart      = 0;

    IPAddress     _ap_static_ip;
    IPAddress     _ap_static_gw;
    IPAddress     _ap_static_sn;
    IPAddress     _sta_static_ip;
    IPAddress     _sta_static_gw;
    IPAddress     _sta_static_sn;

    int           _paramsCount            = 0;
    int           _minimumQuality         = -1;
    boolean       _removeDuplicateAPs     = true;
    boolean       _shouldBreakAfterConfig = false;
    boolean       _tryWPS                 = false;

    const char*   _customHeadElement      = "";

    //String        getEEPROMString(int start, int len);
    //void          setEEPROMString(int start, int len, String string);

    int           status = WL_IDLE_STATUS;
    int           connectWifi(String ssid, String pass);
    uint8_t       waitForConnectResult();

    void          handleRoot();
    void          handleWifi(boolean scan);
    void          handleWifiSave();
    void          handleInfo();
    void          handleReset();
    void          handleNotFound();
    void          handle204();
    boolean       captivePortal();

    // DNS server
    const byte    DNS_PORT = 53;

    //helpers
    int           getRSSIasQuality(int RSSI);
    boolean       isIp(String str);
    String        toStringIp(IPAddress ip);

    boolean       connect;
    boolean       _debug = true;

    void (*_apcallback)(WiFiManager*) = NULL;
    void (*_savecallback)(void) = NULL;

    WiFiManagerParameter* _params[WIFI_MANAGER_MAX_PARAMS];

    template <typename Generic>
    void          DEBUG_WM(Generic text);

    template <class T>
    auto optionalIPFromString(T *obj, const char *s) -> decltype(  obj->fromString(s)  ) {
      return  obj->fromString(s);
    }
    auto optionalIPFromString(...) -> bool {
      DEBUG_WM("NO fromString METHOD ON IPAddress, you need ESP8266 core 2.1.0 or newer for Custom IP configuration to work.");
      return false;
    }
};

#endif
