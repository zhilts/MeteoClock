#include "RTClib.h"

RTC_DS3231 rtc;

void setupRTC() {
#if (DEBUG == 1)
    setLED(2);
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
}