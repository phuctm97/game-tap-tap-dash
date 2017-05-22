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
	Sprite* _child = Sprite::create("res/blank.png");
	if ( !_sprite ) return false;

	addChild( _sprite );
	_sprite->setTextureRect( Rect( 0, 0, 200, 200 ) );
	_child->setTextureRect(Rect(0, 0, 100, 50));
	_child->setColor(Color3B::YELLOW);
	_sprite->addChild(_child);
	_child->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_child->setPosition(Vec2(50, 200));
	_sprite->setColor( Color3B::RED );
	_sprite->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_sprite->setPosition( Vec2::ZERO );
	setContentSize( _sprite->getContentSize() );

	return true;
}

bool Player::initEvents()
{
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

	_sprite->setColor(Color3B::BLUE);

	// play audio running

	_state = RUNNING;
}

void Player::turnLeft()
{
	if ( _state == DEAD ) return;

	// run animation turn left

	_sprite->setRotation(_sprite->getRotation() -90.0f); // xoay trai

	// run audio turn left
}

void Player::turnRight()
{
	if( _state == DEAD ) return;

	// run animation turn right

	_sprite->setRotation(_sprite->getRotation() + 90.0f);

	// run audio turn right
}

void Player::fly()
{
	if( _state == DEAD ) return;

	// run animation fly

	DelayTime* delay = DelayTime::create(0.5f);
	ScaleBy* zoomin = ScaleBy::create(0.5f, 2.0f);
	ScaleBy* zoomout = ScaleBy::create(0.5f, 0.5f);

	
	Sequence* seq = Sequence::create(zoomin, delay, zoomout, delay,nullptr);

	_sprite->runAction(seq);



	// run audio fly
}

void Player::die()
{
	if( _state == DEAD ) return;

	// run animation die

	_sprite->setColor(Color3B::BLACK);

	// run audio die

	_state = DEAD;
}

void Player::win()
{
	if( _state == DEAD ) return;

	stopAllActions();

	// run animation win

	// run audio win

	_state = IDLE;
}
}
