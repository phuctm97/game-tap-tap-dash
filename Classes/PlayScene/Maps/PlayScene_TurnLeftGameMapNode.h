#ifndef __PLAY_SCENE_TURN_LEFT_GAME_MAP_NODE_H__
#define __PLAY_SCENE_TURN_LEFT_GAME_MAP_NODE_H__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
	class TurnLeftGameMapNode : public GameMapNode
	{
	public:

		TurnLeftGameMapNode()
			: _sprite(nullptr), _navigator(nullptr) {}

		static TurnLeftGameMapNode* create();

		bool init() override;

		bool initSprite();

		int checkPositionInside(const cocos2d::Vec2& worldPosition) override;

		int getType() const override;

		void highLightNavi() override;

		void unHighLightNavi() override;

		void decreaseRestCode() override {}

	private:
		cocos2d::Sprite* _sprite;
		cocos2d::Sprite* _navigator;
	};
}

#endif //!__PLAY_SCENE_TURN_LEFT_GAME_MAP_NODE_H__
