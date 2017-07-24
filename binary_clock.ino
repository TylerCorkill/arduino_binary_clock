const long minInterval = 60000;
//const long minInterval = 1000;
const long hourInterval = 3600000;
//const long hourInterval = 1000;

const int minuteBin[6] = {1, 2, 4, 8, 16, 32};
const int hourBin[4] = {1, 2, 4, 8};

int hour = 2; // starting hour
int minute = 6; // starting minute

unsigned long previousMin = 0;
unsigned long previousHour = millis() - minute * 60000;

int led = 1;


void setMin() {
  int copy = minute;
  for (int i = 5; i >= 0; i--) {
    copy -= minuteBin[i];
    if (copy >= 0) {
      digitalWrite(i+2, HIGH);
    } else {
      digitalWrite(i+2, LOW);
      copy += minuteBin[i];
    }
  }
}

void setHour() {
  int hourCopy = hour;
  for (int i = 3; i >= 0; i--) {
    hourCopy -= hourBin[i];
    if (hourCopy >= 0) {
      digitalWrite(i+8, HIGH);
    } else {
      digitalWrite(i+8, LOW);
      hourCopy += hourBin[i];
    }
  }
}




void setup() {
//  Serial.begin(9600);
  for (int x = 2; x < 12; x++) {
    pinMode(x, OUTPUT);
  }
  setMin();
  setHour();
}



void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousMin > minInterval) {
    previousMin = currentTime;
    if (++minute > 59) {
      minute = 0;
    }
    setMin();
  }

  if (currentTime - previousHour > hourInterval) {
    previousHour = currentTime;
    if (++hour > 12) {
      hour = 1;
    }
    setHour();
  }
}
