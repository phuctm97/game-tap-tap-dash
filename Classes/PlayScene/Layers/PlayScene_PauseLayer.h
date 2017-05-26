#pragma once

#ifndef  __PLAY_SCENE_PAUSE_LAYER_H__

#define __PLAY_SCENE_PAUSE_LAYER_H__



#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "Common/MyDirector.h"


namespace PlayScene
{
	class PauseLayer : public cocos2d::Layer
	{
	private:
		cocos2d::Sprite* panel;

		ccos2d:o:Label* lbPause;
		cocos2d::ui::Button* btnResume;
		cocos2d::ui::Button* btnToMenu;
		



	public:

		static PauseLayer* create();
		bool init() override;
		bool initGraphics();
		bool initEvents();
	};

	


}
#endif#pragma once
