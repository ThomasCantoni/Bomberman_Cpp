#pragma once
#include "byteconverter.h"
namespace Bomberman
{
	class SerialData
	{
	public:
		int length;
		unsigned char* data;
		SerialData(int bytesToAllocate);
		
		~SerialData();
		void Print(int lines=4);
		int Append(const SerialData& other);
	};
	class ISerializable 
	{
	public:

		virtual std::shared_ptr<SerialData> Serialize() const = 0;
		
		

	};
}