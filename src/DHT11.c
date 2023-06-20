#include "DHT11.h"

#define DHT_TIMEOUT 200

extern menuStat_t get_menuStat(void);

static uint32_t ht11_ms  = 200;



#if DHT_TYPE == DHT_DHT22
uint16_t temperature_int = 0;
uint16_t humidity_int    = 0;
#elif DHT_TYPE == DHT_DHT11
int8_t temperature_int = 0;
int8_t humidity_int    = 0;

#endif

static uint32_t nextTick = 0;
static uint32_t currTick = 0;
void dht11_init(uint32_t ms){
	ht11_ms = ms;
}
void dht11_loop(void){
  currTick = get_currentTick();
//   if(currTick + ht11_ms > )
  if(nextTick < currTick){
	static uint32_t tmp = 0;
	tmp = currTick + ht11_ms;
	if(tmp < UINT16_MAX){
    	nextTick = tmp;
	}
	else{
    	nextTick = tmp - UINT16_MAX;
	}
    
	dht_GetTempUtil(&temperature_int, &humidity_int);

	if(get_menuStat() == menu_mainPage_Stat){
		LCD_String_xy(0, 2, "  ");
		LCD_String_xy(0, 11, "  ");
		sprintf(display_LCD, "%d", temperature_int);
		LCD_String_xy(0, 2, display_LCD);
		sprintf(display_LCD, "%d", humidity_int);
		LCD_String_xy(0, 11, display_LCD);
	}
  }
}


//main function that communicates with DHT sensor 
#if DHT_TYPE == DHT_DHT22
int8_t dht_GetTemp(uint16_t *temperature, uint16_t *humidity) {
#elif DHT_TYPE == DHT_DHT11
int8_t dht_GetTemp(int8_t *temperature, int8_t *humidity) {
#endif
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	//prepare correct port and pin of DHT sensor
	DHT_DDR |= (1 << DHT_INPUTPIN); //output
	DHT_PORT |= (1 << DHT_INPUTPIN); //high
	_delay_ms(100);

	//begin send request
	DHT_PORT &= ~(1 << DHT_INPUTPIN); //low
	#if DHT_TYPE == DHT_DHT11
	_delay_ms(18);
	#elif DHT_TYPE == DHT_DHT22
	_delay_us(500);
	#endif
	DHT_PORT |= (1 << DHT_INPUTPIN); //high
	DHT_DDR &= ~(1 << DHT_INPUTPIN); //input
	_delay_us(40);

	//check first start condition
	if((DHT_PIN & (1<<DHT_INPUTPIN))) {
		return -1;
	}
	_delay_us(80);
	
	//check second start condition
	if(!(DHT_PIN & (1<<DHT_INPUTPIN))) {
		return -1;
	}
	_delay_us(80);

	//read-in data
	uint16_t timeoutcounter = 0;
	for (j=0; j<5; j++) { //for each byte (5 total)
		uint8_t result = 0;
		for(i=0; i<8; i++) {//for each bit in each byte (8 total)
			timeoutcounter = 0;
			while(!(DHT_PIN & (1<<DHT_INPUTPIN))) { //wait for an high input (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return -1;
				}
			}
			_delay_us(30);
			if(DHT_PIN & (1<<DHT_INPUTPIN))
				result |= (1<<(7-i));
			timeoutcounter = 0;
			while(DHT_PIN & (1<<DHT_INPUTPIN)) {
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return -1;
				}
			}
		}
		bits[j] = result;
	}

	//reset port
	DHT_DDR |= (1<<DHT_INPUTPIN); //output
	DHT_PORT |= (1<<DHT_INPUTPIN); //low
	_delay_ms(100);

	//compare checksum
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) {
		//return temperature and humidity
		#if DHT_TYPE == DHT_DHT22
		*temperature = bits[2]<<8 | bits[3];
		*humidity = bits[0]<<8 | bits[1];
		
		#elif DHT_TYPE == DHT_DHT11
		*temperature = bits[2];
		*humidity = bits[0];
		#endif
		
		return 0;
	}

	return -1;
}

//function that calls data function read-in
#if DHT_TYPE == DHT_DHT22
int8_t dht_GetTempUtil(uint16_t *temperature, uint16_t *humidity)
#elif DHT_TYPE == DHT_DHT11
int8_t dht_GetTempUtil(int8_t *temperature, int8_t *humidity)
#endif
{
	return dht_GetTemp(temperature, humidity);
}
