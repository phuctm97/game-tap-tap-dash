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
		POSITION_EXITED
	};

	virtual int checkPositionInside( const cocos2d::Vec2& worldPosition ) = 0;
};
}

#endif //!__PLAY_SCENE_I_GAME_MAP_NODE_H__
