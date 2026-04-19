#include <Arduino.h>

// Pins
const int MIC_PIN = 34; // Simulating Acoustic Sensor
const int VIB_PIN = 35; // Simulating Vibration Sensor
const int LED_WARN_PIN = 2; // Yellow LED for Moderate Anomaly
const int LED_CRIT_PIN = 4; // Red LED for Critical Anomaly
const int BUZZER_PIN = 5;

// Variables
float mic_val = 0;
float vib_val = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_WARN_PIN, OUTPUT);
  pinMode(LED_CRIT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Simulated setup of Neural Network / TFLiteMicro
  Serial.println("TinyML-Based Autonomous Acoustic and Vibration Signature Recognition System Initialized.");
  Serial.println("Loading Model...");
  delay(1000);
  Serial.println("Model Loaded. Ready for inference.");
}

void extract_features(float mic, float vib, float features[12]) {
  // Simulating feature extraction for MFCC (10) + RMS (1) + Var (1)
  // In a real scenario, audio buffers of size 1024 would be grouped to compute FFT/MFCC
  
  // Here we populate mock MFCC values impacted by the mic analog value
  for(int i=0; i<10; i++) {
    features[i] = (mic / 4095.0) * 10.0 + random(-10, 10)/10.0; 
  }
  
  // Variance and RMS approximations from vibration pot
  features[10] = (vib / 4095.0) * 2.0; // Simulated RMS
  features[11] = (vib / 4095.0) * (vib / 4095.0) * 0.5; // Simulated Variance
}

int perform_inference(float features[12]) {
  // Typical inference logic using TFLite Micro:
  // 1. Copy features into tensor_arena input buffer
  // 2. Invoke interpreter->Invoke()
  // 3. Read output tensor for argmax
  
  // For Wokwi simulation without EdgeImpulse/TFlite C++ library compilation capability,
  // we simulate the decision tree of the neural network
  
  float rms = features[10];
  float var = features[11];
  float avg_mic = 0;
  for(int i=0; i<10; i++) avg_mic += features[i];
  avg_mic /= 10.0;
  
  if (rms > 1.2 && avg_mic > 6.0) return 2; // Critical Anomaly
  if (rms > 0.4 && avg_mic > 3.0) return 1; // Moderate Anomaly
  return 0; // Normal
}

void loop() {
  // 1. Read Sensors
  mic_val = analogRead(MIC_PIN);
  vib_val = analogRead(VIB_PIN);
  
  // 2. Extract Features
  float input_features[12];
  extract_features(mic_val, vib_val, input_features);
  
  // 3. Inference
  int class_pred = perform_inference(input_features);
  
  // 4. Output Actions
  digitalWrite(LED_WARN_PIN, LOW);
  digitalWrite(LED_CRIT_PIN, LOW);
  noTone(BUZZER_PIN);
  
  Serial.print("Mic: ");
  Serial.print(mic_val);
  Serial.print(" | Vib: ");
  Serial.print(vib_val);
  Serial.print(" => Pred: ");
  
  if (class_pred == 0) {
    Serial.println("NORMAL");
    // All off
  }
  else if (class_pred == 1) {
    Serial.println("MODERATE ANOMALY");
    digitalWrite(LED_WARN_PIN, HIGH);
  }
  else if (class_pred == 2) {
    Serial.println("CRITICAL ANOMALY");
    digitalWrite(LED_CRIT_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // 1 kHz tone for buzzer alert
  }
  
  delay(100); // Inference interval simulating edge limitations
}
