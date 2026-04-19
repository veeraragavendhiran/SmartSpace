#define SOUND_PIN 34
#define VIB_PIN 26
#define LED_PIN 23
#define BUZZER_PIN 22

int soundValue;
int vibrationValue;

void setup() {
  Serial.begin(115200);

  pinMode(VIB_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {

  // Read inputs
  soundValue = analogRead(SOUND_PIN);
  vibrationValue = digitalRead(VIB_PIN);

  Serial.print("Sound: ");
  Serial.print(soundValue);
  Serial.print(" | Vibration: ");
  Serial.println(vibrationValue);

  // --- Smart Classification (TinyML-like logic) ---

  if (soundValue < 1500 && vibrationValue == LOW) {
    // NORMAL
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Status: NORMAL");

  } else if (soundValue >= 1500 && soundValue < 3000) {
    // WARNING
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Status: WARNING");

  } else if (soundValue >= 3000 || vibrationValue == HIGH) {
    // DANGER
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Status: DANGER");
  }

  delay(500);
}
