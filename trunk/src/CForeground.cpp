#include "../include/CForeground.h"

CForeground::CForeground( const IplImage * grd)
{
    this->grd = grd;
}
IplImage * CForeground::getForeground( CForegroundExtractMethod & em, IplImage * img )
{
    return em.extractForeground( img, grd );
}
CForeground::~CForeground()
{
    //dtor
}
