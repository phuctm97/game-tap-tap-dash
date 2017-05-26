#pragma once

#ifndef  __PLAY_SCENE_HUD_LAYER_H__

#define __PLAY_SCENE_HUD_LAYER_H__



#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "PlayScene/Layers/PlayScene_PauseLayer.h"

namespace PlayScene
{
	class HudLayer : public cocos2d::Layer
	{
	private:
		cocos2d::Sprite* panelScore;
		cocos2d::ui::Button* btnPause;
		cocos2d::Label* lbScore;
		PauseLayer* pauselayer;
		int _score = 0;
	
	
	public:

		static HudLayer* create();
		void setScore(int score);
		bool init() override;
		bool initGraphics();
		bool initEvents();
	};

}
#endif