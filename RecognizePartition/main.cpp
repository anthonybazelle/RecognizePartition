#include <iostream>
#include <vector>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>



int main()
{
	int thresh = 100;
	int max_thresh = 255;

	cv::RNG rng(12345);

	cv::Mat image;
	cv::Mat imageCvtGray;
	cv::Mat imageThreshold;
	cv::Mat imageCannyOutput;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	image = cv::imread("../resources/partition.jpg", cv::IMREAD_COLOR); // Read the file

	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cv::cvtColor(image, imageCvtGray, cv::COLOR_RGB2GRAY);
	cv::namedWindow("Recognize Partition", cv::WINDOW_NORMAL); 
	cv::imshow("Recognize Partition", image);
	
	cv::threshold(imageCvtGray, imageThreshold, 0, 255, 1);
	cv::namedWindow("Threshold Image", cv::WINDOW_NORMAL);
	cv::imshow("Threshold Image", imageThreshold);

	/// Detect edges using canny
	cv::Canny(imageCvtGray, imageCannyOutput, thresh, thresh * 2, 3);
	/// Find contours
	cv::findContours(imageCannyOutput, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	/// Draw contours
	cv::Mat drawing = cv::Mat::zeros(imageCannyOutput.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(255, 255, 255);
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
	}

	// Use approxPolyDP ???

	/// Show in a window
	cv::namedWindow("Contours", CV_WINDOW_NORMAL);
	cv::imshow("Contours", drawing);

	cv::waitKey(0);

	return 0;
}