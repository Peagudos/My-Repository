//#include "driver/ledc.h"
//#include <analogWrite.h>


#define PINUMBER 4 // can be 0:7, just needs to be unique
#define ONEmS_COUNTS ((1<<12)*50/1000) // 2^12 bit resolution * freq / 1000 (ms/s)
int target = 180;
int timer = 1000;

void setup() {
  //ledcSetup(1, 50, 12); channel 1, 50 Hz, 12-bit PWM resolution
  ledcAttach(4, 50, 12);
  Serial.begin(921600);
}

void loop() {
  int min_counts = .5*ONEmS_COUNTS; // conservative is 1mS for minimum
  int max_counts = 2.5*ONEmS_COUNTS; // conservative is 2mS for max duty cycle
  int target_counts = target * 2 * ONEmS_COUNTS / 180 + min_counts;
  for (int i=min_counts ; i <= target_counts ; i+=1) {
    ledcWrite(PINUMBER, i); // sweep servo forward
    delay(timer/(target_counts - min_counts)); // need this 20mS for 1 cycle at 50Hz
}
  for (int i=target_counts ; i >= min_counts ; i-=1) {
    ledcWrite(PINUMBER, i); // sweep servo back
    delay(timer/(target_counts - min_counts)); // need this 20mS for 1 cycle at 50Hz
  }
}

