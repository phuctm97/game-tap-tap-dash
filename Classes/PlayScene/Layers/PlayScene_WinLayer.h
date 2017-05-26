#ifndef __PLAY_SCENE_WIN_LAYER_H__
#define __PLAY_SCENE_WIN_LAYER_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"

namespace PlayScene
{
class WinLayer : public cocos2d::Layer
{
private:
	cocos2d::Sprite* _spriteWin;
	cocos2d::ui::Button* _btnContinue;
	cocos2d::ui::Button* _btnToMenu;

public:
	WinLayer()
		: _spriteWin( nullptr ),
		  _btnContinue( nullptr ),
		  _btnToMenu( nullptr ) {}

	static WinLayer* create();

	bool init() override;

private:
	bool initGraphics();

	bool initEvents();

	void onBtnContinueClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

	void onBtnToMenuClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );
};
}
#endif
