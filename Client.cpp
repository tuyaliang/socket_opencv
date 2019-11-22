#include "SocketMatTransmissionClient.h"
 
int main()
{
	SocketMatTransmissionClient socketMat;
	if (socketMat.socketConnect("192.168.8.109", 6666) < 0)
	{
		return 0;
	}
	
	cv::VideoCapture capture(0);
	cv::Mat image;
	cv::Mat img_s;
	cv::Mat img_r;
	while (1)
	{
		if (!capture.isOpened())
			return 0;
 
		capture >> image;
    cv::resize(image, img_s, cv::Size(640, 480), (0, 0), (0, 0), cv::INTER_LINEAR); 
 
		if (img_s.empty())
			return 0;
 
		socketMat.transmit(img_s);
    printf("Client send!\n");
		if(socketMat.receive(img_r) > 0)
		{
			cv::imshow("Client",img_r);
			cv::waitKey(30);
		}
    else
    {
      printf("Client recv error!\n");
    }
	}
 
	socketMat.socketDisconnect();
	return 0;
}
