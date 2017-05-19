#ifndef __I_PLAYER_H__
#define __I_PLAYER_H__

#include <cocos2d.h>

namespace PlayScene
{

class IPlayer : public cocos2d::Node
{
public:
	enum
	{
		IDLE,
		RUNNING_TO_LEFT,
		RUNNING_TO_RIGHT,
		DEAD,
	};

	virtual int getState() = 0;

	virtual int idle() = 0;

	virtual int runToLeft() = 0;

	virtual int runToRight() = 0;

	virtual int die() = 0;
};

}

#endif //!__I_PLAYER_H__
