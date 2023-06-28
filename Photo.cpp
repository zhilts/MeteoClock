#include <Arduino.h>
#include "Config.h"
#include "Photo.h"

int getBrightness() {
    return analogRead(PHOTO);
}