
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char** argv)
{
    const char* ImageFile = argv[1];	              
    Mat image;			                    
    image = imread(ImageFile, IMREAD_COLOR);	         
    if (!image.data)
    {
        printf(" No image data \n ");
        return -1;
    }
    
    Mat gray_image;
    resize(image, gray_image, cv::Size(image.cols * 0.8, image.rows * 0.8), 0, 0, INTER_LINEAR); // resize image to 0.8x of orig image
    cvtColor(gray_image, gray_image, COLOR_BGR2GRAY);             
    const char* ASCII = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\" ^ `'. ";
    int shades = 255 / strlen(ASCII);
    std::ofstream File;
    File.open("Pic.txt");

    for (int i = 0; i < gray_image.rows; i++)
    {
        for (int j = 0; j < gray_image.cols; j++)
        {   
            int Scale = (int)gray_image.at<uchar>(i, j);
            int charIndex = std::ceil(float(Scale) / float(shades));
            const char c = ASCII[charIndex];
            File << c;

        }
        File << "\n";
        

    }
    File.close();
    imwrite("gray.png", gray_image);
    namedWindow(ImageFile, WINDOW_AUTOSIZE);
    namedWindow("Gray image", WINDOW_AUTOSIZE);
    imshow(ImageFile, image);	                   
    imshow("Gray image", gray_image);
    waitKey(0);	     
    return 0;
}
