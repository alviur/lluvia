#ifndef SIMAGE_H
#define SIMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opencv2/opencv.hpp"

using namespace std;
class sImage
{
public:
    sImage(const char *_path, int _chanels);//constructor para una IplImage que carga una imagen con un path definido
    sImage(CvSize size, int depth, int channels);//constructor para el molde de una IplImage 
    ~sImage();//destructor
    string sGetPath();//retorna la ruta donde se encuentra alojada la imagen
    int* sWho(IplImage* src);//retorna el tamaño, la profundidad y canales de una imagen

    int chanels;//numero de canales de la imagen
    IplImage* img;// IplImage que contiene la imagen
    int deph;//profundidad de la imagen
    string path;//path de la imagen 

};

#endif // SIMAGE_H
