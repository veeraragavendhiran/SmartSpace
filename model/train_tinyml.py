import os
import numpy as np
import pandas as pd
import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

import json
import codecs

def train_and_convert():
    """
    Trains a lightweight neural network for edge devices
    and converts it to a TensorFlow Lite Micro C array.
    """
    # 1. Load Data
    data_path = os.path.join('dataset', 'sensor_data.csv')
    if not os.path.exists(data_path):
        print(f"Dataset not found at {data_path}. Please run generate_dataset.py first.")
        return
        
    df = pd.read_csv(data_path)
    
    # Separate features and labels
    X = df.drop('label', axis=1).values
    y = df['label'].values
    
    # 2. Preprocessing
    # Standardize features
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    
    # Save the scaler parameters to be used in C/C++
    scaler_params = {
        'mean': scaler.mean_.tolist(),
        'scale': scaler.scale_.tolist()
    }
    with open(os.path.join('model', 'scaler_params.json'), 'w') as f:
        json.dump(scaler_params, f)
        
    X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)
    
    # 3. Model Architecture (Lightweight for TinyML)
    model = tf.keras.models.Sequential([
        tf.keras.layers.Dense(16, activation='relu', input_shape=(X_train.shape[1],)),
        tf.keras.layers.Dense(8, activation='relu'),
        tf.keras.layers.Dense(3, activation='softmax')
    ])
    
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    
    # 4. Train Model
    print("Training Model...")
    model.fit(X_train, y_train, epochs=50, batch_size=32, validation_data=(X_test, y_test), verbose=1)
    
    loss, accuracy = model.evaluate(X_test, y_test, verbose=0)
    print(f"Test Accuracy: {accuracy * 100:.2f}%")
    
    # 5. Convert to TFLite
    print("Converting model to TFLite...")
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    
    # Optimize for size
    converter.optimizations = [tf.lite.Optimize.DEFAULT]
    
    # Note: To fully integer quantize, we would need a representative dataset generator.
    # We will use default quantization for now.
    def representative_dataset():
        for i in range(min(100, len(X_train))):
            yield [X_train[i].astype(np.float32).reshape(1, -1)]

    converter.representative_dataset = representative_dataset
    converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
    converter.inference_input_type = tf.int8
    converter.inference_output_type = tf.int8
    
    try:
        tflite_model = converter.convert()
    except Exception as e:
         print("Quantization failed, falling back to unquantized TFLite:", e)
         converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS]
         converter.inference_input_type = tf.float32
         converter.inference_output_type = tf.float32
         tflite_model = converter.convert()

    
    # 6. Save TFLite model
    tflite_model_path = os.path.join('model', 'anomaly_model.tflite')
    with open(tflite_model_path, 'wb') as f:
        f.write(tflite_model)
        
    print(f"TFLite model saved to {tflite_model_path}")
    
    # 7. Convert TFLite to C Header using simple hex dump mapping
    print("Generating C array...")
    hex_array = ', '.join([f'0x{b:02x}' for b in tflite_model])
    
    c_code = f'''
// This file was automatically generated
#ifndef MODEL_DATA_H
#define MODEL_DATA_H

const unsigned char model_data[] = {{
    {hex_array}
}};
const unsigned int model_data_len = {len(tflite_model)};

#endif // MODEL_DATA_H
'''
    
    c_model_path = os.path.join('model', 'model_data.h')
    with open(c_model_path, 'w') as f:
        f.write(c_code)
        
    print(f"C array sorted to {c_model_path}")

if __name__ == "__main__":
    train_and_convert()
