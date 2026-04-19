import numpy as np

def compute_rms(signal):
    """
    Compute the Root Mean Square (RMS) of a given signal.
    """
    return np.sqrt(np.mean(np.square(signal)))

def compute_variance(signal):
    """
    Compute the variance of a given signal.
    """
    return np.var(signal)

def extract_features(audio_buffer, vib_buffer):
    """
    Simulates feature extraction from raw buffers.
    In a real Python backend, this would use librosa.feature.mfcc.
    Here we simulate the process to match the dataset format.
    """
    # Simulate extraction of 10 MFCC coefficients
    mfcc = np.random.normal(loc=0, scale=1, size=10) 
    
    vib_rms = compute_rms(vib_buffer)
    vib_var = compute_variance(vib_buffer)
    
    features = list(mfcc) + [vib_rms, vib_var]
    return features

if __name__ == "__main__":
    # Test
    dummy_audio = np.random.randn(1024)
    dummy_vib = np.random.randn(128)
    
    features = extract_features(dummy_audio, dummy_vib)
    print("Extracted Features:", features)
