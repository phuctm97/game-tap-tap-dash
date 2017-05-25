#include "PlayScene_GameMap.h"
using namespace cocos2d;

#define INITIAL_NODES 10

namespace PlayScene
{
GameMap* GameMap::create()
{
	auto p = new GameMap();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}

	CC_SAFE_RELEASE( p );
	return nullptr;
}

bool GameMap::init()
{
	if ( !IGameMap::init() ) return false;

	if ( !initGraphics() ) return false;

	if ( !initContent() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

void GameMap::setSpeed( int speed ) { }

void GameMap::scroll() {}

IGameMapNode* GameMap::getCurrentNode() const { throw "Not implemented"; }

IGameMapNode* GameMap::nextNode() { throw "Not implemented"; }

bool GameMap::isEnd() const { throw "Not implemented"; }

int GameMap::getNextControl() const { throw "Not implemented"; }

void GameMap::reset( const cocos2d::Vec2& position ) { throw "Not implemented"; }

void GameMap::stop() { throw "Not implemented"; }


bool GameMap::initGraphics()
{
	generateInitialNodes();

	return true;
}

bool GameMap::initContent() { throw "Not implemented"; }

bool GameMap::initEvents() { throw "Not implemented"; }

void GameMap::generateInitialNodes()
{
	int initialNodes = INITIAL_NODES;
	IGameMapNode* previousNode = nullptr;

	while( initialNodes > 0 ) {
		auto node = _generator->nextNode();
		if( node == nullptr ) break;

		_activeNodes.pushBack( node );
		if( previousNode == nullptr ) {
			node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
			node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
												 Director::getInstance()->getVisibleSize().height * 0.5f );
		}
		else {
			_generator->placeNode( previousNode, node );
		}
	}
}

}