#ifndef __PLAY_SCENE_FORWARD_GAME_MAP_NODE_START_H__
#define __PLAY_SCENE_FORWARD_GAME_MAP_NODE_START_H__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
class ForwardGameMapNodeStart : public GameMapNode
{
public:

	ForwardGameMapNodeStart()
		: _sprite( nullptr ) {}

	static ForwardGameMapNodeStart* create();

	bool init() override;

	bool initSprite();

	int checkPositionInside( const cocos2d::Vec2& worldPosition ) override;

	int getType() const override;

private:
	cocos2d::Sprite* _sprite;
};
}

#endif //!__PLAY_SCENE_FORWARD_GAME_MAP_NODE_START_H__
