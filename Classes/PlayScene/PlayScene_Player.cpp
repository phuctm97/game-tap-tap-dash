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

	if ( !initContent() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

bool Player::initSprite()
{
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

bool Player::initContent()
{
	_state = IDLE;

	return true;
}

bool Player::initEvents()
{
	scheduleUpdate();

	return true;
}

int Player::getState()
{
	return _state;
}

int Player::idle()
{
	stopAllActions();

	// run animation idle

	// play audio idle

	_state = IDLE;

	return 0;
}

int Player::runToLeft()
{
	stopAllActions();

	// run animation running to left

	// play audio running to left

	_state = RUNNING_TO_LEFT;

	return 0;
}

int Player::runToRight()
{
	stopAllActions();

	// run animation running to right

	// play audio running to right

	_state = RUNNING_TO_RIGHT;

	return 0;
}

int Player::die()
{
	// check whether player'd already died
	if ( _state == DEAD ) return -1;

	stopAllActions();

	// run animation die

	// play audio die

	_state = DEAD;

	return 0;
}

void Player::update( float dt )
{
	// update position based on state
}
}
