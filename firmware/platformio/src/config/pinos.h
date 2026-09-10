#ifndef PINOS_H
#define PINOS_H

// ============================================================
// DISPLAY ST7789
// ============================================================

#define TFT_SCLK 18
#define TFT_MOSI 23
#define TFT_CS   33
#define TFT_DC   32
#define TFT_RST  25

// ============================================================
// I2C - PCF8574P
// ============================================================

#define I2C_SDA 21
#define I2C_SCL 22

#define PCF8574_ENDERECO 0x20

// ============================================================
// TECLADO 4x4 NO PCF8574
// ============================================================
//
// P0 - P3 = linhas
// P4 - P7 = colunas
//

#define TECLADO_LINHA1 0
#define TECLADO_LINHA2 1
#define TECLADO_LINHA3 2
#define TECLADO_LINHA4 3

#define TECLADO_COLUNA1 4
#define TECLADO_COLUNA2 5
#define TECLADO_COLUNA3 6
#define TECLADO_COLUNA4 7

#endif