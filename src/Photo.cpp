#include <Arduino.h>
#include "ConfigWTF.h"
#include "Photo.h"

int getBrightness() {
    return analogRead(PHOTO);
}