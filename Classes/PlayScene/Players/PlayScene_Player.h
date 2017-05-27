#ifndef __PLAY_SCENE_PLAYER_H__
#define __PLAY_SCENE_PLAYER_H__

#include "PlayScene_IPlayer.h"

namespace PlayScene
{
class Player : public IPlayer
{
private:
	enum
	{
		ACTION_RUN,
		ACTION_TURN_LEFT,
		ACTION_TURN_RIGHT,
		ACTION_FLY,

		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	cocos2d::Sprite* _sprite;

	cocos2d::Action* _actionRun;

	int _state;

	int _direction;

	float _energy;

public:
	Player()
		: _sprite( nullptr ),
		  _actionRun( nullptr ),
		  _state( IDLE ),
		  _direction( DIRECTION_UP ),
		  _energy( 1.0f ) {}

	~Player();

	static Player* create();

	bool init() override;

	void createAnimationRun();

	int getState() const override;

	int getDirection() const override;

	float getEnergy() const override;

	void increaseEnergy( float energy ) override;

	void reset( const cocos2d::Vec2& position ) override;

	void idle() override;

	void run() override;

	void turnLeft() override;

	void turnRight() override;

	void fly() override;

	void die() override;

	void win() override;

private:
	bool initSprite();

	bool initActions();

	bool initEvents();

	bool initContent();

	void update( float dt ) override;

	float calculateDelay() const;

	void setStateToRunning();
};
}

#endif //!__PLAY_SCENE_PLAYER_H__
