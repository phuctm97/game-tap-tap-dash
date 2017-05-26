#ifndef __PLAY_SCENE_I_GAME_MAP_GENERATOR_H__
#define __PLAY_SCENE_I_GAME_MAP_GENERATOR_H__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
class GameMapGenerator : public cocos2d::Ref
{
public:
	virtual GameMapNode* nextNode() = 0;

	virtual void reset() = 0;

	static void placeNode( GameMapNode* previousNode, GameMapNode* node );
};
}

#endif //!__PLAY_SCENE_I_GAME_MAP_GENERATOR_H__
