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

void HudLayer::setEnergy(float energy)
{
	_energybar->setPercent((energy / 1.0f)*100.0f);
}

bool PlayScene::HudLayer::init()
{
	if ( !Layer::init() ) return false;

	if ( !initGraphics() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

void HudLayer::showRetryLayer()
{
	_retrylayer->setVisible(true);
}

bool PlayScene::HudLayer::initGraphics()
{
	_panelScore = Sprite::create( "res/ui/hud/panel-hud.png" );
	_panelScore->setAnchorPoint( Vec2::ANCHOR_TOP_LEFT);
	_panelScore->setPosition( Vec2( 0, Director::getInstance()->getVisibleSize().height ) );
	addChild( _panelScore ,3);

	_lblScore = Label::createWithTTF("Score : 0", "fonts/Digital_tech.ttf",50.0f);
	_lblScore->setString( "Score : " + std::to_string( _score ) );
		_lblScore->setTextColor( Color4B::WHITE );
	_lblScore->setAnchorPoint( Vec2::ANCHOR_MIDDLE_LEFT );
	_lblScore->setPosition( Vec2( _panelScore->getContentSize().width * 0.1f, _panelScore->getContentSize().height * 0.5f ) );
	_panelScore->addChild( _lblScore );

	_btnPause = Button::create( "res/ui/hud/btn-pause.png", "res/UI/hud/btn-pause-clicked.png" );
	_btnPause->setAnchorPoint( Vec2::ANCHOR_MIDDLE_RIGHT );
	_btnPause->setPosition( Vec2( _panelScore->getContentSize().width * 0.95f,
	                              _panelScore->getContentSize().height *0.5f ) );
	_panelScore->addChild( _btnPause );

	createEnergyBar();

	_pauselayer = PauseLayer::create();
	_pauselayer->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_pauselayer->setPosition( Vec2::ZERO );
	addChild( _pauselayer );
	_pauselayer->setVisible( false );

	_retrylayer = RetryLayer::create();
	_retrylayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_retrylayer->setPosition(Vec2::ZERO);
	addChild(_retrylayer);
	_retrylayer->setVisible(false);

	return true;
}

bool PlayScene::HudLayer::initEvents()
{
	_btnPause->addTouchEventListener( CC_CALLBACK_2(HudLayer::onBtnPauseClicked, this) );

	return true;
}

void HudLayer::createEnergyBar()
{
	_energybarHud = Sprite::create("res/ui/hud/energy hub.png");
	_energybarHud->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_energybarHud->setPosition(Vec2(10, 
		Director::getInstance()->getVisibleSize().height - _panelScore->getContentSize().height * 1.05f));
	addChild(_energybarHud, 3);

	_energybar = LoadingBar::create("res/ui/hud/energy.png",100.0f);
	_energybar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_energybar->setDirection(LoadingBar::Direction::LEFT);
	_energybar->setPosition(Vec2(_energybarHud->getContentSize().width * 0.21f, _energybarHud->getContentSize().height*0.5f));
	_energybarHud->addChild(_energybar);
}

void HudLayer::onBtnPauseClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	experimental::AudioEngine::play2d("audios/click.mp3",false,0.1f);
	if ( type == Widget::TouchEventType::ENDED ) {
		_pauselayer->setVisible( true );
	}
}
}
