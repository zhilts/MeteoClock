#include "Config.h"
#include "Time.h"

#include "RTClib.h"

#include "Display.h"
#include "Log.h"
#include "Led.h"

RTC_DS3231 rtc;

void setupRTC() {
#if (DEBUG == 1)
    rgbSetValue(2);
    lcdSetCursor(0, 1);
    lcdPrint(F("RTC... "));
    log(F("RTC... "));
#endif
    bool status = rtc.begin();
#if (DEBUG == 1)
    if (status) {
        lcdPrint(F("OK"));
        log(F("OK"));
    } else {
        lcdPrint(F("ERROR"));
        log(F("ERROR"));
    }
#endif
    if (RESET_CLOCK || rtc.lostPower())
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

DateTime getNow() {
    return rtc.now();
}
