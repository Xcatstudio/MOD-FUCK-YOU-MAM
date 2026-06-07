#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>

using namespace geode::prelude;

class $modify(CCSprite) {
    void setRotation(float rotation) override {
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            if (auto frame = this->getSpriteFrame()) {
                std::string name = frame->getName();
                if (name.find("musicArrow") != std::string::npos ||
                    name.find("musicBtn") != std::string::npos)
                {
                    CCSprite::setRotation(Mod::get()->getSettingValue<double>("angle"));
                    return;
                }
            }
        }
        CCSprite::setRotation(rotation);
    }
};
