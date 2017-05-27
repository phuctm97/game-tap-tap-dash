#include "PlayScene_Player.h"

using namespace cocos2d;

namespace PlayScene
{
	Player::~Player()
	{
		CC_SAFE_RELEASE(_actionRun);
		CC_SAFE_RELEASE(_actionTurnLeft);
		CC_SAFE_RELEASE(_actionTurnRight);
		CC_SAFE_RELEASE(_actionFly);
	}

	Player* Player::create()
	{
		auto p = new Player();
		if (p && p->init()) {
			p->autorelease();
			return p;
		}

		CC_SAFE_DELETE(p);
		return nullptr;
	}

	bool Player::init()
	{
		if (!IPlayer::init()) return false;

		if (!initSprite()) return false;

		if (!initActions()) return false;

		if (!initEvents()) return false;

		if (!initContent()) return false;

		return true;
	}

	bool Player::initSprite()
	{
		// sprite
		_sprite = Sprite::create("res/pikachu1.png");
		if (!_sprite) return false;

		addChild(_sprite);
		_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_sprite->setPosition(100, 300);
		setContentSize(_sprite->getContentSize());

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
		_energy = 1.0f;

		return true;
	}

	void Player::update(float dt)
	{
		_timer -= dt;
		if (_timer <= 0.0f)
		{
			_timer = 1.0f;
			_energy -= 0.1f;
		}

		_flyingtime -= dt;


		if (_keepflying == false)
		{
			ScaleTo* zoomout = ScaleTo::create(0.7f, 1.0f);
			_sprite->runAction(zoomout->clone());
			setStateToRunning();
		}




		// test
		if (_energy <= 0)
			_energy = 1.0f;
	}

	float Player::setDelay(float _energy)
	{
		if (_energy >= 0.7f)
			return 0.0f;
		else
		{
			if (_energy >= 0.3f)
				return 0.5f;
			else
				return 1.0f;
		}

	}

	void Player::setEnergy(float energy)
	{
		this->_energy = energy;
	}

	float Player::getEnergy()
	{
		return this->_energy;
	}

	void Player::setStateToRunning()`
	{
		_state = RUNNING;
	}

	void Player::resetTurning()
	{
		_isturning = false;
	}

	void Player::setStateFalling()
	{
		_keepflying = false;
	}

	float Player::getFlyingTime()
	{
		return this->_flyingtime;
	}

	void Player::setFlyingTime(float time)
	{
		this->_flyingtime = time;
	}




	void Player::createAnimationRun()
	{
		Vector<SpriteFrame*> frames;
		frames.reserve(3);
		frames.pushBack(SpriteFrame::create("res/pikachu.png", Rect(0, 0, 252, 388)));
		frames.pushBack(SpriteFrame::create("res/pikachu1.png", Rect(0, 0, 252, 388)));
		_actionRun = Animate::create(Animation::createWithSpriteFrames(frames, 0.5f));
		_actionRun->retain();
	}

	void Player::createAnimationTurnLeft()
	{
		_actionTurnLeft = RotateBy::create(0.1f, -90.0f);
		_actionTurnLeft->retain();
	}

	void Player::createAnimationTurnRight()
	{
		_actionTurnRight = RotateBy::create(0.1f, 90.0f);
		_actionTurnRight->retain();
	}

	void Player::createAnimationFly()
	{
		DelayTime* delay = DelayTime::create(0.5f);
		ScaleTo* zoomin = ScaleTo::create(0.2f, 1.5f);

		_actionFly = Sequence::create(zoomin, delay, nullptr);
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

	void Player::reset(const cocos2d::Vec2& position)
	{
		setPosition(position);

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
		if (_state != IDLE) return;

		stopAllActions();

		// run animation running
		_sprite->runAction(RepeatForever::create(_actionRun->clone()));

		// play audio running

		_state = RUNNING;
	}

	void Player::turnLeft()
	{
		if (_state == DEAD) return;


		// run animation turn left
		if (_isturning == false)
		{
			_isturning = true;
			auto seq = Sequence::create(DelayTime::create(setDelay(_energy)), _actionTurnLeft->clone(), nullptr);
			_sprite->runAction(seq);
		}

		// run audio turn left
	}

	void Player::turnRight()
	{
		if (_state == DEAD) return;

		// run animation turn right
		if (_isturning == false)
		{
			_isturning = true;
			auto seq = Sequence::create(DelayTime::create(setDelay(_energy)), _actionTurnRight->clone(), CallFunc::create(CC_CALLBACK_0(Player::resetTurning, this)), nullptr);
			_sprite->runAction(seq);
		}
		// run audio turn right
	}

	void Player::fly()
	{
		if (_state == DEAD) return;

		_state = FLYING;


		_keepflying = true;
		_flyingtime = 1.0f;

		// run animation fly
		auto seq = Sequence::create(DelayTime::create(setDelay(_energy)), _actionFly->clone(),
			CallFunc::create(CC_CALLBACK_0(Player::setStateFalling, this)), nullptr);
		_sprite->runAction(seq);




		// run audio fly


	}

	void Player::die()
	{
		if (_state == DEAD) return;

		// run animation die



		// run audio die

		_state = DEAD;
	}

	void Player::win()
	{
		if (_state == DEAD) return;

		stopAllActions();

		// run animation win

		// run audio win

		_state = IDLE;
	}
}
