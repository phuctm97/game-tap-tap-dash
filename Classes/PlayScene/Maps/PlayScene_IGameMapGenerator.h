#ifndef __PLAY_SCENE_I_GAME_MAP_GENERATOR_H__
#define __PLAY_SCENE_I_GAME_MAP_GENERATOR_H__

#include <cocos2d.h>
#include "PlayScene_IGameMapNode.h"

namespace PlayScene
{
class IGameMapGenerator : public cocos2d::Ref
{
public:
	virtual IGameMapNode* nextNode() = 0;

	virtual void placeNode( IGameMapNode* previousNode, IGameMapNode* node ) = 0;
};
}

#endif //!__PLAY_SCENE_I_GAME_MAP_GENERATOR_H__
