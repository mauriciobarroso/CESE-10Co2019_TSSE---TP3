#include <stdint.h>

void Leds_Create( uint16_t *puerto );
void Leds_On( uint8_t led );
void Leds_Off( uint8_t led );
void Leds_All_Off( void );
void Leds_All_On( void );
uint8_t Leds_Check( uint8_t led);