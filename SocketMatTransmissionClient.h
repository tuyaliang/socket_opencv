#ifndef __SOCKETMATTRANSMISSIONCLIENT_H__
#define __SOCKETMATTRANSMISSIONCLIENT_H__
 
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
using namespace cv;
 
//待传输图像默认大小为 640*480，可修改
#define IMG_WIDTH 640	// 需传输图像的宽
#define IMG_HEIGHT 480	// 需传输图像的高
#define PACKAGE_NUM 2
//默认格式为CV_8UC3
#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM
 
struct sentBuf
{
	char buf[BUFFER_SIZE];
	int flag;
};

struct recvBuf
{
	char buf[BUFFER_SIZE];
	int flag;
};
 
class SocketMatTransmissionClient
{
public:
	SocketMatTransmissionClient(void);
	~SocketMatTransmissionClient(void);
 
private:
	int sockClient;
	struct sentBuf data;
	struct recvBuf data_r;
	int needRecv;
	int count;
 
public:

	int socketConnect(const char* IP, int PORT);
	int transmit(cv::Mat image);
	int receive(cv::Mat& image);
	void socketDisconnect(void);
};
 
#endif
