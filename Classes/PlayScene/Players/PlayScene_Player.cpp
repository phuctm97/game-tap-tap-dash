#include "PlayScene_Player.h"

using namespace cocos2d;

namespace PlayScene
{
Player::~Player()
{
	CC_SAFE_RELEASE(_actionRun);
}

Player* Player::create()
{
	auto p = new Player();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool Player::init()
{
	if ( !IPlayer::init() ) return false;

	if ( !preload() ) return false;

	if ( !initSprite() ) return false;

	if ( !initActions() ) return false;

	if ( !initEvents() ) return false;

	if ( !initContent() ) return false;

	return true;
}

bool Player::preload()
{
	SpriteFrameCache::getInstance()->addSpriteFrame( SpriteFrame::create( "res/test/pikachu_0.png", Rect( 0, 0, 252, 388 ) ),
	                                                 "pikachu_0.png" );
	SpriteFrameCache::getInstance()->addSpriteFrame( SpriteFrame::create( "res/test/pikachu_1.png", Rect( 0, 0, 252, 388 ) ),
	                                                 "pikachu_1.png" );
	return true;
}

bool Player::initSprite()
{
	// sprite
	_sprite = Sprite::createWithSpriteFrameName( "pikachu_1.png" );
	if ( !_sprite ) return false;

	addChild( _sprite );
	setContentSize( _sprite->getContentSize() );

	_sprite->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_sprite->setPosition( getContentSize() * 0.5f );

	setAnchorPoint( Vec2::ANCHOR_MIDDLE );

	return true;
}

bool Player::initActions()
{
	// run
	createAnimationRun();

	return true;
}

bool Player::initEvents()
{
	scheduleUpdate();

	return true;
}

bool Player::initContent()
{
	reset( Vec2( Director::getInstance()->getVisibleSize().width * 0.5f,
	             Director::getInstance()->getVisibleSize().height * 0.5f ) );
	return true;
}

void Player::update( float dt ) {}

float Player::calculateDelay() const
{
	if ( _energy >= 0.7f )
		return 0.0f;
	else if ( _energy >= 0.3f )
		return 0.5f;
	else
		return 1.0f;
}

void Player::createAnimationRun()
{
	// get frames
	Vector<SpriteFrame*> frames;
	frames.pushBack( SpriteFrameCache::getInstance()->getSpriteFrameByName( "pikachu_0.png" ) );
	frames.pushBack( SpriteFrameCache::getInstance()->getSpriteFrameByName( "pikachu_1.png" ) );

	// create animation

	auto animation = Animation::createWithSpriteFrames( frames );
	animation->setDelayPerUnit( 0.25f );
	animation->setLoops( -1 );
	animation->setRestoreOriginalFrame( true );

	// create action
	_actionRun = Animate::create( animation );
	_actionRun->setTag( ACTION_RUN );
	_actionRun->retain();
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
	return _energy;
}

void Player::increaseEnergy( float energy )
{
	_energy += energy;
}

void Player::reset( const cocos2d::Vec2& position )
{
	setPosition( position );

	idle();

	_energy = 1.0f;
}

void Player::idle()
{
	_sprite->stopActionByTag( ACTION_FLY );
	_sprite->stopActionByTag( ACTION_RUN );

	// run animation idle
	if ( _sprite->getScale() > 1.0f ) {
		auto resetScale = ScaleTo::create( 0.1f, 1.0f );
		auto resetState = CallFunc::create( CC_CALLBACK_0( Player::setStateToIdle, this ) );
		_sprite->runAction( Sequence::create( resetScale, resetState, nullptr ) );
	}
	else {
		setStateToIdle();
	}
}

void Player::setStateToIdle()
{
	_sprite->setSpriteFrame( "pikachu_1.png" );
	_state = IDLE;
}

void Player::run()
{
	if ( _state != IDLE && _state != FLYING ) return;

	_sprite->stopActionByTag( ACTION_RUN );

	// run animation running
	auto actionRun = _actionRun->clone();
	actionRun->setTag( ACTION_RUN );

	_sprite->runAction( actionRun );

	// play audio running

	_state = RUNNING;
}

void Player::turnLeft()
{
	if ( _state == DEAD ) return;

	// stop old action
	_sprite->stopActionByTag( ACTION_TURN_LEFT );
	_sprite->stopActionByTag( ACTION_TURN_RIGHT );
	float rotation = 0;

	// calculate rotation
	switch ( _direction ) {
	case DIRECTION_UP: _direction = DIRECTION_LEFT;
		rotation = -90;
		break;
	case DIRECTION_DOWN: _direction = DIRECTION_RIGHT;
		rotation = 90;
		break;
	case DIRECTION_LEFT: _direction = DIRECTION_DOWN;
		rotation = -180;
		break;
	case DIRECTION_RIGHT: _direction = DIRECTION_UP;
		rotation = 0;
		break;
	}

	// run animation turn left
	auto turn = RotateTo::create( 0.25f, rotation );
	turn->setTag( ACTION_TURN_LEFT );

	_sprite->runAction( turn );

	// run audio turn left
}

void Player::turnRight()
{
	if ( _state == DEAD ) return;

	// stop old action
	_sprite->stopActionByTag( ACTION_TURN_RIGHT );
	_sprite->stopActionByTag( ACTION_TURN_LEFT );
	float rotation = 0;

	// calculate rotation
	switch ( _direction ) {
	case DIRECTION_UP: _direction = DIRECTION_RIGHT;
		rotation = 90;
		break;
	case DIRECTION_DOWN: _direction = DIRECTION_LEFT;
		rotation = -90;
		break;
	case DIRECTION_LEFT: _direction = DIRECTION_UP;
		rotation = 0;
		break;
	case DIRECTION_RIGHT: _direction = DIRECTION_DOWN;
		rotation = -180;
		break;
	}

	// run animation turn right
	auto turn = RotateTo::create( 0.25f, rotation );
	turn->setTag( ACTION_TURN_RIGHT );

	_sprite->runAction( turn );

	// run audio turn right
}

void Player::fly()
{
	if ( _state == DEAD ) return;

	_sprite->stopActionByTag( ACTION_RUN );
	_sprite->stopActionByTag( ACTION_FLY );

	// create action fly
	_sprite->setSpriteFrame( "pikachu_1.png" );
	auto zoomOut = ScaleTo::create( 0.25f, 1.5f );
	auto delay = DelayTime::create( 0.1f );
	auto zoomIn = ScaleTo::create( 0.2f, 1.0f );
	auto resetToRun = CallFunc::create( CC_CALLBACK_0( Player::run, this ) );
	auto actionFly = Sequence::create( zoomOut, delay, zoomIn, resetToRun, nullptr );

	actionFly->setTag( ACTION_FLY );

	// run action fly
	_sprite->runAction( actionFly );

	// run audio fly
	_state = FLYING;
}

void Player::die()
{
	if ( _state == DEAD ) return;

	// run animation die

	// run audio die

	_state = DEAD;
}

void Player::win()
{
	if ( _state == DEAD ) return;

	_sprite->stopAllActions();

	// run animation win

	// run audio win

	_state = IDLE;
}
}
