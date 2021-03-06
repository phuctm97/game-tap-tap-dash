#include "PlayScene_GameMap.h"
#include "PlayScene_GameMapNodeBusStop.h"
#include "PlayScene_ForwardGameMapNode.h"
using namespace cocos2d;

#define NUMBER_OF_ACTIVE_NODES 30
#define NUMBER_OF_TAIL_NODES 10

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

	_pushedTail = false;

	// reset generator
	_generator->reset();

	// regenerate initial nodes
	generateInitialNodes( position );

	// begin node iterator
	_currentNodeIndex = 0;

	// find first control node
	_nextControlNodeIndex = 0;
	_nextControlNodeIndex = findNextControlNode();
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
	if ( _currentNodeIndex >= 0 && _currentNodeIndex < _activeNodes.size() )
		return _activeNodes[_currentNodeIndex];

	return nullptr;
}

GameMapNode* GameMap::getBusStopNode() const
{
	if ( !_pushedTail ) return nullptr;

	return _activeNodes[_activeNodes.size() - NUMBER_OF_TAIL_NODES + 1];
}

GameMapNode* GameMap::nextNode()
{
	if ( isEnd() ) return nullptr;

	// player pass current control node, find next control node
	if ( _currentNodeIndex == _nextControlNodeIndex ) {
		_nextControlNodeIndex = findNextControlNode();
	}

	// remove node out of view
	std::vector<GameMapNode*> nodesToRemove;
	for ( auto node: _activeNodes ) {
		if ( checkNodeOutOfView( node ) ) {
			nodesToRemove.push_back( node );
		}
		else break;
	}
	for ( auto node: nodesToRemove ) {
		auto nodeIt = std::find( _activeNodes.cbegin(), _activeNodes.cend(), node );
		if ( nodeIt == _activeNodes.cend() ) continue;

		_activeNodes.erase( nodeIt );
		removeChild( node );

		pushNewNode();

		if ( _currentNodeIndex >= 0 && _currentNodeIndex < _activeNodes.size() ) {
			_currentNodeIndex--;
		}
		if ( _nextControlNodeIndex >= 0 && _nextControlNodeIndex < _activeNodes.size() ) {
			_nextControlNodeIndex--;
		}
	}
	nodesToRemove.clear();

	// next node
	++_currentNodeIndex;

	if ( _currentNodeIndex >= 0 && _currentNodeIndex < _activeNodes.size() )
		return _activeNodes[_currentNodeIndex];

	return nullptr;
}

bool GameMap::isEnd() const
{
	return _currentNodeIndex == _activeNodes.size() - NUMBER_OF_TAIL_NODES;
}

bool GameMap::isPushedTail() const
{
	return _pushedTail;
}

int GameMap::nextControl()
{
	if ( _nextControlNodeIndex < 0 || _nextControlNodeIndex >= _activeNodes.size() ) return NONE;

	// next control
	int controlNodeIndex = _nextControlNodeIndex;
	_nextControlNodeIndex = findNextControlNode();

	// return current control node
	auto node = _activeNodes[controlNodeIndex];
	switch ( node->getType() ) {
	case GameMapNode::NODE_TURN_LEFT: return TURN_LEFT;
	case GameMapNode::NODE_TURN_RIGHT: return TURN_RIGHT;
	case GameMapNode::NODE_FLY: return FLY;
	}

	return NONE;
}

int GameMap::getCurrentNodeIndex() const
{
	return _currentNodeIndex;
}

GameMapNode* GameMap::getNode( int index ) const
{
	if ( index >= 0 && index < _activeNodes.size() )
		return _activeNodes[index];

	return nullptr;
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

void GameMap::pushNewNode()
{
	auto node = _generator->nextNode();
	if ( node == nullptr ) {
		if ( !_pushedTail ) {
			pushTail();
		}
		return;
	}

	_activeNodes.push_back( node );
	addChild( node );

	_generator->placeNode( _activeNodes[_activeNodes.size() - 2], node );
}

void GameMap::pushTail()
{
	_pushedTail = true;

	GameMapNode* node;

	node = ForwardGameMapNode::create();
	_activeNodes.push_back( node );
	addChild( node );
	_generator->placeNode( _activeNodes[_activeNodes.size() - 2], node );

	node = GameMapNodeBusStop::create();
	_activeNodes.push_back( node );
	addChild( node );
	_generator->placeNode( _activeNodes[_activeNodes.size() - 2], node );

	for ( int i = 2; i < NUMBER_OF_TAIL_NODES; i++ ) {
		node = ForwardGameMapNode::create();
		_activeNodes.push_back( node );
		addChild( node );
		_generator->placeNode( _activeNodes[_activeNodes.size() - 2], node );
	}
}

int GameMap::findNextControlNode() const
{
	for ( int i = _nextControlNodeIndex + 1; i < _activeNodes.size(); i++ ) {
		auto node = _activeNodes[i];
		if ( node->getType() == GameMapNode::NODE_FORWARD ) continue;

		return i;
	}
	return -1;
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
}
