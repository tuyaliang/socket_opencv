#include "SocketMatTransmissionServer.h"
 
int main()
{	
	SocketMatTransmissionServer socketMat;
	if (socketMat.socketInit(6666) < 0)
	{
		return 0;
	}
	cv::Mat img_r;
	int key = -1;
	int n = -1;
	while(1)
	{
		if (socketMat.socketConnect() < 0)
		{
			continue;
		}
		while (1)
		{
			n = socketMat.receive(img_r);
       
			if(n > 0)
			{
				printf("Server recv!\n");
				socketMat.transmit(img_r);
				//cv::imshow("Server",img_r);
				//key = cv::waitKey(1);
				//if (key == 'q')
				//    break;
			}
			else
			{
				printf("Server recv error!\n");
				break;
			}
		//printf("Server !!!!!\n");
		//socketMat.transmit(img_r);
		}
		//socketMat.socketDisconnect();
	}
	socketMat.socketDisconnect();
	return 0;
}
