#include "PlayScene_Player.h"
using namespace cocos2d;

namespace PlayScene
{
Player::~Player()
{
	CC_SAFE_RELEASE( _actionRun );
	CC_SAFE_RELEASE( _actionTurnLeft );
	CC_SAFE_RELEASE( _actionTurnRight );
	CC_SAFE_RELEASE( _actionFly );
}

Player* Player::create()
{
	auto p = new Player();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE( p );
	return nullptr;
}

bool Player::init()
{
	if ( !IPlayer::init() ) return false;

	if ( !initSprite() ) return false;

	if ( !initActions() ) return false;

	if ( !initEvents() ) return false;

	if ( !initContent() ) return false;

	return true;
}

bool Player::initSprite()
{
	// sprite
	_sprite = Sprite::create( "res/player.png", Rect( 0, 0, 130, 125 ) );
	if ( !_sprite ) return false;

	addChild( _sprite );
	_sprite->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_sprite->setPosition( 100, 300 );
	setContentSize( _sprite->getContentSize() );

	return true;
}

bool Player::initActions()
{
	// run
	createAnimationRun();

	// turn left
	createAnimationTurnLeft();

	// turn right
	createAnimationTurnRight();

	// fly
	createAnimationFly();

	return true;
}

bool Player::initEvents()
{
	scheduleUpdate();

	return true;
}

bool Player::initContent()
{
	_state = IDLE;

	return true;
}

void Player::createAnimationRun()
{
	Vector<SpriteFrame*> frames;
	frames.reserve( 3 );
	frames.pushBack( SpriteFrame::create( "res/player.png", Rect( 0, 0, 130, 125 ) ) );
	frames.pushBack( SpriteFrame::create( "res/player.png", Rect( 130, 0, 130, 125 ) ) );
	frames.pushBack( SpriteFrame::create( "res/player.png", Rect( 260, 0, 130, 125 ) ) );
	_actionRun = Animate::create( Animation::createWithSpriteFrames( frames, 0.5f ) );
	_actionRun->retain();
}

void Player::createAnimationTurnLeft()
{
	_actionTurnLeft = RotateBy::create( 0.1f, -90.0f );
	_actionTurnLeft->retain();
}

void Player::createAnimationTurnRight()
{
	_actionTurnRight = RotateBy::create( 0.1f, 90.0f );
	_actionTurnRight->retain();
}

void Player::createAnimationFly()
{
	DelayTime* delay = DelayTime::create( 0.5f );
	ScaleBy* zoomin = ScaleBy::create( 0.5f, 2.0f );
	ScaleBy* zoomout = ScaleBy::create( 0.5f, 0.5f );
	_actionFly = Sequence::create( zoomin, delay, zoomout, delay, nullptr );
	_actionFly->retain();
}

int Player::getState() const
{
	return _state;
}

int Player::getDirection() const
{
	throw "not implemented";
}

float Player::getEnergy() const
{
	throw "not implemented";
}

void Player::reset( const cocos2d::Vec2& position )
{
	setPosition( position );

	idle();
}

void Player::idle()
{
	stopAllActions();

	// run animation idle

	// run audio idle

	_state = IDLE;
}

void Player::run()
{
	if ( _state != IDLE ) return;

	stopAllActions();

	// run animation running
	_sprite->runAction( _actionRun );

	// play audio running

	_state = RUNNING;
}

void Player::turnLeft()
{
	if ( _state == DEAD ) return;

	// run animation turn left
	_sprite->runAction( _actionTurnLeft );

	// run audio turn left
}

void Player::turnRight()
{
	if ( _state == DEAD ) return;

	// run animation turn right
	_sprite->runAction( _actionTurnRight );

	// run audio turn right
}

void Player::fly()
{
	if ( _state == DEAD ) return;

	// run animation fly
	_sprite->runAction( _actionFly );

	// run audio fly
}

void Player::die()
{
	if ( _state == DEAD ) return;

	// run animation die

	_sprite->setColor( Color3B::BLACK );

	// run audio die

	_state = DEAD;
}

void Player::win()
{
	if ( _state == DEAD ) return;

	stopAllActions();

	// run animation win

	// run audio win

	_state = IDLE;
}

void Player::increaseEnergy( float energy )
{
	
}
}
