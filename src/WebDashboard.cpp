#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

#include "Log.h"
#include "Led.h"
#include "Display1.h"

WebServer server(80);

const String DASHBOARD = "<!DOCTYPE html>\n"
                         "<html lang=\"en\">\n"
                         "<head>\n"
                         "    <meta charset=\"UTF-8\">\n"
                         "    <title>Meteo clock setup</title>\n"
                         "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                         "    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js\"></script>\n"
                         "</head>\n"
                         "<body>\n"
                         "<form action=\"/update\" method=\"POST\">\n"
                         "    <p>\n"
                         "        <label for=\"LedValue\">Led value:</label>\n"
                         "        <select id=\"LedValue\" name=\"ledValue\">\n"
                         "            <option value=\"0\">Off</option>\n"
                         "            <option value=\"1\">Red</option>\n"
                         "            <option value=\"2\">Green</option>\n"
                         "            <option value=\"3\">Blue</option>\n"
                         "            <option value=\"4\">Yellow</option>\n"
                         "        </select>\n"
                         "    </p>\n"
                         "    <p>\n"
                         "        <label for=\"LcdText\">LCD Text:</label>\n"
                         "        <input id=\"LcdText\" name=\"lcdText\"/>\n"
                         "    </p>\n"
                         "    <button type=\"submit\">Save</button>\n"
                         "</form>\n"
                         "<script>\n"
                         "    const {ledValue} = currentData;\n"
                         "    $(`#LedValue option[value=\"${ledValue}\"]`).prop('selected', true);\n"
                         "</script>\n"
                         "</body>\n"
                         "</html>";


void httpDashboard() {
    DynamicJsonDocument jsonDoc(256);

    jsonDoc["ledValue"] = rgbGetValue();

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    String html = String(DASHBOARD);
    html.replace("currentData;", jsonString + ";");
    server.send(200, "text/html", html);
}

void httpUpdate() {
    int ledValue = server.arg("ledValue").toInt();
    log("ledValue: " + String(ledValue));
    rgbSetValue(ledValue);

    String lcdText = server.arg("lcdText");
    if (lcdText.length() > 0) {
        lcdSetCursor(0, 3);
        lcdPrint(lcdText);
    }

    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "go back");
}

void setupServer() {
    MDNS.addService("http", "tcp", 80);
    server.on("/", httpDashboard);
    server.on("/update", HTTP_POST, httpUpdate);
    server.begin();
}

void serverHandle() {
    server.handleClient();
}