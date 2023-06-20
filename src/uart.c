#include "uart.h"


// ------------------------>> prototypes <<--------------------------------

char* rxGetLine(void);
void txSendData(void);
extern void GSM_lineProcess(char *line, size_t len);

// ------------------------>> loop <<--------------------------------
// char display[17] = {0};

void uart_loop(void){
   if(rx_lineReady){
      rx_lineReady = false;

      //process line ...
      GSM_lineProcess(rxGetLine(), rx_len);
   }
}

// ------------------------>> RX <<--------------------------------

extern bool smsSignReceived;
extern bool forceNeedCrLf;
char rx_buffer[2][RX_BUFFER_SIZE] = {0};
bool rx_curr_buffer = false;
size_t rx_ind = 0;
size_t rx_len = 0;
bool rx_lineReady = 0;
bool rx_buff_overflow = 0;
ISR(USART_RXC_vect)
{
cli();
char data;
// char status;
   // status = UCSRA;
   UCSRA |= (1 << RXC);
   data = UDR;
   rx_buffer[rx_curr_buffer][rx_ind++] = data;
   if(rx_ind >= RX_BUFFER_SIZE){
      rx_ind = 0;
      rx_buff_overflow = true;
   }
   else if(data == '\n'){
      if(rx_buffer[rx_curr_buffer][rx_ind - 1] == '\r'){
         --rx_ind;
         forceNeedCrLf = false;
      }
      rx_buffer[rx_curr_buffer][--rx_ind] = 0;
      rx_len = rx_ind;

      rx_ind = 0;
      rx_curr_buffer = !rx_curr_buffer;
      rx_lineReady = true;
   }
   else if((data == '>') && (!smsSignReceived)){
      smsSignReceived = true;
      rx_ind = 0;
   }

   /*if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0){
      
      // rxUart_debug = data;
   }*/
sei();
}

char* rxGetLine(void){
   return rx_buffer[!rx_curr_buffer];
}

// ------------------------>> TX <<--------------------------------

char tx_buffer[TX_BUFFER_SIZE];

// USART Transmitter interrupt service routine
ISR(USART_TXC_vect)
{  
   cli();
   UCSRA |= (1 << TXC);
   txSendData();
   sei();
}

static size_t tx_len = 0;
static size_t tx_ind = 0;
void putChar(char c){
   UDR = c;
}
void txSendData(void){
   if(tx_ind < tx_len){
      putChar(tx_buffer[tx_ind++]);
   }
   else{
      tx_ind = 0;
   }
}
void txSendDataLen(char* data, size_t len){
   tx_len = strlen(data);
   tx_ind = 0;
   memcpy(tx_buffer, data, len);

   txSendData();
}
void uart_init(void){
//   DDRD  &= ~(1 << PD0);
//   PORTD &= ~(1 << PD0);
//   DDRD  |=  (1 << PD1);
  
  
  // UDR reg for send and receive
  // UCSRA for flag
  //    UDRE: USART Data Register Empty
  UCSRA  = 0;
  // UCSRB
  //    RXCIE: RX Complete Interrupt Enable
  //    TXCIE: TX Complete Interrupt Enable
  //    RXEN: Receiver Enable
  //    TXEN: Receiver Enable
  UCSRB = (1 << RXCIE)|(1 << TXCIE)|(1 << RXEN)|(1 << TXEN);
  // UCSRC 
  //    URSEL: Register Select //1:when read//1:when we write
  //    UMSEL: USART Mode Select //0:UMSEL: USART Mode Select
  //    USBS: Stop Bit Select //1:2bit stop bit
  //    UCSZ0:1/UCSZ1:1 //for 8bit data
  uint8_t UCSRC_tmp = (1 << URSEL)|(1 << UCSZ0)|(1 << UCSZ1);//|(1 << USBS)
  UCSRC_tmp &= ~(1 << UMSEL);
  UCSRC = UCSRC_tmp;
  // UBRRL and UBRRH
  //    URSEL: Register Select //0:when read//0:when we write
  //    Bit 14:12: must be zero when we write reg
  //    UBRR11:0: USART Baud Rate Register : 51 for (U2X = 0)
//   uint8_t UBRRH_tmp = (1 << URSEL)|(1 << 4)|(1 << 5)|(1 << 6)|(0x0F);
  UBRRH = 0x00;
  UBRRL = 51;//UBRRL = 0x67;
  
//   UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<PE) | (1<<U2X) | (0<<MPCM);
//   UCSRB=(1<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
//   UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
//   UBRRH=0x00;
//   UBRRL=0x67;
}
/*
// char uart_send_buff[50];
// size_t uart_send_ind = 0;
// uint8_t rxCom = 0;
// void uart_send_ch(char data){
//   UDR = data;
// }
// void uart_send_data(const char*data, size_t len){
//   memcpy(uart_send_buff, data, len);
// }
// ISR(USART_RXC_vect){

// }
// ISR(USART_TXC_vect){
//   rxCom = 1;
// }
// void putChar(char c)
// {
//   // cli();
//   if (((UCSRA & (1<<UDRE))==0))
//   UDR=c;
//   // sei();
// }*/
