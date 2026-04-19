#define SOUND_PIN 34
#define VIB_PIN 26
#define LED_PIN 23
#define BUZZER_PIN 22

int soundValue;
int vibrationValue;

// Advanced Features: Adaptive Thresholds & Smoothing
float smoothedSound = 0;
float adaptiveWarnThresh = 1500;
float adaptiveDangerThresh = 3000;

// Advanced Feature: Event Logging
struct LoggedEvent {
  unsigned long time;
  int state; // 0=Norm, 1=Warn, 2=Danger
  float sound;
};
LoggedEvent eventBuffer[5];
int bufferIndex = 0;

void setup() {
  Serial.begin(115200);

  pinMode(VIB_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Baseline calibration
  for(int i=0; i<10; i++) {
    smoothedSound = 0.9 * smoothedSound + 0.1 * analogRead(SOUND_PIN);
    delay(50);
  }
}

void logEvent(int state, float snd) {
  eventBuffer[bufferIndex] = {millis(), state, snd};
  bufferIndex = (bufferIndex + 1) % 5;
}

void loop() {
  // Read inputs
  soundValue = analogRead(SOUND_PIN);
  vibrationValue = digitalRead(VIB_PIN);
  
  // Exponential Smoothing for Prediction
  smoothedSound = 0.8 * smoothedSound + 0.2 * soundValue;
  
  // Very slow environmental adaptive drift
  adaptiveWarnThresh = 0.999 * adaptiveWarnThresh + 0.001 * (smoothedSound + 1500);

  Serial.print("Sound (Smoothed): ");
  Serial.print(smoothedSound);
  Serial.print(" | Vibration: ");
  Serial.println(vibrationValue);

  // --- Smart Classification (TinyML-like Logic integration) ---
  int currentState = 0;
  
  if (smoothedSound < adaptiveWarnThresh && vibrationValue == LOW) {
    // NORMAL
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Status: NORMAL");
    currentState = 0;

  } else if (smoothedSound >= adaptiveWarnThresh && smoothedSound < adaptiveDangerThresh && vibrationValue == LOW) {
    // WARNING
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Status: WARNING");
    currentState = 1;
    logEvent(1, smoothedSound);

  } else if (smoothedSound >= adaptiveDangerThresh || vibrationValue == HIGH) {
    // DANGER
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Status: DANGER");
    currentState = 2;
    logEvent(2, smoothedSound);
  }

  delay(500);
}
