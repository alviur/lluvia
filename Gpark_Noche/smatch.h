#ifndef SMATCH_H
#define SMATCH_H

#include "cxcore.h"


class sMatch
{
public:
    sMatch();


    IplImage* MatchT(IplImage* source,IplImage* patch);
    IplImage* sHistMatch(IplImage* patch,IplImage* source);
    IplImage* sHistPathMatch(IplImage *src2, IplImage *src,int x,int y,int width,int height);
    int pixval(IplImage* Ioriginal,float umbral);
int pixval(IplImage* Ioriginal,int umbral);
    int pixval(IplImage* Ioriginal,long umbral);
    int pixval(IplImage* Ioriginal);

    IplImage* equalization(IplImage* src);

};

#endif // SMATCH_H