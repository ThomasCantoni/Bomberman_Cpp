#include "INetObject.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>
namespace Bomberman
{


SerialData::SerialData(int bytesToAllocate)
{
	length = bytesToAllocate;
	data = static_cast<unsigned char*>(malloc( length));
}

SerialData::~SerialData()
{
	//std::cout << "SERIALDATA DESTROYED" << std::endl;
	//Print();
	
}
int SerialData::Append(const SerialData& other)
{
	int previousLength = length;
	//unsigned char* swapper = static_cast<unsigned char*>(malloc(length));
	//memcpy(swapper, data.get(),length);
	//
	length= other.length+this->length;
	realloc(data, length);
	//data = std::make_shared<unsigned char>( length);
	//memcpy(data.get(), swapper, previousLength);
	//free(swapper);
	
	return byteconverter::BytesAppend(data, length, previousLength, other.data, other.length);
	 
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