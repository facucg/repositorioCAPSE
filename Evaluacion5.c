#include "sapi.h"        // <= Biblioteca sAPI

typedef struct {
   uint16_t x;
   uint16_t y;
} coord_t;

coord_t leerPosicion();

int main( void )
{
   boardConfig();
   adcConfig(ADC_ENABLE);
   uartInit(UART_USB, 115200);
   
   coord_t vector;
   int numero;

   while( TRUE ) {
      vector= leerPosicion();
      printf("%d, %d\r\n", vector.x, vector.y);
      delay(500);
   }


   return 0;
}

coord_t leerPosicion(){
   
   coord_t posicion;
    
   posicion.x= adcRead(CH1);
   posicion.y= adcRead(CH2);
   return posicion;
}
