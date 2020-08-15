#include "imagemanipulation.h"

cv::Mat ImageManipulation::transpose(cv::Mat image){
    cv::Mat transposedImage = cv::Mat::ones(image.cols,image.rows,CV_8UC3);

    for(int i=0; i<image.rows; i++){
        for (int j=0; j<image.cols; j++){
            transposedImage.at<cv::Vec3b>(cv::Point(i,j)) = image.at<cv::Vec3b>(cv::Point(j,i));
        }
    }
    return transposedImage;
}

cv::Mat ImageManipulation::reverse(cv::Mat image){ //reverse a matrix -> mirror effect on an image
    for(int j = 0; j < image.rows; j++){
        for(int i = 0; i < image.cols/2; i++) {
            cv::Vec3b temp = image.at<cv::Vec3b>(cv::Point(i,j));
            image.at<cv::Vec3b>(cv::Point(i,j)) = image.at<cv::Vec3b>(cv::Point(image.cols - i - 1, j));
            image.at<cv::Vec3b>(cv::Point(image.cols - i - 1, j)) = temp;
        }
    }
    return image;
}

cv::Mat ImageManipulation::rotate(cv::Mat image, int degree){
    if(degree == 90){
        return reverse(transpose(image));
    } else if(degree == 180){
        return reverse(transpose(reverse(transpose(image))));
    } else if(degree == 270){
        return transpose(reverse(image));
    } else {
        std::cout << "No valid degrees!" << std::endl;
        return image;
    }
}

cv::Mat ImageManipulation::mirror(cv::Mat image, int axe){
    if(axe==0){
        //vertical mirror
        return ImageManipulation::reverse(image);
    } else if(axe == 1){
        //horizontal mirror
        cv::Mat rotationImage= ImageManipulation::rotate(image, 180);
        return ImageManipulation::reverse(rotationImage);
    } else if(axe == 2){
        cv::Mat verticalMirror = ImageManipulation::reverse(image);
        cv::Mat rotationImage= ImageManipulation::rotate(verticalMirror, 180);
        return ImageManipulation::reverse(rotationImage);
    } else {
        return image;
    }
}

cv::Mat ImageManipulation::scale(cv::Mat image, float factor){ //nearest-neighbor interpolation
    float newCols = image.cols * factor;
    float newRows = image.rows * factor;

    float xRatio = image.cols / newCols;
    float yRatio = image.rows / newRows;

    cv::Mat resizedImage = cv::Mat::ones(static_cast<int>(newRows), static_cast<int>(newCols), CV_8UC3);

    int px, py;
    for (int i = 0; i < newCols; i++) {
        for (int j = 0; j < newRows; j++) {
            px = static_cast<int>(floor(i * xRatio));
            py = static_cast<int>(floor(j * yRatio));

            resizedImage.at<cv::Vec3b>(cv::Point(static_cast<int>(i), static_cast<int>(j))) = image.at<cv::Vec3b>(cv::Point(static_cast<int>(px),static_cast<int>(py)));
        }
    }
    return resizedImage;
}

cv::Mat ImageManipulation::mymean_filter(cv::Mat image, int intensity){
    if(intensity%2 != 0){
        int tmpR, tmpG, tmpB = 0;
        uchar meanValueR, meanValueG, meanValueB;
        cv::Mat meanImage = cv::Mat::ones(image.rows - (intensity-1), image.cols - (intensity-1), CV_8UC3);
        int rand = (intensity-1)/2;

        for(int i = rand; i<image.rows-rand; i++){
            for(int j = rand; j<image.cols-rand; j++){

                for(int k = -rand; k<=rand; k++){
                    for(int l = -rand; l<=rand; l++){
                        tmpR += static_cast<int>(image.at<cv::Vec3b>(i + l, j + k)[2]);
                        tmpG += static_cast<int>(image.at<cv::Vec3b>(i + l, j + k)[1]);
                        tmpB += static_cast<int>(image.at<cv::Vec3b>(i + l, j + k)[0]);
                    }
                }
                meanValueR = static_cast<uchar>(round(tmpR/(intensity*intensity)));
                meanValueG = static_cast<uchar>(round(tmpG/(intensity*intensity)));
                meanValueB = static_cast<uchar>(round(tmpB/(intensity*intensity)));
                meanImage.at<cv::Vec3b>(i-rand,j-rand) = cv::Vec3b(meanValueB, meanValueG, meanValueR);
                tmpR = tmpG = tmpB = 0;
            }
        }
        return meanImage;
    } else {
        std::cout << "only odd numbers allowed for intensity" << std::endl;
    }
}

