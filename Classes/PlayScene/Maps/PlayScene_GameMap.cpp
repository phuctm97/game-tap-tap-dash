#include "PlayScene_GameMap.h"
using namespace cocos2d;

#define NUMBER_OF_ACTIVE_NODES 10

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
	if ( !Node::init() ) return false;

	if ( !initContent() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

void GameMap::update( float dt )
{
	if ( _scrolling ) {
		doScroll();
	}
}

void GameMap::setScrollSpeed( float speed )
{
	_scrollSpeed = speed;
}

void GameMap::setScrollDirection( int direction )
{
	_scrollDirection = direction;
}

void GameMap::scroll()
{
	_scrolling = true;
}

GameMapNode* GameMap::getCurrentNode() const
{
	return *_currentNodeIt;
}

GameMapNode* GameMap::nextNode()
{
	if ( isEnd() ) return nullptr;

	return *(++_currentNodeIt);
}

bool GameMap::isEnd() const
{
	return (_currentNodeIt + 1) == _activeNodes.cend();
}

int GameMap::getNextControl() const
{
	return _nextControl;
}

void GameMap::reset( const cocos2d::Vec2& position ) { }

void GameMap::stop()
{
	_scrolling = false;
}

bool GameMap::initContent()
{
	_generator->retain();

	generateInitialNodes();

	_currentNodeIt = _activeNodes.cbegin();

	return true;
}

bool GameMap::initEvents()
{
	scheduleUpdate();

	return true;
}

void GameMap::generateInitialNodes()
{
	int initialNodes = NUMBER_OF_ACTIVE_NODES;
	GameMapNode* previousNode = nullptr;

	while ( initialNodes > 0 ) {
		auto node = _generator->nextNode();
		if ( node == nullptr ) break;

		_activeNodes.push_back( node );
		addChild( node );

		// first node
		if ( previousNode == nullptr ) {
			node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
			node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
			                   Director::getInstance()->getVisibleSize().height * 0.5f );
		}
		// second and later nade
		else {
			_generator->placeNode( previousNode, node );
		}

		previousNode = node;
		initialNodes--;
	}
}

cocos2d::Vec2 GameMap::calculateScrollVector() const
{
	auto scrollVector = Vec2( 0, 0 );
	switch( _scrollDirection ) {
	case SCROLL_UP: scrollVector.y = 1;
		break;
	case SCROLL_DOWN: scrollVector.y = -1;
		break;
	case SCROLL_LEFT: scrollVector.x = -1;
		break;
	case SCROLL_RIGHT: scrollVector.x = 1;
		break;
	}

	scrollVector *= _scrollSpeed;
	return scrollVector;
}

void GameMap::doScroll()
{
	auto scrollVector = calculateScrollVector();

	for ( auto node : _activeNodes ) {
		node->setPosition( node->getPosition() + scrollVector );
	}
}

}
