#pragma once

#include "MultiBridgeRenderer.h"

class RainbowRenderer : public MultiBridgeRenderer
{
public:
	RainbowRenderer(const Config & config);

private:
	static constexpr unsigned N = 24;
	static constexpr double hueDelta = 1.0;

	virtual void prepareFrame() override;

	double sat_ = 1.0, brightness_ = 1.0;
	double hue_[N];
};
