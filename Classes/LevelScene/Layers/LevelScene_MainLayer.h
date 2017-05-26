#ifndef __LEVEL_SCENE_MAIN_LAYER_H__
#define __LEVEL_SCENE_MAIN_LAYER_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"

namespace LevelScene
{
class MainLayer : public cocos2d::Layer
{
private:
	cocos2d::ui::Button* _btnStart;
	cocos2d::ui::Button* _btnLevel;
	cocos2d::Sprite* _background;
	cocos2d::Sprite* _panelStart;
	cocos2d::ui::Button* _btnBack;
	cocos2d::ui::Button* _btnNext;
	cocos2d::ui::Button* _btnPrev;
	int _page;

public:
	MainLayer()
		: _btnStart( nullptr ),
		  _btnLevel( nullptr ),
		  _background( nullptr ),
		  _panelStart( nullptr ),
		  _btnBack( nullptr ),
		  _btnNext( nullptr ),
		  _btnPrev( nullptr ),
		  _page( 0 ) {}

	static MainLayer* create();

	bool init() override;

	void reset();

private:
	cocos2d::Vec2 calculatePosition( int itemNum );

	void createLevelGrid();

	bool initGraphics();

	bool initEvents();

	void onBtnStartClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );
	
	void onBtnLevelClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

	void onBtnNextClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

	void onBtnPrevClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type );

};
}

#endif //!__INTRO_SCENE_MAIN_LAYER_H__
