#ifndef HUESTREAM_EXAMPLE_CONSOLE_RAINBOWEFFECT_H_
#define HUESTREAM_EXAMPLE_CONSOLE_RAINBOWEFFECT_H_

#include <huestream/effect/effects/base/AnimationEffect.h>

#include <string>

namespace huestream {

    class RainbowEffect : public AnimationEffect {
    public:
        static constexpr const char* type = "huestream.RainbowEffect";

        explicit RainbowEffect(const std::string &name = "", unsigned int layer = 0);

        std::string GetTypeName() const override;

        void Serialize(JSONNode *node) const override;

        void Deserialize(JSONNode *node) override;

        void PrepareEffect();

        Color GetColor(LightPtr light) override;

        void RenderUpdate() override;

        AnimationListPtr GetAnimations() override;

	private:
		unsigned i_ = 0;

		double sat_ = 1.0, brightness_ = 1.0;
		double hue_[10];
		Color colors_[10];
    };
}  // namespace huestream
#endif  // HUESTREAM_EXAMPLE_CONSOLE_RAINBOWEFFECT_H_
