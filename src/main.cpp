/*******************************************************************************
 Copyright (C) 2019 Signify Holding
 All Rights Reserved.
 ********************************************************************************/

#include <huestream/config/Config.h>
#include <huestream/HueStream.h>
//#include <huestream_example_console/App.h>
//#include <huestream_example_console/ExplosionMenu.h>
//#include <huestream_example_console/SequenceMenu.h>
//#include <huestream_example_console/SawAndLightningMenu.h>
//#include <huestream_example_console/RGBSpeedControlMenu.h>
//#include <huestream_example_console/MyDemo.h>
#include "Terminal.h"
#include "RainbowEffect.h"

#include <stdio.h>
#include <thread>
#include <string>
#include <iostream>
#include <array>

using namespace std;
using namespace huestream;

/*
class ConnectionFlowExample : public App {
public:
    ConnectionFlowExample() : App("HueConsoleExample", "PC") {}

    void StartExample() override {
        MainMenu();
    }

    void MainMenu() const {
        auto print = true;
        while (true) {
            if (print) {
                cout << "Main menu:" << endl;
                cout << "e  Explosion demo" << endl;
                cout << "s  Sequence demo" << endl;
                cout << "l  Saw and Lightning demo" << endl;
                cout << "r  RGB Speed Control demo" << endl;
                cout << "m  My own personal demo" << endl;
                cout << "q  Quit" << endl;
                print = false;
            }
            auto key = Terminal::GetChar();
            if (key == 'e') {
                ExplosionMenu(_huestream).Run();
                print = true;
            } else if (key == 'l') {
                SawAndLightningMenu(_huestream).Run();
                print = true;
            } else if (key == 's') {
                SequenceMenu(_huestream).Run();
                print = true;
            } else if (key == 'r') {
                RGBSpeedControlMenu(_huestream).Run();
                print = true;
            } else if (key == 'm') {
                MyDemo(_huestream).Run();
                print = true;
            } else if (key == 'q') {
                break;
            }
        }
    }
};
*/

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

	/*
	while (!huestream->IsStreamableBridgeLoaded()) {
		auto bridge = huestream->GetLoadedBridge();
		if (bridge->GetStatus() == BRIDGE_INVALID_GROUP_SELECTED) {
			//A choice should be made between multiple groups
			//Here we just pick the first one in the list
			huestream->SelectGroup(bridge->GetGroups()->at(0));
		} else {
			PressAnyKey();
			huestream->ConnectBridge();
		}
	}
	*/

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
