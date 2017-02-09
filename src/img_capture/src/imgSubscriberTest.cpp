#include "ros/ros.h"
#include "img_capture/imgRawData.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void image_rcv_callback(const img_capture::imgRawData::ConstPtr& msg)
{
	Mat image = Mat(msg->row, msg->col, CV_8UC3);

	//copy data
	for(int i=0; i<msg->img.size(); ++i)
	{
		image.data[i] = msg->img[i];	
	}
	
	//display image
	imshow("Display Test", image);
    waitKey(10);	
}


int main(int argc, char **argv)
{
	//initial ros node
	ros::init(argc, argv, "image_subscrib_tester");
	
	//create namedwindow for display
	namedWindow("Display Test", WINDOW_AUTOSIZE);
	startWindowThread();

	//create node handler
	ros::NodeHandle node_obj;

	//subscribe raw image for testing
	ros::Subscriber image_subscriber = node_obj.subscribe("/img_raw", 10, image_rcv_callback);
	
	//ros timing control function
	ros::spin();
	
	return 0;
}
