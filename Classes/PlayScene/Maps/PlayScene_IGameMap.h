#ifndef __PLAY_SCENE_I_GAME_MAP_H__
#define __PLAY_SCENE_I_GAME_MAP_H__

#include <cocos2d.h>
#include "PlayScene_IGameMapNode.h"

namespace PlayScene
{
class IGameMap : public cocos2d::Node
{
public:
	enum
	{
		NONE,
		TURN_LEFT,
		TURN_RIGHT,
		FLY
	};

	virtual void setSpeed( int speed ) = 0;

	virtual void scroll() = 0;

	virtual IGameMapNode* getCurrentNode() const = 0;

	virtual IGameMapNode* nextNode() = 0;

	virtual bool isEnd() const = 0;

	virtual int getNextControl() const = 0;

	virtual void reset( const cocos2d::Vec2& position ) = 0;

	virtual void stop() = 0;
};
}

#endif //!__PLAY_SCENE_I_GAME_MAP_H__
