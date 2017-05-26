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

PlayScene::GameMapNode* PlayScene::RandomGameMapGenerator::nextNode()
{
	if ( !_firstNodeGenerated ) {
		_firstNodeGenerated = true;
		return ForwardGameMapNode::create();
	}

	int type = random<int>( 1, 4 );
	switch ( type ) {
	case 1: return ForwardGameMapNode::create();
	case 2: return TurnLeftGameMapNode::create();
	case 3: return TurnRightGameMapNode::create();
	case 4: return FlyGameMapNode::create();
	}
	return nullptr;
}

void PlayScene::RandomGameMapGenerator::reset()
{
	_firstNodeGenerated = false;
}
