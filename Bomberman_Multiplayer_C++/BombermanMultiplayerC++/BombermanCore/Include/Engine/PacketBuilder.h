#pragma once
#include <vector>
#include <memory>
#include "NetworkPacket.h"
#include "NetworkBase.h"

namespace Bomberman
{

class PacketBuilder
{
public:
	
	static std::shared_ptr<std::vector<NetworkPacket>> Unpack(const std::vector<unsigned char>* toUnpack);
	static std::shared_ptr<std::vector<NetworkPacket>> Unpack(std::shared_ptr<std::vector<unsigned char>> toUnpack);
	static std::shared_ptr<std::vector<unsigned char>> Pack(std::shared_ptr<std::vector<NetworkPacket>> toPack);

	

};

}
