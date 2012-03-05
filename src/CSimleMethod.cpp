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
         for( j = 0; j < img->widthStep; j++ )
         {
             pv = (  img->imageData[ i * img->widthStep + j ] - grd->imageData[ i * grd->widthStep + j ] );

             if ( pv < val * 5 )
             {
                  img->imageData[ i * img->widthStep + j ] = '\0';
             }
             else
             {
                 //img->imageData[ i * img->widthStep + j ]
             }

             //img->imageData[ i * img->widthStep +  j ] = abs(pv);
             total += abs( pv );
         }
     }
     val = total / img->height / img->widthStep;

     return img;
 }
