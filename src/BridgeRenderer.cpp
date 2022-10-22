#include "BridgeRenderer.h"

using namespace huestream;

BridgeRenderer::BridgeRenderer(const BridgeConfig & config, Color * framebuffer)
	: BridgeRenderer(config, framebuffer, std::make_unique<huestream::Config>(
			    "render", "thinkpad", PersistenceEncryptionKey("")))
{ }

BridgeRenderer::BridgeRenderer(const BridgeConfig & config, huestream::Color * framebuffer,
               huestream::ConfigPtr hueConfig)
	: HueStream(hueConfig)
{
	//Register feedback callback
	RegisterFeedbackCallback([this](const FeedbackMessage &message)
	{
		//Handle connection flow feedback messages here to guide user to connect to the HUE bridge
		//Here we just write to stdout
		if (message.GetMessageType() == FeedbackMessage::FEEDBACK_TYPE_USER) {
			std::cout << message.GetUserMessage() << std::endl;
		}
		if (message.GetId() == FeedbackMessage::ID_DONE_COMPLETED) {
			std::cout << "Connected to bridge with ip: " << message.GetBridge()->GetIpAddress() << std::endl;
			connected_ = true;
		}
	});

	//Connect to the bridge synchronous
	auto bridge = std::make_shared<Bridge>(
		std::make_shared<BridgeSettings>());
	bridge->SetIpAddress(config.ip);
	bridge->SetUser(config.user);
	bridge->SetClientKey(config.clientKey);
	std::cout << "Initiating attempt to connect to " << config.ip << "..." << std::endl;
	ConnectManualBridgeInfoAsync(bridge);

	auto layer = 0;
	auto name = "my-renderer";
	auto effect = std::make_shared<RenderEffect>(name, layer, framebuffer);
	effect->PrepareEffect();
	LockMixer();
	AddEffect(effect);
	effect->Enable();
	UnlockMixer();
}

void BridgeRenderer::render()
{
	RenderSingleFrame();
}
