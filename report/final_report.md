# Final Project Report: TinyML-Based Autonomous Acoustic and Vibration Signature Recognition

## 1. Introduction
The advent of edge AI shifts processing power and intelligence directly to IoT sensors. This project harnesses Tiny Machine Learning (TinyML) to autonomously recognize and classify acoustic and mechanical vibration anomalies locally on an ESP32 microcontroller. The primary benefit is reduced latency, high privacy, and minimized bandwidth usage.

## 2. Dataset Collection & Processing
Due to environmental constraints, synthetic acoustic signatures structured around MFCC-like behavior, mapped alongside theoretical variance and RMS outputs from a vibration sensor, were employed. 
Classes built:
- **0 - Normal:** Ambient noise and baseline mechanical vibration.
- **1 - Moderate Anomaly:** Significant acoustic interruptions aligned with elevated mechanical stress.
- **2 - Critical Anomaly:** Extreme sound variance accompanied by destructive mechanical vibrations.

## 3. TinyML Model Engineering
We trained a simple Fully Connected Neural Network layout featuring 16 and 8 nodes in hidden layers respectively. The model ingested standardized features and achieved highly robust separation using the Softmax layer for output categorization. TFLite Converter shrunk the resulting Keras model payload, allowing generation of a static C-compatible byte array that effortlessly flashes to a microcontroller’s SRAM without breaking spatial limits.

## 4. Hardware Implementation
The edge hardware comprises an ESP32 orchestrating analog endpoints. Pins 34 and 35 handle acoustic and vibration reading loops respectively. The main loop cycles at 100ms processing cadence, performing inference locally with zero cloud dependencies. LEDs mapped to Pins 2 and 4 provide visual indication alongside an auditory alarm governed by Pin 5 whenever the array of predictions evaluates to state 2 (Critical).

## 5. Simulation Testing
Using the Wokwi virtual simulator environment, we validated the pin mappings, the ADC loop reads, and logic bounds prior to physical integration. Serial terminal outputs successfully logged real-time predictions responding accurately to sliding potentiometer inputs meant to represent raw variance feeds.

## 6. Conclusion
This TinyML system is functionally capable of identifying mechanical failure modes through multimodal inference directly at the edge, offering an intelligent monitoring protocol designed inherently for Industry 4.0 applications.
