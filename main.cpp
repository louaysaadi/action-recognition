#include <iostream>

using namespace std;

// 该程序实现视频和图片的相互转换.
// Image_to_video()函数将一组图片合成AVI视频文件.
// Video_to_image()函数将AVI视频文件读入，将每一帧存储为jpg文件.
//
////////////////////////////////////////////////////////////////////////
#include "cvinclude.h"
////////////////////////////////////////////////////////////////////////
#include "include/CForeground.h"
#include "include/CSimleMethod.h"

#define NUM_FRAME 1000 //处理前300帧，根据视频帧数可修改


void Video_to_image(char* filename)
{
    printf("------------- video to image ... ----------------\n");

    //初始化一个视频文件捕捉器
    CvCapture* capture = cvCaptureFromAVI(filename);
    if( !capture )
    {
        printf( "Failed to open vedo:%s\n", filename );
        exit( -1 );
    }
    //定义和初始化变量
    int i = 0;
    IplImage * img = 0, * grd = 0, * proimg = 0;
    char image_name[13];

    CSimleMethod sm;

    //获取视频信息
    grd = cvCloneImage( cvQueryFrame(capture) );
    int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
    printf("\tvideo height : %d\n\tvideo width : %d\n\tfps : %d\n\tframe numbers : %d\n", frameH, frameW, fps, numFrames);

    //create a window named "mainWin"
    cvNamedWindow( "mainWin", CV_WINDOW_AUTOSIZE );
    cvShowImage( "mainWin", grd );
    CForeground fg( grd );
    //读取和显示
    for( i = 1; i < NUM_FRAME ; i++ )
    {

       img = cvQueryFrame(capture); //获取一帧图片
       //extract the foreground

       if( proimg )
       {
            cvReleaseImage( &proimg );
       }

       proimg = cvCloneImage( img );

       proimg = fg.getForeground( sm, proimg );
       cvShowImage( "mainWin", proimg ); //将其显示
       char key = cvWaitKey(20);

       //sprintf(image_name, "%s%d%s", "image", i, ".jpg");//保存的图片名

       //cvSaveImage( image_name, img);   //保存一帧图片

    }

    cvReleaseCapture(&capture);
    cvDestroyWindow("mainWin");
}


void Image_to_video()
{
    int i = 0;
    IplImage* img = 0;
    char image_name[13];

    printf("------------- image to video ... ----------------\n");

    //初始化视频编写器，参数根据实际视频文件修改
    CvVideoWriter *writer = 0;
    int isColor = 1;
    int fps     = 30; // or 25
    int frameW = 400; // 744 for firewire cameras
    int frameH = 240; // 480 for firewire cameras
    writer=cvCreateVideoWriter("out.avi",CV_FOURCC('X','V','I','D'),fps,cvSize(frameW,frameH),isColor);

    printf("\tvideo height : %d\n\tvideo width : %d\n\tfps : %d\n", frameH, frameW, fps);

    //创建窗口
    cvNamedWindow( "mainWin", CV_WINDOW_AUTOSIZE );

    while(i < NUM_FRAME - 1)
    {
       sprintf(image_name, "%s%d%s", "image", ++i, ".jpg");
       img = cvLoadImage(image_name);
       if(!img)
       {
        printf("Could not load image file...\n");
        exit(0);
       }
       cvShowImage("mainWin", img);
       char key = cvWaitKey(20);

       cvWriteFrame(writer, img);
    }

    cvReleaseVideoWriter(&writer);
    cvDestroyWindow("mainWin");
}


int main(int argc, char *argv[])
{

    char filename[13] = "cam0.avi";

    Video_to_image(filename); //视频转图片

    //Image_to_video();    //图片转视频

    return 0;
}


