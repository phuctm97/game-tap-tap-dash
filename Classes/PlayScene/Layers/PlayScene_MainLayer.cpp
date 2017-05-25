#include "PlayScene_MainLayer.h"
#include "Common/MyDirector.h"
using namespace cocos2d;

namespace PlayScene
{
MainLayer* MainLayer::create( IPlayer* player, IGameMap* map )
{
	MainLayer* p = new MainLayer( player, map );
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

	initGame();

	initEvents();

	return true;
}

void MainLayer::initGraphics()
{
	// map
	addChild( _map, 10 );

	// player
	addChild( _player, 20 );
	_player->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
}

void MainLayer::initGame()
{
	reset();
}

void MainLayer::initEvents()
{
	scheduleUpdate();

	// touch: main control
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2( MainLayer::onTouchBegan, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerTouch, this );

	// keyboard: allow exit
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2( MainLayer::onKeyReleased, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerKeyboard, this );
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
	switch ( _state ) {

		// start game
	case WAIT_FOR_PLAY: {
		startGame();
	}
		break;

		// gameplay
	case PLAYING: {
		switch ( _map->getNextControl() ) {
		case IGameMap::TURN_LEFT: {
			_player->turnLeft();
		}
			break;
		case IGameMap::TURN_RIGHT: {
			_player->turnRight();
		}
			break;
		case IGameMap::FLY: {
			_player->fly();
		}
			break;
		}
		break;
	}
	}

	return true;
}

void MainLayer::reset()
{
	auto startPosition = Vec2( Director::getInstance()->getVisibleSize().width / 2,
	                           Director::getInstance()->getVisibleSize().height * 0.1f );

	_player->reset( startPosition );
	_map->reset( startPosition );

	_state = WAIT_FOR_PLAY;
}

void MainLayer::startGame()
{
	_state = PLAYING;

	_map->scroll();

	_player->run();
}

void MainLayer::winGame()
{
	_player->win();

	_map->stop();

	_state = GAME_OVER;
}

void MainLayer::loseGame()
{
	_player->die();

	_map->stop();

	_state = GAME_OVER;
}

void MainLayer::update( float dt )
{
	if ( _state != PLAYING ) return;

	if ( _map->isEnd() ) {
		winGame();
	}

	if ( _map->getCurrentNode()->checkPositionInside( _player->getPosition() ) == GameMapNode::POSITION_OUTSIDE ) {
		if ( _map->isEnd() ) {
			throw "Player exit last map node";
		}

		if ( _map->nextNode()->checkPositionInside( _player->getPosition() ) == GameMapNode::POSITION_OUTSIDE ) {
			loseGame();
		}
	}
}
}
