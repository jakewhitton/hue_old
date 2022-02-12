#pragma once

#include <string>
#include <vector>

struct BridgeConfig
{
	std::string ip;
	std::string user;
	std::string clientKey;
};

std::vector<BridgeConfig> parseBridgeConfigs(const char * config);
