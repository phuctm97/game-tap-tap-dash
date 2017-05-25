#ifndef __PLAY_SCENE_TURN_RIGHT_GAME_MAP_NODE_H__
#define __PLAY_SCENE_TURN_RIGHT_GAME_MAP_NODE_H__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
	class TurnRightGameMapNode : public GameMapNode
	{
	public:

		TurnRightGameMapNode()
			: _sprite(nullptr), _navigator(nullptr) {}

		static TurnRightGameMapNode* create();

		bool init() override;

		bool initSprite();

		int checkPositionInside(const cocos2d::Vec2& worldPosition) override;

		int getType() const override;

	private:
		cocos2d::Sprite* _sprite;
		cocos2d::Sprite* _navigator;
	};
}

#endif //!__PLAY_SCENE_TURN_RIGHT_GAME_MAP_NODE_H__
