#include "PlayScene_GameMap.h"
using namespace cocos2d;

#define NUMBER_OF_ACTIVE_NODES 15

namespace PlayScene
{
GameMap::~GameMap()
{
	CC_SAFE_RELEASE( _generator );

	_activeNodes.clear();
}

GameMap* GameMap::create( GameMapGenerator* generator )
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

	if ( !initGraphics() ) return false;

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

void GameMap::stop()
{
	_scrolling = false;
}

GameMapNode* GameMap::getCurrentNode() const
{
	return *_currentNodeIt;
}

GameMapNode* GameMap::nextNode()
{
	if ( isEnd() ) return nullptr;

	// player pass current control node, find next control node
	if ( *_currentNodeIt == *_nextControlNodeIt ) {
		_nextControlNodeIt = findNextControlNode();
	}

	// remove node out of view
	for ( auto node: _activeNodes ) {
		if ( checkNodeOutOfView( node ) ) {
			node->runAction( CallFuncN::create( CC_CALLBACK_1( GameMap::doRemoveNode, this ) ) );
		}
		else break;
	}

	// next node
	++_currentNodeIt;

	return *_currentNodeIt;
}

bool GameMap::isEnd() const
{
	return (_currentNodeIt + 1) == _activeNodes.cend();
}

int GameMap::getNextControl() const
{
	if ( _nextControlNodeIt == _activeNodes.cend() ) return NONE;

	auto node = *_nextControlNodeIt;
	switch ( node->getType() ) {
	case GameMapNode::NODE_TURN_LEFT: return TURN_LEFT;
	case GameMapNode::NODE_TURN_RIGHT: return TURN_RIGHT;
	case GameMapNode::NODE_FLY: return FLY;
	}

	return NONE;
}

void GameMap::reset( const cocos2d::Vec2& position )
{
	// reset scrolling values
	_scrolling = false;
	_scrollSpeed = 0;
	_scrollDirection = SCROLL_UP;

	// release current active nodes
	for ( auto activeNode : _activeNodes ) {
		removeChild( activeNode );
	}
	_activeNodes.clear();

	// reset generator
	_generator->reset();

	// regenerate initial nodes
	generateInitialNodes( position );

	// begin node iterator
	_currentNodeIt = _activeNodes.cbegin();

	// find first control node
	_nextControlNodeIt = findNextControlNode();
}

bool GameMap::initGraphics()
{
	setAnchorPoint( Vec2::ANCHOR_MIDDLE );

	return true;
}

bool GameMap::initContent()
{
	// retain reference to generator
	_generator->retain();

	reset( Vec2( Director::getInstance()->getVisibleSize().width * 0.5f,
	             Director::getInstance()->getVisibleSize().height * 0.5f ) );

	return true;
}

bool GameMap::initEvents()
{
	scheduleUpdate();

	return true;
}

void GameMap::generateInitialNodes( const cocos2d::Vec2& initialPosition )
{
	// number of node to generate
	int initialNodes = NUMBER_OF_ACTIVE_NODES;

	// previous node for placing
	GameMapNode* previousNode = nullptr;

	while ( initialNodes > 0 ) {

		// generate next node
		auto node = _generator->nextNode();
		if ( node == nullptr ) break;

		// push into tracking array and add to map
		_activeNodes.push_back( node );
		addChild( node );

		// first node, place at initial position
		if ( previousNode == nullptr ) {
			node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
			node->setPosition( initialPosition );
		}
		// place next to previous node based on its direction and type
		else {
			node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
			_generator->placeNode( previousNode, node );
		}

		// iterate next loop
		previousNode = node;
		initialNodes--;
	}
}

std::vector<GameMapNode*>::const_iterator GameMap::findNextControlNode() const
{
	for ( auto it = _currentNodeIt + 1; it != _activeNodes.cend(); ++it ) {
		auto node = *it;
		if ( node->getType() == GameMapNode::NODE_FORWARD ) continue;

		return it;
	}
	return _activeNodes.cend();
}

cocos2d::Vec2 GameMap::calculateScrollVector() const
{
	auto scrollVector = Vec2( 0, 0 );
	switch ( _scrollDirection ) {
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

// ReSharper disable once CppMemberFunctionMayBeStatic
bool GameMap::checkNodeOutOfView( GameMapNode* node ) const
{
	if ( node->getPositionX() + node->getContentSize().width < 0 ) return true;
	if ( node->getPositionX() - node->getContentSize().width > Director::getInstance()->getVisibleSize().width ) return true;
	if ( node->getPositionY() + node->getContentSize().height < 0 ) return true;
	if ( node->getPositionY() - node->getContentSize().height > Director::getInstance()->getVisibleSize().height ) return true;
	return false;
}

void GameMap::doScroll()
{
	auto scrollVector = calculateScrollVector();

	for ( auto node : _activeNodes ) {
		node->setPosition( node->getPosition() + scrollVector );
	}
}

void GameMap::doRemoveNode( cocos2d::Node* node )
{
	auto nodeIt = std::find( _activeNodes.cbegin(), _activeNodes.cend(), node );
	if ( nodeIt == _activeNodes.cend() ) return;

	removeChild( node );
	_activeNodes.erase( nodeIt );
}
}
