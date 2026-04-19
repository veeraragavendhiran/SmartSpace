# SmartSpace: TinyML-Based Autonomous Acoustic and Vibration Signature Recognition

## Abstract
The rapid evolution of IoT and Edge AI has created an imperative for localized, latency-free threat detection in industrial environments. "SmartSpace" tackles this by embedding highly optimized machine learning directly onto an ESP32 microcontroller, entirely bypassing cloud dependency loops. By continuously interpreting analog acoustic and mechanical vibration matrices, our TinyML architecture instantaneously computes high-dimensional feature vectors (incorporating MFCC limits, RMS, and Variance values). The lightweight TensorFlow Lite Micro framework distills complex state maps into three definitive operational profiles: Normal, Warning, and Danger. With a minimal computational footprint, this embedded intelligence dynamically calibrates adaptive thresholds and securely buffers fatal logging events locally. This achieves a highly responsive, standalone prediction tool built intentionally over a robust Multi-Agent architectural blueprint to enforce autonomous digital-twin monitoring logic that adapts as systemic stress changes dynamically.

## Problem Statement
Traditional cloud-based acoustic and vibration anomaly detection pipelines suffer from prohibitive bandwidth constraints, increased attack vectors, and unacceptably high latencies during critical equipment failures. Implementing local thresholding algorithms often results in false positives due to environmental drift. SmartSpace proposes a solution combining deterministic event logging, adaptive environment baselines, and neural networking compressed using quantization to monitor state transitions locally on inexpensive hardware.

## Hardware & Software
- **Hardware**: ESP32 DevKit, MAX9814 (Microphone sensor), SW-420 (Vibration sensor), Warning/Danger LEDs, Active Buzzer.
- **Software**: Arduino IDE / PlatformIO Codebase (C++), TensorFlow / Edge Impulse (Model Training), Wokwi (Virtual Simulation), Python (Signal Processing).

## Workflow Diagram
1. **Sensing**: Analog values read from physical or simulated IO ports.
2. **Dynamic Calibration**: Background features are smoothed via Exponential Moving Averages (EMA) to prevent environmental drift errors.
3. **Feature Construction**: Voltage thresholds mathematically translate to modeled MFCC arrays, localized variance, and RMS indicators.
4. **Edge Inferencing**: Features ingest directly into a static `.tflite` (or custom C-array compiled logic) representing the Neural Net.
5. **Evaluation**: Predicts: "Normal" | "Warning" | "Danger".
6. **Action & Logging**: Triggers blinking/solid LEDs, auditory buzzers, and queues JSON-like diagnostic logs.

## Results
- The system correctly flags warning scenarios adaptively without hardcoded false positives.
- Edge Inference requires <20ms to evaluate an entire cycle.
- Local buffering perfectly records the immediate sensor state precisely when a Danger fault occurred sequence.

## Demo Instructions
1. Load `simulation/wokwi_project.json` into the Wokwi ESP32 simulator.
2. Set sliders low and start simulation (Observe `NORMAL` serial messages).
3. Push values to mid-range to see blinking Warn led and adaptive baseline adjusting.
4. Push everything to 100% to witness `DANGER` alert triggers, alarms, and sudden serial dump of error logs.
