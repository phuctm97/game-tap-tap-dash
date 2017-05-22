#include "PlayScene_GameMap.h"
using namespace cocos2d;

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

bool GameMap::initGraphics() { throw "Not implemented"; }

bool GameMap::initContent() { throw "Not implemented"; }

bool GameMap::initEvents() { throw "Not implemented"; }
}
