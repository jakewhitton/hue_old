#include "RainbowRenderer.h"
#include <cassert>
#include <iostream>
#include "Terminal.h"

void PressAnyKey() {
	char c;
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {

	assert(argc == 2);
	auto config = configFromFile(argv[1]);

	std::cout << "Using " << config.size() << " bridges..." << std::endl;
	unsigned i = 0;
	for (const auto & bridge : config) {
		++i;
		std::cout << "  Bridge " << i << ":" << std::endl;
		std::cout << "    ip=" << bridge.ip << std::endl;
		std::cout << "    user=" << bridge.user << std::endl;
		std::cout << "    clientKey=" << bridge.clientKey << std::endl;
	}
	std::cout << std::endl;

	auto renderer = RainbowRenderer(config);
	std::cout << "Press any key to stop..." << std::endl;
	renderer.start();

	PressAnyKey();
	Terminal::GetChar();
	renderer.stop();
}
