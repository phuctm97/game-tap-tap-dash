#ifndef __PLAY_SCENE_FLY_GAME_MAP_NODE_H__
#define __PLAY_SCENE_FLY_GAME_MAP_NODE_H__

#include <cocos2d.h>
#include "PlayScene_IGameMapNode.h"

namespace PlayScene
{
class FlyGameMapNode : public IGameMapNode
{
public:

	FlyGameMapNode()
		: _sprite( nullptr ) {}

	static FlyGameMapNode* create();

	bool init() override;

	bool initSprite();

	int checkPositionInside( const cocos2d::Vec2& worldPosition ) override;

	int getType() const override;

private:
	cocos2d::Sprite* _sprite;
};
}

#endif //!__PLAY_SCENE_FLY_GAME_MAP_NODE_H__
