#include "PlayScene_RandomGameMapGenerator.h"
#include "PlayScene_ForwardGameMapNode.h"
#include "PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene_TurnRightGameMapNode.h"
#include "PlayScene_FlyGameMapNode.h"
using namespace cocos2d;

PlayScene::RandomGameMapGenerator* PlayScene::RandomGameMapGenerator::create()
{
	auto p = new RandomGameMapGenerator();
	if ( p ) {
		p->autorelease();
		return p;
	}
	return nullptr;
}

PlayScene::IGameMapNode* PlayScene::RandomGameMapGenerator::nextNode()
{
	if ( !_firstNodeGenerated ) {
		_firstNodeGenerated = true;
		return new ForwardGameMapNode();
	}

	int type = random<int>( 1, 4 );
	switch ( type ) {
	case 1: return new ForwardGameMapNode();
	case 2: return new TurnLeftGameMapNode();
	case 3: return new TurnRightGameMapNode();
	case 4: return new FlyGameMapNode();
	}
	return nullptr;
}

void PlayScene::RandomGameMapGenerator::placeNode( IGameMapNode* previousNode, IGameMapNode* node )
{
	
}
