PanoramicECP
=================================

It gets the camera frames, make JNI calls with its gray matrices references as parameters, add some random noise to the images from a C++ method, and render the generated frames.

It works with Android Studio 3+

OpenCV version: 3.2.0

This application uses the settings of https://github.com/leadrien/opencv_native_androidstudio.git to connect with OpenCV, and uses the OpenCV 3.2.0 Android Library (because the 3.4.x and the 4.x compiled versions don't define stitching methods).
