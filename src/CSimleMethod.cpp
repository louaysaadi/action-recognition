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
     //cvAbsDiff( img->imageData, grd->imageData, img->imageData );
     int i,j;
     char pv;
     for( i = 0; i < img->height ; i ++ )
     {
         for( j = 0; j < img->widthStep; j++ )
         {
             pv = ( img->imageData[ i * img->widthStep + j ] - grd->imageData[ i * img->widthStep + j ] );
             if ( pv < 10 )
             {
                  //img->imageData[ i * img->widthStep + j ] = img->imageData[ i * img->widthStep + j ];
             }
             else
             {
                 img->imageData[ i * img->widthStep + j ] = '\0';
             }

         }
     }
     return img;
 }
