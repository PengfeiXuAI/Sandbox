// TestDataProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataOperator.h"


//#include <unistd.h>

using namespace Utility;

void SetBuff(char * buff, Kinect::FrameBuffer frame)
{
	char * pBuff = static_cast<char *>(frame.getBuffer());

	for (int i = 0; i < 10; i++)
	{
		pBuff[i] = buff[i];
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Basic data save finish.

	// TODO: write a callback strategy to process data

	DataOperator op("D:\\Data\\data.txt", 10, true);

	cout << "Start to sleep..." << endl;
	//sleep(2);

	cout << "End sleep..." << endl;

	Kinect::FrameBuffer test(10, 10, 1);
	for (int i = 0; i < 1; i++)
	{	
		char * buff = new char[10];
		buff[0] = '0';
		buff[1] = '1';
		buff[2] = '2';
		buff[3] = '3';
		buff[4] = '3';

		SetBuff(op.Get(), test);


		//op.SetFromFrame(test);

		//char * pBuff = static_cast<char *>(test.getBuffer()); //test.buff = op.Get();

		//pBuff[0] = '0';
		//pBuff[1] = '1';
		//pBuff[2] = '2';
		//pBuff[3] = '3';

		void * pBuff2 = test.getBuffer();

		//test.PrintBuff();

		//if (test.buff)
		//{
			for (int i = 0; i < 10; i++)
			{
				cout << (int)((char *)pBuff2)[i] << endl;
			}
		//}
	}

	return 0;
}


