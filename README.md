# Path Planning Visualizer
A desktop application developed to visualize the path planning process, starting from defining environment geometry and robot geometry, until generating a path using the graph generated based on the type of path planning. 
Take note that this project being tested on Ubuntu 20.04 environment only.

## RUNNING ON DOCKER CONTAINER (CURRENTLY NOT WORKING)

### To build this image
```
./builldDockerImage.sh
```

### To run the docker image
```
./runDockerFile.sh
```

## TO-DO
1. Configuration space with consideration of robot geometry
2. Make this project runnable as a docker container

## References
1. [How to expand contour by certain radius](https://stackoverflow.com/questions/58981397/how-to-dilate-a-contour-by-a-specific-number-of-pixels-without-iterating-over-e)
2. [Converting OpenCV image to wxBitmap](https://github.com/PBfordev/wxopencvtest)
