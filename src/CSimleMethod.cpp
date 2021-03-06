#include "../include/CSimleMethod.h"

CSimleMethod::CSimleMethod()
{
    //ctor

}

CSimleMethod::~CSimleMethod()
{
    //dtor

}

 IplImage *CSimleMethod::extractForeground( IplImage * img, const IplImage * grd )
 {
     //IplImage * nimg = cvCloneImage( img );
     //cvAbsDiff( img->imageData, grd->imageData, nimg->imageData );

     int i,j;
     long total = 0;
     char pv;
     static int val = 0;

     for( i = 0; i < img->height ; i ++ )
     {
         for( j = 0; j < img->widthStep; j += 3 )
         {

             pv = (  img->imageData[ i * img->widthStep + j ] - grd->imageData[ i * grd->widthStep + j ] );
             pv += (  img->imageData[ i * img->widthStep + j + 1 ] - grd->imageData[ i * grd->widthStep + j + 1 ] );
             pv += (  img->imageData[ i * img->widthStep + j + 2 ] - grd->imageData[ i * grd->widthStep + j + 2 ] );

             if ( pv < val * 3  )
             {

                  img->imageData[ i * img->widthStep + j ] = 0;
                  img->imageData[ i * img->widthStep + j + 1 ] = 0;
                  img->imageData[ i * img->widthStep + j + 2 ] = 0;
             }
             else
             {
                 //img->imageData[ i * img->widthStep + j ]
                 img->imageData[ i * img->widthStep + j ] = 255;
                 img->imageData[ i * img->widthStep + j + 1 ] = 255;
                 img->imageData[ i * img->widthStep + j + 2 ] = 255;
             }

             //img->imageData[ i * img->widthStep +  j ] = abs(pv);
             total += abs( pv );

         }
     }
     val = total / img->height / img->width;

     return img;
 }
IplImage * CSimleMethod::crDifImg( const IplImage * grd1, const IplImage * grd2 )
{
    int i,j;
    IplImage * difGrd = cvCloneImage( grd1 );
    for( i = 0; i < difGrd->height; i++ )
    {
        for( j = 0; j < difGrd->widthStep; j++ )
        {
            difGrd->imageData[ i * difGrd->widthStep + j ] = abs(grd1->imageData[ i * grd1->widthStep + j ] - grd2->imageData[ i * grd2->widthStep + j ]);
        }
    }
    return difGrd;
}
IplImage * CSimleMethod::extractForeground( IplImage * img, const IplImage * grd1, const IplImage * grd2)
 {
    IplImage * difGrd = crDifImg( grd1, grd2);
    IplImage * tmp = crDifImg( difGrd, img );
    cvReleaseImage( & img );
    img = tmp;


    return extractForeground( img, grd1 );

 }
