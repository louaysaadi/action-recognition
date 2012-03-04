#ifndef CSIMLEMETHOD_H
#define CSIMLEMETHOD_H

#include "CForegroundExtractMethod.h"


class CSimleMethod : public CForegroundExtractMethod
{
    public:
        CSimleMethod();
        virtual ~CSimleMethod();
        virtual IplImage *extractForeground( IplImage * img, const IplImage * grd );
    protected:
    private:
};

#endif // CSIMLEMETHOD_H
