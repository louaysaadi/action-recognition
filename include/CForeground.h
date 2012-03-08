#ifndef CFOREGROUND_H
#define CFOREGROUND_H
#include "CForegroundExtractMethod.h"

class CForeground
{
    public:
        CForeground( IplImage * grd);
        CForeground( IplImage *grd1, IplImage * grd2 );
        virtual ~CForeground();

        IplImage * getForeground( CForegroundExtractMethod & em , IplImage * img );
    protected:
        IplImage * grd1, *grd2;
    private:
};

#endif // CFOREGROUND_H
