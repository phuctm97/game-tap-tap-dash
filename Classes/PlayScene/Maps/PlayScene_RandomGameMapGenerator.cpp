#include "PlayScene_RandomGameMapGenerator.h"
#include "PlayScene_ForwardGameMapNode.h"
#include "PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene_TurnRightGameMapNode.h"
#include "PlayScene_FlyGameMapNode.h"
using namespace cocos2d;

#define FLY_DISTANCE 100

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
	switch ( previousNode->getType() ) {
	case IGameMapNode::NODE_FORWARD:
	case IGameMapNode::NODE_TURN_LEFT:
	case IGameMapNode::NODE_TURN_RIGHT: {

		switch ( previousNode->getDirection() ) {

		case IGameMapNode::DIRECTION_UP: {
			// set position
			node->setPosition( previousNode->getPositionX(),
			                   previousNode->getPositionY()
			                   + previousNode->getContentSize().height * 0.5f
			                   + node->getContentSize().height * 0.5f );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_UP );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_LEFT );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_RIGHT );
				break;
			}
		}
			break;

		case IGameMapNode::DIRECTION_LEFT: {
			// set position
			node->setPosition( previousNode->getPositionX()
			                   - previousNode->getContentSize().width * 0.5f
			                   - node->getContentSize().width * 0.5f,
			                   previousNode->getPositionY() );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_LEFT );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_DOWN );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_UP );
				break;
			}
		}

			break;
		case IGameMapNode::DIRECTION_RIGHT: {
			// set position
			node->setPosition( previousNode->getPositionX()
			                   + previousNode->getContentSize().width * 0.5f
			                   + node->getContentSize().width * 0.5f,
			                   previousNode->getPositionY() );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_RIGHT );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_UP );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_DOWN );
				break;
			}
		}
			break;

		case IGameMapNode::DIRECTION_DOWN: {
			// set position
			node->setPosition( previousNode->getPositionX(),
			                   previousNode->getPositionY()
			                   - previousNode->getContentSize().height * 0.5f
			                   - node->getContentSize().height * 0.5f );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_DOWN );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_RIGHT );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_LEFT );
				break;
			}
		}
			break;
		}
	}
		break;

	case IGameMapNode::NODE_FLY: {

		switch ( previousNode->getDirection() ) {

		case IGameMapNode::DIRECTION_UP: {
			// set position
			node->setPosition( previousNode->getPositionX(),
			                   previousNode->getPositionY()
			                   + previousNode->getContentSize().height * 0.5f
			                   + FLY_DISTANCE
			                   + node->getContentSize().height * 0.5f );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_UP );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_LEFT );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_RIGHT );
				break;
			}
		}
			break;

		case IGameMapNode::DIRECTION_LEFT: {
			// set position
			node->setPosition( previousNode->getPositionX()
			                   - previousNode->getContentSize().width * 0.5f
			                   - FLY_DISTANCE
			                   - node->getContentSize().width * 0.5f,
			                   previousNode->getPositionY() );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_LEFT );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_DOWN );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_UP );
				break;
			}
		}

			break;
		case IGameMapNode::DIRECTION_RIGHT: {
			// set position
			node->setPosition( previousNode->getPositionX()
			                   + previousNode->getContentSize().width * 0.5f
			                   + FLY_DISTANCE
			                   + node->getContentSize().width * 0.5f,
			                   previousNode->getPositionY() );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_RIGHT );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_UP );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_DOWN );
				break;
			}
		}
			break;

		case IGameMapNode::DIRECTION_DOWN: {
			// set position
			node->setPosition( previousNode->getPositionX(),
			                   previousNode->getPositionY()
			                   - previousNode->getContentSize().height * 0.5f
			                   - FLY_DISTANCE
			                   - node->getContentSize().height * 0.5f );
			// set direction
			switch ( node->getType() ) {
			case IGameMapNode::NODE_FORWARD: case IGameMapNode::NODE_FLY:
				node->setDirection( IGameMapNode::DIRECTION_DOWN );
				break;
			case IGameMapNode::NODE_TURN_LEFT: node->setDirection( IGameMapNode::DIRECTION_RIGHT );
				break;
			case IGameMapNode::NODE_TURN_RIGHT: node->setDirection( IGameMapNode::DIRECTION_LEFT );
				break;
			}
		}
			break;
		}
	}
		break;
	}
}
