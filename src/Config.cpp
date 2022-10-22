#include "Config.h"
#include <cassert>
#include <fstream>
#include <sstream>

BridgeConfig::BridgeConfig(std::string_view configStr)
{
	const char * buf = configStr.data();
	const char * const bufEnd = buf + configStr.size();

	enum Field {IP_NEXT, USER_NEXT, CLIENT_KEY_NEXT, DONE} field = IP_NEXT;
	std::string * target = &ip;
	const char * tokenStart = buf;
	for (; buf <= bufEnd; ++buf)
	{
		char c = buf < bufEnd ? *buf : ',';
		if (c == ',')
		{
			// Write token to target
			*target = std::string(tokenStart, buf);
			tokenStart = buf + 1;

			// Shift target to be the next field
			switch (field)
			{
			case IP_NEXT:
				target = &user;
				field = USER_NEXT;
				break;
			case USER_NEXT:
				target = &clientKey;
				field = CLIENT_KEY_NEXT;
				break;
			case CLIENT_KEY_NEXT:
				target = &ip;
				field = DONE;
				break;
			case DONE:
				// Too many fields on one line in the config
				throw std::exception();
				break;
			default:
				assert(false);
			}
		}
	}
}

Config configFromFile(const char * path)
{
	Config result;
	
	// Load file into memory
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string bufferStr = buffer.str();
	const char * buf = bufferStr.c_str();
	const char * const bufEnd = buf + bufferStr.size();

	// Create one BridgeRenderer for each line in the config
	const char * lineStart = buf;
	for (; buf < bufEnd; ++buf)
	{
		char c = *buf;
		if (c == '\n' )
		{
			result.emplace_back(std::string_view(lineStart, buf - lineStart));
			lineStart = buf + 1;
		}
	}

	return result;
}
