#ifndef __PLAY_SCENE_FORWARD_GAME_MAP_NODE_H_2__
#define __PLAY_SCENE_FORWARD_GAME_MAP_NODE_H_2__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
class ForwardGameMapNode2 : public GameMapNode
{
public:

	ForwardGameMapNode2()
		: _sprite( nullptr ) {}

	static ForwardGameMapNode2* create();

	bool init() override;

	bool initSprite();

	int checkPositionInside( const cocos2d::Vec2& worldPosition ) override;

	int getType() const override;

private:
	cocos2d::Sprite* _sprite;
};
}

#endif //!__PLAY_SCENE_FORWARD_GAME_MAP_NODE_H_2__