cv::Mat ImageManipulation::mygauss_filter(cv::Mat image){
    int gauss_mask[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
    int tmpR, tmpG, tmpB = 0;
    int counter = 0;
    uchar gaussValueR, gaussValueG, gaussValueB;
    cv::Mat gaussImage = cv::Mat::ones(image.rows-2,image.cols-2,CV_8UC3);
    for(int i = 1; i<image.rows-1; i++){
        for(int j = 1; j<image.cols-1; j++){

            for(int k = i-1; k<i+2; k++){
                for(int l = j-1; l<j+2; l++){
                    tmpR += static_cast<int>(gauss_mask[counter]) * static_cast<int>(image.at<cv::Vec3b>(k,l)[2]);
                    tmpG += static_cast<int>(gauss_mask[counter]) * static_cast<int>(image.at<cv::Vec3b>(k,l)[1]);
                    tmpB += static_cast<int>(gauss_mask[counter]) * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    counter++;
                }
            }
            gaussValueR = static_cast<uchar>(tmpR/16);
            gaussValueG = static_cast<uchar>(tmpG/16);
            gaussValueB = static_cast<uchar>(tmpB/16);
            gaussImage.at<cv::Vec3b>(i-1,j-1) = cv::Vec3b(gaussValueB, gaussValueG, gaussValueR);
            tmpR = tmpG = tmpB = 0;
            counter = 0;
        }
    }
    return gaussImage;
}

cv::Mat ImageManipulation::mysobel_filter_x_signed(cv::Mat image){
    if(ImageManipulation::isGreyImage(image) == 0){
        image = ImageManipulation::toGreyscaleByLuminosity(image);
    }
    int gauss_mask[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int tmp = 0;
    int counter = 0;
    cv::Mat sobelImage = cv::Mat::ones(image.rows-2,image.cols-2,CV_8UC3);
    uchar gaussValue;
    for(int i = 1; i<image.rows-1; i++){
        for(int j = 1; j<image.cols-1; j++){

            for(int k = i-1; k<i+2; k++){
                for(int l = j-1; l<j+2; l++){
                    tmp += gauss_mask[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    counter++;
                }
            }
            gaussValue = static_cast<uchar>(255.0/2048.0*(tmp+1024));
            sobelImage.at<cv::Vec3b>(i-1,j-1) = cv::Vec3b(gaussValue, gaussValue, gaussValue);
            tmp = 0;
            counter = 0;
        }
    }
    return sobelImage;
}

cv::Mat ImageManipulation::mysobel_filter_y_signed(cv::Mat image){
    if(ImageManipulation::isGreyImage(image) == 0){
        image = ImageManipulation::toGreyscaleByLuminosity(image);
    }
    int gauss_mask[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int tmp = 0;
    int counter = 0;
    uchar sobelValue;
    cv::Mat sobelImage = cv::Mat::ones(image.rows-2,image.cols-2,CV_8UC3);
    for(int i = 1; i<image.rows-1; i++){
        for(int j = 1; j<image.cols-1; j++){

            for(int k = i-1; k<i+2; k++){
                for(int l = j-1; l<j+2; l++){
                    tmp += gauss_mask[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    counter++;
                }
            }
            sobelValue = static_cast<uchar>(255.0/2048.0*(tmp+1024));
            sobelImage.at<cv::Vec3b>(i-1,j-1) = cv::Vec3b(sobelValue, sobelValue, sobelValue);
            tmp = 0;
            counter = 0;
        }
    }
    return sobelImage;
}

cv::Mat ImageManipulation::mysobel_filter_xy(cv::Mat image){
    if(ImageManipulation::isGreyImage(image) == 0){
        image = ImageManipulation::toGreyscaleByLuminosity(image);
    }
    int gauss_mask_x[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int gauss_mask_y[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int tmpX = 0;
    int tmpY = 0;
    int counter = 0;
    uchar sobelValue;
    cv::Mat sobelImage = cv::Mat::ones(image.rows-2,image.cols-2,CV_8UC3);
    for(int i = 1; i<image.rows-1; i++){
        for(int j = 1; j<image.cols-1; j++){

            for(int k = i-1; k<i+2; k++){
                for(int l = j-1; l<j+2; l++){
                    tmpX += gauss_mask_x[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    tmpY += gauss_mask_y[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    counter++;
                }
            }
            sobelValue = static_cast<uchar>(255.0/1449.0*sqrt(tmpX*tmpX+tmpY*tmpY));
            sobelImage.at<cv::Vec3b>(i-1,j-1) = cv::Vec3b(sobelValue, sobelValue, sobelValue);
            tmpX = 0;
            tmpY = 0;
            counter = 0;
        }
    }
    return sobelImage;
}

cv::Mat ImageManipulation::mysobel_filter_gradient(cv::Mat image){
    if(ImageManipulation::isGreyImage(image) == 0){
        image = ImageManipulation::toGreyscaleByLuminosity(image);
    }
    int gauss_mask_x[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int gauss_mask_y[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int tmpX = 0;
    int tmpY = 0;
    int counter = 0;
    int angle;
    cv::Mat sobelImage = cv::Mat::ones(image.rows-2,image.cols-2,CV_8UC3);
    for(int i = 1; i<image.rows-1; i++){
        for(int j = 1; j<image.cols-1; j++){

            for(int k = i-1; k<i+2; k++){
                for(int l = j-1; l<j+2; l++){
                    tmpX += gauss_mask_x[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    tmpY += gauss_mask_y[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    counter++;
                }
            }
            angle = static_cast<int>(floor(atan2(tmpY,tmpX)*(180/M_PI)));
            std::cout << angle << std::endl;
            sobelImage.at<cv::Vec3b>(i-1,j-1) = cv::Vec3b(ImageManipulation::hsvToRgb(angle, 1.0, 1.0));
            tmpX = 0;
            tmpY = 0;
            counter = 0;
        }
    }
    return sobelImage;
}


cv::Mat ImageManipulation::mylaplace_filter(cv::Mat image){
    if(ImageManipulation::isGreyImage(image) == 0){
        image = ImageManipulation::toGreyscaleByLuminosity(image);
    }
    int gauss_mask[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int tmp = 0;
    int counter = 0;

    uchar filteredValue;

    cv::Mat laplaceImage = cv::Mat::ones(image.rows-2,image.cols-2,CV_8UC3);
    for(int i = 1; i<image.rows-1; i++){
        for(int j = 1; j<image.cols-1; j++){

            for(int k = i-1; k<i+2; k++){
                for(int l = j-1; l<j+2; l++){
                    tmp += gauss_mask[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    counter++;
                }
            }
            filteredValue = static_cast<uchar>(255.0/2048.0*(tmp+1024));
            laplaceImage.at<cv::Vec3b>(i-1,j-1) = cv::Vec3b(filteredValue, filteredValue, filteredValue);
            tmp = 0;
            counter = 0;
        }
    }
    return laplaceImage;
}

void ImageManipulation::myLaplacePyramide(cv::Mat image){
    ulong numberOfImages = 1;
    std::vector<cv::Mat> sol(numberOfImages);
    sol[0] = image;

    for(ulong i = 1; i<(numberOfImages)+1; i++){
        sol[i] = ImageManipulation::mylaplace_filter(sol[i-1]);
        //sol[i] = ImageManipulation::scale(sol[i], 0.5f);
        cv::namedWindow(std::to_string(i), CV_WINDOW_AUTOSIZE);
        cv::imshow(std::to_string(i), sol[i]);
        //ImageManipulation::showImage(test, std::to_string(i));
    }
    cv::waitKey(0);
}

cv::Mat ImageManipulation::linearScaling(cv::Mat image, int c1, float c2){
    cv::Mat linearScaleImage = cv::Mat::ones(image.rows, image.cols, CV_8UC3);
    int linearScaleFunctionR, linearScaleFunctionG, linearScaleFunctionB, linearScaleFunctionMean;

    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){

            linearScaleFunctionR = static_cast<int>((c2*image.at<cv::Vec3b>(j,i)[2])+c1*c2);
            linearScaleFunctionG = static_cast<int>((c2*image.at<cv::Vec3b>(j,i)[1])+c1*c2);
            linearScaleFunctionB = static_cast<int>((c2*image.at<cv::Vec3b>(j,i)[0])+c1*c2);
            linearScaleFunctionMean = (linearScaleFunctionB + linearScaleFunctionG + linearScaleFunctionR)/3;

            if(linearScaleFunctionMean>=0 && linearScaleFunctionMean<=255){
                linearScaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(static_cast<uchar>(linearScaleFunctionB), static_cast<uchar>(linearScaleFunctionG), static_cast<uchar>(linearScaleFunctionR));
            } else if(linearScaleFunctionMean>255){
                linearScaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(255, 255, 255);
            } else {
                linearScaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(0, 0, 0);
            }
        }
    }
return linearScaleImage;
}

cv::Mat ImageManipulation::equidensities(cv::Mat image, int equiOrder, float mean){
    int pixelValueR, pixelValueG, pixelValueB, pixelValueMean;
    if(equiOrder==1){
        cv::Mat equidensitiesImage = cv::Mat::ones(image.rows, image.cols, CV_8UC3);
        uchar equidensitiesValues;
        for(int i = 0; i < image.cols; i++){
            for(int j = 0; j < image.rows; j++){
                pixelValueR = image.at<cv::Vec3b>(j,i)[2];
                pixelValueG = image.at<cv::Vec3b>(j,i)[1];
                pixelValueB = image.at<cv::Vec3b>(j,i)[0];
                pixelValueMean = (pixelValueR + pixelValueG + pixelValueB)/3;

                if(pixelValueMean>=0 && pixelValueMean<=63){
                    equidensitiesImage.at<cv::Vec3b>(j,i) = cv::Vec3b(32, 32, 32);
                } else if(pixelValueMean>=64 && pixelValueMean<=127){
                    equidensitiesValues = static_cast<uchar>(mean);
                    equidensitiesImage.at<cv::Vec3b>(j,i) = cv::Vec3b(equidensitiesValues, equidensitiesValues, equidensitiesValues);
                } else {
                    equidensitiesImage.at<cv::Vec3b>(j,i) = cv::Vec3b(255, 255, 255);
                }
            }
        }
        return equidensitiesImage;
    } else {
        cv::Mat equidensitiesImageSecondOrder = cv::Mat::ones(image.rows+2, image.cols+2, CV_8UC3);
        for(int i = 1; i < image.cols-1; i++){
            for(int j = 1; j < image.rows-1; j++){
                pixelValueR = 4 * image.at<cv::Vec3b>(j,i)[2] - image.at<cv::Vec3b>(j,i-1)[2] - image.at<cv::Vec3b>(j,i+1)[2] - image.at<cv::Vec3b>(j-1,i)[2] - image.at<cv::Vec3b>(j+1,i)[2];
                pixelValueG = 4 * image.at<cv::Vec3b>(j,i)[1] - image.at<cv::Vec3b>(j,i-1)[1] - image.at<cv::Vec3b>(j,i+1)[1] - image.at<cv::Vec3b>(j-1,i)[1] - image.at<cv::Vec3b>(j+1,i)[1];
                pixelValueB = 4 * image.at<cv::Vec3b>(j,i)[0] - image.at<cv::Vec3b>(j,i-1)[0] - image.at<cv::Vec3b>(j,i+1)[0] - image.at<cv::Vec3b>(j-1,i)[0] - image.at<cv::Vec3b>(j+1,i)[0];
                pixelValueMean = (pixelValueR + pixelValueG + pixelValueB)/3;

                if(pixelValueMean>=0 && pixelValueMean<=127){
                    equidensitiesImageSecondOrder.at<cv::Vec3b>(j,i) = cv::Vec3b(255, 255, 255);
                } else {
                    equidensitiesImageSecondOrder.at<cv::Vec3b>(j,i) = cv::Vec3b(0, 0, 0);
                }
            }
        }
        return equidensitiesImageSecondOrder;
    }
}

//cv::Mat ImageManipulation::createPixelBorder(cv::Mat image){
//    cv::Mat imageWithBorder = cv::Mat::ones(image.rows+2, image.cols+2, CV_8U);
//
//    for(int i = 0; i < image.cols; i++){
//        for(int j = 0; j < image.rows; j++){
//            imageWithBorder.at<uchar>(j+1,i+1) = image.at<uchar>(j,i);
//        }
//    }
//    return imageWithBorder;
//}

/**
cv::Mat ImageManipulation::createPixelMirrorBorder(cv::Mat image){
    cv::Mat imageWithBorder = cv::Mat::ones(image.rows+2, image.cols+2, CV_8U);

    //copy original image in the middle of the new image
    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            imageWithBorder.at<uchar>(j+1,i+1) = image.at<uchar>(j,i);
        }
    }

    //horizontal borders
    for(int i = 0; i < image.cols; i++){
        imageWithBorder.at<uchar>(0,i+1) = image.at<uchar>(0,i);
        imageWithBorder.at<uchar>(image.rows+1,i+1) = image.at<uchar>(image.rows-1,i);
    }

    //vertical borders
    for(int i = 0; i < image.rows; i++){
        imageWithBorder.at<uchar>(i+1,0) = image.at<uchar>(i,0);
        imageWithBorder.at<uchar>(i+1,image.cols+1) = image.at<uchar>(i, image.cols-1);
    }

    //corners
    imageWithBorder.at<uchar>(0, 0) = image.at<uchar>(0, 0); //top left
    imageWithBorder.at<uchar>(0, image.cols+1) = image.at<uchar>(0, image.cols-1); //top right
    imageWithBorder.at<uchar>(image.rows+1,image.cols+1) = image.at<uchar>(image.rows-1, image.cols-1); //bottom right
    imageWithBorder.at<uchar>(image.rows+1,0) = image.at<uchar>(image.rows-1, 0); //bottom left

    return imageWithBorder;
}

cv::Mat ImageManipulation::deletePixelBorder(cv::Mat image){
    cv::Mat imageWithoutBorder = cv::Mat::ones(image.rows-2, image.cols-2, CV_8U);

    for(int i = 0; i < imageWithoutBorder.cols; i++){
        for(int j = 0; j < imageWithoutBorder.rows; j++){
            imageWithoutBorder.at<uchar>(j,i) = image.at<uchar>(j+1,i+1);
        }
    }
    return imageWithoutBorder;
}
**/

cv::Mat ImageManipulation::toGreyscaleByLightness(cv::Mat image){
    cv::Mat greyscaleImage = cv::Mat::ones(image.rows, image.cols, CV_8UC3);

    int max = 0;
    int min = 0;

    uchar greyValue;

    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            if(image.at<cv::Vec3b>(j,i)[0]>image.at<cv::Vec3b>(j,i)[1]){
                if(image.at<cv::Vec3b>(j,i)[0]>image.at<cv::Vec3b>(j,i)[2]){
                    max = image.at<cv::Vec3b>(j,i)[0];
                } else {
                    max = image.at<cv::Vec3b>(j,i)[2];
                }
            } else if(image.at<cv::Vec3b>(j,i)[1]>image.at<cv::Vec3b>(j,i)[2]){
                max = image.at<cv::Vec3b>(j,i)[1];
            } else {
                max = image.at<cv::Vec3b>(j,i)[2];
            }

            if(image.at<cv::Vec3b>(j,i)[0]<image.at<cv::Vec3b>(j,i)[1]){
                if(image.at<cv::Vec3b>(j,i)[0]<image.at<cv::Vec3b>(j,i)[2]){
                    min = image.at<cv::Vec3b>(j,i)[0];
                } else {
                    min = image.at<cv::Vec3b>(j,i)[2];
                }
            } else if(image.at<cv::Vec3b>(j,i)[1]<image.at<cv::Vec3b>(j,i)[2]){
                min = image.at<cv::Vec3b>(j,i)[1];
            } else {
                min = image.at<cv::Vec3b>(j,i)[2];
            }
            greyValue = static_cast<uchar>((max+min)/2);
            greyscaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(greyValue, greyValue, greyValue);
        }
    }
    return greyscaleImage;
}

cv::Mat ImageManipulation::toGreyscaleByAverage(cv::Mat image){
    cv::Mat greyscaleImage = cv::Mat::ones(image.rows, image.cols, CV_8UC3);
    uchar greyValue;
    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            greyValue = (image.at<cv::Vec3b>(j,i)[0]+image.at<cv::Vec3b>(j,i)[1]+image.at<cv::Vec3b>(j,i)[2])/3;
            greyscaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(greyValue, greyValue, greyValue);
        }
    }
    return greyscaleImage;
}

cv::Mat ImageManipulation::toGreyscaleByLuminosity(cv::Mat image){
    cv::Mat greyscaleImage = cv::Mat::ones(image.rows, image.cols, CV_8UC3);
    uchar greyValue;
    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            greyValue = static_cast<uchar>(0.07*image.at<cv::Vec3b>(j,i)[0]+0.72*image.at<cv::Vec3b>(j,i)[1]+0.21*image.at<cv::Vec3b>(j,i)[2]);
            greyscaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(greyValue, greyValue, greyValue);
        }
    }
    return greyscaleImage;
}

cv::Mat ImageManipulation::toGreyscaleByOpenCV(cv::Mat image){
    cv::Mat greyscaleImage = cv::Mat::ones(image.rows, image.cols, CV_8UC3);
    uchar greyValue;
    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            greyValue = static_cast<uchar>(0.114*image.at<cv::Vec3b>(j,i)[0]+0.587*image.at<cv::Vec3b>(j,i)[1]+0.229*image.at<cv::Vec3b>(j,i)[2]);
            greyscaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(greyValue, greyValue, greyValue);
        }
    }
    return greyscaleImage;
}

bool ImageManipulation::isGreyImage(cv::Mat image){
    for(int i=0; i<image.rows; i++){
        for (int j=0; j<image.cols; j++){
            if((static_cast<int>(image.at<cv::Vec3b>(i,j)[0]) != static_cast<int>(image.at<cv::Vec3b>(i,j)[1]) || static_cast<int>(image.at<cv::Vec3b>(i,j)[1]) != static_cast<int>(image.at<cv::Vec3b>(i,j)[2]))){
                return false;
            }
        }
    }
    return true;
}

void ImageManipulation::showImage(cv::Mat image, std::string text){
    cv::namedWindow(text, CV_WINDOW_AUTOSIZE);
    cv::imshow(text, image);
    cv::waitKey(0);
}

cv::Mat ImageManipulation::readImage(std::string path){
    cv::Mat inputImage = cv::imread(path);

    if(inputImage.empty()){
        std::cout << "Input Image is empty" << std::endl;
    }
    return inputImage;
}

cv::Vec3b ImageManipulation::hsvToRgb(int hue, float saturation, float value){
    int h = static_cast<int>(floor(hue/60));
    float f = (hue/60) - h;

    uchar p = static_cast<uchar>(round((value * (1 - saturation))*255));
    uchar q = static_cast<uchar>(round((value * (1 - saturation * f))*255));
    uchar t = static_cast<uchar>(round((value * (1 - saturation * (1 - f)))*255));
    uchar valueUchar = static_cast<uchar>(round(value * 255));
    cv::Vec3b bgr;
    if(h == 0 || h == 6){
        bgr = cv::Vec3b(p, t, valueUchar);
    } else if(h == 1){
        bgr = cv::Vec3b(p, valueUchar, q);
    } else if(h == 2){
        bgr = cv::Vec3b(t, valueUchar, p);
    } else if(h == 3){
        bgr = cv::Vec3b(valueUchar, q, p);
    } else if(h == 4){
        bgr = cv::Vec3b(valueUchar, p, t);
    } else if(h == 5){
        bgr = cv::Vec3b(q, p, valueUchar);
    }
    return bgr;
}

cv::Vec3b ImageManipulation::angleToRgb(float angle){

}

std::list<cv::Point>* ImageManipulation::getLineCoordinates(cv::Point start, cv::Point end){
    int x1 = start.x;
    int y1 = start.y;

    int x2 = end.x;
    int y2 = end.y;

    int size = 100;
    int y;
    std::list<cv::Point> *list = new std::list<cv::Point>[size];
    int dx = x2 - x1;
    int dy = y2 - y1;
    for(int x = x1; x<x2; x++){
      y = y1 + dy * (x - x1) / dx;
      list->push_back(cv::Point(x, y));
    }
    return list;
}
