#include "MultiBridgeRenderer.h"
#include "Config.h"
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
	auto renderer = MultiBridgeRenderer(config);
	std::cout << "Press any key to stop..." << std::endl;
	renderer.start();

	PressAnyKey();
	Terminal::GetChar();
	renderer.stop();
}
