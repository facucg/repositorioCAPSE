#include "sapi.h"        // <= Biblioteca sAPI
#include "string.h"

#define COMMON_CATHODE
//#define COMMON_ANODE

#ifdef COMMON_CATHODE
#define DIGIT_ON       0
#define DIGIT_OFF      1
#define PIN_VALUE_ON   1
#define PIN_VALUE_OFF  0
#endif

#ifdef COMMON_ANODE
#define DIGIT_ON       1
#define DIGIT_OFF      0
#define PIN_VALUE_ON   0
#define PIN_VALUE_OFF  1
#endif

#define TIEMPO_ON 500
#define DISPLAY_OFF 25
#define TECLADO_SCAN 40
#define TECLADO_MOSTRAR 100

const uint8_t display7SegmentOut[26] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9

    0b01011111, // a
    0b01111100, // b
    0b01011000, // c
    0b01011110, // d
    0b01111011, // e
    0b01110001, // f

    0b01110111, // A
    0b00111001, // C
    0b01111001, // E
    0b01110110, // H
    0b00011110, // J
    0b00111000, // L
    0b01110011, // P
    0b00111110, // U

    0b10000000, // .

    0b00000000  // display off
};

gpioMap_t valor[] = {
    GPIO2,
    GPIO3,
    GPIO6,
    GPIO5,
    GPIO4,
    GPIO1,
    GPIO0,
    GPIO7
};

gpioMap_t digito[] = {
    LCD1, // D4
    LCD2, // D3
    LCD3, // D2
    LCD4  // D1
};

uint8_t TecladoPinesFilas[4] = {
    RS232_TXD,
    CAN_RD,
    CAN_TD,
    T_COL1,
};

uint8_t TecladoPinesColumnas[4] = {
    T_FIL0,
    T_FIL3,
    T_FIL2,
    T_COL0,
};

int8_t indiceACaracter[] = {
    '1', '2', '3', '/',  // 1/2 Enter
    '4', '5', '6', '+' ,
    '7', '8', '9', '-' ,
    '?', '0', '#', '*' ,  // 8 = Retroceso
};



void displayMostrarDigito( uint8_t val, uint8_t dig );
void displayRefresh( void );
void displayMostrar( uint16_t val );
uint8_t leerAngulo(void);

void tecladoInit( void );
int8_t escanearTeclado( void );

char bufNumeros[80];
char bufAuxiliar[80];
int indice = 0;

int numero1 =0;
char operando;

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    // ---------- CONFIGURACIONES ------------------------------

    // Inicializar y configurar la plataforma
    boardConfig();
    servoInit(0, SERVO_ENABLE);
    servoInit(SERVO0, SERVO_ENABLE_OUTPUT);
    adcInit(ADC_ENABLE);

    uint32_t i = 0;
    uint8_t angulo=0;

    int8_t teclaAnt = -1;
    int8_t tecla = -1;
    uint8_t numAuxiliar= 0;

    for( i=0; i<8; i++ ) {
        gpioInit( valor[i], GPIO_OUTPUT );
    }

    for( i=0; i<4; i++ ) {
        gpioInit( digito[i], GPIO_OUTPUT );
    }

    gpioWrite( digito[0], DIGIT_OFF );
    gpioWrite( digito[1], DIGIT_OFF );
    gpioWrite( digito[2], DIGIT_OFF );
    gpioWrite( digito[3], DIGIT_OFF );

    for( i=0; i<8; i++ ) {
        gpioWrite( valor[i], PIN_VALUE_OFF );
    }

    delay_t delayRefresh;
    delayInit( &delayRefresh, 5 );

    delay_t delayMostrarValores;
    delayInit( &delayMostrarValores, 100 );

    tecladoInit();
    delay_t escaneoTeclado;
    delayInit( &escaneoTeclado, TECLADO_SCAN );

    delay_t mostrarTeclado;
    delayInit( &mostrarTeclado, TECLADO_MOSTRAR );

    tecla = teclaAnt = -1;
    i=0;

    // ---------- REPETIR POR SIEMPRE --------------------------
    while( TRUE ) {

        if( delayRead(&delayRefresh) ) {
            displayRefresh();
        }

        if( delayRead(&delayMostrarValores) ) {
            angulo = numero1;
            displayMostrar(angulo);
        }

        if(delayRead(&escaneoTeclado)) {
            tecla = escanearTeclado();
            if (teclaAnt != tecla) {
                switch (tecla) {
                case -1:
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    bufAuxiliar[indice] = tecla;
                    indice++;
                    bufAuxiliar[indice] = 0;
                    printf("bufNumeros. %s\r\n", bufAuxiliar);
                    sscanf(bufAuxiliar, "%d", &numAuxiliar);
                    if(numAuxiliar<=180) {
                        numero1 = numAuxiliar;
                        strcpy(bufNumeros, bufAuxiliar);
                    } else {
                        strcpy(bufAuxiliar, bufNumeros);
                    }
                    printf("Convirtiendo numero1 a entero %d\r\n", numero1);
                    break;
                case '*':
                    if(angulo<=180) {
                        servoWrite(SERVO0, angulo);
                        for(i=0; i<80; i++) {
                            ;
                            bufAuxiliar[i] = '0';
                        }

                    }
                    break;
                }
            }
            teclaAnt = tecla;
        }

    }
    return 0;
}


