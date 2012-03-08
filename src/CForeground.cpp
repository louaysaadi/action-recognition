#include "../include/CForeground.h"

CForeground::CForeground( IplImage * grd)
{
    this->grd1 = grd;
    this->grd2 = 0;
}
CForeground::CForeground( IplImage *grd1, IplImage * grd2 )
{
        this->grd1 = grd1;
        this->grd2 = grd2;
}
IplImage * CForeground::getForeground( CForegroundExtractMethod & em, IplImage * img )
{
    return em.extractForeground( img, grd1, grd2);
}
CForeground::~CForeground()
{
    //dtor
}
