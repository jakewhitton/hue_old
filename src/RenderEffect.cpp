#include <huestream/effect/animation/animations/ConstantAnimation.h>
#include <huestream/effect/animation/animations/SequenceAnimation.h>
#include <huestream/effect/animation/animations/TweenAnimation.h>
#include "RenderEffect.h"

#include <string>
#include <memory>
#include <cassert>
#include <cstdio>

using namespace huestream;

RenderEffect::RenderEffect(const std::string &name, unsigned int layer, const Color * framebuffer)
	: AnimationEffect(name, layer)
	, framebuffer_(framebuffer)
{ }

std::string RenderEffect::GetTypeName() const {
	return type;
}

void RenderEffect::Serialize(JSONNode *node) const
{
	AnimationEffect::Serialize(node);
}

void RenderEffect::Deserialize(JSONNode *node)
{
	AnimationEffect::Deserialize(node);
}

void RenderEffect::PrepareEffect()
{

}

void RenderEffect::RenderUpdate()
{ }

Color RenderEffect::GetColor(LightPtr light)
{
	auto i = std::stoul(light->GetId());
	assert(i >= 0 && i < 8);
	const Color & c = framebuffer_[i];

	//printf("id %d => (%f, %f, %f)\n", i, c.GetR(), c.GetG(), c.GetB());
	return Color(c.GetR(), c.GetG(), c.GetB());
}

AnimationListPtr RenderEffect::GetAnimations()
{
	auto list = std::make_shared<AnimationList>();
	return list;
}
