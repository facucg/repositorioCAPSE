#include "sapi.h"        // <= Biblioteca sAPI

uint8_t leerAdc(uint16_t adc);

int main( void )
{
    boardConfig();
    servoInit(0, SERVO_ENABLE);
    servoInit(SERVO0, SERVO_ENABLE_OUTPUT);
    adcInit(ADC_ENABLE);
    uartInit(UART_USB, 115200);

    uint16_t valorAdc=0;
    uint8_t angulo;

    while( TRUE ) {
        valorAdc = adcRead(CH3);
        angulo= leerAdc(valorAdc);
        printf("%d\n", angulo);
        delay(50);

    }
    return 0;
}

uint8_t leerAdc(uint16_t adc)
{
    uint8_t ang;
    ang = (adc * 180)/1024;
    servoWrite(SERVO0, ang);
    return ang;
}


