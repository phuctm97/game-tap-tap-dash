#ifndef __PLAY_SCENE_GAME_MAP_NODE_H__
#define __PLAY_SCENE_GAME_MAP_NODE_H__

#include <cocos2d.h>
#include "PlayScene_IGameMapNode.h"

namespace PlayScene
{
	class GameMapNode : public IGameMapNode
	{
	public:

		GameMapNode()
		{
			imgNode = nullptr;
		}

		static GameMapNode* create();

		bool init() override;

		bool initSprite();

		int checkPositionInside(const cocos2d::Vec2& worldPosition) override;


	private:

		cocos2d::Sprite *imgNode;

	};
}

#endif //!__PLAY_SCENE_GAME_MAP_NODE_H__
