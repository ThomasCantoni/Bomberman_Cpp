#include "INetObject.h"
#include <iostream>
#include <iomanip>
namespace Bomberman
{

SerialData::SerialData(int bytesToAllocate)
{
	//std::cout << "NEW SERIALDATA CREATED" << std::endl;
	length = bytesToAllocate;
	//data = std::string(length, 0x00);
	data = (unsigned char*)calloc(1, length);
	
}

SerialData::~SerialData()
{
	//std::cout << "SERIALDATA DESTROYED" << std::endl;
	//Print();
	free(data);
}
int SerialData::Append(const SerialData& other)
{
	int previousLength = length;
	length= other.length+this->length;
	
	data = (unsigned char*)realloc(data,length);

	return byteconverter::BytesAppend(data,length,  previousLength, other.data, other.length);
	 
}
void SerialData::Print(int bytesPerLine)
{
	for (int i = 0; i < length; ++i)
	{
		if (i % bytesPerLine==0)
		{
			std::cout << std::endl;
		}
		std::cout << std::hex << std::setfill('0') << "0x" << std::setw(2) << (int)data[i] << "|";
	}
	std::cout << std::endl;

}
}