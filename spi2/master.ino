#include <SPI.h>

int SS_arduino_uno = 53;
int SS_EEPROM = 42;

void setup() {
  pinMode(SS_arduino_uno, OUTPUT);
  pinMode(SS_EEPROM, OUTPUT);
  digitalWrite(SS_arduino_uno, HIGH); // 슬레이브가 선택되지 않은 상태
  digitalWrite(SS_EEPROM, HIGH);
  SPI.begin(); // SPI 통신 초기화
  // 안정적인 전송을 위해 분주비를 높여 전송 속도를 낮춤
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(SS_arduino_uno, LOW); // 슬레이브 선택
  // 마스터에서 1바이트의 의미 없는 데이터를 전송함으로써
  // 슬레이브로부터 1바이트의 데이터를 수신한다.
  byte data = SPI.transfer16(0);
  Serial.println(int(data)); // 데이터 출력
  
  delay(1000);
}
