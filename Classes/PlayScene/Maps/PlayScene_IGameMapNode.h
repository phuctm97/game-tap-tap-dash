#ifndef __PLAY_SCENE_I_GAME_MAP_NODE_H__
#define __PLAY_SCENE_I_GAME_MAP_NODE_H__

#include <cocos2d.h>

namespace PlayScene
{
class IGameMapNode : public cocos2d::Node
{
public:
	enum
	{
		POSITION_INSIDE,
		POSITION_OUTSIDE,

		NODE_FORWARD,
		NODE_TURN_LEFT,
		NODE_TURN_RIGHT,
		NODE_FLY,

		DIRECTION_UP,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	virtual int checkPositionInside( const cocos2d::Vec2& worldPosition ) = 0;

	virtual int getType() const = 0;

	virtual int getDirection() const = 0;

	void setDirection( int direction ) = 0;
};
}

#endif //!__PLAY_SCENE_I_GAME_MAP_NODE_H__
