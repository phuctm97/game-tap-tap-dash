#ifndef __INTRO_SCENE_MAIN_LAYER_H__
#define __INTRO_SCENE_MAIN_LAYER_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"

namespace IntroScene
{
class MainLayer : public cocos2d::Layer
{
private:
	cocos2d::Sprite* _logo;
	cocos2d::ui::Button* _btnStart;
	cocos2d::Sprite* _background;
	cocos2d::ui::CheckBox* _chkSound;
	cocos2d::ui::Button* _btnFb;

public:
	MainLayer()
		: _logo( nullptr ),
		  _btnStart( nullptr ),
		  _background( nullptr ),
		  _chkSound( nullptr ),
		  _btnFb( nullptr ) {}

	static MainLayer* create();

	bool init() override;

	void reset();

private:
	bool initGraphics();

	bool initEvents();

	void onBtnStartClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

	void onBtnFbClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

	void onChkSoundClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );
};
}

#endif //!__INTRO_SCENE_MAIN_LAYER_H__
