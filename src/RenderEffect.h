#pragma once

#include <huestream/effect/effects/base/AnimationEffect.h>
#include <huestream/common/data/Color.h>

#include <string>

class RenderEffect : public huestream::AnimationEffect
{
public:
	static constexpr const char* type = "huestream.RenderEffect";

	explicit RenderEffect(const std::string &name, unsigned int layer, const huestream::Color * framebuffer);

	std::string GetTypeName() const override;

	void Serialize(JSONNode *node) const override;

	void Deserialize(JSONNode *node) override;

	void PrepareEffect();

	huestream::Color GetColor(huestream::LightPtr light) override;

	void RenderUpdate() override;

	huestream::AnimationListPtr GetAnimations() override;

private:

	const huestream::Color * framebuffer_;
};
