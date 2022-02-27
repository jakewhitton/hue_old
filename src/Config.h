#pragma once

#include <string>
#include <string_view>
#include <vector>

struct BridgeConfig
{
	BridgeConfig() = default;
	BridgeConfig(std::string_view configStr);
	BridgeConfig(const BridgeConfig & e)
		: ip(e.ip)
		, user(e.user)
		, clientKey(e.clientKey)
	{ }
	BridgeConfig(BridgeConfig && e)
		: ip(std::move(e.ip))
		, user(std::move(e.user))
		, clientKey(std::move(e.clientKey))
	{ }


	std::string ip;
	std::string user;
	std::string clientKey;
};

using Config = std::vector<BridgeConfig>;
Config configFromFile(const char * path);
