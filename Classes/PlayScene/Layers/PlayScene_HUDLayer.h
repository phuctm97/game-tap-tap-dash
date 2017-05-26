#ifndef __PLAY_SCENE_HUD_LAYER_H__
#define __PLAY_SCENE_HUD_LAYER_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "PlayScene/Layers/PlayScene_PauseLayer.h"

namespace PlayScene
{
class HudLayer : public cocos2d::Layer
{
private:
	cocos2d::Sprite* _panelScore;
	cocos2d::ui::Button* _btnPause;
	cocos2d::Label* _lblScore;
	PauseLayer* _pauselayer;
	int _score;

public:
	HudLayer()
		: _panelScore( nullptr ),
		  _btnPause( nullptr ),
		  _lblScore( nullptr ),
		  _pauselayer( nullptr ),
		  _score( 0 ) {}

	static HudLayer* create();

	void setScore( int score );

	bool init() override;

private:
	bool initGraphics();

	bool initEvents();
	
	void onBtnPauseClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

};
}
#endif //!__PLAY_SCENE_HUD_LAYER_H__
