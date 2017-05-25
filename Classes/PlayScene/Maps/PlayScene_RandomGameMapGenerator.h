#ifndef __GAME_MAP_GENERATOR_H__
#define __GAME_MAP_GENERATOR_H__
#include "PlayScene_IGameMapGenerator.h"

namespace PlayScene
{
class RandomGameMapGenerator : public IGameMapGenerator
{
private:
	bool _firstNodeGenerated;

public:
	RandomGameMapGenerator()
		: _firstNodeGenerated( false ) {}

	static RandomGameMapGenerator* create();

	IGameMapNode* nextNode() override;

	void placeNode( IGameMapNode* previousNode, IGameMapNode* node ) override;
};
}

#endif //!__GAME_MAP_GENERATOR_H__
