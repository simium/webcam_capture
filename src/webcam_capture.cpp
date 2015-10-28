#include <cstdlib>
#include <iostream>

#include "cv.h"
#include "highgui.h"

int main(int argc, char *argv[])
{
  // OpenCV video capture object
  cv::VideoCapture camera;

  // OpenCV image objects and ROIs
  cv::Mat camImage;
  cv::Mat camSubimage;
  cv::Rect roi;

  // Camera id. Associated to device number in /dev/videoX
  int cam_id;

  // Check user args
  switch(argc)
  {
    case 1: // No argument provided, so try /dev/video0
      cam_id = 0;
      break;
    case 2: // An argument is provided. Get it and set cam_id
      cam_id = atoi(argv[1]);
      break;
    default:
      std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
      std::cout << "EXIT program." << std::endl;
      break;
  }

  // Advertising to the user
  std::cout << "Opening video device " << cam_id << std::endl;

  // Open the video stream and make sure it's opened
  if( !camera.open(cam_id) )
  {
    std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
    return -1;
  }

  // Capture loop until user presses a key
  while(true)
  {
    // Read image and check it
    if(!camera.read(camImage))
    {
      std::cout << "No frame" << std::endl;
      cv::waitKey();
    }

    /* Provide info about central pixel */
    std::cout << "Central pixel is (" << camImage.cols/2 << "," << camImage.rows/2 << ")" << std::endl;

    /* Create a ROI (region of interest) inside the original image */
    roi = cv::Rect((camImage.cols/2)-1, (camImage.rows/2)-1, 3, 3);
    camSubimage = camImage(roi);

    /* Quick and easy transformation, just multiply the matrix */
    camSubimage = camSubimage*5;

    // Show image in a window
    cv::imshow("Output Window", camImage);

    // Print image dimensions
    std::cout << "Image size is [" << camImage.cols << "x" << camImage.rows << "] pixels" << std::endl;

    // Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
    if(cv::waitKey(1) >= 0) break;
  }
}
