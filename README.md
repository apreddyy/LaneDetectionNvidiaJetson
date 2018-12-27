# LaneDetectionNvidiaJetson 
### Distortion corrected calibration image.   
The code for this step is contained in the calibration.cpp [Here](../LaneDetectionNvidiaJetson/calibration.cpp).  
Start by preparing "object points", which will be the (x, y, z) coordinates of the chessboard corners in the world. Here we are assuming the chessboard is fixed on the (x, y) plane at z=0, such that the object points are the same for each calibration image. Thus, objp is just a replicated array of coordinates, and objpoints will be appended with a copy of it every time I successfully detect all chessboard corners in a test image. imgpoints will be appended with the (x, y) pixel position of each of the corners in the image plane with each successful chessboard detection. Then use the output objpoints and imgpoints to compute the camera calibration and distortion coefficients using the calibrateCamera() function.  
Example:   
![alt text]( images/image1.png)    
#### Pipeline.   
At First,  resize the image and then  convert frame as Bird view and then use a combination of color and gradient thresholds to generate a binary image.  
**Step 1:** Undisort Image.   
**Step 2:** Binary Image.   
**Step 3:** Take a histogram along all the columns in the lower half of the image and split histogram for two sides for each lane.   
**Step 4:** Use the two highest peaks from histogram as a starting point for determining where the lane lines are, and then use sliding windows moving upward in the image to determine where the lane lines go.   
Example: 
![alt text](images/image2.png)   
**Step 5:**  Identify lane-line pixels.    
Find all non zero pixels.  
Example:   
![alt text](images/image3.png)    
**Step 6:** Fit their positions with a polynomial.   
After performing 2nd order polynomial fit for nonzero pixels, drawing polyline and unwrap image the final output.  
Example:   
![alt text](images/image4.png)     
### Radius of curvature of the lane and the position of the vehicle with respect to center. 
Get the left and right cordinates and calculate the midpoint of lanes and use the image center as reference to calculate distance away from center.  
## Dependencies and Compiling.  
1- Nvidia Jetson TX2.  
2- OpenCV 3.4.  
3- aarch64.lib file required to compile.   
4- Run make file from output folder.    
5- Code was optimized specifically for ARM Cortex processor.  

