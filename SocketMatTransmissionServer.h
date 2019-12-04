#ifndef __SOCKETMATTRANSMISSIONSEVER_H__
#define __SOCKETMATTRANSMISSIONSEVER_H__
 
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
using namespace cv;
 
#define PACKAGE_NUM 1
 
#define IMG_WIDTH 640
#define IMG_HEIGHT 480
 
#define BLOCKSIZE IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM
 
struct recvBuf
{
	char head[2];
	char buf[BLOCKSIZE];
	//int flag;
};

struct sentBuf
{
	char head[2];
	char buf[BLOCKSIZE];
	//int flag;
};

class SocketMatTransmissionServer
{
public:
	SocketMatTransmissionServer(void);
	~SocketMatTransmissionServer(void);
	int sockConn;
	int server_sockfd;
private:
	struct recvBuf data;
	struct sentBuf data_s;
	int needRecv;
	int count;
 
public:

	int socketInit(int PORT);
	int socketConnect(void);
	int transmit(cv::Mat image);	
	int receive(cv::Mat& image);
	void socketDisconnect(void);
};
 
#endif
