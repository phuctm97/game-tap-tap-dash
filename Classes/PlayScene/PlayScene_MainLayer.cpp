#include "PlayScene_MainLayer.h"
#include "Common/MyDirector.h"
using namespace cocos2d;

namespace PlayScene
{
MainLayer* MainLayer::create( IPlayer* player )
{
	MainLayer* p = new MainLayer( player );
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

	initGraphics();

	initEvents();

	initGame();

	return true;
}

void MainLayer::reset()
{
	
}

void MainLayer::initGraphics()
{
	addChild( _player );
	_player->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_player->setVisible( false );
}

void MainLayer::initEvents()
{
	scheduleUpdate();

	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2( MainLayer::onTouchBegan, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerTouch, this );

	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2( MainLayer::onKeyReleased, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerKeyboard, this );
}

void MainLayer::onKeyReleased( cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e )
{
	if(key == EventKeyboard::KeyCode::KEY_BACK || key == EventKeyboard::KeyCode::KEY_ESCAPE) {
		MyDirector::getInstance()->end();
	}
}

void MainLayer::initGame() {}

void MainLayer::update( float dt )
{
	if ( !_playing ) return;
}

bool MainLayer::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e )
{
	if ( !_playing ) {
		startGame();
		return true;
	}

	if ( _player->getState() == IPlayer::IDLE )
		_player->runToLeft();

	if ( _player->getState() == IPlayer::RUNNING_TO_LEFT )
		_player->runToRight();

	if ( _player->getState() == IPlayer::RUNNING_TO_RIGHT )
		_player->runToLeft();

	return true;
}

void MainLayer::startGame()
{
	_player->setPosition( Director::getInstance()->getVisibleSize().width / 2,
	                      Director::getInstance()->getVisibleSize().height * 0.1f );
	_player->setVisible( true );
	_player->idle();

	_playing = true;
}

void MainLayer::stopGame()
{
	_playing = false;
	_player->setVisible( false );
}
}
