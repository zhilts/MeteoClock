#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "Log.h"
#include "Led.h"
#include "Display.h"
#include "RTCTime.h"
#include "Photo.h"
#include "CO2.h"
#include "BME.h"
#include "Button.h"
#include "Rain.h"
#include "Memory.h"
#include "MQTT.h"

WebServer server(80);

DynamicJsonDocument getCO2Json() {
    DynamicJsonDocument jsonDoc(256);
    jsonDoc["status"] = getCO2Status();
    jsonDoc["value"] = getCO2();
    return jsonDoc;
}

DynamicJsonDocument getBMEJson() {
    DynamicJsonDocument jsonDoc(256);
    BMEValue value = getBMEValue();
    jsonDoc["pressure"] = value.pressure;
    jsonDoc["temperature"] = value.temperature;
    jsonDoc["humidity"] = value.humidity;
    return jsonDoc;
}

DynamicJsonDocument getTimeJson() {
    DynamicJsonDocument jsonDoc(256);
    jsonDoc["iso"] = getNowISO();
    return jsonDoc;
}

DynamicJsonDocument getLogsJson() {
    DynamicJsonDocument jsonDoc(256);
    jsonDoc["enabled"] = getHttpLogsEnabled();
    jsonDoc["host"] = getHttpLogsHost();
    jsonDoc["port"] = getHttpLogsPort();
    return jsonDoc;
}

DynamicJsonDocument getMQTTJson() {
    DynamicJsonDocument jsonDoc(256);
    MQTTConfig config = getMQTTConfig();
    jsonDoc["enabled"] = config.enabled;
    jsonDoc["name"] = config.name;
    jsonDoc["host"] = config.host;
    jsonDoc["port"] = config.port;
    return jsonDoc;
}

DynamicJsonDocument getWifiJson() {
    DynamicJsonDocument jsonDoc(256);
    WiFiCredentials credentials = readWiFiCredentials();
    jsonDoc["ssid"] = credentials.ssid;
    return jsonDoc;
}

DynamicJsonDocument getData() {
    DynamicJsonDocument jsonDoc(512);

    jsonDoc["ledValue"] = rgbGetValue();
    jsonDoc["modeValue"] = getMeteoMode();
    jsonDoc["photoValue"] = getBrightness();
    jsonDoc["co2"] = getCO2Json();
    jsonDoc["bme"] = getBMEJson();
    jsonDoc["time"] = getTimeJson();
    jsonDoc["rain"] = getRainValue();
    jsonDoc["logs"] = getLogsJson();
    jsonDoc["mqtt"] = getMQTTJson();
    jsonDoc["wifi"] = getWifiJson();
    return jsonDoc;
}

void httpDashboard() {
    File indexHtml = SPIFFS.open("/index.html", "r");
    if (!indexHtml) {
        server.send(404, "text/plain", "Page not found");
        return;
    }
    server.sendHeader("Content-Type", "text/html");

    while (indexHtml.available()) {
        server.streamFile(indexHtml, "text/html");
    }

    indexHtml.close();
}
void httpData() {
    DynamicJsonDocument jsonDoc = getData();

    String jsonString;
    serializeJson(jsonDoc, jsonString);
    server.send(200, "application/json", jsonString);
}

void httpUpdateDebug() {
    auto ledValue = static_cast<RGB_COLOR>(server.arg("ledValue").toInt());
    rgbSetValue(ledValue);

    auto modeValue = static_cast<METEO_MODE>(server.arg("modeValue").toInt());
    setMeteoMode(modeValue);

    String lcdText = server.arg("lcdText");
    if (lcdText.length() > 0) {
        lcdSetCursor(0, 0);
        lcdPrint(lcdText);
    }

    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Refresh");
}

void httpUpdateConfig() {
    String logsEnabledStr = server.arg("logsEnabled");
    setHttpLogsEnabled(logsEnabledStr == "on");

    String logsHost = server.arg("logsHost");
    setHttpLogsHost(logsHost);

    int logsPort = server.arg("logsPort").toInt();
    setHttpLogsPort(logsPort);

    MQTTConfig mqtt;
    mqtt.enabled = server.arg("mqttEnabled") == "on";
    mqtt.name = server.arg("mqttName");
    mqtt.host = server.arg("mqttHost");
    mqtt.port = server.arg("mqttPort").toInt();
    setMQTTConfig(mqtt);

    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Refresh");
}

void httpUpdateWiFi() {
    WiFiCredentials credentials;
    credentials.ssid = server.arg("wifiSSID");
    credentials.password = server.arg("wifiPassword");
    writeWiFiCredentials(credentials);

    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Refresh");

    ESP.restart();
}

void httpSetDatetime() {
    String datetimeStr = server.arg("datetime");
    unsigned long long datetime = atoll(datetimeStr.c_str());
    setEpochTime(datetime);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Refresh");
}

void setupServer() {
    SPIFFS.begin(true);
    MDNS.addService("http", "tcp", 80);
    server.on("/", httpDashboard);
    server.on("/data", httpData);
    server.on("/debug", HTTP_POST, httpUpdateDebug);
    server.on("/config", HTTP_POST, httpUpdateConfig);
    server.on("/wifi", HTTP_POST, httpUpdateWiFi);
    server.on("/datetime", HTTP_POST, httpSetDatetime);
    server.begin();
}

void serverHandle() {
    server.handleClient();
}