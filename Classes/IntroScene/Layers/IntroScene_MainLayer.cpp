#include "IntroScene_MainLayer.h"
#include "Common/MyDirector.h"
using namespace cocos2d;
using namespace cocos2d::ui;

namespace IntroScene
{
MainLayer* MainLayer::create()
{
	MainLayer* p = new MainLayer();
	if( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE( p );
	return nullptr;
}

bool MainLayer::init()
{
	if( !Layer::init() ) return false;

	if( !initGraphics() ) return false;

	if( !initEvents() ) return false;

	return true;
}

bool MainLayer::initGraphics()
{
	_background = Sprite::create( "res/ui/intro-scene/background.png" );
	_background->setContentSize( Director::getInstance()->getVisibleSize() );
	_background->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_background->setPosition( Vec2::ZERO );
	addChild( _background );

	_logo = Sprite::create( "res/ui/intro-scene/logo-on.png" );

	_logo->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_logo->setPosition( Vec2( Director::getInstance()->getVisibleSize().width*0.5f, Director::getInstance()->getVisibleSize().height * 0.6 ) );

	addChild( _logo, 3 );

	createLogoAnimation();

	_layer = LayerColor::create();
	_layer->initWithColor( Color4B( 0, 0, 0, 120 ) );
	_layer->setContentSize( _background->getContentSize() );
	_layer->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_layer->setPosition( Vec2::ZERO );
	_background->addChild( _layer );

	_btnStart = Button::create( "res/ui/intro-scene/btn-play.png", "res/ui/intro-scene/btn-play-clicked.png" );
	_btnStart->setAnchorPoint( Vec2::ANCHOR_MIDDLE_TOP );
	_btnStart->setPosition( Vec2( Director::getInstance()->getVisibleSize().width*0.5f,
																Director::getInstance()->getVisibleSize().height*0.3f ) );
	_background->addChild( _btnStart );

	_btnFb = Button::create( "res/ui/intro-scene/fb.png", "res/ui/intro-scene/fb-clicked.png" );
	_btnFb->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnFb->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.2f,
														 Director::getInstance()->getVisibleSize().height * 0.1f ) );
	_background->addChild( _btnFb );

	_chkSound = CheckBox::create( "res/ui/intro-scene/speaker-off.png", "res/ui/intro-scene/speaker-on.png",
																"res/ui/intro-scene/speaker-on.png", "res/ui/intro-scene/speaker-off.png", "res/UI/IntroScene/speaker-off.png" );
	_chkSound->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_chkSound->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.8f,
																Director::getInstance()->getVisibleSize().height * 0.1f ) );
	_background->addChild( _chkSound );

	return true;
}

bool MainLayer::initEvents()
{
	_btnStart->addTouchEventListener( CC_CALLBACK_2( MainLayer::onBtnStartClicked, this ) );

	_btnFb->addTouchEventListener( CC_CALLBACK_2( MainLayer::onBtnFbClicked, this ) );

	_chkSound->addTouchEventListener( CC_CALLBACK_2( MainLayer::onChkSoundClicked, this ) );

	return true;
}

void MainLayer::onBtnStartClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{

	if( type == Widget::TouchEventType::ENDED ) {
		//Director::getInstance()->replaceScene( MyDirector::getInstance()->getLevelScene() );
	}
}


void MainLayer::onBtnFbClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if( type == Widget::TouchEventType::ENDED ) {
		// do something
	}
}

void MainLayer::onChkSoundClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if( type == Widget::TouchEventType::ENDED ) {
		if( _chkSound->isSelected() == true ) {}
		else {}
	}
}

void MainLayer::createLogoAnimation()
{


	Vector<SpriteFrame*> frames;
	frames.reserve( 2 );

	frames.pushBack( SpriteFrame::create( "res/ui/intro-scene/logo-on.png", Rect( 0, 0, 1620, 2880 ) ) );
	frames.pushBack( SpriteFrame::create( "res/ui/intro-scene/logo-off.png", Rect( 0, 0, 1620, 2880 ) ) );

	auto animate = Animate::create( Animation::createWithSpriteFrames( frames, 0.3f ) );
	_logo->runAction( RepeatForever::create( animate ) );
}

void MainLayer::reset() {}
}
