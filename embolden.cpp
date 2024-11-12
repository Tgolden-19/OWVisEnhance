#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <tuple>
 
using namespace cv;
using namespace std;

Mat preproccessing(Mat inImg){

    Mat hsvImage;
    cvtColor(inImg, hsvImage, COLOR_BGR2HSV);


    Mat mask1;
    inRange(inImg, Scalar(8, 15, 160), Scalar(8, 15, 160), mask1);
    Mat mask2;
    inRange(hsvImage, Scalar(0, 110, 175), Scalar(5, 255, 255), mask2);
    Mat mask3;
    inRange(hsvImage, Scalar(175, 110, 175), Scalar(180, 255, 255), mask3);

    Mat finImg;
    cv::add(mask1, mask2, finImg);
    cv::add(finImg, mask3, finImg);
    return finImg;

}

void removePlayer(Mat inImg) {
    int width = inImg.size().width;
    int height = inImg.size().height;
    int pRegionX = width / 3;
    int pRegionY = height / 3;
    Rect blackReg((pRegionX*2), (pRegionY*2), pRegionX, pRegionY);
    Mat toBlackReg = inImg(blackReg);
    toBlackReg.setTo(Scalar(0, 0, 0));

}
 
int vis_main()
{
    //grab image from window could also use opencv image grab
    // @TODO look into openCV screengrab method for better integration
    //HWND screengrab = GetDesktopWindow();
    std::string imgPath = "images/bots1.png";
    Mat ogImage = imread(imgPath, IMREAD_COLOR);
    Mat enemyImg = preproccessing(ogImage);
    removePlayer(enemyImg);
    




    // namedWindow("test_image", WINDOW_AUTOSIZE );
    imshow("test_image", ogImage);
 
    waitKey(0);
 
    return 0;
}