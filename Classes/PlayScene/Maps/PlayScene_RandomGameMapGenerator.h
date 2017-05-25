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

	GameMapNode* nextNode() override;

	void placeNode( GameMapNode* previousNode, GameMapNode* node ) override;
};
}

#endif //!__GAME_MAP_GENERATOR_H__
