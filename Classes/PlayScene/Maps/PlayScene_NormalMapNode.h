#ifndef __PLAY_SCENE_NORMAL_MAP_NODE_H__
#define __PLAY_SCENE_NORMAL_MAP_NODE_H__

#include "PlayScene_IGameMapNode.h"

namespace PlayScene
{
class IGameMap;

class NormalMapNode: public IGameMapNode
{
public:
	static NormalMapNode* create();

	bool init() override;

	int checkPositionInside( const cocos2d::Vec2& worldPosition ) override;

private:
	bool initSprite();

	bool initContent();

	bool initEvents();
};
}

#endif //!__PLAY_SCENE_NORMAL_MAP_NODE_H__
