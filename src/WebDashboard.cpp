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

WebServer server(80);

const String DASHBOARD = "<!DOCTYPE html>\n"
                         "<html lang=\"en\">\n"
                         "<head>\n"
                         "    <meta charset=\"UTF-8\">\n"
                         "    <title>Meteo clock setup</title>\n"
                         "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                         "    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js\"></script>\n"
                         "    <style>\n"
                         "        .section {\n"
                         "        }\n"
                         "    </style>\n"
                         "</head>\n"
                         "<body>\n"
                         "<div class=\"section\">\n"
                         "    <h2>Status</h2>\n"
                         "    <p>\n"
                         "        CO2: <span id=\"co2Value\"></span> ppm; Status: <span id=\"co2Status\"></span>\n"
                         "    </p>\n"
                         "    <p>\n"
                         "        Pressure: <span id=\"pressure\"></span> Pa; Temperature: <span id=\"temperature\"></span>°C; Humidity: <span\n"
                         "            id=\"humidity\"></span>%\n"
                         "    </p>\n"
                         "    <p style=\"display: flex; align-items: center; gap: 20px\">\n"
                         "        Time: <span id=\"time\"></span>\n"
                         "        <button type=\"button\" onclick=\"postTime()\">Set current</button>\n"
                         "    </p>\n"
                         "</div>\n"
                         "<div class=\"section\">\n"
                         "    <h2>Update</h2>\n"
                         "    <form action=\"/update\" method=\"POST\">\n"
                         "        <p>\n"
                         "            <label for=\"LedValue\">Led value:</label>\n"
                         "            <select id=\"LedValue\" name=\"ledValue\">\n"
                         "                <option value=\"0\">Off</option>\n"
                         "                <option value=\"1\">Red</option>\n"
                         "                <option value=\"2\">Green</option>\n"
                         "                <option value=\"3\">Blue</option>\n"
                         "                <option value=\"4\">Yellow</option>\n"
                         "            </select>\n"
                         "        </p>\n"
                         "        <p>\n"
                         "            <label for=\"LcdText\">LCD Text:</label>\n"
                         "            <input id=\"LcdText\" name=\"lcdText\"/>\n"
                         "        </p>\n"
                         "        <p>\n"
                         "            <label for=\"LogsEnabled\">Logs:</label>\n"
                         "            <input type=\"checkbox\" id=\"LogsEnabled\" name=\"logsEnabled\">\n"
                         "\n"
                         "            <label for=\"LogsHost\">Host:</label>\n"
                         "            <input id=\"LogsHost\" name=\"logsHost\">\n"
                         "\n"
                         "            <label for=\"LogsPort\">Port:</label>\n"
                         "            <input id=\"LogsPort\" name=\"logsPort\">\n"
                         "        </p>\n"
                         "        <button type=\"submit\">Save</button>\n"
                         "    </form>\n"
                         "</div>\n"
                         "<script>\n"
                         "    const {\n"
                         "        ledValue,\n"
                         "        co2: {status: co2Status, value: co2Value},\n"
                         "        bme: {pressure, temperature, humidity},\n"
                         "        time: {iso: isoTime},\n"
                         "        logs: {enabled: logsEnabled, host: logsHost, port: logsPort},\n"
                         "    } = currentData;\n"
                         "    $('#co2Status').text(co2Status);\n"
                         "    $('#co2Value').text(co2Value);\n"
                         "    $('#pressure').text(pressure.toFixed(2));\n"
                         "    $('#temperature').text(temperature.toFixed(1));\n"
                         "    $('#humidity').text(humidity);\n"
                         "    $('#time').text(isoTime);\n"
                         "\n"
                         "    $(`#LedValue option[value=\"${ledValue}\"]`).prop('selected', true);\n"
                         "    $(\"#LogsEnabled\").prop('checked', logsEnabled);\n"
                         "    $(\"#LogsHost\").val(logsHost);\n"
                         "    $(\"#LogsPort\").val(logsPort);\n"
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

void httpDashboard() {
    DynamicJsonDocument jsonDoc(512);

    jsonDoc["ledValue"] = rgbGetValue();
    jsonDoc["photoValue"] = getBrightness();
    jsonDoc["co2"] = getCO2Json();
    jsonDoc["bme"] = getBMEJson();
    jsonDoc["time"] = getTimeJson();
    jsonDoc["logs"] = getLogsJson();

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    String html = String(DASHBOARD);
    html.replace("currentData;", jsonString + ";");
    server.send(200, "text/html", html);
}

void httpUpdate() {
    auto ledValue = static_cast<RGB_COLOR>(server.arg("ledValue").toInt());
    rgbSetValue(ledValue);

    String lcdText = server.arg("lcdText");
    if (lcdText.length() > 0) {
        lcdSetCursor(0, 0);
        lcdPrint(lcdText);
    }

    String logsEnabledStr = server.arg("logsEnabled");
    setHttpLogsEnabled(logsEnabledStr == "on");

    String logsHost = server.arg("logsHost");
    setHttpLogsHost(logsHost);

    int logsPort = server.arg("logsPort").toInt();
    setHttpLogsPort(logsPort);

    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Refresh");
}

void httpSetDatetime() {
    String datetimeStr = server.arg("datetime");
    unsigned long long  datetime = atoll(datetimeStr.c_str());
    setEpochTime(datetime);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Refresh");
}

void setupServer() {
    MDNS.addService("http", "tcp", 80);
    server.on("/", httpDashboard);
    server.on("/update", HTTP_POST, httpUpdate);
    server.on("/datetime", HTTP_POST, httpSetDatetime);
    server.begin();
}

void serverHandle() {
    server.handleClient();
}