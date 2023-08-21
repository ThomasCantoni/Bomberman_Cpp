#pragma once
#include "byteconverter.h"
#include <unordered_map>
#include <functional>
namespace Bomberman
{
	/// <summary>
	/// the purpose of this class is to represent raw binary data from/to the server.
	/// </summary>
	struct SerialData
	{
		int length;
		//unsigned char* data;
		unsigned char* data;
		SerialData(int bytesToAllocate);
		
		~SerialData();
		void Print(int lines=4);
		int Append(const SerialData& other);
	};

	
	/// <summary>
	/// Class that implement this interface are classes that can be converted into a SerialData struct, into raw data.
	/// </summary>
	class ISerializable
	{
	public:
		
		virtual std::shared_ptr<SerialData> Serialize() const =0;
		virtual std::shared_ptr<ISerializable> Deserialize(std::shared_ptr<SerialData>) const =0;

	};


}