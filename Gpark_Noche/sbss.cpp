#include "sbss.h"


sBss::sBss()
{
    //control= NULL;

}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: obtine mascara  movimiento de una imagen

***************************************************************************************************/


/**
 * @brief sBss::sGetSimpleMotionMask
 * @param controlImageGRAY
 * @param currentImage
 * @return
 */

IplImage *sBss::sGetSimpleMotionMask( IplImage *controlImageGRAY,  IplImage *currentImage)
{
    IplImage* GRAY=cvCreateImage(cvGetSize(currentImage), IPL_DEPTH_8U, 1);
    cvSmooth(currentImage, currentImage, CV_MEDIAN,5,5); //smooth the original image using Gaussian kernel
    cvCvtColor( currentImage, GRAY, CV_BGR2GRAY);
    IplImage* sub = cvCreateImage(cvGetSize(currentImage), IPL_DEPTH_8U, 1);
    IplImage* mask=cvCreateImage(cvGetSize(currentImage), IPL_DEPTH_8U, 1);
    cvSub(controlImageGRAY,GRAY,sub);
    cvThreshold(sub,mask,5,255,CV_THRESH_BINARY);
    cvErode(mask,mask,NULL,5);
    cvDilate(mask,mask,NULL,100);
    cvErode(mask,mask,NULL,70);

    cvReleaseImage(&sub);
    cvReleaseImage(&GRAY);

    return mask;
}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: obtine una mascara de los lugares donde esta color entre los umbrales

***************************************************************************************************/


IplImage *sBss::sGetColorMask(IplImage* Binary,int lowerLimitH,int upperLimitH,int lowerLimitS,int upperLimitS,int lowerLimitV,int upperLimitV)

{

    IplImage* imgHSV = cvCreateImage(cvGetSize(Binary), IPL_DEPTH_8U, 3); //imagen para conversion
    IplImage* imgThresh2=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1); //imagen para mascara
    IplImage* temp=cvCreateImage(cvGetSize(imgThresh2),8,1);
    IplImage* temp2=cvCreateImage(cvGetSize(imgThresh2),8,1);
    IplImage* temp3=cvCreateImage(cvGetSize(Binary),8,3);
    temp3=cvCloneImage(Binary);
    cvSmooth(temp3, temp3, CV_GAUSSIAN,3,7); //suavizo la imagen original
    cvCvtColor(temp3, imgHSV, CV_BGR2HSV); //cambio espacio imagen de  BGR a HSV
    cvInRangeS(imgHSV, cvScalar(lowerLimitH,upperLimitH,lowerLimitS), cvScalar(upperLimitS,lowerLimitV,upperLimitV), imgThresh2);//pone en 255 los valores en el umbral
    cvSmooth(imgThresh2, imgThresh2, CV_GAUSSIAN,3,3); //smooth the binary image using Gaussian kernel
    cvMorphologyEx(imgThresh2,temp,NULL,NULL,CV_MOP_GRADIENT,12);
    cvDilate(temp,temp2,NULL,5);


    //libero imagenes
    cvReleaseImage(&imgHSV);
    cvReleaseImage(&temp);
    cvReleaseImage(&temp3);
    cvReleaseImage(&imgThresh2);

    return temp2;

}
