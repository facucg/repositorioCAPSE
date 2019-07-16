#include "sapi.h"

void retardo();


volatile char caracter = 0;
void leerCaracter(void * puntero){
    caracter = uartRxRead(UART_USB);
}

uint8_t i =0;
delay_t parpadeo;
delay_t botonRetardo;


int main( void )
{
    boardConfig();
    uartInit(UART_USB, 115200);
    uartCallbackSet( UART_USB, UART_RECEIVE, leerCaracter, 0 );
    uartInterrupt( UART_USB, true );
    

    delayInit(&parpadeo, 50);
    delayInit(&botonRetardo, 50);

    gpioWrite(LEDB, OFF);
    gpioWrite(LED1, OFF);
    gpioWrite(LED2, OFF);
    gpioWrite(LED3, OFF);

    while( TRUE ) {
        while(caracter) {
            switch (caracter) {
            case 'a':
                gpioWrite(LED1, OFF);
                gpioWrite(LED2, OFF);
                gpioWrite(LED3, OFF);
                if(delayRead(&botonRetardo)) {
                    retardo();
                }
                if(delayRead(&parpadeo)) {
                    gpioToggle(LEDB);
                    //uartReadByte(UART_USB, &caracter);
                printf("aaaaa\r\n");
                }
                printf("%c", caracter);
                //leerCaracter();
                break;

            case '1':
                gpioWrite(LEDB, OFF);
                gpioWrite(LED2, OFF);
                gpioWrite(LED3, OFF);
                if(delayRead(&botonRetardo)) {
                    retardo();
                }
                if(delayRead(&parpadeo)) {
                    gpioToggle(LED1);
                    //uartReadByte(UART_USB, &caracter);
                }
                //leerCaracter();
                break;

            case '2':
                gpioWrite(LEDB, OFF);
                gpioWrite(LED1, OFF);
                gpioWrite(LED3, OFF);
                if(delayRead(&botonRetardo)) {
                    retardo();
                }
                if(delayRead(&parpadeo)) {
                    gpioToggle(LED2);
                    //uartReadByte(UART_USB, &caracter);
                }
                //leerCaracter();
                break;

            case '3':
                gpioWrite(LEDB, OFF);
                gpioWrite(LED1, OFF);
                gpioWrite(LED2, OFF);
                if(delayRead(&botonRetardo)) {
                    retardo();
                }
                if(delayRead(&parpadeo)) {
                    gpioToggle(LED3);
                    //uartReadByte(UART_USB, &caracter);
                }
                //leerCaracter();
                break;
            }
        }
    }
    return 0;
}



void retardo(void)
{
    gpioMap_t tecla [4]= {TEC1, TEC2, TEC3, TEC4};
    uint32_t tiempo [4]= {50, 100, 200, 500};

    for(i=0; i<4; i++) {
        if(!gpioRead(tecla[i])) {
            delayWrite(&parpadeo, tiempo[i]);
        }
    }
}


