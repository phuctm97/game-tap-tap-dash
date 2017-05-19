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

void MainLayer::initGame()
{
	reset();
}

void MainLayer::onKeyReleased( cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e )
{
	// allow exit game
	if ( key == EventKeyboard::KeyCode::KEY_BACK || key == EventKeyboard::KeyCode::KEY_ESCAPE ) {
		MyDirector::getInstance()->end();
	}
}

bool MainLayer::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e )
{
	if ( !_playing ) {
		startGame();
		return true;
	}

	return true;
}

void MainLayer::reset()
{
	_player->reset( Vec2( Director::getInstance()->getVisibleSize().width / 2,
												Director::getInstance()->getVisibleSize().height * 0.1f ) );
	_playing = false;
}

void MainLayer::startGame()
{
	_player->setVisible( true );

	_playing = true;
}

void MainLayer::stopGame()
{
	_player->setVisible( false );
	
	_playing = false;
}
}
