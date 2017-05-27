#include "PlayScene_MainLayer.h"
#include "Common/MyDirector.h"
using namespace cocos2d;

#define TIME_TO_START 3

namespace PlayScene
{
MainLayer::~MainLayer() {}

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
	if ( !Layer::init() ) return false;

	initGraphics();

	initGame();

	initEvents();

	return true;
}

void MainLayer::initGraphics()
{
	// background
	auto drawNode = DrawNode::create();
	drawNode->drawSolidCircle( Vec2( Director::getInstance()->getVisibleSize().width * 0.5f,
	                                 Director::getInstance()->getVisibleSize().height * 0.5f ),
	                           Director::getInstance()->getVisibleSize().height * 2, 360, 10,
	                           Color4F( Color3B( 117, 211, 80 ) ) );
	addChild( drawNode, 0 );

	// house
	_house = Sprite::create( "res/play-scene/house.png" );
	_house->setVisible( false );
	addChild( _house, 25 );

	// bus
	_bus = Sprite::create( "res/play-scene/bus-0.png" );
	_bus->setVisible( false );
	addChild( _bus, 25 );

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
	_map->reset( Vec2::ZERO );
	_player->reset( Vec2::ZERO );

	// reset game state
	_state = WAIT_FOR_PLAY;

	// start intro cut
	startIntroCut();
}

void MainLayer::startGame()
{
	_state = PLAYING;

	_map->scroll();

	_player->run();

	updateMapScrollDirection();

	setGameSpeed( 6.0f );
}

void MainLayer::interactGame() const
{
	// rest node
	if ( _map->getCurrentNode()->isRestNode() ) {
		_map->getCurrentNode()->decreaseRestCode();
	}
	// normal node
	else {
		switch ( _map->nextControl() ) {
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

	// update house position
	if ( _house->isVisible() ) {
		_house->setPosition( _houseAnchor->getPosition() - _houseOffset );

		if ( _house->getPositionY() < -_house->getContentSize().height * 0.5f ) {
			_house->setVisible( false );
		}
	}

	// update bus
	if( _map->isPushedTail() ) {
		_bus->setVisible( true );
		_bus->setPosition( _map->getBusStopNode()->getPosition() );
	}

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
	if ( _player->getState() != IPlayer::FLYING && currentNode->checkPositionInside( _player->getPosition() ) == GameMapNode::POSITION_OUTSIDE ) {

		// exception
		if ( _map->isEnd() ) {
			throw "Player exit last map node";
		}

		if ( _map->nextNode()->checkPositionInside( _player->getPosition() ) == GameMapNode::POSITION_INSIDE ) {
			onPassedNode( currentNode );
		}
		// drop out the road
		else {
			loseGame();
		}
	}
}

void MainLayer::setGameSpeed( float speed )
{
	_gameSpeed = speed;

	_map->setScrollSpeed( speed );

	_player->setSpeed( speed );
}

void MainLayer::startIntroCut()
{
	// reset map position
	auto mapStartPosition = Vec2( Director::getInstance()->getVisibleSize().width * 0.5f,
	                              _map->getCurrentNode()->getContentSize().height * 0.5f );
	_map->reset( mapStartPosition );

	// reset house
	auto playerStartPosition = Vec2( Director::getInstance()->getVisibleSize().width * 0.5f
	                                 + _map->getCurrentNode()->getContentSize().width * 0.5f
	                                 + _house->getContentSize().width * 0.5f
	                                 + 50,
	                                 Director::getInstance()->getVisibleSize().height * 0.5f );
	_house->setPosition( playerStartPosition );
	_house->setVisible( true );

	// reset bus
	auto busStartPosition = Vec2( Director::getInstance()->getVisibleSize().width * 0.5f,
	                              -_bus->getContentSize().height * 0.5f );
	_bus->setPosition( busStartPosition );
	_bus->setVisible( true );

	// reset player in house
	_player->reset( playerStartPosition );

	// bus run
	_bus->stopAllActions();
	_bus->runAction( Sequence::create( MoveBy::create( 1.5f, Vec2( 0, Director::getInstance()->getVisibleSize().height + _bus->getContentSize().height ) ),
	                                   Hide::create(),
	                                   nullptr ) );
	_bus->runAction( Sequence::create( DelayTime::create( 0.7f ),
	                                   CallFunc::create( CC_CALLBACK_0(MainLayer::postIntroCut0, this) ),
	                                   nullptr ) );
}

void MainLayer::postIntroCut0()
{
	// player walk out house
	_player->setSpeed( 5.0f );
	_player->stopAllActions();

	_player->run();
	_player->turnLeft();

	_player->runAction( Sequence::create( MoveTo::create( 1.5f, Director::getInstance()->getVisibleSize() * 0.5f ),
	                                      DelayTime::create( 0.2f ),
	                                      CallFunc::create( CC_CALLBACK_0( MainLayer::postIntroCut1, this ) ),
	                                      nullptr ) );
}

void MainLayer::postIntroCut1()
{
	_player->idle();

	// add popup
	auto popup = Sprite::create( "res/play-scene/ui/popup.png" );
	popup->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	popup->setPosition( _player->getPositionX(),
	                    _player->getPositionY()
	                    + _player->getContentSize().height * 0.5f
	                    + popup->getContentSize().height * 0.5f + 10 );
	addChild( popup, 30, "popup" );

	// popup label
	auto label = Label::createWithTTF( "...", "res/font/Bungee-Regular.ttf", 20 );
	label->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	label->setTextColor( Color4B::BLACK );
	label->setPosition( popup->getContentSize().width * 0.5f,
	                    popup->getContentSize().height * 0.6f );
	popup->addChild( label );

	// next post intro
	runAction( Sequence::create( DelayTime::create( 1.0f ),
	                             CallFunc::create( CC_CALLBACK_0( MainLayer::postIntroCut2, this ) ), nullptr ) );
}

void MainLayer::postIntroCut2()
{
	// remove popup
	removeChildByName( "popup" );

	_player->turnRight();

	// update map current node
	while ( _map->getCurrentNode()->checkPositionInside( _player->getPosition() ) != GameMapNode::POSITION_INSIDE )
		_map->nextNode();

	_houseAnchor = _map->getNode( _map->getCurrentNodeIndex() + 2 );
	_houseOffset = _houseAnchor->getPosition() - _house->getPosition();

	startGame();
}
}
