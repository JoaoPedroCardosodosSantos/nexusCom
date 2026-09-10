#include "pcf8574.h"

#include "../config/pinos.h"

PCF8574::PCF8574(
    uint8_t addr
)
{
    endereco = addr;
}

void PCF8574::iniciar()
{
    Wire.begin(
        I2C_SDA,
        I2C_SCL
    );

    escrever(0xFF);
}

void PCF8574::escrever(
    uint8_t valor
)
{
    Wire.beginTransmission(
        endereco
    );

    Wire.write(
        valor
    );

    Wire.endTransmission();
}

uint8_t PCF8574::ler()
{
    Wire.requestFrom(
        endereco,
        (uint8_t)1
    );

    if(
        Wire.available()
    )
    {
        return Wire.read();
    }

    return 0xFF;
}