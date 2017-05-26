#ifndef __PLAY_SCENE_PAUSE_LAYER_H__
#define __PLAY_SCENE_PAUSE_LAYER_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"

namespace PlayScene
{
class PauseLayer : public cocos2d::Layer
{
private:
	cocos2d::Sprite* _panel;
	cocos2d::Label* _lblPause;
	cocos2d::ui::Button* _btnResume;
	cocos2d::ui::Button* _btnToMenu;

public:
	PauseLayer()
		: _panel( nullptr ),
		  _lblPause( nullptr ),
		  _btnResume( nullptr ),
		  _btnToMenu( nullptr ) {}

	static PauseLayer* create();

	bool init() override;

private:
	bool initGraphics();

	bool initEvents();

	void onBtnResumeClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

	void onBtnToMenuClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );
};
}

#endif //!__PLAY_SCENE_PAUSE_LAYER_H__
