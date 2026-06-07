#include <Geode/Geode.hpp>
#include <Geode/modify/UILayer.hpp>

using namespace geode::prelude;

static CCNode* g_musicArrow = nullptr;

class $modify(MyUILayer, UILayer) {
    bool init(GJBaseGameLayer* layer) {
        if (!UILayer::init(layer)) return false;
        g_musicArrow = nullptr;
        this->schedule(schedule_selector(MyUILayer::onTick), 0.0f);
        return true;
    }

    void onTick(float) {
        if (!g_musicArrow) {
            findArrow(this);
        }
        if (g_musicArrow && Mod::get()->getSettingValue<bool>("enabled")) {
            g_musicArrow->setRotation(Mod::get()->getSettingValue<double>("angle"));
        }
    }

    void findArrow(CCNode* node) {
        if (auto spr = typeinfo_cast<CCSprite*>(node)) {
            if (auto frame = spr->displayFrame()) {
                auto name = frame->getFrameName();
                if (name.find("musicArrow") != std::string::npos ||
                    name.find("musicBtn") != std::string::npos) {
                    g_musicArrow = spr;
                    return;
                }
            }
        }
        for (int i = 0; i < node->getChildrenCount(); i++) {
            if (auto child = typeinfo_cast<CCNode*>(node->getChildren()->objectAtIndex(i))) {
                findArrow(child);
            }
        }
    }
};
