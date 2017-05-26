#pragma once

#ifndef  __PLAY_SCENE_WIN_LAYER_H__

#define __PLAY_SCENE_WIN_LAYER_H__



#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "PlayScene/Layers/PlayScene_WinLayer.h"

namespace PlayScene
{
	class WinLayer : public cocos2d::Layer
	{
	private:
		cocos2d::Sprite* spriteWin;

		cocos2d::ui::Button* btnContinue;
		cocos2d::ui::Button* btnToMenu;

	public:

		static WinLayer* create();
		
		bool init() override;
		bool initGraphics();
		bool initEvents();
	};

}
#endif
