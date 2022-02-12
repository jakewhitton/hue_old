#include "BridgeConfig.h"
#include <fstream>
#include <sstream>
#include <cassert>

std::vector<BridgeConfig> parseBridgeConfigs(const char * path)
{
	// Load file into memory
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string bufferStr = buffer.str();
	const char * buf = bufferStr.c_str();
	const char * const bufEnd = buf + bufferStr.size();

	// Extract one BridgeConfig from each line
	std::vector<BridgeConfig> result;
	BridgeConfig config;
	enum Field {IP, USER, CLIENT_KEY} field = IP;
	std::string * target = &config.ip;
	const char * tokenStart = buf;
	for (; buf <= bufEnd; ++buf)
	{
		// Interpret end of file as newline
		char c = buf < bufEnd ? *buf : '\n';
		switch (c)
		{
		case ',':
		case '\n':
			// Write token to target
			*target = std::string(tokenStart, buf);
			tokenStart = buf + 1;

			// Shift target to be the next field
			switch (field)
			{
			case IP:
				target = &config.user;
				field = USER;
				break;
			case USER:
				assert(c == ',');
				target = &config.clientKey;
				field = CLIENT_KEY;
				break;
			case CLIENT_KEY:
				assert(c == '\n');
				result.push_back(config);
				target = &config.ip;
				field = IP;
				break;
			}
			break;

		default:
			break;
		}

	}

	return result;
}
