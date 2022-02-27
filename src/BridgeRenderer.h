#pragma once

#include "Config.h"
#include "RenderEffect.h"
#include <huestream/HueStream.h>

class BridgeRenderer : public huestream::HueStream
{
public:
	BridgeRenderer(const BridgeConfig & config, huestream::Color * framebuffer);
	virtual ~BridgeRenderer()
	{ }

	void render();
private:

	BridgeRenderer(const BridgeConfig & config, huestream::Color * framebuffer,
		           huestream::ConfigPtr hueConfig);
};
