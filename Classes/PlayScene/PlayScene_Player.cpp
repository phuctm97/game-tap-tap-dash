#include "PlayScene_Player.h"
using namespace cocos2d;

namespace PlayScene
{
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

	if ( !initEvents() ) return false;

	if ( !initContent() ) return false;

	return true;
}

bool Player::initSprite()
{
	// sample sprite
	_sprite = Sprite::create( "res/blank.png" );
	if ( !_sprite ) return false;

	addChild( _sprite );
	_sprite->setTextureRect( Rect( 0, 0, 200, 200 ) );
	_sprite->setColor( Color3B::RED );
	_sprite->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_sprite->setPosition( Vec2::ZERO );
	setContentSize( _sprite->getContentSize() );

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

int Player::getState() const
{
	return _state;
}

void Player::reset( const cocos2d::Vec2& position )
{
	_state = IDLE;

	setPosition( position );
}

void Player::run()
{
	if ( _state != IDLE ) return;

	stopAllActions();

	// run animation running

	// play audio running

	_state = RUNNING;
}

void Player::turnLeft()
{
	if ( _state == DEAD ) return;

	// run animation turn left

	// run audio turn left
}

void Player::turnRight()
{
	if( _state == DEAD ) return;

	// run animation turn right

	// run audio turn right
}

void Player::fly()
{
	if( _state == DEAD ) return;

	// run animation fly

	// run audio fly
}

void Player::die()
{
	if( _state == DEAD ) return;

	// run animation die

	// run audio die

	_state = DEAD;
}

void Player::update( float dt )
{
	// update position based on state
}
}
