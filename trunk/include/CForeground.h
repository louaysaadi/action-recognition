#ifndef CFOREGROUND_H
#define CFOREGROUND_H
#include "CForegroundExtractMethod.h"

class CForeground
{
    public:
        CForeground( const IplImage * grd);
        virtual ~CForeground();

        IplImage * getForeground( CForegroundExtractMethod & em , IplImage * img );
    protected:
        const IplImage * grd;
    private:
};

#endif // CFOREGROUND_H
