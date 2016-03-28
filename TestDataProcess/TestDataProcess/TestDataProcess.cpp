// TestDataProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataOperator.h"
#include <vector>

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

bool IsFist(int map[10][10])
{
	int wid = 10;
	int hei = 10;

	/* 1 means valid region */

	std::vector<int> regionWidths;
	std::vector<int> regionHeights;

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "unsigned short" << sizeof(unsigned short) << endl;
	// Basic data save finish.

	// TODO: write a callback strategy to process data

	DataOperator op("D:\\Data\\data.txt", 10, true);

	cout << "Start to sleep..." << endl;
	//sleep(2);

	cout << "End sleep..." << endl;

	Kinect::FrameBuffer Frame(2, 5, 10);
	for (int i = 0; i < 1; i++)
	{	
		char * buff = new char[10];
		buff[0] = '0';
		buff[1] = '1';
		buff[2] = '2';
		buff[3] = '3';
		buff[4] = '3';

		//SetBuff(op.ReadBuff(), test);

		if (op.ReadFrame(Frame))
		{
			for (int i = 0; i < 10; i++)
			{
				cout << (int)((char *)Frame.getBuffer())[i] << endl;
			}
		}


		//op.SetFromFrame(test);

		//char * pBuff = static_cast<char *>(test.getBuffer()); //test.buff = op.Get();

		//pBuff[0] = '0';
		//pBuff[1] = '1';
		//pBuff[2] = '2';
		//pBuff[3] = '3';

		//void * pBuff2 = test.getBuffer();

		//test.PrintBuff();

		//if (test.buff)
		//{
			//for (int i = 0; i < 10; i++)
			//{
			//	cout << (int)((char *)pBuff2)[i] << endl;
			//}
		//}
	}

	return 0;
}


