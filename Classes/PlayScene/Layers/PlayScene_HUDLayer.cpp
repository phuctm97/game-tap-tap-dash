#include "PlayScene_HUDLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace PlayScene
{
HudLayer* PlayScene::HudLayer::create()
{
	HudLayer* p = new HudLayer();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

void PlayScene::HudLayer::setScore( int score )
{
	_score = score;

	std::stringstream stringBuilder;
	stringBuilder << "Score: " << score;

	_lblScore->setString( stringBuilder.str() );
}

bool PlayScene::HudLayer::init()
{
	if ( !Layer::init() ) return false;

	if ( !initGraphics() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

bool PlayScene::HudLayer::initGraphics()
{
	_panelScore = Sprite::create( "res/blank.png" );
	_panelScore->setTextureRect( Rect( 0, 0, Director::getInstance()->getVisibleSize().width,
	                                   Director::getInstance()->getVisibleSize().height * 0.05f ) );
	_panelScore->setAnchorPoint( Vec2::ANCHOR_TOP_LEFT );
	_panelScore->setColor( Color3B::MAGENTA );
	_panelScore->setPosition( Vec2( 0, Director::getInstance()->getVisibleSize().height ) );
	addChild( _panelScore );

	_lblScore = Label::create();
	_lblScore->setString( "Score : " + std::to_string( _score ) );
	_lblScore->setContentSize( Size( _panelScore->getContentSize().width * 0.3f, _panelScore->getContentSize().height * 0.9f ) );
	_lblScore->setSystemFontSize( 30.0f );
	_lblScore->setSystemFontName( "Arial" );
	_lblScore->setTextColor( Color4B::BLUE );
	_lblScore->setAnchorPoint( Vec2::ANCHOR_MIDDLE_LEFT );
	_lblScore->setPosition( Vec2( _panelScore->getContentSize().width * 0.1f, _panelScore->getContentSize().height * 0.5f ) );
	_panelScore->addChild( _lblScore );

	_btnPause = Button::create( "res/btnPause.png", "res/btnPause2.png" );
	_btnPause->setAnchorPoint( Vec2::ANCHOR_MIDDLE_RIGHT );
	_btnPause->setPosition( Vec2( _panelScore->getContentSize().width * 0.9f,
	                              _panelScore->getContentSize().height / 2 ) );
	_panelScore->addChild( _btnPause );

	_pauselayer = PauseLayer::create();
	_pauselayer->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_pauselayer->setPosition( Vec2::ZERO );
	addChild( _pauselayer );
	_pauselayer->setVisible( false );

	return true;
}

bool PlayScene::HudLayer::initEvents()
{
	_btnPause->addTouchEventListener( CC_CALLBACK_2(HudLayer::onBtnPauseClicked, this) );

	return true;
}

void HudLayer::onBtnPauseClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		_pauselayer->setVisible( true );
	}
}
}
