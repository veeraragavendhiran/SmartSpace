# Demo Video Script: TinyML Acoustic and Vibration Signature Recognition

**[0:00 - 0:15] Introduction & Setup**
- **Visual:** Screen captures of the Wokwi simulation and the GitHub repository.
- **Narrator:** "Welcome to the demonstration of our TinyML Edge AI monitor. In this system, an ESP32 is simulating continuous scanning of mechanical vibration and acoustic noise."

**[0:15 - 0:35] Normal Operational State**
- **Visual:** Simulator running. Both potentiometers (Mic and Vib) at low levels. System outputs "NORMAL" to serial. LEDs are off.
- **Narrator:** "Here, the sensor inputs are well within nominal operational limits. Our TinyML neural network evaluates the environment 10 times a second and confidently classifies this as 'Normal'."

**[0:35 - 0:55] Moderate Anomaly Detection**
- **Visual:** User slides the vibration and mic potentiometers to mid-range. Serial terminal dynamically updates to "MODERATE ANOMALY". The Yellow Warn LED lights up.
- **Narrator:** "As mechanical variance builds up, the extracted RMS and frequency approximations tell the TinyML model that anomalous behavior is occurring. Instantly, our system adapts, flagging a Moderate Anomaly, turning on the visual warning LED without hitting any cloud dependencies."

**[0:55 - 1:15] Critical Anomaly & Alert System**
- **Visual:** Sliders maxed out. Serial outputs "CRITICAL ANOMALY". Red LED turns on and buzzer tone is audible.
- **Narrator:** "If the state deteriorates into extreme chaotic sound waves and high-RMS oscillations, the embedded logic registers a Critical system fault. The Red LED flares, and a buzzer is triggered immediately to alert local operators to shut down hardware."

**[1:15 - 1:30] Conclusion**
- **Visual:** Wide shot of project structure and architecture diagram.
- **Narrator:** "By relying on local TinyML inference, this system prevents catastrophic failures dynamically, with zero cloud latency."
