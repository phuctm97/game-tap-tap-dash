#ifndef __PLAY_SCENE_TURN_RIGHT_GAME_MAP_NODE_H__
#define __PLAY_SCENE_TURN_RIGHT_GAME_MAP_NODE_H__

#include <cocos2d.h>
#include "PlayScene_IGameMapNode.h"

namespace PlayScene
{
class TurnRightGameMapNode : public IGameMapNode
{
public:

	TurnRightGameMapNode()
		: _sprite( nullptr ) {}

	static TurnRightGameMapNode* create();

	bool init() override;

	bool initSprite();

	int checkPositionInside( const cocos2d::Vec2& worldPosition ) override;

	int getType() const override;

private:
	cocos2d::Sprite* _sprite;
};
}

#endif //!__PLAY_SCENE_TURN_LEFT_GAME_MAP_NODE_H__
