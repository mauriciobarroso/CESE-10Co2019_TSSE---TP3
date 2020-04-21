#include "unity.h"
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

/* declaración del puerto virtual que maneja los LEDs */
static uint16_t ledsVirtuales;

void setUp( void )
{
    Leds_Create( &ledsVirtuales );
}

void tearDown( void )
{

}

/* Después de la inicialización todos los LEDs deben quedar apagados */
void test_LedsOffAfterCreate( void )
{
    uint16_t ledsVirtuales = ALL_ON;
    Leds_Create( &ledsVirtuales );
    TEST_ASSERT_EQUAL_HEX16( 0, ledsVirtuales );
}

/* Se puede prender un LED individual */
void test_IndividualLedOn( void )
{
    const uint8_t led = 1;
    Leds_On( led );
    TEST_ASSERT_EQUAL( BIT_ON << ( led - 1 ), ledsVirtuales );
}

/* Se puede apagar un LED individual */
void test_IndividualLedOff( void )
{
    const uint8_t led = 1;
    Leds_On( led );
    Leds_Off( led );
    TEST_ASSERT_EQUAL( BIT_OFF << ( led - LED_OFFSET ), ledsVirtuales );
}

/* Se pueden prender y apagar múltiples LEDs */
void test_MultipleLedOnAndOff( void )
{
    const uint8_t led1 = 9;
    const uint8_t led2 = 2;

    Leds_On( led1 );
    Leds_On( led2 );
    Leds_Off( led1 );
    TEST_ASSERT_EQUAL( BIT_ON << ( led2 - LED_OFFSET ), ledsVirtuales );
}

/* Se pueden apagar todos los LEDs de una vez */
void test_OffAllLeds( void )
{
    /* se encienden 3 LEDs para verificar que se apagan */
    const uint8_t led1 = 2;
    const uint8_t led2 = 5;
    const uint8_t led3 = 10;
    Leds_On( led1 );
    Leds_On( led2 );
    Leds_On( led3 );
    /* se apagan todos los LEDs */
    Leds_All_Off();
    TEST_ASSERT_EQUAL_HEX16( ALL_OFF, ledsVirtuales );
}

/* Se pueden prender todos los LEDs de una vez */
void test_OnAllLeds( void )
{
    /* cuando se inicilizan los LEDs todos están apagados */
    Leds_All_On();
    TEST_ASSERT_EQUAL_HEX16( ALL_ON, ledsVirtuales );
}

/* Se puede consultar el estado de un LED */
void test_CheckLedStatus( void )
{
    uint8_t ledStatus;
    const uint8_t led = 16;
    /* se prende el LED 16 para verificar que su estado es 1 */
    Leds_On( led );
    ledStatus = Leds_Check( led );
    TEST_ASSERT_EQUAL( BIT_ON, ledStatus );
    /* se apaga el LED 16 para verificar que su estado es 0 */
    Leds_Off( led );
    ledStatus = Leds_Check( led );
    TEST_ASSERT_EQUAL( BIT_OFF, ledStatus );
}