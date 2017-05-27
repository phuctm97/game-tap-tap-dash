#ifndef __PLAY_SCENE_HUD_LAYER_H__
#define __PLAY_SCENE_HUD_LAYER_H__

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <AudioEngine.h>
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

	cocos2d::Sprite* _energybarHud;
	cocos2d::ui::LoadingBar* _energybar;
	int _score;

public:
	HudLayer()
		: _panelScore( nullptr ),
		  _btnPause( nullptr ),
		  _lblScore( nullptr ),
		  _pauselayer( nullptr ),
		  _energybarHud( nullptr ),
		  _energybar( nullptr ),
		  _score( 0 ) {}

	static HudLayer* create();

	void setScore( int score );

	void setEnergy( float energy );

	bool init() override;

private:
	bool initGraphics();

	bool initEvents();

	void createEnergyBar();

	void onBtnPauseClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );
};
}
#endif //!__PLAY_SCENE_HUD_LAYER_H__
