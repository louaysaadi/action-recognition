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

/*
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
    IplImage * img = 0, * grd1 = 0,* grd2 = 0, * proimg = 0;
    char image_name[13];

    CSimleMethod sm;

    //获取视频信息
    grd1 = cvCloneImage( cvQueryFrame(capture) );
    grd2 = cvCloneImage( cvQueryFrame(capture) );
    int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
    printf("\tvideo height : %d\n\tvideo width : %d\n\tfps : %d\n\tframe numbers : %d\n", frameH, frameW, fps, numFrames);
    printf( "The Channel number is %d\n", grd1->nChannels );

    //create a window named "mainWin"
    cvNamedWindow( "mainWin", CV_WINDOW_AUTOSIZE );
    cvShowImage( "mainWin", grd1 );
    CForeground fg( grd1, grd2 );
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

*/

int main( int argc, char** argv )
{
  //声明IplImage指针
  IplImage* pFrame = NULL;
  IplImage* pFrImg = NULL;
  IplImage* pBkImg = NULL;

  CvMat* pFrameMat = NULL;
  CvMat* pFrMat = NULL;
  CvMat* pBkMat = NULL;

  CvCapture* pCapture = NULL;

  int nFrmNum = 0;

  //创建窗口
  cvNamedWindow("video", 1);
  cvNamedWindow("background",1);
  cvNamedWindow("foreground",1);
  //使窗口有序排列
  cvMoveWindow("video", 30, 0);
  cvMoveWindow("background", 360, 0);
  cvMoveWindow("foreground", 690, 0);



  if( argc > 2 )
    {
      fprintf(stderr, "Usage: bkgrd [video_file_name]\n");
      return -1;
    }

  //打开摄像头
  if (argc ==1)
    if( !(pCapture = cvCaptureFromCAM(-1)))
      {
	fprintf(stderr, "Can not open camera.\n");
	return -2;
      }

  //打开视频文件
  if(argc == 2)
    if( !(pCapture = cvCaptureFromFile(argv[1])))
      {
	fprintf(stderr, "Can not open video file %s\n", argv[1]);
	return -2;
      }

  //逐帧读取视频
  while(pFrame = cvQueryFrame( pCapture ))
    {
      nFrmNum++;

      //如果是第一帧，需要申请内存，并初始化
      if(nFrmNum == 1)
	{
	  pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
	  pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);

	  pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

	  //转化成单通道图像再处理
	  cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
	  cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);

	  cvConvert(pFrImg, pFrameMat);
	  cvConvert(pFrImg, pFrMat);
	  cvConvert(pFrImg, pBkMat);
	}
      else
	{
	  cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
	  cvConvert(pFrImg, pFrameMat);
	  //高斯滤波先，以平滑图像
	  //cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);

	  //当前帧跟背景图相减
	  cvAbsDiff(pFrameMat, pBkMat, pFrMat);

	  //二值化前景图
	  cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);

	  //进行形态学滤波，去掉噪音
	  //cvErode(pFrImg, pFrImg, 0, 1);
	  //cvDilate(pFrImg, pFrImg, 0, 1);

	  //更新背景
	  cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
	  //将背景转化为图像格式，用以显示
	  cvConvert(pBkMat, pBkImg);

	  //显示图像
	  cvShowImage("video", pFrame);
	  cvShowImage("background", pBkImg);
	  cvShowImage("foreground", pFrImg);

	  //如果有按键事件，则跳出循环
	  //此等待也为cvShowImage函数提供时间完成显示
	  //等待时间可以根据CPU速度调整
	  if( cvWaitKey(20) >= 0 )
	    break;


	}

    }




  //销毁窗口
  cvDestroyWindow("video");
  cvDestroyWindow("background");
  cvDestroyWindow("foreground");

  //释放图像和矩阵
  cvReleaseImage(&pFrImg);
  cvReleaseImage(&pBkImg);

  cvReleaseMat(&pFrameMat);
  cvReleaseMat(&pFrMat);
  cvReleaseMat(&pBkMat);

  cvReleaseCapture(&pCapture);

  return 0;
}

