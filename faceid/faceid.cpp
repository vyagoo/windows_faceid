// faceid.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvaux.h>//必须引此头文件
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <tv_sdk_api.h>
using namespace std;

using namespace cv;
enum FACE_CALLBACK_MODE {
	FACE_DETECT_MODE,
	FACEID_RECEIVE_MODE,
	FACEID_SEND_MODE,
	OTA_MODE,
};

void face_detect_callback(int mode, int filesize, int transfered_size, int event) {
	int num=0;
	float feature[512];
	if (mode == FACE_DETECT_MODE) {
		//detect faces
		if (event == 1){
			int ret = dev_getFaceNum();
			int *rect = NULL;
			num =ret;
			printf("num:%d\n", ret);
			for(int i = 0; i < num; i++){
				rect = dev_getFaceRect(i);
				printf("rect(%d,%d,%d,%d) \n", rect[0],rect[1],rect[2],rect[3]);
				printf("info: id:%d , gender:%d, age:%d, emotion:%d, attention:%d\n",
						dev_getFaceID(i),
						dev_faceGetGender(i),
						dev_faceGetAge(i),
						dev_faceGetEmotion(i),
						dev_faceGetAttention(i)
					);
	//			dev_faceGetFRFeature(i, feature);
	//			printf("i=%d, fr: ",i);
	//			for(int j = 0; j< 512; j++){
	//				printf("%.2f ", feature[j]);
	//			}
	//			printf("\n");
				//dev_isAlive();
	#if 0
				//如果没有注册过，id小于等于0
				if (dev_getFaceID(i) <=0) {
					dev_enterRegisterMode();
					int id = dev_registerFaceID(i);
					if (id > 0) {
						//todo map id to name;
					}
					dev_exitRegisterMode();
				}
	#endif
			}
		
		}
	} else if(mode == FACEID_RECEIVE_MODE){
		if(filesize ==1){
			printf("end transfer, %s,l:%d,mode:%d,filesize:%d,transfered_size:%d\n", __FUNCTION__, __LINE__, mode, filesize, transfered_size);
		} else {
			printf("transdering %s,l:%d,mode:%d,filesize:%d,transfered_size:%d\n", __FUNCTION__, __LINE__, mode, filesize, transfered_size);
		}
	} else if (mode == FACEID_SEND_MODE){
		printf("transdering %s,l:%d,mode:%d,filesize:%d,transfered_size:%d\n", __FUNCTION__, __LINE__, mode, filesize, transfered_size);
	} else if (mode == OTA_MODE){
		printf("transdering %s,l:%d,mode:%d,filesize:%d,transfered_size:%d\n", __FUNCTION__, __LINE__, mode, filesize, transfered_size);
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	int i = 0;
	double start, end, cost;
#if 1
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cerr << "Unable to connect to camera" << endl;
		return 1;
	}
	Mat temp;
	vector<cv::Rect> faces;
	Mat face_gray;

	//namedWindow("face", CV_WINDOW_NORMAL);
	cvResizeWindow("face", 800, 480);
#endif
	dev_init(face_detect_callback, NULL,0, 0, 0, NULL, 0, 0);
	start = GetTickCount();//Millisecond
#if 0
	ret = dev_sendPhotoFile("e:\\faceid\\hx_1920_1080_2.jpg");
	ret = dev_set_facetrack_state(1);
	ret = dev_decoder_facetrack_jpeg();
	ret = dev_set_facetrack_state(0);
#endif
//	ret = dev_receiveFaceidDBFile("e:\\faceid\\faceid.db");
#if 0
//	ret = dev_sendFaceidDBFile("e:\\faceid\\faceid.db");
printf("%s,l:%d,ret:%d\n", __FUNCTION__, __LINE__, ret);
//	ret = dev_rebootDevice();
	printf("%s,l:%d,ret:%d\n", __FUNCTION__, __LINE__, ret);
#endif
	printf("%s,l:%d,ret:%d\n", __FUNCTION__, __LINE__, ret);
	//ret = dev_sendOtaFile("e:\\faceid\\Firmware_ota.img");
	end = GetTickCount();//Millisecond
	cost =end-start;
	printf("%s,l:%d,ret:%d,cost:%f\n", __FUNCTION__, __LINE__, ret, cost);
	//ret = dev_startUpdate();
	printf("%s,l:%d,ret:%d\n", __FUNCTION__, __LINE__, ret);
	//设置回调频率，30FPS
	dev_setCallBackFreq(0, 30);
	printf("version:%s\n", dev_getSysVersion());

	while (waitKey(30) != 27)
	{  

		cap >> temp; 
	//	cvtColor(temp, face_gray, CV_BGR2GRAY);
	//	faces.clear();
	//	ccf.detectMultiScale(face_gray, faces, 1.2, 2, CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150), cv::Size(400, 400)); //检测人脸
	//	if (!faces.empty())
	//	{
	//		rectangle(temp,cvPoint(faces[0].x,faces[0].y),cvPoint(faces[0].x+faces[0].width-1,faces[0].y+faces[0].height-1),Scalar(0, 255, 0));
//
//			imshow("face", temp);
//		}
	    imshow("face", temp);

	}

dev_release();
	return 0;
}

