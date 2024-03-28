# 3D Sound Visualization
Visualizes the sound captured by a spherical microphone for a music piece with spatial elements. The sound is captured by a microphone array with 32 microphones placed on the surface of a sphere. The output visualizes the sound intensity captured by each microphone on the sphere and interpolates the data across the surface of the sphere.

## Reproduce
To reproduce, run the following:
```
python visualize.py
```

## Data
To run the code, the microphone and sound data needs to be provided. A file, `mic_locations.txt`, needs to be provided. Each line of this file should contain the number of the microphone, the elevation of the microphone, and the azimuth of the microphone, i.e.:

```
1 elevation1 azimuth1
2 elevation2 azimuth2
...
32 elevation32 azimuth32
```

Additionally, the separate sound files for each of the microphones needs to be provided. These are `.wav` files, and should be stored in `sound_data/mic_1.wav, ..., sound_data/mic_32.wav`, where each sound file corresponds to the location provided in `mic_locations.txt`.

## Visualizations
Visualizations of the data are provided on [YouTube](https://www.youtube.com/playlist?list=PL-5kLq3t5DHx6u151c2lGbQ1H-ZkOe-Ho).

![](https://github.com/marco-grond/Visualization/blob/main/Visualize_3D_Sound/Output/exampleOutput.gif)

## Report
A report detailing this work is presented is this repo:
[Report](https://github.com/marco-grond/Visualization/blob/main/Visualize_3D_Sound/SphericalMicrophoneVisualization.pdf)
