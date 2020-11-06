#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;

/* fonction negatif*/

void negatif(const cv::Mat &img, cv::Mat &imgOUT)
{
    imgOUT.create(img.size(), CV_32F);
    for (int i=0; i<img.rows; i++)
        for (int j=0; j<img.cols; j++)
            imgOUT.at<float>(i,j)=255-img.at<float>(i,j);
}

/* fonction binarisation*/

void binarisation(const float &seuil, const cv::Mat &img, cv::Mat &imgOUT)
{
    imgOUT.create(img.size(), CV_32F);
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            if(img.at<float>(i,j) < seuil){
                imgOUT.at<float>(i,j) = 0;
            }
            else{
                imgOUT.at<float>(i,j) = 255;
            }
        }
    }
}

/* fonction convolution*/

void convolution(const cv::Mat &filtre, const cv::Mat &img, cv::Mat &imgOUT, const bool padding)
{
    imgOUT.create(img.size(), CV_32F);
    // prendre la taille du filtre
    int f;
    f = filtre.rows;
    // calcul de courrone
    int couronne;
    couronne = (f-1)/2;

    float conv;

    if(padding==false)
    {
        // copier les valeurs d'image origin a image sorti
        imgOUT = img.clone();
        for(int i=couronne; i<img.rows-couronne; i++)
        {
            for(int j=couronne; j<img.cols-couronne; j++)
            {
                conv = 0.0;
                for(int r=0; r<f; r++)
                {
                    for(int c=0; c<f; c++)
                    {
                        conv += img.at<float>(i-couronne+r, j-couronne+c)*filtre.at<float>(r,c);
                        imgOUT.at<float>(i,j) = conv;
                    }
                }
            }
        }

    }
    else
    {
        cout << "je ne sais pas encore";
    }
}

void normGradient(const cv::Mat &imgX, const cv::Mat &imgY, cv::Mat &imgOUT)
{
    imgOUT.create(imgX.size(), CV_32F);
    for (int i=0; i<imgX.rows; i++)
        for (int j=0; j<imgX.cols; j++)
            imgOUT.at<float>(i,j)=sqrt(imgX.at<float>(i,j)*imgX.at<float>(i,j)+imgY.at<float>(i,j)*imgY.at<float>(i,j));
}

int main(int argc, const char** argv)
{
    /* Pour des question de partie 3*/
//    cv::Mat img,imgOUT;
//    cv::Mat filtre_H1, filtre_H2, filtre_H3;
//
//    // creer filtre moyen H1
//    filtre_H1.create(3, 3, CV_32F);
//    filtre_H1.setTo(1.);
//    filtre_H1 *= 1.0/9;
//
//    // creer filtre moyen H2
//    filtre_H2.create(3, 3, CV_32F);
//    filtre_H2.setTo(1.);
//    filtre_H2 *= 1.0/10;
//    filtre_H2.at<float>(1,1) *= 2;
//
//    // creer filtre moyen H3
//    filtre_H3.create(5, 5, CV_32F);
//    filtre_H3.setTo(1.);
//    filtre_H3 *= 1.0/42;
//    filtre_H3.at<float>(1,2) *=4;
//    filtre_H3.at<float>(2,1) *=4;
//    filtre_H3.at<float>(3,2) *=4;
//    filtre_H3.at<float>(2,3) *=4;
//    filtre_H3.at<float>(2,2) *=6;
//
//
//    // Reads image in grayscale
//    img = cv::imread("./images/brain.jpg", cv::IMREAD_GRAYSCALE);
//    if (img.data==NULL)
//    {
//        cout<<"Cannot open ./images/brain.jpg"<<endl;
//        return -1;
//    }
//
//        // Displays the image in a new window and waits for user key press
//    cv::imshow("Initial image", img);
//    cv::waitKey();
//
//        // real value conversion
//    img.convertTo(img, CV_32F);
//    //negatif(img,imgOUT);
//    //binarisation(128, img,imgOUT);
//    convolution(filtre_H3, img, imgOUT,false);
//        // Normalization before display
//    imgOUT/=255.0;
//
//    cv::imshow("filtre moyen H3", imgOUT);
//    cv::waitKey();




    /*Pour des question de partie 3*/
    cv::Mat img, imgOUTX, imgOUTY, imgOUT;
    cv::Mat filtre_SoX, filtre_SoY;

    // Creer filtre sobel Hx

    filtre_SoX.create(3,3, CV_32F);
    filtre_SoX.at<float>(0,0) = -1;
    filtre_SoX.at<float>(0,1) = 0;
    filtre_SoX.at<float>(0,2) = 1;
    filtre_SoX.at<float>(1,0) = -2;
    filtre_SoX.at<float>(1,1) = 0;
    filtre_SoX.at<float>(1,2) = 2;
    filtre_SoX.at<float>(2,0) = -1;
    filtre_SoX.at<float>(2,1) = 0;
    filtre_SoX.at<float>(2,2) = 1;

    // Creer filtre sobel Hy
    filtre_SoY.create(3,3, CV_32F);
    filtre_SoY.at<float>(0,0) = 1;
    filtre_SoY.at<float>(0,1) = 2;
    filtre_SoY.at<float>(0,2) = 1;
    filtre_SoY.at<float>(1,0) = 0;
    filtre_SoY.at<float>(1,1) = 0;
    filtre_SoY.at<float>(1,2) = 0;
    filtre_SoY.at<float>(2,0) = -1;
    filtre_SoY.at<float>(2,1) = -2;
    filtre_SoY.at<float>(2,2) = -1;

    cv::Mat filtre_H1, filtre_H2, filtre_H3;

    // creer filtre moyen H1
    filtre_H1.create(3, 3, CV_32F);
    filtre_H1.setTo(1.);
    filtre_H1 *= 1.0/9;

    // creer filtre moyen H2
    filtre_H2.create(3, 3, CV_32F);
    filtre_H2.setTo(1.);
    filtre_H2 *= 1.0/10;
    filtre_H2.at<float>(1,1) *= 2;

    // creer filtre moyen H3
    filtre_H3.create(5, 5, CV_32F);
    filtre_H3.setTo(1.);
    filtre_H3 *= 1.0/42;
    filtre_H3.at<float>(1,2) *=4;
    filtre_H3.at<float>(2,1) *=4;
    filtre_H3.at<float>(3,2) *=4;
    filtre_H3.at<float>(2,3) *=4;
    filtre_H3.at<float>(2,2) *=6;

        // Reads image in grayscale
    img = cv::imread("./images/brain.jpg", cv::IMREAD_GRAYSCALE);
    if (img.data==NULL)
    {
        cout<<"Cannot open ./images/brain.jpg"<<endl;
        return -1;
    }

        // Displays the image in a new window and waits for user key press
    cv::imshow("Initial image", img);
    cv::waitKey();

        // real value conversion
    img.convertTo(img, CV_32F);

    convolution(filtre_H3, img, img, false);
    convolution(filtre_SoX, img, imgOUTX,false);
    convolution(filtre_SoY, img, imgOUTY,false);
    normGradient(imgOUTX, imgOUTY, imgOUT);
    binarisation(64, imgOUT, imgOUT);
        // Normalization before display
    imgOUT/=255.0;

    cv::imshow("norm gradient/binarisation", imgOUT);
    cv::waitKey();

    return 0;
}
