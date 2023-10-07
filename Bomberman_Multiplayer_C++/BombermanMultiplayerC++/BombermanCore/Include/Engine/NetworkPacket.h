#pragma once
#include "NetworkBase.h"
#include "INetObject.h"
namespace Bomberman
{

struct  NetworkPacket
{
	NETCOMMANDType CommandType;
	int PlayerID;
	bool BigEndian;
	std::shared_ptr<SerialData> Payload;
	
	NetworkPacket() = default;
	NetworkPacket(NETCOMMANDType comm, int pID, std::shared_ptr<SerialData> payload)
		:CommandType(comm), PlayerID(pID)
	{
		int extraSpace = 0;

	

		if (CommandType != ByteConverter::BytesToInt(payload->data, 0, BigEndian) ||
			PlayerID != ByteConverter::BytesToInt(payload->data, 4, true))
		{
			extraSpace += 8;
			Payload = std::make_shared<SerialData>(extraSpace + payload->data->size());
			ByteConverter::BytesAppend(Payload->data, 0, CommandType);
			ByteConverter::BytesAppend(Payload->data, 4, PlayerID);
		}
		else
		{
			ByteConverter::BytesAppend(Payload->data, extraSpace, payload->data);

		}
	};
	NetworkPacket(NETCOMMANDType comm, int pID)
		:CommandType(comm), PlayerID(pID)
	{
			Payload = std::make_shared<SerialData>(8);
			
			ByteConverter::BytesAppend(Payload->data, 0, CommandType);
			ByteConverter::BytesAppend(Payload->data, 4, PlayerID);
		

	};
	void AppendPayload(std::shared_ptr<SerialData> other)
	{
		int OtherID = ByteConverter::BytesToInt(other->data, 0);
		NETCOMMANDType OtherType = (NETCOMMANDType)ByteConverter::BytesToInt(other->data, 4);
	}
	NetworkPacket(std::vector<unsigned char> rawBytes)
	{
		 std::logic_error("Not implemented!");
	};
	static std::shared_ptr<std::vector<NetworkPacket>> Unpack(const std::vector<unsigned char>* toUnpack,bool bigEndian);
	static std::shared_ptr<std::vector<NetworkPacket>> Unpack(std::shared_ptr<std::vector<unsigned char>> toUnpack, bool bigEndian);
	static std::shared_ptr<std::vector<unsigned char>> Pack(std::shared_ptr<std::vector<NetworkPacket>> toPack, bool bigEndian);

};
}

