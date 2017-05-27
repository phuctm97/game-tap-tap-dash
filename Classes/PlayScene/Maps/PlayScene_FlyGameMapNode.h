#ifndef __PLAY_SCENE_FLY_GAME_MAP_NODE_H__
#define __PLAY_SCENE_FLY_GAME_MAP_NODE_H__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
	class FlyGameMapNode : public GameMapNode
	{
	public:

		FlyGameMapNode()
			: _sprite(nullptr), _navigator(nullptr)
		{
			_restCode = -1;
			_energy = -1;
			_isRestNode = false;
		}

		static FlyGameMapNode* create();

		bool init() override;

		bool initSprite();

		int checkPositionInside(const cocos2d::Vec2& worldPosition) override;

		int getType() const override;

	private:
		cocos2d::Sprite* _sprite;
		cocos2d::Sprite* _navigator;
	};
}

#endif //!__PLAY_SCENE_FLY_GAME_MAP_NODE_H__
