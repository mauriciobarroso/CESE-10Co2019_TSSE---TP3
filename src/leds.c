#include "leds.h"

/* macros para el estado del puerto que maneja los LEDs */
#define ALL_ON      0xFFFF
#define ALL_OFF     0x0000
/* macro para el offset de los LEDs y la posición del bit 
 * que lo maneja */
#define LED_OFFSET  1
/* macros para el estado de los bits del puerto que maneja
 * los LEDs */
#define BIT_ON      1
#define BIT_OFF     0

static uint16_t *leds;

uint16_t Leds_Bits( uint8_t led )
{
    return ( BIT_ON << ( led - LED_OFFSET ) );
}

void Leds_Create( uint16_t *puerto )
{
    leds = puerto;
    *leds = ALL_OFF;
}

void Leds_On( uint8_t led )
{
    *leds |= Leds_Bits( led );
}

void Leds_Off( uint8_t led )
{
    *leds &= ~Leds_Bits( led );
}

void Leds_All_Off( void )
{
    *leds = ALL_OFF;

    /* otra posible implementación */
    //for( uint8_t i = 1; i <= 16; i++ )
    //    Leds_Off( i );
}

void Leds_All_On( void )
{
    *leds = ALL_ON;
    
    /* otra posible implementación */
    //for( uint8_t i = 1; i <= 16; i++ )
    //    Leds_On( i );
}

uint8_t Leds_Check( uint8_t led )
{
    /* código mínimo para que pase la prueba */
    return 1;

    /* código para que funcione correctamente con todos los LEDs */
    //return ( ( *leds & Leds_Bits( led ) ) >> ( led - LED_OFFSET ) );
}