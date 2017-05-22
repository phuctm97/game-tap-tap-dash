#include "PlayScene_NormalMapNode.h"
using namespace cocos2d;

namespace PlayScene
{
NormalMapNode* NormalMapNode::create()
{
	auto p = new NormalMapNode();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE( p );
	return nullptr;
}

bool NormalMapNode::init()
{
	if ( !IGameMapNode::init() ) return false;

	if ( !initSprite() ) return false;

	if ( !initContent() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

int NormalMapNode::checkPositionInside( const cocos2d::Vec2& worldPosition )
{
	throw "Not implemented";
}

bool NormalMapNode::initSprite() { throw "Not implemented"; }

bool NormalMapNode::initContent() { throw "Not implemented"; }

bool NormalMapNode::initEvents() { throw "Not implemented"; }
}
