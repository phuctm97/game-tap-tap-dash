#pragma once

#ifndef __LEVEL_SCENE_MAIN_LAYER_H__
#define __LEVEL_SCENE_MAIN_LAYER_H__



#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "Common/MyDirector.h"


#define MENU_ITEMS_COLS 3
#define MENU_ITEMS_ROWS 4
#define MENU_ITEMS_PAGE (MENU_ITEMS_COLS*MENU_ITEMS_ROWS)
#define MENU_ITEMS_TOTAL 30

#define MENU_PAGES ((MENU_ITEMS_TOTAL/MENU_ITEMS_PAGE)+1)
#define MENU_FRACTION (ccp(0.8,0.8))
#define MENU_ANCHOR (ccp(0.5,0.5))


namespace LevelScene
{
	class MainLayer : public cocos2d::Layer
	{
	private:
		cocos2d::ui::Button* btnStart;
		cocos2d::ui::Button* btnLevel;
		cocos2d::Sprite* background;
		cocos2d::Sprite* panelStart;
		cocos2d::ui::Button* btnBack;
		cocos2d::ui::Button* btnNext;
		cocos2d::ui::Button* btnPrev;
		int page = 0;

	public:
		static MainLayer* create();

		bool init() override;
		
		void reset();

	private:
		cocos2d::Vec2 CalculatePosition(int itemNum);
		void CreateLevelGrid();
		bool initGraphics();
		bool initEvents();
	};
}

#endif //!__INTRO_SCENE_MAIN_LAYER_H__
