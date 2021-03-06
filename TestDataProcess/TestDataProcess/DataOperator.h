#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>

#include "FrameBuffer.h"

using namespace std;

namespace Utility {
	
	class DataOperator
	{
		/* Embedded classes: */
	private:
		std::string dataFilePath;
		int unitDataLengthInByte;
		bool isRead;
		char* buffer = NULL; // Pointer to the reference-counted frame buffer
		int currentIndex;
		std::fstream file;

	public:
		DataOperator(std::string filePath, int unitLength, bool read)
		{
			dataFilePath = filePath;
			unitDataLengthInByte = unitLength;
			isRead = read;
			currentIndex = 0; 
			if (isRead)
			{
				buffer = new char[unitDataLengthInByte];
				file.open(dataFilePath, std::fstream::in | std::fstream::binary);

				cout << "Data file is opened for reading." << endl;
			}
			else
			{
				file.open(dataFilePath, std::fstream::out | std::fstream::binary);
				cout << "Data file is opened for writing." << endl;
			}
		}

		~DataOperator()
		{
			if (buffer)
			{
				delete buffer;
				buffer = NULL;
			}

			if (file && file.is_open())
			{
				file.close();
				cout << "Data file is closed." << endl;
			}
		}

		char* ReadBuff()
		{
			if (file.read(buffer, unitDataLengthInByte))
			{
				cout << "Get data, index: " << currentIndex << endl;
				currentIndex++;

				return buffer;
			}
			
			cout << "Get data failed." << endl;

			return NULL;
		}

		bool SaveBuff(char * buffer)
		{
			if(file.write(buffer, unitDataLengthInByte))
			{				
				cout << "Set data, index: " << currentIndex << endl;

				currentIndex++;
				return true;
			}

			cout << "Set data failed." << endl;

			return false;
		}

		bool ReadFrame(Kinect::FrameBuffer& frame)
		{
			char * buff = ReadBuff();

			if (buff == NULL)
			{
				return false;
			}
			else
			{
				char * pBuff = static_cast<char *>(frame.getBuffer());

				for (int i = 0; i < 10; i++)
				{
					pBuff[i] = buff[i];
				}
			}
		}

		bool SaveFrame(Kinect::FrameBuffer frame)
		{
			return SaveBuff((char*)frame.getBuffer());
		}
	};
}