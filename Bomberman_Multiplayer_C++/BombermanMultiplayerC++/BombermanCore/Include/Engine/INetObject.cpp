#include "INetObject.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>
namespace Bomberman
{


SerialData::SerialData(int bytesToAllocate)
{
	
	data = std::make_shared< std::vector<unsigned char>>(bytesToAllocate);
	
}

SerialData::~SerialData()
{
	
	//std::cout << "SERIALDATA DESTROYED" << std::endl;
	//Print();
	
}
int SerialData::Append(const SerialData& other)
{
	int previousLength = data->size();
	//unsigned char* swapper = static_cast<unsigned char*>(malloc(length));
	//memcpy(swapper, data.get(),length);
	//
	int newLength= other.data->size() + this->data->size();
	data->resize(newLength);
	//data = std::make_shared<unsigned char>( length);
	//memcpy(data.get(), swapper, previousLength);
	//free(swapper);
	
	return ByteConverter::BytesAppend(data, previousLength, other.data);
	 
}
void SerialData::Print(int bytesPerLine)
{
	for (int i = 0; i < data->size(); ++i)
	{
		if (i % bytesPerLine==0)
		{
			std::cout << std::endl;
		}
		std::cout << std::hex << std::setfill('0') << "0x" << std::setw(2) << (int)data->at(i) << "|";
	}
	std::cout << std::endl;

}
}