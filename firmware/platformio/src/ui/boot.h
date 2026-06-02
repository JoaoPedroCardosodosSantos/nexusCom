#ifndef BOOT_H
#define BOOT_H

#include <Arduino.h>

void drawBootScreen();

void updateBootProgress(
    uint8_t percentual,
    const char* texto
);

void bootAnimation();

#endif