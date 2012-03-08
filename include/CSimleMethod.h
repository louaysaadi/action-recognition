#ifndef CSIMLEMETHOD_H
#define CSIMLEMETHOD_H

#include "CForegroundExtractMethod.h"


class CSimleMethod : public CForegroundExtractMethod
{
    public:
        CSimleMethod();
        virtual ~CSimleMethod();
        virtual IplImage *extractForeground( IplImage * img, const IplImage * grd );
        virtual IplImage * extractForeground( IplImage * img, const IplImage * grd, const IplImage * difGrd);

        IplImage * crDifImg( const IplImage * grd1, const IplImage * grd2 );
    protected:

    private:
};

#endif // CSIMLEMETHOD_H
