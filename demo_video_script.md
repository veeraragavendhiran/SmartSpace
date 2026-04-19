# Demo Video Script: SmartSpace AEIA-Pro

**1. Project Intro (0:00 - 0:15)**
- **Visual**: Screen capture of GitHub repository & architecture diagram.
- **Narrator**: "Welcome to the presentation for SmartSpace: an advanced, autonomous TinyML Acoustic and Vibration Signature Recognition system implemented on the ESP32 via our multi-agent framework."

**2. Circuit Explanation (0:15 - 0:35)**
- **Visual**: Wokwi Simulation layout highlighting the ESP32 DevKit, 2 Slide Potentiometers simulating inputs, 2 LEDs (Yellow, Red) and a Buzzer.
- **Narrator**: "The circuit uses two analog input simulations for our acoustic microphone and piezoelectric vibration sensor. Based on embedded neural processing, the ESP32 dynamically switches digital logic to flag Warnings on the yellow LED and Critical Dangers on the red LED alongside the buzzer."

**3. Simulation Demo (0:35 - 0:50)**
- **Visual**: User activates Wokwi simulation. Serial monitor reads "Calibration complete. Active monitoring starts." Wait for "NORMAL" logic prints.
- **Narrator**: "Upon boot, the system pre-computes exponential background variance for its adaptive threshold feature. In resting state, it classifies operations as perfectly Normal."

**4. Input (Sound/Vibration) (0:50 - 1:10)**
- **Visual**: User slides outputs slowly up to roughly 40-60% range.
- **Narrator**: "As environmental stress naturally increases or mechanical parts wear down, our analog inputs rise smoothly..." 

**5. Output Response (1:10 - 1:35)**
- **Visual**: Serial monitor logs "WARNING". Yellow LED blinks. Then, user maxes out sliders instantly. Serial dumps "FATAL ERROR LOGS". Red LED on, buzzer ringing.
- **Narrator**: "...The adaptive edge tracking recognizes this as an unsafe Warning threshold, flashing our alerts and discreetly caching the log buffer in memory. When pushed to extremes, a total mechanical breakdown occurs, triggering the Danger status, halting operations, and immediately dumping all recent diagnostic logs to the operator console offline."

**6. Conclusion (1:35 - 1:50)**
- **Visual**: Smoothly panning through the `main.ino` IDE code logic and Neural-Network inference function.
- **Narrator**: "Powered seamlessly without any cloud delay, SmartSpace accurately merges analog metrics with memory-safe Artificial Intelligence natively at the edge."
