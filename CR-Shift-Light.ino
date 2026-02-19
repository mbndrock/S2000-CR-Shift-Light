const int tachPin = 2;
const int ledPin = 13;

unsigned long ighigh, iglow, igfreq;
unsigned int rpm = 0;
const int pulsesPerRevolution = 2; 

unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  pinMode(tachPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Startup: 1s Solid + 3 Flashes
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(250); 
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }
}

void loop() {
  ighigh = pulseIn(tachPin, HIGH);
  iglow = pulseIn(tachPin, LOW);

  // If we have a valid signal, calculate RPM
  if (ighigh > 0 && iglow > 0) {
    igfreq = 1000000 / (ighigh + iglow);
    rpm = (igfreq * 60) / pulsesPerRevolution;

    // --- FIXED LED LOGIC ---
    if (rpm >= 8100) {
      digitalWrite(ledPin, HIGH); // Force Solid
    } 
    else if (rpm >= 6000) {
      int flashRate = map(rpm, 6000, 7800, 400, 25);
      
      if (millis() - lastBlinkTime >= flashRate) {
        lastBlinkTime = millis();
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
    } 
    else {
      digitalWrite(ledPin, LOW); // Off below 6000
    }

    Serial.print("RPM: ");
    Serial.println(rpm);
  } 
  // If no signal is detected, we only turn it off if the engine is truly stopped
  else if (ighigh == 0 && iglow == 0) {
    digitalWrite(ledPin, LOW);
  }
}