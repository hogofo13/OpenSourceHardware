#include <SPI.h>

int SS_arduino_uno = 53;
int SS_EEPROM = 42;

void setup (void) {
  pinMode(SS_arduino_uno, OUTPUT);
  pinMode(SS_EEPROM, OUTPUT);
  digitalWrite(SS_arduino_uno, HIGH); // 슬레이브가 선택되지 않은 상태
  digitalWrite(SS_EEPROM, HIGH);
  SPI.begin( ); // SPI 통신 초기화
  // 안정적인 전송을 위해 분주비를 높여 전송 속도를 낮춤
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop (void) {
  
  int data = 1024;
  digitalWrite(SS_arduino_uno, LOW); // 슬레이브 선택
  SPI.transfer16(data);
  digitalWrite(SS_arduino_uno, HIGH); // 슬레이브 선택 해제
  delay(1000);
}
