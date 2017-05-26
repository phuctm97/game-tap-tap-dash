#ifndef __INTRO_SCENE_MAIN_LAYER_H__
#define __INTRO_SCENE_MAIN_LAYER_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "Common/MyDirector.h"

namespace IntroScene
{
class MainLayer : public cocos2d::Layer
{
private:
	cocos2d::Sprite* logo;
	cocos2d::ui::Button* btnStart;
	cocos2d::Sprite* background;
	cocos2d::ui::CheckBox* sound;
	cocos2d::ui::Button* btnFb;

public:
	static MainLayer* create();

	bool init() override;

	
	void reset();

private:
	bool initGraphics();
	bool initEvents();
};
}

#endif //!__INTRO_SCENE_MAIN_LAYER_H__
