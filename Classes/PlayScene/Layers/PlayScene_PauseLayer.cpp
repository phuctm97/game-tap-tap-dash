#include "PlayScene_PauseLayer.h"
#include "Common/MyDirector.h"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace PlayScene
{
PauseLayer* PlayScene::PauseLayer::create()
{
	PauseLayer* p = new PauseLayer();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::PauseLayer::init()
{
	if ( !Layer::init() ) return false;

	if ( !initGraphics() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

bool PlayScene::PauseLayer::initGraphics()
{
	_lblPause = Label::createWithSystemFont( "Pause", "Arial", 200 );
	_lblPause->setContentSize( Size( Director::getInstance()->getVisibleSize().width / 4,
	                                 Director::getInstance()->getVisibleSize().height / 8 ) );
	_lblPause->setTextColor( Color4B::WHITE );
	_lblPause->setAnchorPoint( Vec2::ANCHOR_MIDDLE_BOTTOM );
	_lblPause->setPosition( Vec2( Director::getInstance()->getVisibleSize().width / 2
	                              , Director::getInstance()->getVisibleSize().height * 0.7f ) );
	addChild( _lblPause );

	_btnResume = Button::create( "res/btnResume.png", "res/btnResume2.png", "res/btnResume2.png" );
	_btnResume->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnResume->setPosition( Vec2( Director::getInstance()->getVisibleSize().width / 2
	                               , Director::getInstance()->getVisibleSize().height / 2 ) );
	addChild( _btnResume );

	_btnToMenu = Button::create( "res/btnToMenu.png", "res/btnToMenu2.png", "res/btnToMenu2.png" );
	_btnToMenu->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnToMenu->setPosition( Vec2( Director::getInstance()->getVisibleSize().width / 2
	                               , Director::getInstance()->getVisibleSize().height * 0.55f ) );
	addChild( _btnToMenu );

	return true;
}

bool PlayScene::PauseLayer::initEvents()
{
	_btnResume->addTouchEventListener( CC_CALLBACK_2(PauseLayer::onBtnResumeClicked, this) );

	_btnToMenu->addTouchEventListener( CC_CALLBACK_2(PauseLayer::onBtnToMenuClicked, this) );

	return true;
}

void PauseLayer::onBtnResumeClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		//resume game
		//tat

		this->setVisible( false );
	}
}

void PauseLayer::onBtnToMenuClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {

		Director::getInstance()->replaceScene( MyDirector::getInstance()->getIntroScene() );
	}
}
}
