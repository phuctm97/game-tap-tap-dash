#ifndef __PLAY_SCENE_I_PLAYER_H__
#define __PLAY_SCENE_I_PLAYER_H__

#include <cocos2d.h>

namespace PlayScene
{
class IPlayer : public cocos2d::Node
{
public:
	enum
	{
		IDLE,
		RUNNING,
		FLYING,
		DEAD,

		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	virtual int getState() const = 0;

	virtual int getDirection() const = 0;

	virtual void reset( const cocos2d::Vec2& position ) = 0;

	virtual void idle() = 0;

	virtual void run() = 0;

	virtual void turnLeft() = 0;

	virtual void turnRight() = 0;

	virtual void fly() = 0;

	virtual void die() = 0;

	virtual void win() = 0;

	virtual void setSpeed( float speed ) = 0;

	virtual float getEnergy() const = 0;

	virtual void increaseEnergy( float energy ) = 0;
};
}

#endif //!__I_PLAYER_H__
