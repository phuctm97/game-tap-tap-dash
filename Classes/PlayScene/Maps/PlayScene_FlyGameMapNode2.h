#ifndef __PLAY_SCENE_FLY_GAME_MAP_NODE_H_2__
#define __PLAY_SCENE_FLY_GAME_MAP_NODE_H_2__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
class FlyGameMapNode2 : public GameMapNode
{
public:

	FlyGameMapNode2()
		: _sprite( nullptr ), _navigator( nullptr ) {}

	static FlyGameMapNode2* create();

	bool init() override;

	bool initSprite();

	int checkPositionInside( const cocos2d::Vec2& worldPosition ) override;

	int getType() const override;

private:
	cocos2d::Sprite* _sprite;
	cocos2d::Sprite* _navigator;
};
}

#endif //!__PLAY_SCENE_FLY_GAME_MAP_NODE_H__
