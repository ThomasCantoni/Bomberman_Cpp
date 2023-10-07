#include "NetworkPacket.h"

namespace Bomberman
{
	std::shared_ptr<std::vector<NetworkPacket>> NetworkPacket::Unpack(const std::vector<unsigned char>* toUnpack,bool bigEndian)
	{
		auto list = std::make_shared<std::vector<NetworkPacket>>();
		int index = 0;
		while (index < toUnpack->size())
		{
			auto CommandType = (NETCOMMANDType)ByteConverter::BytesToInt(toUnpack, index, bigEndian);
			index += 4;
			int PlayerID = ByteConverter::BytesToInt(toUnpack, index, bigEndian);
			index += 4;
			int payloadLength = ByteConverter::BytesToInt(toUnpack, index, bigEndian);
			index += 4;
			NetworkPacket n = NetworkPacket(CommandType, PlayerID);
			n.BigEndian = bigEndian;
			if (payloadLength > 0)
			{
				n.Payload->data->resize(payloadLength);
			}
			if (payloadLength > 100)
			{
				std::cout << "HOLD UP";
			}
			if (payloadLength == 0)
			{
				break;
			}
			for (int i = 12; i < payloadLength; i++)
			{
				n.Payload->data->data()[i] = toUnpack->at(index);
				index++;
			}
			list->push_back(n);

		}
		return list;
	}
	std::shared_ptr<std::vector<NetworkPacket>> NetworkPacket::Unpack(std::shared_ptr<std::vector<unsigned char>> toUnpack,bool bigEndian)
	{
		auto list = std::make_shared<std::vector<NetworkPacket>>();
		int index = 0;
		while (index < toUnpack->size())
		{
			NetworkPacket n;
			n.CommandType = (NETCOMMANDType)ByteConverter::BytesToInt(toUnpack->data(), index, bigEndian);
			index += 4;
			n.PlayerID = ByteConverter::BytesToInt(toUnpack->data(), index, bigEndian);
			index += 4;
			int payloadLength = ByteConverter::BytesToInt(toUnpack->data(), index, bigEndian);
			n.Payload->data->resize(payloadLength);
			for (int i = 0; i < payloadLength; i++)
			{
				unsigned char x = toUnpack->data()[i];
				n.Payload->data->at(i) = x;
			}
			list->push_back(n);

		}
		return list;
	}
}