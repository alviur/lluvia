#ifndef SCONTOUR_H
#define SCONTOUR_H
#include "opencv2/opencv.hpp"
#include <stdlib.h>




class sContour
{
public:
	CvSeq *sGetContourn(IplImage *source);
	CvSeq * sGetBC(CvSeq *contorno);
	bool sBandPassC(CvSeq *ce, int minh, int minw, int maxh, int maxw);
	IplImage*  sGetContournImage(CvRect r , IplImage *src);
	CvSeq* sGetContB(IplImage *source);
	IplImage* gSetMaskSeed(IplImage* src, int lowThreshold, int highThreshold, int SetValue, int condition);
	IplImage* gSetMaskSeed2(IplImage* src, int lowThreshold, int highThreshold, int SetValue, int condition);
	IplImage* rotate(IplImage *Ioriginal, int angulo);
	int numcont;
    	sContour();
	~sContour();


    //atributos
	CvMemStorage* tempStorage;
    
        CvSeq* Bc; //apuntador a secuencia auxiliar que guarda temporalmente la direccion de algun contorno
        CvSeq* contorno;//apuntador a secuencia auxiliar que guarda temporalmente los contornos de una imagen 
	double perimetro;//guarda el dato del perimetro de una imagen
	double perimetromax;//guarda el dato del perimetro mas largo
	
};

#endif // SCONTOUR_H
