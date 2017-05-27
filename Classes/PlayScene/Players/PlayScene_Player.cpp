#include "PlayScene_Player.h"

using namespace cocos2d;

namespace PlayScene
{
Player::~Player()
{
	CC_SAFE_RELEASE(_actionRun);
	CC_SAFE_RELEASE(_actionFly);
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

	if ( !initSprite() ) return false;

	if ( !initActions() ) return false;

	if ( !initEvents() ) return false;

	if ( !initContent() ) return false;

	return true;
}

bool Player::initSprite()
{
	// sprite
	_sprite = Sprite::create( "res/test/pikachu1.png" );
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

void Player::setStateToRunning()
{
	_state = RUNNING;
}

void Player::createAnimationRun()
{
	// get frames
	Vector<SpriteFrame*> frames;
	frames.pushBack( SpriteFrame::create( "res/test/pikachu.png", Rect( 0, 0, 252, 388 ) ) );
	frames.pushBack( SpriteFrame::create( "res/test/pikachu1.png", Rect( 0, 0, 252, 388 ) ) );

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

void Player::createAnimationFly()
{
	DelayTime* delay = DelayTime::create( 0.5f );
	ScaleTo* zoomin = ScaleTo::create( 0.2f, 1.5f );

	_actionFly = Sequence::create( zoomin, delay, nullptr );
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
	stopAllActions();

	// run animation idle

	// run audio idle

	_state = IDLE;
}

void Player::run()
{
	if ( _state != IDLE ) return;

	stopActionByTag( ACTION_RUN );

	// run animation running
	_sprite->runAction( _actionRun );

	// play audio running

	_state = RUNNING;
}

void Player::turnLeft()
{
	if ( _state == DEAD ) return;
	
	// stop old action
	stopActionByTag( ACTION_TURN_LEFT );
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

	// run animation turn right

	// run audio turn right
}

void Player::fly()
{
	if ( _state == DEAD ) return;

	_state = FLYING;

	// run audio fly
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

	stopAllActions();

	// run animation win

	// run audio win

	_state = IDLE;
}
}
