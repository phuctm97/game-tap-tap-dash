#include "PlayScene/Layers/PlayScene_WinLayer.h"
#include "Common/MyDirector.h"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace PlayScene
{
WinLayer* PlayScene::WinLayer::create()
{
	WinLayer* p = new WinLayer();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::WinLayer::init()
{
	if ( !Layer::init() ) return false;

	if ( !initGraphics() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

bool PlayScene::WinLayer::initGraphics()
{
	_btnContinue = Button::create( "res/btnContinue.png", "res/btnContinue2.png", "res/btnContinue2.png" );
	_btnContinue->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnContinue->setPosition( Vec2( Director::getInstance()->getVisibleSize().width / 2,
	                                 Director::getInstance()->getVisibleSize().height / 2 ) );
	addChild( _btnContinue );

	_btnToMenu = Button::create( "res/btnToMenu.png", "res/btnToMenu2.png", "res/btnToMenu2.png" );
	_btnToMenu->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnToMenu->setPosition( Vec2( Director::getInstance()->getVisibleSize().width / 2
	                               , Director::getInstance()->getVisibleSize().height * 0.55f ) );
	addChild( _btnToMenu );

	return true;
}

bool PlayScene::WinLayer::initEvents()
{
	_btnContinue->addTouchEventListener( CC_CALLBACK_2(WinLayer::onBtnContinueClicked, this) );

	_btnToMenu->addTouchEventListener( CC_CALLBACK_2(WinLayer::onBtnToMenuClicked, this) );

	return true;
}

void WinLayer::onBtnContinueClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		//next level
	}
}

void WinLayer::onBtnToMenuClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		Director::getInstance()->replaceScene( MyDirector::getInstance()->getIntroScene() );
	}
}
}
