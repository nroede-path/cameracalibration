# cameracalibration

## circlegrid

Finds the circle centers on a picture of an asymmetrical circular calibration board and draws them, then shows the annotated image

## calibratecam

Takes an input series of images of a calibration board from various angles (from a directory called calibimgs in the workspace folder), attempts to find the circle centers, and sorts bad/failed images into another folder called badimgs inside the calibimgs folder. Then, the good images are used to calibrate the camera and output the camera matrix, distortion coefficients, rotation vector, and translation vector in the console.
