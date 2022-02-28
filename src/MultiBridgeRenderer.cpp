#include "MultiBridgeRenderer.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdio>

void HSVtoRGB(double& fR, double& fG, double& fB, double& fH, double& fS, double& fV);

MultiBridgeRenderer::MultiBridgeRenderer(const Config & config)
{
	huestream::Color * fb = colors_;
	for (const auto & bridgeConfig : config)
	{
		renderer_.emplace_back(std::make_unique<BridgeRenderer>(bridgeConfig, fb));
		fb += 8;
	}
}

void MultiBridgeRenderer::start()
{
	std::cout << "Starting MultiBridgeRenderer..." << std::endl;
	running_ = true;
	thread_ = std::thread(&MultiBridgeRenderer::run, this);
}

void MultiBridgeRenderer::stop()
{
	std::cout << "Stopping MultiBridgeRenderer..." << std::endl;

	running_ = false;
	thread_.join();

	for (const auto & renderer : renderer_)
	{
		renderer->ShutDown();
	}

}

void MultiBridgeRenderer::run()
{
	while (running_)
	{
		prepareFrame();
		renderFrame();


		frameEnd_ = std::chrono::system_clock::now();
		
		std::chrono::duration<double> measuredFrameTime = frameEnd_ - frameStart_;
		std::this_thread::sleep_for(desiredFrameTime_ - measuredFrameTime);
		frameStart_ = std::chrono::system_clock::now();
	}
}

void MultiBridgeRenderer::prepareFrame()
{ }

void MultiBridgeRenderer::renderFrame()
{
	for (auto & renderer : renderer_)
	{
		renderer->render();
	}
}
