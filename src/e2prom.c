#include "e2prom.h"

dataBase_t dataBase = {0};

bool dataBase_wasFirst = false;
bool dataBase_wasFirstTime(void){
    return dataBase_wasFirst;
}

void dataBase_load(void){
    eeprom_read_block(&dataBase, 0, sizeof(dataBase_t));
}
void dataBase_update(void){
    eeprom_write_block(&dataBase, 0, sizeof(dataBase_t));
}

void dataBase_init(void){
    dataBase_load();
    if(dataBase.key != DATA_BASE_KEY){
        //need initialize
        memset(&dataBase, 0, sizeof(dataBase_t));
        dataBase.key = DATA_BASE_KEY;
        dataBase_update();
        dataBase_wasFirst = true;
    }
    else{
        //dataBase ready
        dataBase_wasFirst = false;
    }
}
void dataBase_set_max(dataBaseSec_t section, uint16_t max){
    dataBase.setUp[section].max = max;
    dataBase_update();
}
void dataBase_set_min(dataBaseSec_t section, uint16_t min){
    dataBase.setUp[section].min = min;
    dataBase_update();
}
void dataBase_set_alarm(dataBaseSec_t section, uint8_t hour, uint8_t min, uint8_t sec){
    dataBase.setUp[section].alarm.hour = hour;
    dataBase.setUp[section].alarm.min  = min;
    dataBase.setUp[section].alarm.sec  = sec;
    dataBase_update();
}
void dataBase_get_max(dataBaseSec_t section, uint16_t *max){
    *max = dataBase.setUp[section].max;
}
void dataBase_get_min(dataBaseSec_t section, uint16_t *min){
    *min = dataBase.setUp[section].min;
}
void dataBase_get_alarm(dataBaseSec_t section, uint8_t *hour, uint8_t *min, uint8_t *sec){
    *hour = dataBase.setUp[section].alarm.hour;
    *min  = dataBase.setUp[section].alarm.min;
    *sec  = dataBase.setUp[section].alarm.sec;
}
