#include <Geode/Geode.hpp>
#include <Geode/modify/UILayer.hpp>

using namespace geode::prelude;

static CCNode* g_musicArrow = nullptr;

void findMusicArrow(CCNode* node) {
    if (g_musicArrow) return;
    if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
        if (auto frame = sprite->getSpriteFrame()) {
            auto name = std::string(frame->getName());
            if (name.find("musicArrow") != std::string::npos ||
                name.find("musicBtn") != std::string::npos)
            {
                g_musicArrow = sprite;
                return;
            }
        }
    }
    for (int i = 0; i < node->getChildrenCount(); i++) {
        if (auto child = typeinfo_cast<CCNode*>(node->getChildren()->objectAtIndex(i))) {
            findMusicArrow(child);
        }
    }
}

class $modify(UILayer) {
    bool init(GJBaseGameLayer* layer) {
        if (!UILayer::init(layer)) return false;
        g_musicArrow = nullptr;
        findMusicArrow(this);
        return true;
    }

    void update(float dt) override {
        UILayer::update(dt);
        if (g_musicArrow && Mod::get()->getSettingValue<bool>("enabled")) {
            g_musicArrow->setRotation(Mod::get()->getSettingValue<double>("angle"));
        }
    }
};
