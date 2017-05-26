#ifndef __PLAY_SCENE_PLAYER_H__
#define __PLAY_SCENE_PLAYER_H__

#include "PlayScene_IPlayer.h"

namespace PlayScene
{
class Player : public IPlayer
{
private:
	cocos2d::Sprite* _sprite;

	int _state;

	cocos2d::Action* _actionRun;
	cocos2d::Action* _actionTurnLeft;
	cocos2d::Action* _actionTurnRight;
	cocos2d::Action* _actionFly;

public:
	Player()
		: _state( -1 ),
		  _sprite( nullptr ),
		  _actionRun( nullptr ),
		  _actionTurnLeft( nullptr ),
		  _actionTurnRight( nullptr ),
		  _actionFly( nullptr ) {}

	~Player();

	static Player* create();

	bool init() override;

	void createAnimationRun();

	void createAnimationTurnLeft();

	void createAnimationTurnRight();

	void createAnimationFly();

	int getState() const override;

	int getDirection() const override;
	
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

};
}

#endif //!__PLAY_SCENE_PLAYER_H__
