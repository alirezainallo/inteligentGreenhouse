#ifndef _KEY_H
#define _KEY_H

#include "main.h"
#include "relay.h"

#define keyWatering_PORT PORTC
#define keyWatering_DDR  DDRC
#define keyWatering_PIN  PINC
#define keyWatering_pin  PC2

#define keyFan_PORT PORTC
#define keyFan_DDR  DDRC
#define keyFan_PIN  PINC
#define keyFan_pin  PC3

#define keyHeater_PORT PORTD
#define keyHeater_DDR  DDRD
#define keyHeater_PIN  PIND
#define keyHeater_pin  PD2

#define keyLight_PORT PORTA
#define keyLight_DDR  DDRA
#define keyLight_PIN  PINA
#define keyLight_pin  PA7

#define keyFertilizing_PORT PORTB
#define keyFertilizing_DDR  DDRB
#define keyFertilizing_PIN  PINB
#define keyFertilizing_pin  PB3

typedef void (*key_onPressed)(bool state);

void keys_init(void);
void keys_loop(void);

#endif //_KEY_H

