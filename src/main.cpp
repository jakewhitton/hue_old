#include <huestream/config/Config.h>
#include <huestream/HueStream.h>
#include "Terminal.h"
#include "RainbowEffect.h"

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

struct BridgeInfo
{
	string ip;
	string user;
	string clientKey;
};

array<BridgeInfo, 2> bridgeInfos
{
	BridgeInfo {
		"192.168.0.122",
		"oiH9kefbWTflGmd0jhe6Eb-RMLh4ChzJpwgiiryL",
		"2E72B335B89510C40AC445AC93169D82"
		
	},
	BridgeInfo {
		"192.168.0.159",
		"xfvYK0dUVgyEPVkSyw4QSoPP8SdEEI70dsGbxsp2",
		"6F4F56702C83DC0843B786934FF94437"
	}
};

bool running = true;

void worker(const BridgeInfo & info) {

	//Configure
	string applicationName = "render";
	string deviceName      = "thinkpad";
	PersistenceEncryptionKey key("");
    auto config = std::make_shared<Config>(applicationName, deviceName, key);

	//Create the HueStream instance to work with
	//Maintain this instance as a single instance per bridge in the application
	auto huestream = std::make_shared<HueStream>(config);
	
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
	bridge->SetIpAddress(info.ip);
	bridge->SetUser(info.user);
	bridge->SetClientKey(info.clientKey);
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

	vector<thread> workers;
	for (const auto & info : bridgeInfos) {
		workers.emplace_back(worker, info);
	}

	PressAnyKey();
	running = false;

	for (auto & worker : workers) {
		worker.join();
	}
}
