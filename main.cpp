#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "imagemanipulation.h"
#include "ppmcreator.h"
#include "imagecalculation.h"
#include "schemerecognition.h"

int main(){
    //MANIPULATION

    cv::Mat inputImage = ImageManipulation::readImage("/home/lars/Documents/Verkehrsschilder/ALL/images (9).jpg");

    //NORMAL
    //ImageManipulation::showImage(inputImage, "Normal");

    //ROTATION
    //ImageManipulation::showImage(ImageManipulation::rotate(inputImage, 90), "Rotation");

    //MIRROR
    //#################
    //vertical mirror #
    //#################
    //ImageManipulation::showImage(ImageManipulation::mirror(inputImage, 0), "vertical mirror");

    //###################
    //horizontal mirror #
    //###################
    //ImageManipulation::showImage(ImageManipulation::mirror(inputImage, 1), "horizontal mirror");

    //################################
    //horizontal and vertical mirror #
    //################################
    //ImageManipulation::showImage(ImageManipulation::mirror(inputImage, 2), "horizontal vertical mirror");

    //SCALE
    //ImageManipulation::showImage(inputImage, "");
    //ImageManipulation::showImage(ImageManipulation::scale(inputImage, 50.0f), "scale");

    //PPM

    //PpmCreator *ppmCreator = new PpmCreator();


    //HISTOGRAM 
    //ImageManipulation::showImage(grayImg, "gray");
    //cv::Mat grayImage = ImageManipulation::toGreyscaleByLuminosity(inputImage);
    //ImageManipulation::showImage(grayImage, "");
    //ImageCalculation::showHistogram(grayImage);

    //std::cout << "MEAN: " << ImageCalculation::getMean(grayImage) << std::endl; //obama = 140.64
    //std::cout << "STANDARD DEVIATION: " << ImageCalculation::getStandardDeviation(grayImage) << std::endl; //obama = 61
    //std::cout << "ENTROPY: " << ImageCalculation::getEntropy(grayImage) << std::endl; //obama = 5.07 aber falsch

    //PART 4

    //linear Scaling
    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, 0, 1.0), "c2=1");
    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, 0, 0.5), "c2=0.5");
    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, 0, 0.25), "c2=0.25");

    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, 0, 1.0), "c1=0");
    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, 40, 1.0), "c1=40");
    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, 100, 1.0), "c1=100");

    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, 0, 1.0), "c1=0");
    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, -40, 1.0), "c1=-40");
    //ImageManipulation::showImage(ImageManipulation::linearScaling(inputImage, -100, 1.0), "c1=-100");


    //equidensities
    //ImageManipulation::showImage(ImageManipulation::equidensities(ImageManipulation::equidensities(inputImage, 1, ImageCalculation::getMean(inputImage)), 2, ImageCalculation::getMean(inputImage)), "equidensities");
    //ImageManipulation::showImage(ImageManipulation::equidensities(inputImage, 1, ImageCalculation::getMean(inputImage)), "equi");

    //sum frequency
    //ImageCalculation::showSumFrequency(inputImage);

    //FILTER 

    //ImageManipulation::showImage(ImageManipulation::mymean_filter(inputImage, 21), "mean");
    //ImageManipulation::showImage(ImageManipulation::mygauss_filter(inputImage), "gaussFilter");
    //ImageManipulation::showImage(ImageManipulation::mysobel_filter_x_signed(inputImage), "sobelXsigned");
    //ImageManipulation::showImage(ImageManipulation::mysobel_filter_y_signed(inputImage), "sobelYsigned");
    //ImageManipulation::showImage(ImageManipulation::mysobel_filter_xy(inputImage), "sobel XY");
    //ImageManipulation::showImage(ImageManipulation::mysobel_filter_gradient(inputImage), "sobel gradient");
    //ImageManipulation::showImage(ImageManipulation::mylaplace_filter(inputImage), "laplace");

    //ImageManipulation::showImage(ImageManipulation::mysobel_filter_xy(ImageManipulation::mymean_filter(inputImage, 7)), "sobel XY with mean");
    //ImageManipulation::showImage(ImageManipulation::mysobel_filter_xy(ImageManipulation::mygauss_filter(inputImage)), "sobel XY with gauss");


    //PART 6
    //ImageManipulation::myLaplacePyramide(inputImage);


    //RGB TO GREYSCALE

    //ImageManipulation::showImage(ImageManipulation::toGreyscaleByAverage(inputImage), "average");
    //ImageManipulation::showImage(ImageManipulation::toGreyscaleByLuminosity(inputImage), "luminosity");
    //ImageManipulation::showImage(ImageManipulation::toGreyscaleByLightness(inputImage), "lightness");
    //ImageManipulation::showImage(ImageManipulation::toGreyscaleByOpenCV(inputImage), "openCV");

    //TRIANGLE DETECTION
    /**
    cv::Mat filteredImage = ImageManipulation::mysobel_filter_xy(ImageManipulation::scale(inputImage, 1.0f));
    //cv::Mat filteredImage = inputImage;

    //ImageManipulation::showImage(filteredImage, "");
    //int range = 90;
    int top, bottom, left, right;
    int minRadius = 100;
    int maxRadius = 300;
    int max = 30;
    for(int i = maxRadius; i<filteredImage.rows-(maxRadius); i++){
        //std::cout << "drinne" << std::endl;
        for(int j = maxRadius; j<filteredImage.cols-(maxRadius); j++){
            for(int k = minRadius; k < maxRadius; k++){
                //std::cout << "drinne" << std::endl;
                //mani = filteredImage;
                //cv::circle(filteredImage, cv::Point(i,j),k,cv::Scalar(0,255,0));

                //filteredImage.at<cv::Vec3b>(i-k,j) = cv::Vec3b(0,255,0);
                //ImageManipulation::showImage(filteredImage, "");
                top = filteredImage.at<cv::Vec3b>(i-k,j)[0];
                bottom = filteredImage.at<cv::Vec3b>(i+k,j)[0];
                left = filteredImage.at<cv::Vec3b>(i,j-k)[0];
                right = filteredImage.at<cv::Vec3b>(i,j+k)[0];

                if(top > max && bottom > max && left > max && right > max){
                    std::cout << std::to_string(i-k) + " " + std::to_string(j) << std::endl;
                    std::cout << "drin" << std::endl;
                    cv::circle(filteredImage, cv::Point(i,j),k,cv::Scalar(0,255,0));
                    ImageManipulation::showImage(filteredImage, "");
                }
            }

        }
    }
    //ImageManipulation::showImage(filteredImage, "");
    //ImageManipulation::showImage(ImageManipulation::mysobel_filter_xy(ImageManipulation::mymean_filter(ImageManipulation::scale(inputImage, 0.2f), 11)), "mean");

    **/
    //cv::Vec3b test = ImageManipulation::hsvToRgb(60, 1, 1);
    //printf("%d %d %d", test[2], test[1], test[0]);

    //octagonDetection
    /**
    cv::VideoCapture stream1(2);   //0 is the id of video device.0 if you have only one camera.

    if (!stream1.isOpened()) { //check if video device has been initialised
    std::cout << "cannot open camera";
    }

    //unconditional loop
    while (true) {
        cv::Mat cameraFrame;
        stream1.read(cameraFrame);
        cv::Mat sizedFrame = ImageManipulation::mirror(ImageManipulation::scale(cameraFrame, 0.2f), 0);
        cv::Mat filteredImage = ImageManipulation::mysobel_filter_xy(sizedFrame);
        int G;
        int counter = 0;
        int min = 100; //helligkeit
        uchar a,b,c,d,e,f,g,h;
        int maxRadius = 0;
        for(int numberOfRows = 1; numberOfRows <= filteredImage.rows-2; numberOfRows++){ // anzahl reihen
            for(int numberOfCols = 1; numberOfCols < filteredImage.cols-2; numberOfCols++){ // anzahl spalten
                if(numberOfRows < floor(filteredImage.rows/2)){
                    if(numberOfRows < numberOfCols){
                        maxRadius = numberOfRows;
                    } else {
                        maxRadius = numberOfCols;
                    }
                } else {
                    if((filteredImage.rows - numberOfRows) < numberOfCols){
                        maxRadius = filteredImage.rows - numberOfRows;
                    } else {
                        maxRadius = numberOfCols;
                    }

                }
                for(int i = 0; i <= maxRadius; i++){ // radius
                    //std::cout << std::to_string(numberOfRows) + " " + std::to_string(numberOfCols) + " " + std::to_string(maxRadius) << std::endl;
                    G = static_cast<int>(round(tan(22.5*(M_PI/180))*i));
                    for(int j = 0; j < G; j++){ // laenge der striche
                        a = filteredImage.at<cv::Vec3b>(numberOfRows+i,numberOfCols+j)[0];
                        b = filteredImage.at<cv::Vec3b>(numberOfRows+i,numberOfCols-j)[0];

                        c = filteredImage.at<cv::Vec3b>(numberOfRows-i,numberOfCols+j)[0];
                        d = filteredImage.at<cv::Vec3b>(numberOfRows-i,numberOfCols-j)[0];

                        e = filteredImage.at<cv::Vec3b>(numberOfRows+j,numberOfCols+i)[0];
                        f = filteredImage.at<cv::Vec3b>(numberOfRows-j,numberOfCols+i)[0];

                        g = filteredImage.at<cv::Vec3b>(numberOfRows+j,numberOfCols-i)[0];
                        h = filteredImage.at<cv::Vec3b>(numberOfRows-j,numberOfCols-i)[0];

                        if(a >= min){
                            counter++;
                        }
                        if(b >= min){
                            counter++;
                        }
                        if(c >= min){
                            counter++;
                        }
                        if(d >= min){
                            counter++;
                        }
                        if(e >= min){
                            counter++;
                        }
                        if(f >= min){
                            counter++;
                        }
                        if(g >= min){
                            counter++;
                        }
                        if(h >= min){
                            counter++;
                        }
                    }
                    if(counter > 20){ //50
                        cv::circle(sizedFrame, cv::Point(numberOfCols, numberOfRows),i,cv::Scalar(0,255,0),1);
                    }
                    counter = 0;
                }
            }
        }
        cv::imshow("cam", sizedFrame);
        //cv::waitKey(0);
        if (cv::waitKey(30) >= 0){
            break;
        }
    }
    **/

    /**
    cv::Mat filteredImage = ImageManipulation::mysobel_filter_xy(inputImage);
    ImageManipulation::showImage(filteredImage, "");
    //############################ PARAMETERS ################################
    int numberOfIgnoredBounds = 10; //ignore X border pixel around the image
    int checkRate = 5; // check sign every X pixel
    int radiusSteps = 5; // radius every X steps
    int min = 100; // greyvalue; every pixel over X is counted
    int min1 = 90;
    int threshold = 20; // min number of pixels which have to be count
    int threshold1 = 0;
    //########################################################################

    int G;
    int counter, counter1 = 0;
    int lastCount, lastCount1 = 0;
    int numberOfRowsCoord, numberOfColsCoord, rad, numberOfRowsCoord1, numberOfColsCoord1, rad1;
    uchar a,b,c,d,e,f,g,h;
    uchar a1,b1,c1,d1; // Vorfahrtsstraße
    int maxRadius = 0;

    int size=100;
    std::list<cv::Point> *listA = new std::list<cv::Point>[size];
    std::list<cv::Point> *listB = new std::list<cv::Point>[size];
    std::list<cv::Point> *listC = new std::list<cv::Point>[size];
    std::list<cv::Point> *listD = new std::list<cv::Point>[size];


    for(int numberOfRows = 1 + numberOfIgnoredBounds; numberOfRows <= filteredImage.rows-2 + numberOfIgnoredBounds*2; numberOfRows += checkRate){ // anzahl reihen
        for(int numberOfCols = 1 + numberOfIgnoredBounds; numberOfCols < filteredImage.cols-2 + numberOfIgnoredBounds*2; numberOfCols += checkRate){ // anzahl spalten

            if(numberOfRows < floor(filteredImage.rows/2) && numberOfCols < floor(filteredImage.cols/2)){ //oben links
                if(numberOfRows < numberOfCols){
                    maxRadius = numberOfRows;
                } else {
                    maxRadius = numberOfCols;
                }
            } else if(numberOfRows < floor(filteredImage.rows/2) && numberOfCols >= floor(filteredImage.cols/2)){ //oben rechts
                if(numberOfRows < (filteredImage.cols - numberOfCols)){
                    maxRadius = numberOfRows;
                } else {
                    maxRadius = filteredImage.cols - numberOfCols;
                }

            } else if(numberOfRows >= floor(filteredImage.rows/2) && numberOfCols < floor(filteredImage.cols/2)){ //unten links
                if((filteredImage.rows - numberOfRows) < numberOfCols){
                    maxRadius = filteredImage.rows - numberOfRows;
                } else {
                    maxRadius = numberOfCols;
                }
            } else if(numberOfRows >= floor(filteredImage.rows/2) && numberOfCols >= floor(filteredImage.cols/2)){ //unten rechts
                if((filteredImage.rows - numberOfRows) < (filteredImage.cols - numberOfCols)){
                    maxRadius = filteredImage.rows - numberOfRows;
                } else {
                    maxRadius = filteredImage.cols - numberOfCols;
                }

            }
            for(int i = 0; i <= maxRadius; i += radiusSteps){ // radius
                //G = static_cast<int>(round(tan(22.5*(M_PI/180))*i));
                //for(int j = 0; j < G; j++){ // laenge der striche
                    listA = ImageManipulation::getLineCoordinates(cv::Point(numberOfRows, numberOfCols+i), cv::Point(numberOfRows+i, numberOfCols)); //unten nach rechts
                    listB = ImageManipulation::getLineCoordinates(cv::Point(numberOfRows-i, numberOfCols), cv::Point(numberOfRows, numberOfCols+i)); //rechts nach oben
                    listC = ImageManipulation::getLineCoordinates(cv::Point(numberOfRows-i, numberOfCols), cv::Point(numberOfRows, numberOfCols-i)); //links nach oben
                    listD = ImageManipulation::getLineCoordinates(cv::Point(numberOfRows, numberOfCols-i), cv::Point(numberOfRows+i, numberOfCols)); //unten links

                    std::list<cv::Point>::iterator it;
                    for (it = listA->begin(); it != listA->end(); ++it){
                        a1 = inputImage.at<cv::Vec3b>(it->x, it->y)[0];
                        if(a1 >= min1){
                            counter1++;
                        }
                    }
                    for (it = listB->begin(); it != listB->end(); ++it){
                        b1 = inputImage.at<cv::Vec3b>(it->x, it->y)[0];
                        if(b1 >= min1){
                            counter1++;
                        }
                    }
                    for (it = listC->begin(); it != listC->end(); ++it){
                        c1 = inputImage.at<cv::Vec3b>(it->x, it->y)[0];
                        if(c1 >= min1){
                            counter1++;
                        }
                    }
                    for (it = listD->begin(); it != listD->end(); ++it){
                        d1 = inputImage.at<cv::Vec3b>(it->x, it->y)[0];
                        if(d1 >= min1){
                            counter1++;
                        }
                    }


                    a = filteredImage.at<cv::Vec3b>(numberOfRows+i,numberOfCols+j)[0];
                    b = filteredImage.at<cv::Vec3b>(numberOfRows+i,numberOfCols-j)[0];

                    c = filteredImage.at<cv::Vec3b>(numberOfRows-i,numberOfCols+j)[0];
                    d = filteredImage.at<cv::Vec3b>(numberOfRows-i,numberOfCols-j)[0];

                    e = filteredImage.at<cv::Vec3b>(numberOfRows+j,numberOfCols+i)[0];
                    f = filteredImage.at<cv::Vec3b>(numberOfRows-j,numberOfCols+i)[0];

                    g = filteredImage.at<cv::Vec3b>(numberOfRows+j,numberOfCols-i)[0];
                    h = filteredImage.at<cv::Vec3b>(numberOfRows-j,numberOfCols-i)[0];


                    if(a >= min){
                        counter++;
                    }
                    if(b >= min){
                        counter++;
                    }
                    if(c >= min){
                        counter++;
                    }
                    if(d >= min){
                        counter++;
                    }
                    if(e >= min){
                        counter++;
                    }
                    if(f >= min){
                        counter++;
                    }
                    if(g >= min){
                        counter++;
                    }
                    if(h >= min){
                        counter++;
                    }


                    if(lastCount1 < counter1 && counter1 > threshold1){
                        numberOfColsCoord1 = numberOfCols;
                        numberOfRowsCoord1 = numberOfRows;
                        rad1 = i;
                        lastCount1 = counter1;
                    }
                    counter1 = 0;
                    counter = 0;
                }

                if(lastCount < counter && counter > threshold){
                    numberOfColsCoord = numberOfCols;
                    numberOfRowsCoord = numberOfRows;
                    rad = i;
                    lastCount = counter;               
                }



            //}
        }
    }
    if(lastCount != 0){
        cv::circle(inputImage, cv::Point(numberOfColsCoord, numberOfRowsCoord),rad,cv::Scalar(0,255,0),1);
    }
    if(lastCount1 != 0){
        cv::circle(inputImage, cv::Point(numberOfColsCoord, numberOfRowsCoord),rad,cv::Scalar(0,255,0),1);
    }

    ImageManipulation::showImage(inputImage, "test");
    **/


    //schraegentest
    /**
    cv::Mat test = cv::Mat::ones(10,10,CV_8UC3);
    int size=100;
    std::list<cv::Point> *list = new std::list<cv::Point>[size];
    list = ImageManipulation::getLineCoordinates(cv::Point(0,5), cv::Point(10,5));
    std::list<cv::Point>::iterator it;
    for (it = list->begin(); it != list->end(); ++it){
        std::cout << std::to_string(it->x) + " " + std::to_string(it->y) << std::endl;
    }
    **/

    SchemeRecognition *scheme = new SchemeRecognition();
    ImageManipulation::showImage(scheme->recognizeScheme(inputImage), "");

    return 0;
}
