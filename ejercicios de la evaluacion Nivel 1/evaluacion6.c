#include "sapi.h"        // <= Biblioteca sAPI

typedef struct {
    uint16_t x;
    uint16_t y;
} coord_t;

coord_t leerPosicion();
void imprimirPosicion(coord_t);

int main( void )
{
    boardConfig();
    adcConfig(ADC_ENABLE);
    uartInit(UART_USB, 115200);

    delay_t retardoImpresion;
    delayInit(&retardoImpresion, 1000);

    coord_t vector;
    int numero;

    while( TRUE ) {
        vector= leerPosicion();
        if(delayRead(&retardoImpresion)) {
            imprimirPosicion(vector);
        }
        // printf("%d, %d\r\n", vector.x, vector.y);
    }


    return 0;
}

coord_t leerPosicion()
{

    coord_t posicion;

    posicion.x= adcRead(CH1);
    posicion.y= adcRead(CH2);
    return posicion;
}

void imprimirPosicion(coord_t coordenada)
{
    printf("[%d, %d]\r\n", coordenada.x, coordenada.y);
}
