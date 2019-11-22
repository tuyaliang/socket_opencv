#include "SocketMatTransmissionServer.h"
 
int main()
{
	SocketMatTransmissionServer socketMat;
	if (socketMat.socketConnect(6666) < 0)
	{
		return 0;
	}
 
	cv::Mat img_r;
	while (1)
	{
		if(socketMat.receive(img_r) > 0)
		{
			printf("Server recv!\n");
			cv::imshow("Server",img_r);
			cv::waitKey(30);
      socketMat.transmit(img_r);
			printf("Server send!\n");
		}
    else
    {
			printf("Server recv error!\n");
    }
		//socketMat.transmit(img_r);
	}
 
	socketMat.socketDisconnect();
	return 0;
}
