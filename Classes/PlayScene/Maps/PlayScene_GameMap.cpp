#include "PlayScene_GameMap.h"
using namespace cocos2d;

#define INITIAL_NODES 10

namespace PlayScene
{
GameMap::~GameMap()
{
	CC_SAFE_RELEASE( _generator );

	_activeNodes.clear();
}

GameMap* GameMap::create( IGameMapGenerator* generator )
{
	auto p = new GameMap( generator );
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

GameMapNode* GameMap::getCurrentNode() const { throw "Not implemented"; }

GameMapNode* GameMap::nextNode() { throw "Not implemented"; }

bool GameMap::isEnd() const { throw "Not implemented"; }

int GameMap::getNextControl() const { throw "Not implemented"; }

void GameMap::reset( const cocos2d::Vec2& position ) { throw "Not implemented"; }

void GameMap::stop() { throw "Not implemented"; }

bool GameMap::initGraphics()
{
	_generator->retain();

	generateInitialNodes();

	return true;
}

bool GameMap::initContent()
{
	return true;
}

bool GameMap::initEvents()
{
	return true;
}

void GameMap::generateInitialNodes()
{
	int initialNodes = INITIAL_NODES;
	GameMapNode* previousNode = nullptr;

	while ( initialNodes > 0 ) {
		auto node = _generator->nextNode();
		if ( node == nullptr ) break;

		_activeNodes.pushBack( node );
		addChild( node );

		if ( previousNode == nullptr ) {
			node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
			node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
			                   Director::getInstance()->getVisibleSize().height * 0.5f );
		}
		else {
			_generator->placeNode( previousNode, node );
		}

		previousNode = node;

		initialNodes--;
	}
}
}
