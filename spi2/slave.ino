#include <SPI.h>

volatile byte count = 0; // 수신 버퍼에 문자를 기록할 위치

void setup() {
  Serial.begin (9600);
  // MOSI, SCLK, SS는 입력으로 설정하지 않아도 된다.
  // MISO 역시 이 예에서는 사용하지 않으므로 생략할 수 있다.
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  // 마스터의 전송 속도에 맞추어 통신 속도를 설정
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  // SPI 통신을 위한 레지스터 설정
  // SPCR : SPI Control Register
  SPCR |= (1 << SPE); // SPE : SPI Enable
  SPCR &= ~(1 << MSTR); // MSTR : Master Slave Select
  SPCR |= (1 << SPIE); // SPIE : SPI Interrupt Enable
}

// SPI 통신으로 데이터가 수신된 경우 자동 호출
ISR (SPI_STC_vect) {
  count++;
  union{ uint16_t val; struct{ uint8_t lsb; uint8_t msb; }; } out;
  out.val = count;

  SPDR = out.msb;
  while(!(SPSR & _BV(SPIF)));
  SPDR = out.lsb;
  while(!(SPSR & _BV(SPIF)));
}

void loop() {
}
