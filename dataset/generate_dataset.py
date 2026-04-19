import os
import numpy as np
import pandas as pd

def generate_synthetic_data(num_samples=1000):
    """
    Generates synthetic data representing acoustic (MFCC-like) and vibration (RMS, Variance) features.
    Classes:
    0 - Normal
    1 - Moderate Anomaly
    2 - Critical Anomaly
    """
    np.random.seed(42)
    
    data = []
    labels = []
    
    samples_per_class = num_samples // 3
    
    # Class 0: Normal
    # Low vibration, low acoustic noise
    for _ in range(samples_per_class):
        # Audio features (e.g., 10 MFCC coefficients)
        mfcc = np.random.normal(loc=-10, scale=2, size=10)
        # Vibration features
        vib_rms = np.abs(np.random.normal(loc=0.1, scale=0.05))
        vib_var = np.abs(np.random.normal(loc=0.01, scale=0.005))
        
        feature_vector = list(mfcc) + [vib_rms, vib_var]
        data.append(feature_vector)
        labels.append(0)
        
    # Class 1: Moderate Anomaly
    # Medium vibration, irregular acoustic noise
    for _ in range(samples_per_class):
        mfcc = np.random.normal(loc=0, scale=5, size=10)
        vib_rms = np.abs(np.random.normal(loc=0.5, scale=0.1))
        vib_var = np.abs(np.random.normal(loc=0.1, scale=0.05))
        
        feature_vector = list(mfcc) + [vib_rms, vib_var]
        data.append(feature_vector)
        labels.append(1)
        
    # Class 2: Critical Anomaly
    # High vibration, loud/chaotic acoustic noise
    for _ in range(samples_per_class):
        mfcc = np.random.normal(loc=15, scale=8, size=10)
        vib_rms = np.abs(np.random.normal(loc=1.5, scale=0.3))
        vib_var = np.abs(np.random.normal(loc=0.5, scale=0.2))
        
        feature_vector = list(mfcc) + [vib_rms, vib_var]
        data.append(feature_vector)
        labels.append(2)
        
    # Create DataFrame
    columns = [f'mfcc_{i}' for i in range(1, 11)] + ['vib_rms', 'vib_var']
    df = pd.DataFrame(data, columns=columns)
    df['label'] = labels
    
    # Shuffle
    df = df.sample(frac=1).reset_index(drop=True)
    
    # Create directory if it doesn't exist
    os.makedirs('dataset', exist_ok=True)
    
    # Save to CSV
    output_path = os.path.join('dataset', 'sensor_data.csv')
    df.to_csv(output_path, index=False)
    print(f"Synthetic dataset generated and saved to {output_path}")
    print(df.head())

if __name__ == "__main__":
    generate_synthetic_data(1500)
