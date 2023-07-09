#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

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

const String DASHBOARD = "<!DOCTYPE html>\n"
                         "<html lang=\"en\">\n"
                         "<head>\n"
                         "    <meta charset=\"UTF-8\">\n"
                         "    <title>Meteo clock setup</title>\n"
                         "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                         "    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js\"></script>\n"
                         "    <link href=\"//cdn.muicss.com/mui-0.10.3/css/mui.min.css\" rel=\"stylesheet\" type=\"text/css\"/>\n"
                         "    <script src=\"//cdn.muicss.com/mui-0.10.3/js/mui.min.js\"></script>\n"
                         "    <style>\n"
                         "        h3 {\n"
                         "            margin-top: 0;\n"
                         "            margin-bottom: 0;\n"
                         "            padding: 20px;\n"
                         "        }\n"
                         "\n"
                         "        .control {\n"
                         "            display: flex;\n"
                         "            gap: 20px;\n"
                         "        }\n"
                         "\n"
                         "        .control label {\n"
                         "            min-width: 80px;\n"
                         "        }\n"
                         "\n"
                         "        .control input:not([type='checkbox']), .control select {\n"
                         "            flex-grow: 2;\n"
                         "        }\n"
                         "\n"
                         "        .multi-control {\n"
                         "            display: flex;\n"
                         "            flex-direction: column;\n"
                         "        }\n"
                         "\n"
                         "        .mui-container {\n"
                         "            padding: 20px;\n"
                         "            display: grid;\n"
                         "            grid-template-columns: repeat(auto-fill, minmax(400px, 1fr));\n"
                         "            grid-template-rows: auto;\n"
                         "            grid-auto-rows: auto;\n"
                         "            gap: 20px\n"
                         "        }\n"
                         "\n"
                         "        .mui-panel {\n"
                         "            margin: 0;\n"
                         "        }\n"
                         "\n"
                         "        .mui-container::before {\n"
                         "            display: none;\n"
                         "        }\n"
                         "\n"
                         "        .mui-appbar {\n"
                         "            margin-bottom: 15px;\n"
                         "        }\n"
                         "    </style>\n"
                         "</head>\n"
                         "<body class=\"mui-container\">\n"
                         "<div class=\"mui-panel\">\n"
                         "    <div class=\"mui-appbar\">\n"
                         "        <h3>Status</h3>\n"
                         "    </div>\n"
                         "    <p class=\"control\">\n"
                         "        <label>CO2:</label>\n"
                         "        <span id=\"co2Value\"></span>\n"
                         "    </p>\n"
                         "    <p class=\"control\">\n"
                         "        <label>Pressure:</label>\n"
                         "        <span id=\"pressure\"></span>\n"
                         "    </p>\n"
                         "    <p class=\"control\">\n"
                         "        <label>Temperature:</label>\n"
                         "        <span id=\"temperature\"></span>\n"
                         "    </p>\n"
                         "    <p class=\"control\">\n"
                         "        <label>Humidity:</label>\n"
                         "        <span id=\"humidity\"></span>\n"
                         "    </p>\n"
                         "    <p class=\"control\">\n"
                         "        <label>Rain:</label>\n"
                         "        <span id=\"rain\"></span>\n"
                         "    </p>\n"
                         "    <p class=\"control\">\n"
                         "        <label>Time:</label>\n"
                         "        <span id=\"time\"></span>\n"
                         "    </p>\n"
                         "</div>\n"
                         "<div class=\"mui-panel\">\n"
                         "    <div class=\"mui-appbar\">\n"
                         "        <h3>Config</h3>\n"
                         "    </div>\n"
                         "    <form action=\"/config\" method=\"POST\" class=\"mui-form\">\n"
                         "        <div class=\"multi-control\">\n"
                         "            <h4>Logs</h4>\n"
                         "            <p class=\"control\">\n"
                         "                <label for=\"LogsEnabled\">Enabled:</label>\n"
                         "                <input type=\"checkbox\" id=\"LogsEnabled\" name=\"logsEnabled\">\n"
                         "            </p>\n"
                         "\n"
                         "            <p class=\"control\">\n"
                         "                <label for=\"LogsHost\">Host:</label>\n"
                         "                <input id=\"LogsHost\" name=\"logsHost\">\n"
                         "            </p>\n"
                         "            <p class=\"control\">\n"
                         "                <label for=\"LogsPort\">Port:</label>\n"
                         "                <input id=\"LogsPort\" name=\"logsPort\">\n"
                         "            </p>\n"
                         "        </div>\n"
                         "        <div class=\"mui-divider\"></div>\n"
                         "        <div class=\"multi-control\">\n"
                         "            <h4>MQTT</h4>\n"
                         "\n"
                         "            <p class=\"control\">\n"
                         "                <label for=\"LogsEnabled\">Enabled:</label>\n"
                         "                <input type=\"checkbox\" id=\"MQTTEnabled\" name=\"mqttEnabled\">\n"
                         "            </p>\n"
                         "\n"
                         "            <p class=\"control\">\n"
                         "                <label for=\"MQTTName\">Name:</label>\n"
                         "                <input id=\"MQTTName\" name=\"mqttName\">\n"
                         "            </p>\n"
                         "\n"
                         "            <p class=\"control\">\n"
                         "                <label for=\"MQTTHost\">Host:</label>\n"
                         "                <input id=\"MQTTHost\" name=\"mqttHost\">\n"
                         "            </p>\n"
                         "\n"
                         "            <p class=\"control\">\n"
                         "                <label for=\"MQTTPort\">Port:</label>\n"
                         "                <input id=\"MQTTPort\" name=\"mqttPort\">\n"
                         "            </p>\n"
                         "        </div>\n"
                         "        <button type=\"submit\" class=\"mui-btn mui-btn--primary\">Save</button>\n"
                         "        <button type=\"button\" class=\"mui-btn mui-btn--primary\" onclick=\"postTime()\">Set Date & Time</button>\n"
                         "    </form>\n"
                         "</div>\n"
                         "<div class=\"mui-panel\">\n"
                         "    <div class=\"mui-appbar\">\n"
                         "        <h3>Wi-Fi</h3>\n"
                         "    </div>\n"
                         "    <form action=\"/wifi\" method=\"POST\" class=\"mui-form\">\n"
                         "        <p class=\"control\">\n"
                         "            <label for=\"WiFiSSID\">SSID:</label>\n"
                         "            <input id=\"WiFiSSID\" name=\"wifiSSID\">\n"
                         "        </p>\n"
                         "\n"
                         "        <p class=\"control\">\n"
                         "            <label for=\"WiFiPassword\">Password:</label>\n"
                         "            <input id=\"WiFiPassword\" name=\"wifiPassword\" type=\"password\">\n"
                         "        </p>\n"
                         "        <button type=\"submit\" class=\"mui-btn mui-btn--primary\">Save & Restart</button>\n"
                         "    </form>\n"
                         "</div>\n"
                         "<div class=\"mui-panel\">\n"
                         "    <div class=\"mui-appbar\">\n"
                         "        <h3>Debug</h3>\n"
                         "    </div>\n"
                         "    <form action=\"/debug\" method=\"POST\">\n"
                         "        <p class=\"control\">\n"
                         "            <label for=\"LedValue\">Led value:</label>\n"
                         "            <select id=\"LedValue\" name=\"ledValue\">\n"
                         "                <option value=\"0\">Off</option>\n"
                         "                <option value=\"1\">Red</option>\n"
                         "                <option value=\"2\">Green</option>\n"
                         "                <option value=\"3\">Blue</option>\n"
                         "                <option value=\"4\">Yellow</option>\n"
                         "            </select>\n"
                         "        </p>\n"
                         "        <p class=\"control\">\n"
                         "            <label for=\"ModeValue\">Mode:</label>\n"
                         "            <select id=\"ModeValue\" name=\"modeValue\">\n"
                         "                <option value=\"0\">Clock</option>\n"
                         "                <option value=\"1\">Temperature hourly</option>\n"
                         "                <option value=\"2\">Temperature daily</option>\n"
                         "                <option value=\"3\">Humidity hourly</option>\n"
                         "                <option value=\"4\">Humidity daily</option>\n"
                         "                <option value=\"5\">Pressure hourly</option>\n"
                         "                <option value=\"6\">Pressure daily</option>\n"
                         "                <option value=\"7\">CO2 hourly</option>\n"
                         "                <option value=\"8\">CO2 daily</option>\n"
                         "                <option value=\"9\">Rain hourly</option>\n"
                         "                <option value=\"10\">Rain daily</option>\n"
                         "            </select>\n"
                         "        </p>\n"
                         "        <p class=\"control\">\n"
                         "            <label for=\"LcdText\">LCD Text:</label>\n"
                         "            <input id=\"LcdText\" name=\"lcdText\"/>\n"
                         "        </p>\n"
                         "        <button type=\"submit\" class=\"mui-btn mui-btn--primary\">Submit</button>\n"
                         "    </form>\n"
                         "</div>\n"
                         "<script>\n"
                         "    const {\n"
                         "        ledValue,\n"
                         "        modeValue,\n"
                         "        co2: {value: co2Value},\n"
                         "        bme: {pressure, temperature, humidity},\n"
                         "        time: {iso: isoTime},\n"
                         "        rain,\n"
                         "        logs: {enabled: logsEnabled, host: logsHost, port: logsPort},\n"
                         "        mqtt: {enabled: mqttEnabled, name: mqttName, host: mqttHost, port: mqttPort},\n"
                         "        wifi: {ssid}\n"
                         "    } = currentData;\n"
                         "    $('#co2Value').text(co2Value + 'ppm');\n"
                         "    $('#pressure').text(pressure.toFixed(2) + 'Pa');\n"
                         "    $('#temperature').text(temperature.toFixed(1) + '°C');\n"
                         "    $('#humidity').text(humidity + '%');\n"
                         "    $('#rain').text(rain + '%');\n"
                         "    $('#time').text(isoTime);\n"
                         "\n"
                         "    $(`#LedValue option[value=\"${ledValue}\"]`).prop('selected', true);\n"
                         "    $(`#ModeValue option[value=\"${modeValue}\"]`).prop('selected', true);\n"
                         "    $(\"#LogsEnabled\").prop('checked', logsEnabled);\n"
                         "    $(\"#LogsHost\").val(logsHost);\n"
                         "    $(\"#LogsPort\").val(logsPort);\n"
                         "    $(\"#MQTTEnabled\").prop('checked', mqttEnabled);\n"
                         "    $(\"#MQTTName\").val(mqttName);\n"
                         "    $(\"#MQTTHost\").val(mqttHost);\n"
                         "    $(\"#MQTTPort\").val(mqttPort);\n"
                         "    $(\"#WiFiSSID\").val(ssid);\n"
                         "</script>\n"
                         "<script>\n"
                         "    async function postTime() {\n"
                         "        const rawEpochTime = Date.now().valueOf();\n"
                         "        const timezoneOffset = new Date().getTimezoneOffset();\n"
                         "        const timezoneOffsetMs = timezoneOffset * 60 * 1000;\n"
                         "        const adjustedEpochTime = rawEpochTime - timezoneOffsetMs;\n"
                         "        const body = new URLSearchParams();\n"
                         "        body.append('datetime', adjustedEpochTime);\n"
                         "        const response = await fetch('/datetime', {\n"
                         "            method: 'POST',\n"
                         "            body\n"
                         "        });\n"
                         "        if (response.ok) {\n"
                         "            window.location.href = response.url;\n"
                         "        }\n"
                         "    }\n"
                         "</script>\n"
                         "</body>\n"
                         "</html>";

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

void httpDashboard() {
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

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    String html = String(DASHBOARD);
    html.replace("currentData;", jsonString + ";");
    server.send(200, "text/html", html);
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
    MDNS.addService("http", "tcp", 80);
    server.on("/", httpDashboard);
    server.on("/debug", HTTP_POST, httpUpdateDebug);
    server.on("/config", HTTP_POST, httpUpdateConfig);
    server.on("/wifi", HTTP_POST, httpUpdateWiFi);
    server.on("/datetime", HTTP_POST, httpSetDatetime);
    server.begin();
}

void serverHandle() {
    server.handleClient();
}