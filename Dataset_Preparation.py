import json
import os
import math
import librosa

DATASET_PATH = "C://Users//Necro//Desktop//song//Snoring"
JSON_PATH = "data.json"
SAMPLE_RATE = 22050
DURATION = 30 #measured in seconds
SAMPLES_PER_TRACK = SAMPLE_RATE * DURATION

def save_mfcc(dataset_path, json_path, num_mfcc=13, n_fft=2048, hop_length=512, num_segments=5):


    #dictionary to store data

    data = {
        "mapping": [],
        "mfcc": [],    #inputs
        "labels": []               #outputs
    }

    samples_per_segment = int(SAMPLES_PER_TRACK / num_segments)
    num_mfcc_vectors_per_segment = math.ceil(samples_per_segment / hop_length) # 1.2 -> 2

    #loop through all the genres

    for i, (dirpath, dirnames, filenames) in enumerate(os.walk(dataset_path)):

        #ensure that we're not at the root level

        if dirpath is not dataset_path:

            #save the semantic label

            semantic_label = dirpath.split("\\")[-1] # if we have a dir path that is genre/blues then it will give list ["genre", "blues"]
            data["mapping"].append(semantic_label)
            print("Processing {}".format(semantic_label))

            #process files for a specific genre

            for f in filenames:

                #load audio file
                file_path = os.path.join(dirpath, f)
                signal, sr = librosa.load(file_path, sr=SAMPLE_RATE)

                #divides file into segments extracting mfcc and storing data

                for s in range(num_segments):
                    start_sample = samples_per_segment * s # s=0 -> 0
                    finish_sample = start_sample + samples_per_segment # s=0 -> num_samples_per_segment

                    #store mfcc for segment if it has the expected length
                    mfcc = librosa.feature.mfcc(signal[start_sample:finish_sample],
                                                sr=sr,
                                                n_fft = n_fft,
                                                n_mfcc = num_mfcc,
                                                hop_length = hop_length)
                    mfcc = mfcc.T
                    #print(mfcc)
                    if len(mfcc) == num_mfcc_vectors_per_segment:
                        data["mfcc"].append(mfcc.tolist())
                        data["labels"].append(i-1)
                        print("{}, segment:{}".format(file_path, s+1))
    with open(json_path, "w") as fp:
        json.dump(data, fp, indent = 4)


if __name__ == "__main__":
    save_mfcc(DATASET_PATH, JSON_PATH, num_segments=10)