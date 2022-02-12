#include <huestream/config/Config.h>
#include <huestream/HueStream.h>
#include "Terminal.h"
#include "RainbowEffect.h"
#include "BridgeConfig.h"

#include <stdio.h>
#include <thread>
#include <string>
#include <iostream>
#include <array>

using namespace std;
using namespace huestream;

void PressAnyKey() {
	cout << "Press any key to continue...";
    auto key = Terminal::GetChar();
	cout << endl;
}

bool running = true;

void worker(const BridgeConfig & config) {

	//Configure

	//Create the HueStream instance to work with
	//Maintain this instance as a single instance per bridge in the application
	string applicationName = "render";
	string deviceName      = "thinkpad";
	PersistenceEncryptionKey key("");
	auto huestream = std::make_shared<HueStream>(
		std::make_shared<Config>(applicationName, deviceName, key));
	
	//Register feedback callback
	huestream->RegisterFeedbackCallback([](const FeedbackMessage &message) {
		//Handle connection flow feedback messages here to guide user to connect to the HUE bridge
		//Here we just write to stdout
		if (message.GetMessageType() == FeedbackMessage::FEEDBACK_TYPE_USER) {
			std::cout << message.GetUserMessage() << std::endl;
		}
		if (message.GetId() == FeedbackMessage::ID_DONE_COMPLETED) {
			std::cout << "Connected to bridge with ip: " << message.GetBridge()->GetIpAddress() << std::endl;
		}
	});

	//Connect to the bridge synchronous
	auto bridgeSettings = std::make_shared<BridgeSettings>();
	auto bridge = std::make_shared<Bridge>(bridgeSettings);
	bridge->SetIpAddress(config.ip);
	bridge->SetUser(config.user);
	bridge->SetClientKey(config.clientKey);
	huestream->ConnectManualBridgeInfo(bridge);

	cout << "Starting effect..." << endl;

	//Create an explosion effect object
	auto layer = 0;
	auto name = "my-rainbow";
	auto explosion = std::make_shared<RainbowEffect>(name, layer);

	//Configure the explosion with color and explosion behaviour and position
	explosion->PrepareEffect();

	//Play the effect
	huestream->LockMixer();
	huestream->AddEffect(explosion);
	explosion->Enable();
	huestream->UnlockMixer();

	while (running) { }

	huestream->ShutDown();
}

int main(int argc, char *argv[]) {

	assert(argc == 2);
	auto bridgeConfigs = parseBridgeConfigs(argv[1]);

	vector<thread> workers;
	for (const auto & config : bridgeConfigs) {
		workers.emplace_back(worker, config);
	}

	PressAnyKey();
	running = false;

	for (auto & worker : workers) {
		worker.join();
	}
}
