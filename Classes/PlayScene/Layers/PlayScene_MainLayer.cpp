#include "PlayScene_MainLayer.h"
#include "Common/MyDirector.h"
using namespace cocos2d;

#define TIME_TO_START 1

namespace PlayScene
{
MainLayer* MainLayer::create( IPlayer* player, GameMap* map )
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
	if ( !LayerColor::initWithColor( Color4B::WHITE ) ) return false;

	initGraphics();

	initGame();

	initEvents();

	return true;
}

void MainLayer::initGraphics()
{
	// label time to start
	_labelTimeToStart = Label::createWithTTF( "0", "res/font/Bungee-Regular.ttf", 150 );
	_labelTimeToStart->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
	                                Director::getInstance()->getVisibleSize().height * 0.5f );
	_labelTimeToStart->setTextColor( Color4B::WHITE );
	_labelTimeToStart->enableOutline( Color4B::BLACK, 7 );
	_labelTimeToStart->enableShadow( Color4B::BLACK, Size( 7, -7 ) );
	addChild( _labelTimeToStart, 30 );

	// map
	addChild( _map, 10 );

	// player
	addChild( _player, 20 );
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
	// TODO: back to level scene
	if ( key == EventKeyboard::KeyCode::KEY_BACK || key == EventKeyboard::KeyCode::KEY_ESCAPE ) {
		MyDirector::getInstance()->end();
	}
}

bool MainLayer::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e )
{
	if ( _state == PLAYING ) {
		interactGame();
	}

	return true;
}

void MainLayer::updateMapScrollDirection() const
{
	switch ( _player->getDirection() ) {
	case IPlayer::DIRECTION_UP: _map->setScrollDirection( GameMap::SCROLL_DOWN );
		break;
	case IPlayer::DIRECTION_DOWN: _map->setScrollDirection( GameMap::SCROLL_UP );
		break;
	case IPlayer::DIRECTION_LEFT: _map->setScrollDirection( GameMap::SCROLL_RIGHT );
		break;
	case IPlayer::DIRECTION_RIGHT: _map->setScrollDirection( GameMap::SCROLL_LEFT );
		break;
	}
}

void MainLayer::reset()
{
	// reset map and player
	auto startPosition = Vec2( Director::getInstance()->getVisibleSize().width / 2,
	                           Director::getInstance()->getVisibleSize().height * 0.1f );
	_map->reset( startPosition );
	_player->reset( startPosition );
	_map->setScrollSpeed( 5.0f );
	updateMapScrollDirection();

	// reset game state
	_state = WAIT_FOR_PLAY;

	// start timer
	startCountdownTimeToStart();
}

void MainLayer::startGame()
{
	stopCountdownTimeToStart();

	_state = PLAYING;

	_map->scroll();

	_player->run();
}

void MainLayer::interactGame() const
{
	// rest node
	if ( _map->getCurrentNode()->isRestNode() ) {
		_map->getCurrentNode()->decreaseRestCode();
	}
	// normal node
	else {
		switch ( _map->getNextControl() ) {
		case GameMap::TURN_LEFT: {
			_player->turnLeft();
		}
			break;
		case GameMap::TURN_RIGHT: {
			_player->turnRight();
		}
			break;
		case GameMap::FLY: {
			_player->fly();
		}
			break;
		}
	}

	updateMapScrollDirection();
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

void MainLayer::onPassedNode( GameMapNode* node ) const
{
	if ( node->isRestNode() && node->getRestCode() == 0 ) {
		_player->increaseEnergy( node->getRestEnergy() );
	}

	// increase score
}

void MainLayer::update( float dt )
{
	if ( _state != PLAYING ) return;

	// finish map
	if ( _map->isEnd() ) {
		winGame();
		return;
	}

	// player out of energy
	if ( _player->getEnergy() == 0 ) {
		loseGame();
	}

	// check position
	auto currentNode = _map->getCurrentNode();
	if ( currentNode->checkPositionInside( _player->getPosition() ) == GameMapNode::POSITION_OUTSIDE ) {

		// exception
		if ( _map->isEnd() ) {
			throw "Player exit last map node";
		}

		// pass to next node
		if ( _map->nextNode()->checkPositionInside( _player->getPosition() ) == GameMapNode::POSITION_INSIDE ) {
			onPassedNode( currentNode );
		}
		// drop out the road
		else {
			loseGame();
		}
	}
}

void MainLayer::startCountdownTimeToStart()
{
	_timeToStart = TIME_TO_START;
	_labelTimeToStart->setVisible( true );

	// show label
	std::stringstream stringBuilder;
	stringBuilder << _timeToStart;

	_labelTimeToStart->setString( stringBuilder.str() );
	_labelTimeToStart->setVisible( true );

	schedule( CC_CALLBACK_1( MainLayer::countdownTimeToStart, this ), 1.0f, "updateTimeToStart" );
}

void MainLayer::stopCountdownTimeToStart()
{
	_timeToStart = TIME_TO_START;
	_labelTimeToStart->setVisible( false );

	unschedule( "updateTimeToStart" );
}

void MainLayer::countdownTimeToStart( float dt )
{
	if ( _state != WAIT_FOR_PLAY ) return;

	// update time
	_timeToStart -= 1;

	// update label
	std::stringstream stringBuilder;
	stringBuilder << _timeToStart;

	_labelTimeToStart->setString( stringBuilder.str() );

	if ( _timeToStart <= 0 ) {
		startGame();
	}
}
}
