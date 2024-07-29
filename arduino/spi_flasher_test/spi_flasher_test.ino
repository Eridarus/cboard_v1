#include <SPI.h>
#define CS_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13
#define NS_200_CYCLES 4
#define US_1200_CYCLES 13400
#define CRESET_B_PIN 9
#define CDONE_PIN 8

// DATA TRANSMITTED TO ICE40 ON FALLING EDGE OF SCK - USE SPI MODE 0
// STEPS
// 1: POWER UP ICE40 OR TOGGLE RESET LOW FOR 200ns THEN TOGGLE BACK TO HIGH WITH SPI_SS=0 DON'T SEND CLOCKS
// 2: WAIT >= 1200 US FOR HOUSEKEEPING, TOGGLE SPI_SS HIGH, SEND 8 DUMMY CLOCKS (FALLING EDGES), SET SPI_SS LOW
// 3: Keep sending SPI_SCKs
// 4: Start sending the bitmap image on SPI_SDI
// 5: Send 100 dummy clocks. CDONE should go high
// 6: If CDONE=1. configuration passes. otherwise, fails
// 7: Send 49 more dummy clocks to get SPI signals to be GPIOs

uint8_t sck_en = 0;

void delayClocks( uint16_t clocks ){
  do
  {
    __asm( "nop" );
  }
  while ( --clocks );
}

void spi_setup(uint8_t sck, uint8_t mosi, uint8_t miso, uint8_t cs){
  pinMode(sck, OUTPUT);
  pinMode(mosi, INPUT);
  pinMode(miso, OUTPUT);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  digitalWrite(mosi, LOW);
  digitalWrite(sck, LOW);
}

void set_creset(uint8_t value){
  if(value==HIGH){
    digitalWrite(CRESET_B_PIN, LOW);
  }else{
    digitalWrite(CRESET_B_PIN, HIGH);
  }
}

void setup() {
  // put your setup code here, to run once:
  spi_setup(SCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
  pinMode(CRESET_B_PIN, OUTPUT);
  pinMode(CDONE_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
