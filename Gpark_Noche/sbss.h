#ifndef SBSS_H
#define SBSS_H
#include <cv.h>
#include <highgui.h>

class sBss
{
public:
    sBss();

    IplImage* sGetSimpleMotionMask(IplImage *controlImageGRAY, IplImage *currentImage);
    IplImage* sGetColorMask(IplImage* Binary,int lowerLimitH,int upperLimitH,int lowerLimitS,int upperLimitS,int lowerLimitV,int upperLimitV);
private:
    IplImage* mask;

};

#endif // SBSS_H
