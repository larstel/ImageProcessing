#include "imagecalculation.h"

float ImageCalculation::getMean(cv::Mat image){
    float mean = 0;
    std::map<int, int> numberOfGreyvalues = getNumberOfGreyvalues(image);

    for(int i = 0; i < 256; i++){
        mean += numberOfGreyvalues[i]*i;
    }

    mean = mean/getNumberOfPixel(image);
    return mean;
}

float ImageCalculation::getStandardDeviation(cv::Mat image){
    float standardDeviation = 0;
    float mean = getMean(image);

    std::map<int, int> numberOfGreyvalues = ImageCalculation::getNumberOfGreyvalues(image);

    for(int i = 0; i < 256; i++){
        for(int j = 0; j < numberOfGreyvalues[i]; j++){
            standardDeviation += pow(i-mean, 2);
        }
    }

    standardDeviation = sqrt(standardDeviation/getNumberOfPixel(image));
    return standardDeviation;
}

float ImageCalculation::getEntropy(cv::Mat image){
    float entropy = 0;
    std::map<int, int> numberOfGreyvalues = ImageCalculation::getNumberOfGreyvalues(image);

    for(int k = 0; k < 256; k++){
        if(numberOfGreyvalues[k]!=0){
            entropy += (static_cast<float>(numberOfGreyvalues[k])/static_cast<float>(getNumberOfPixel(image)))*log2(numberOfGreyvalues[k]/static_cast<float>(getNumberOfPixel(image)));
        }
    }

    entropy = entropy*-1;
    return entropy;
}

std::map<int, int> ImageCalculation::getNumberOfGreyvalues(cv::Mat image){
    std::map<int, int> numberOfGreyvalues;

    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            numberOfGreyvalues[static_cast<int>(image.at<uchar>(j,i))] = numberOfGreyvalues[static_cast<int>(image.at<uchar>(j,i))]+1;
        }
    }

    return numberOfGreyvalues;
}

uint ImageCalculation::getNumberOfPixel(cv::Mat image){
    return static_cast<uint>(image.rows*image.cols);
}

void ImageCalculation::showHistogram(cv::Mat image){
    std::map<int, int> histogram_values = ImageCalculation::getNumberOfGreyvalues(image);

    int graphScale = 5;

    cv::Mat graph = cv::Mat::ones(100*graphScale,256*graphScale,CV_8UC3);
    for(int k = 0; k < 256; k++){
        cv::line(graph, cv::Point2d(k*graphScale,0), cv::Point2d(k*graphScale,histogram_values[k]/50*graphScale),cv::Scalar(0,255,0),graphScale/2);
    }

    ImageManipulation::showImage(ImageManipulation::mirror(ImageManipulation::rotate(graph, 180), 0),"histogram");
}

void ImageCalculation::showSumFrequency(cv::Mat image){
    std::map<int, int> histogram_values = ImageCalculation::getNumberOfGreyvalues(image);
    std::map<int, float> sumFrequencyValues;

    for(int i = 0; i < 256; i++){
        sumFrequencyValues[i] += histogram_values[i]/static_cast<float>(getNumberOfPixel(image));
        std::cout << sumFrequencyValues[i] << std::endl;
    }

    float addi = 0;
    for(int j = 0; j < 256; j++){
        addi += sumFrequencyValues[j];
    }
    std::cout << addi << std::endl;

    int graphScale = 5;

    float lastPoint = 0.0;

    cv::Mat graph = cv::Mat::ones(100*graphScale,256*graphScale,CV_8UC3);
    for(int k = 0; k < 256; k++){
        cv::line(graph, cv::Point2d(k*graphScale,lastPoint*graphScale*50), cv::Point2d(k*graphScale,(sumFrequencyValues[k]/50*graphScale)+(lastPoint*graphScale*50)),cv::Scalar(0,255,0),graphScale/2);
        lastPoint += sumFrequencyValues[k];
    }

    ImageManipulation::showImage(ImageManipulation::mirror(ImageManipulation::rotate(graph, 180), 0),"histogram");
}
