#ifndef METEO_CLOCK_LOG_H
#define METEO_CLOCK_LOG_H

#include <Arduino.h>

void setupLog();

bool getHttpLogsEnabled();

void setHttpLogsEnabled(bool enabled);

String getHttpLogsHost();

void setHttpLogsHost(String host);

int getHttpLogsPort();

void setHttpLogsPort(int port);

void log(String message);

#endif //METEO_CLOCK_LOG_H
