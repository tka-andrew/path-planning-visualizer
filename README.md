# Path Planning Visualizer
A desktop application developed to visualize the path planning process, starting from defining environment geometry and robot geometry, until generating a path using the graph generated based on the type of path planning. 
Take note that this project being tested on Ubuntu 20.04 environment only.

## RUNNING ON LOCAL MACHINE

### Install libwxgtk3.0-dev binaries
```
sudo apt-get update -y
sudo apt-get install -y libwxgtk3.0-gtk3-dev  (PS: for Ubuntu 20.04)
sudo apt-get install -y libwxgtk3.0-dev  (PS: for other versions of Ubuntu)
```

### Install OpenCV 
1. [Reference](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)

### CMake and build
In this directory
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Run the exectubale
```
./PathPlanningVisualizer
```

## TO-DO
1. Support more decomposition methods such as visibility graph
2. Make this project runnable as a docker container

## References
1. [How to expand contour by certain radius](https://stackoverflow.com/questions/58981397/how-to-dilate-a-contour-by-a-specific-number-of-pixels-without-iterating-over-e)
2. [Converting OpenCV image to wxBitmap](https://github.com/PBfordev/wxopencvtest)
3. [Accessing value of cv::Mat](https://docs.opencv.org/3.3.0/db/da5/tutorial_how_to_scan_images.html)
