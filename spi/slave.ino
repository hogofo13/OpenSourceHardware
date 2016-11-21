typedef union{ int a; byte binary[2]; } binaryInt;

#include <SPI.h>

char buf[100]; // 수신된 문자 저장을 위한 버퍼
int recInt;
int count=1;
binaryInt tempInt;

// pos와 process_it은 인터럽트 처리 루틴에서 값을 바꾸는 변수이므로
// volatile 선언을 통해 매번 값을 참조하도록 설정해야 한다.
volatile byte pos = 0; // 수신 버퍼에 문자를 기록할 위치
volatile boolean process_it = false; // 수신 데이터 종료 알림

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
  tempInt.binary[count++]=byte(SPDR);
  if(count==2){
    process_it = true;
    count=0;
  }
}

void loop() {
  if (process_it) {
    Serial.println(int(tempInt.a));
    pos = 0;
    process_it = false;
  }
}
