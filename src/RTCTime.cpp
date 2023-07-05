#include "Config.h"
#include "RTCTime.h"

#include <RTClib.h>

#include "Display.h"
#include "Log.h"
#include "Led.h"

RTC_DS3231 rtc;

void setupRTC() {
#if (DEBUG == 1)
    rgbSetValue(2);
    lcdSetCursor(0, 1);
    lcdPrint(F("RTC... "));
#endif
    bool status = rtc.begin();
#if (DEBUG == 1)
    if (status) {
        lcdPrint(F("OK"));
        log(F("RTC: OK"));
    } else {
        lcdPrint(F("ERROR"));
        log(F("RTC: ERROR"));
    }
#endif
    if (RESET_CLOCK || rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        log("Adjust time: " + String(F(__DATE__)) + "-" + String(F(__TIME__)));
    }
}

DateTime getNow() {
    return rtc.now();
}

String dateTimeToISO8601(const DateTime &dt) {
    char isoStr[20];
    snprintf(isoStr, sizeof(isoStr), "%04d-%02d-%02dT%02d:%02d:%02d",
             dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
    return String(isoStr);
}

String getNowISO() {
    return dateTimeToISO8601(getNow());
}