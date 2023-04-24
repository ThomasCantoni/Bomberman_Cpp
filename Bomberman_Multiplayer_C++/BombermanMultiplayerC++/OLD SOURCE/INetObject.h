#pragma once
#include "byteconverter.cpp"
namespace Bomberman
{
	struct INetObjectInfo
	{
	
		int length,networkID;
		unsigned char* data;
		INetObjectInfo() = default;
	};
	class INetObject 
	{
	public:
		virtual std::shared_ptr<INetObjectInfo> Serialize() const = 0;
		

	};
}