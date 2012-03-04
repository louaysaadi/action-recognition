#ifndef CFOREGROUNDEXTRACTMETHOD_H
#define CFOREGROUNDEXTRACTMETHOD_H
#include "../cvinclude.h"

class CForegroundExtractMethod
{
    public:
        CForegroundExtractMethod();
        virtual ~CForegroundExtractMethod();
        virtual IplImage * extractForeground( IplImage * img, const IplImage * grd ) = 0;
    protected:
    private:
};

#endif // CFOREGROUNDEXTRACTMETHOD_H
