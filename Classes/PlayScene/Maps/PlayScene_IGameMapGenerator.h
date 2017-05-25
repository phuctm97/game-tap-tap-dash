#ifndef __PLAY_SCENE_I_GAME_MAP_GENERATOR_H__
#define __PLAY_SCENE_I_GAME_MAP_GENERATOR_H__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
class IGameMapGenerator : public cocos2d::Ref
{
public:
	virtual GameMapNode* nextNode() = 0;

	virtual void placeNode( GameMapNode* previousNode, GameMapNode* node ) = 0;
};
}

#endif //!__PLAY_SCENE_I_GAME_MAP_GENERATOR_H__
