#pragma once

#include "BridgeRenderer.h"
#include "Config.h"
#include <huestream/common/data/Color.h>
#include <thread>
#include <memory>

class MultiBridgeRenderer
{
public:
	MultiBridgeRenderer(const Config & config);

	void start();
	void stop();

private:
	static constexpr unsigned N = 24;
	static constexpr double hueDelta = 1.0;

	void run();
	void prepareFrame();
	void renderFrame();

	bool running_ = false;
	std::thread thread_;
	std::vector<std::unique_ptr<BridgeRenderer>> renderer_;

	double sat_ = 1.0, brightness_ = 1.0;
	double hue_[N];
	huestream::Color colors_[N];

	// Timing
	double fps_ = 30;
	std::chrono::time_point<std::chrono::system_clock> frameStart_;
	std::chrono::time_point<std::chrono::system_clock> frameEnd_;
	std::chrono::duration<double> desiredFrameTime_ =
		std::chrono::milliseconds(33);
};