void displayMostrarDigito( uint8_t val, uint8_t dig )
{
    uint8_t j = 0;
    gpioWrite( digito[dig], DIGIT_ON );
    for( j=0; j<8; j++ ) {
        if( display7SegmentOut[val] & (1<<j) ) {
            gpioWrite( valor[j], PIN_VALUE_ON );
        } else {
            gpioWrite( valor[j], PIN_VALUE_OFF );
        }
    }
}


uint8_t digitosAMostrar[4] = { DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF };

void displayRefresh( void )
{
    static uint8_t digitoAMostrar = 0;

    uint8_t i = 0;
    for( i=0; i<4; i++ ) {
        gpioWrite( digito[i], DIGIT_OFF );
    }

    if(digitoAMostrar <= 3) {
        displayMostrarDigito( digitosAMostrar[digitoAMostrar], digitoAMostrar );
        digitoAMostrar++;
    } else {
        digitoAMostrar=0;
    }
}

void displayMostrar( uint16_t val )
{
    if( val <= 9999 ) {
        digitosAMostrar[3] = val/1000;      // unidad de mil
        digitosAMostrar[2] = (val%1000)/100;      // centena
        digitosAMostrar[1] = (val%100)/10; // decena
        digitosAMostrar[0] = val%10;       // unidad
    }
    if( val <= 999 ) {
        digitosAMostrar[3] = DISPLAY_OFF;  // centena
    }
    if( val <= 99 ) {
        digitosAMostrar[2] = DISPLAY_OFF;  // centena
    }
    if( val <= 9 ) {
        digitosAMostrar[1] = DISPLAY_OFF;  // decena
    }
}


void tecladoInit( void )
{
    uint8_t pin = 0;
    for( pin=0; pin<4; pin++ ) {
        // Configuro las filas como salida
        gpioInit( TecladoPinesFilas[pin], GPIO_OUTPUT );
        gpioWrite( TecladoPinesFilas[pin], ON );
        // Configuro las columnas como entradas, con resistencias de pull-up internas
        gpioInit( TecladoPinesColumnas[pin], GPIO_INPUT_PULLUP );
    }
}

int8_t escanearTeclado( void ) // devuelve el indice de tecla [0,15] o -1 si no hay tecla presionada
{
    int8_t f = 0;
    int8_t i = 0;
    int8_t c = 0;

    // Escanear todas las filas
    for( f=0; f<4; f++ ) {

        // Prendo todas las filas (el estado normal por las resistencias de pull-up)
        for( i=0; i<4; i++ ) {
            gpioWrite( TecladoPinesFilas[i], ON );
        }

        // Apago la fila que quiero escanear
        gpioWrite( TecladoPinesFilas[f], OFF );

        // Chequeo si alguna columna lee el OFF de mi fila actual
        for( c=0; c<4; c++ ) {
            // Chequeo que la columna actual este en OFF (hay una en OFF si se presiona algun boton)
            if( gpioRead( TecladoPinesColumnas[c] ) == OFF ) {
                return indiceACaracter[4*f + c];
            }
        }
    }
    return -1;
}


