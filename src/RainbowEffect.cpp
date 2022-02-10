/*******************************************************************************
 Copyright (C) 2019 Signify Holding
 All Rights Reserved.
 ********************************************************************************/

#include <huestream/effect/animation/animations/ConstantAnimation.h>
#include <huestream/effect/animation/animations/SequenceAnimation.h>
#include <huestream/effect/animation/animations/TweenAnimation.h>
#include "RainbowEffect.h"

#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <cmath>

namespace huestream {

	/*! \brief Convert HSV to RGB color space

	Converts a given set of HSV values `h', `s', `v' into RGB
	coordinates. The output RGB values are in the range [0, 1], and
	the input HSV values are in the ranges h = [0, 360], and s, v =
	[0, 1], respectively.

	\param fR Red component, used as output, range: [0, 1]
	\param fG Green component, used as output, range: [0, 1]
	\param fB Blue component, used as output, range: [0, 1]
	\param fH Hue component, used as input, range: [0, 360]
	\param fS Hue component, used as input, range: [0, 1]
	\param fV Hue component, used as input, range: [0, 1]

	*/
	void HSVtoRGB(double& fR, double& fG, double& fB, double& fH, double& fS, double& fV) {
		double fC = fV * fS; // Chroma
		double fHPrime = fmod(fH / 60.0, 6);
		double fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
		double fM = fV - fC;

		if(0 <= fHPrime && fHPrime < 1) {
			fR = fC;
			fG = fX;
			fB = 0;
		} else if(1 <= fHPrime && fHPrime < 2) {
			fR = fX;
			fG = fC;
			fB = 0;
		} else if(2 <= fHPrime && fHPrime < 3) {
			fR = 0;
			fG = fC;
			fB = fX;
		} else if(3 <= fHPrime && fHPrime < 4) {
			fR = 0;
			fG = fX;
			fB = fC;
		} else if(4 <= fHPrime && fHPrime < 5) {
			fR = fX;
			fG = 0;
			fB = fC;
		} else if(5 <= fHPrime && fHPrime < 6) {
			fR = fC;
			fG = 0;
			fB = fX;
		} else {
			fR = 0;
			fG = 0;
			fB = 0;
		}

		fR += fM;
		fG += fM;
		fB += fM;
	}

    RainbowEffect::RainbowEffect(const std::string &name, unsigned int layer) :
        AnimationEffect(name, layer) {

		for (int i = 0; i < 10; ++i) {
			hue_[i] = i*(360.0/10.0);
		}
	}

    std::string RainbowEffect::GetTypeName() const {
        return type;
    }

    void RainbowEffect::Serialize(JSONNode *node) const {
        AnimationEffect::Serialize(node);

        //SerializeAttribute(node, AttributeX, _x);
        //SerializeAttribute(node, AttributeY, _y);
        //SerializeAttribute(node, AttributeRadius, _radius);
    }

    void RainbowEffect::Deserialize(JSONNode *node) {
        AnimationEffect::Deserialize(node);

        //_x = DeserializeAttribute<Animation>(node, AttributeX, _x);
        //_y = DeserializeAttribute<Animation>(node, AttributeY, _y);
        //_radius = DeserializeAttribute<Animation>(node, AttributeRadius, _radius);
    }

    void RainbowEffect::PrepareEffect() {

	}

    void RainbowEffect::RenderUpdate() {

		constexpr auto hueDelta = 1.0;
		for (int i = 0; i < 10; ++i) {
			hue_[i] = fmod(hue_[i] + hueDelta, 360.0);
			Color & c = colors_[i];
			double r, g, b;
			HSVtoRGB(r, g, b, hue_[i], sat_, brightness_);
			c.SetR(r);
			c.SetG(g);
			c.SetB(b);
		}
    }

    Color RainbowEffect::GetColor(LightPtr light) {
		auto i = std::stoul(light->GetId());
		const Color & c = colors_[i];
		//std::cout << "Color for " << i << " = (" << c.GetR() << ", " << c.GetG() << ", " << c.GetB() << ")" << std::endl;
		return Color(c.GetR(), c.GetG(), c.GetB());
    }

    AnimationListPtr RainbowEffect::GetAnimations() {
        auto list = std::make_shared<AnimationList>();
        //list->push_back(_x);
        //list->push_back(_y);
        //list->push_back(_radius);
        return list;
    }

}  // namespace huestream
