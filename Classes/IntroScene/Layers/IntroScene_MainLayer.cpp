#include "IntroScene_MainLayer.h"
#include "Common/MyDirector.h"
using namespace cocos2d;
using namespace cocos2d::ui;

namespace IntroScene
{
MainLayer* MainLayer::create()
{
	MainLayer* p = new MainLayer();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE( p );
	return nullptr;
}

bool MainLayer::init()
{
	if ( !Layer::init() ) return false;

	if ( !initGraphics() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

bool MainLayer::initGraphics()
{
	_background = Sprite::create( "res/background.jpg" );
	_background->setContentSize( Director::getInstance()->getVisibleSize() );
	_background->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_background->setPosition( Vec2::ZERO );
	addChild( _background );

	_logo = Sprite::create( "res/Logo.png" );
	_logo->setContentSize( Size( Director::getInstance()->getVisibleSize().width
	                             , Director::getInstance()->getVisibleSize().height * 0.3f ) );
	_logo->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_logo->setPosition( Vec2( 0, Director::getInstance()->getVisibleSize().height * 0.7f ) );
	_background->addChild( _logo );

	_btnStart = Button::create( "res/btnPlay.png", "res/btnPlay2.png" );
	_btnStart->setAnchorPoint( Vec2::ANCHOR_MIDDLE_TOP );
	_btnStart->setPosition( Vec2( Director::getInstance()->getVisibleSize().width / 2,
	                              Director::getInstance()->getVisibleSize().height / 2 ) );
	_background->addChild( _btnStart );

	_btnFb = Button::create( "res/iconfacebook.png", "res/iconfacebook2.png" );
	_btnFb->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnFb->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.3f,
	                           Director::getInstance()->getVisibleSize().height * 0.1f ) );
	_background->addChild( _btnFb );

	_chkSound = CheckBox::create( "res/soundOff.png", "res/soundOn.png", "res/soundOn.png", "res/soundOff.png", "res/soundOff.png" );
	_chkSound->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_chkSound->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.7f,
	                              Director::getInstance()->getVisibleSize().height * 0.1f ) );
	_background->addChild( _chkSound );

	return true;
}

bool MainLayer::initEvents()
{
	_btnStart->addTouchEventListener( CC_CALLBACK_2(MainLayer::onBtnStartClicked, this) );

	_btnFb->addTouchEventListener( CC_CALLBACK_2( MainLayer::onBtnFbClicked, this ) );

	_chkSound->addTouchEventListener( CC_CALLBACK_2( MainLayer::onChkSoundClicked, this ) );

	return true;
}

void MainLayer::onBtnStartClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		Director::getInstance()->replaceScene( MyDirector::getInstance()->getLevelScene() );
	}
}

void MainLayer::onBtnFbClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		// do something
	}
}

void MainLayer::onChkSoundClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		if ( _chkSound->isSelected() == true ) {}
		else {}
	}
}

void MainLayer::reset() { }
}
