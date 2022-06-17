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
1. [Mouse as a Paint-Brush](https://docs.opencv.org/4.x/db/d5b/tutorial_py_mouse_handling.html)
2. [How to Scale and Rotate Contours](https://medium.com/analytics-vidhya/tutorial-how-to-scale-and-rotate-contours-in-opencv-using-python-f48be59c35a2)
3. [Converting OpenCV image to wxBitmap](https://github.com/PBfordev/wxopencvtest)
