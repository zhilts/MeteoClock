#ifndef METEO_CLOCK_RTCTIME_H
#define METEO_CLOCK_RTCTIME_H

#include <RTClib.h>

void setupRTC();
DateTime getNow();
String getNowISO();;

#endif //METEO_CLOCK_RTCTIME_H
