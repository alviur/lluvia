#include "simage.h"
#include<stdio.h>


  //constructor para el molde de una IplImage 

sImage::sImage(const char* _path,int _chanels)//constructor para una IplImage que carga una imagen con un path definido
{
    img = cvLoadImage(_path,_chanels);
    path=_path;
    chanels=_chanels;
}

sImage::sImage(CvSize size, int depth, int channels)//constructor para el molde de una IplImage 
{
    img= cvCreateImage( size,  depth, channels);
}

string sImage::sGetPath()//retorna la ruta donde se encuentra alojada la imagen
{
    return path;
}

int *sImage::sWho(IplImage *src)//retorna el tamaño, la profundidad y canales de una imagen
{
    int datos[4];
    datos[0]=img->height;//asigna la longitud vertical de la imagen
    datos[1]=img->width;//asigna la longitud horizontal de la imagen
    datos[2]=img->depth;//asigna la profundidad de la imagen
    datos[3]=chanels;//asigna el numero de canales de la imagen
    return datos;
}

sImage::~sImage()//destructor
{
    cvReleaseImage(&img);
}
