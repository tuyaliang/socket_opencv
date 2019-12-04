#include "SocketMatTransmissionServer.h"
 
SocketMatTransmissionServer::SocketMatTransmissionServer(void)
{
}
 
 
SocketMatTransmissionServer::~SocketMatTransmissionServer(void)
{
}
 
 
int SocketMatTransmissionServer::socketInit(int PORT)
{
	server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
 
	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(PORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int contain=1;  
	setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &contain, sizeof(int));

	if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
	{
		perror("bind");
		return -1;
	}
	
	if(listen(server_sockfd,5) == -1)
	{
		perror("listen");
		return -1;
	}
}


int SocketMatTransmissionServer::socketConnect(void)
{
 
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
 
	sockConn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
	if(sockConn<0)
	{
		perror("connect");
		return -1;
	}
	else
	{
		printf("connect successful!\n");
		//close(sockConn);
		return 1;
	}
}
 
 
void SocketMatTransmissionServer::socketDisconnect(void)
{
	close(sockConn);
}
 
int SocketMatTransmissionServer::receive(cv::Mat& image)
{
	int returnflag = 0;
	cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));
	needRecv = sizeof(recvBuf) - 2;
	count = 0;
	memset(&data,0,sizeof(data));
 
	int pos = 0;
	int len0 = 0;
 
	recv(sockConn, (char*)(&data), 2, 0);
	printf("===========data.head[0]=====%c\n",data.head[0]);
	printf("===========data.head[1]=====%c\n",data.head[1]);
  
	if((data.head[0] == NULL) || (data.head[1] == NULL))
	{
		return -1;
	}

	while (pos < needRecv)
	{
		len0 = recv(sockConn, (char*)(&data) + pos + 2, needRecv - pos, 0);
		if (len0 < 0)
		{
			printf("Server Recieve Data Failed!\n");
			return -1;
			break;
		}
		pos += len0;
	}
 
	if((data.head[0] != 'a') || (data.head[1] != 'b'))
	{
		return -1;
	}

	if((data.head[0] == 'c') && (data.head[1] == 'd'))
	{
		return 0;
	}

	for (int j = 0; j < IMG_HEIGHT / PACKAGE_NUM; j++)
	{
		int num2 = j * IMG_WIDTH * 3;
		uchar* ucdata = img.ptr<uchar>(j);
		for (int k = 0; k < IMG_WIDTH * 3; k++)
		{
			ucdata[k] = data.buf[num2 + k];
		}
	}
 
	image = img;
	returnflag = 1;
	
	if(returnflag == 1)
		return 1;
	else
		return -1;
}

int SocketMatTransmissionServer::transmit(cv::Mat image)
{
	if (image.empty())
	{
		printf("empty image\n\n");
		return -1;
	}
 
	if(image.cols != IMG_WIDTH || image.rows != IMG_HEIGHT || image.type() != CV_8UC3)
	{
		printf("the image must satisfy : cols == IMG_WIDTH（%d）  rows == IMG_HEIGHT（%d） type == CV_8UC3\n\n", IMG_WIDTH, IMG_HEIGHT);
		return -1;
	}

  
	data_s.head[0] = 'a';
	data_s.head[1] = 'b';
	for (int i = 0; i < IMG_HEIGHT; i++)
	{
		int num2 = i * IMG_WIDTH * 3;
		uchar* ucdata = image.ptr<uchar>(i);
		for (int j = 0; j < IMG_WIDTH * 3; j++)
		{
			data_s.buf[num2 + j] = ucdata[j];
		}
	}
 
	if (send(sockConn, (char *)(&data_s), sizeof(data_s), 0) < 0)
	{
		printf("send image error: %s(errno: %d)\n", strerror(errno), errno);
		return -1;
	}
}
