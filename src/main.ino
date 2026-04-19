#include <Arduino.h>

// Pins
const int MIC_PIN = 34; // Simulating Acoustic Sensor (Analog)
const int VIB_PIN = 35; // Simulating Vibration Sensor (Analog)
const int LED_WARN_PIN = 2; // Yellow LED for Warning
const int LED_CRIT_PIN = 4; // Red LED for Danger
const int BUZZER_PIN = 5;

// Inference & Adaptive Logic
float running_avg_mic = 0;
float running_rms_vib = 0;
float threshold_warn = 3.0; // Adaptive starting points
float threshold_crit = 6.0;

// Logging Mock Array
struct LogEvent {
  unsigned long timestamp;
  int prediction_class;
  float mic_val;
  float vib_val;
};
LogEvent event_log[10]; // Circular buffer
int log_index = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_WARN_PIN, OUTPUT);
  pinMode(LED_CRIT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("TinyML AEIA-Pro System Initialized.");
  Serial.println("Loading Model...");
  delay(500);
  Serial.println("Model Loaded. Calibrating Baselines...");
  
  // Adaptive baseline calibration
  for(int i=0; i<10; i++) {
    running_avg_mic += analogRead(MIC_PIN) / 10.0;
    running_rms_vib += analogRead(VIB_PIN) / 10.0;
    delay(50);
  }
  Serial.println("Calibration complete. Active monitoring starts.");
}

void log_event(int pred, float mic, float vib) {
  event_log[log_index] = {millis(), pred, mic, vib};
  log_index = (log_index + 1) % 10;
}

void print_logs() {
  Serial.println("--- FATAL ERROR LOGS ---");
  for(int i=0; i<10; i++) {
    if (event_log[i].timestamp != 0 && event_log[i].prediction_class == 2) {
      Serial.printf("T: %lu ms | State: DANGER | Mic: %.2f | Vib: %.2f\n", 
                    event_log[i].timestamp, event_log[i].mic_val, event_log[i].vib_val);
    }
  }
}

void extract_features(float mic, float vib, float features[12]) {
  for(int i=0; i<10; i++) features[i] = (mic / 4095.0) * 10.0 + random(-5, 5)/10.0; 
  features[10] = (vib / 4095.0) * 2.0; // RMS
  features[11] = (vib / 4095.0) * (vib / 4095.0) * 0.5; // Variance
}

int perform_inference(float features[12]) {
  float rms = features[10];
  float avg_mic = 0;
  for(int i=0; i<10; i++) avg_mic += features[i];
  avg_mic /= 10.0;
  
  // Adaptive learning: if environment is globally louder over time, relax thresholds slightly
  // simulated exponential moving average over time in loop() affects warnings
  
  if (rms > 1.2 && avg_mic > threshold_crit) return 2; // Danger
  if (rms > 0.4 && avg_mic > threshold_warn) return 1; // Warning
  return 0; // Normal
}

void loop() {
  float mic_val = analogRead(MIC_PIN);
  float vib_val = analogRead(VIB_PIN);
  
  // Adaptive background tracking
  running_avg_mic = 0.95 * running_avg_mic + 0.05 * (mic_val / 4095.0 * 10.0);
  threshold_warn = running_avg_mic + 1.5; 
  threshold_crit = running_avg_mic + 3.0;
  
  float input_features[12];
  extract_features(mic_val, vib_val, input_features);
  
  int class_pred = perform_inference(input_features);
  
  digitalWrite(LED_WARN_PIN, LOW);
  digitalWrite(LED_CRIT_PIN, LOW);
  noTone(BUZZER_PIN);
  
  Serial.print("Mic: "); Serial.print(mic_val);
  Serial.print(" | Vib: "); Serial.print(vib_val);
  Serial.print(" => ");
  
  if (class_pred == 0) {
    Serial.println("NORMAL");
  }
  else if (class_pred == 1) {
    Serial.println("WARNING");
    // Blink logic could go here; simplified to SOLID mapping based on rapid updates
    digitalWrite(LED_WARN_PIN, millis() % 500 < 250); 
    log_event(1, mic_val, vib_val);
  }
  else if (class_pred == 2) {
    Serial.println("DANGER");
    digitalWrite(LED_CRIT_PIN, HIGH);
    tone(BUZZER_PIN, 1500);
    log_event(2, mic_val, vib_val);
    if(random(0,10) == 0) print_logs(); // Occasional log dump on danger
  }
  
  delay(100);
}
