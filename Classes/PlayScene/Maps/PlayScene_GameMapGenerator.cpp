#include "PlayScene_GameMapGenerator.h"
using namespace cocos2d;

#define FLY_DISTANCE 100

namespace PlayScene
{
void IGameMapGenerator::placeNode( GameMapNode* previousNode, GameMapNode* node )
{
	switch ( previousNode->getDirection() ) {
	case GameMapNode::DIRECTION_UP: {
		// set position
		node->setPosition( previousNode->getPositionX(),
		                   previousNode->getPositionY()
		                   + previousNode->getContentSize().height * 0.5f
		                   + (previousNode->getType() == GameMapNode::NODE_FLY ? FLY_DISTANCE : 0)
		                   + node->getContentSize().height * 0.5f );

		// set direction
		switch ( node->getType() ) {
		case GameMapNode::NODE_FORWARD:
		case GameMapNode::NODE_FLY:
			node->setDirection( GameMapNode::DIRECTION_UP );
			break;
		case GameMapNode::NODE_TURN_LEFT:
			node->setDirection( GameMapNode::DIRECTION_LEFT );
			break;
		case GameMapNode::NODE_TURN_RIGHT:
			node->setDirection( GameMapNode::DIRECTION_RIGHT );
			break;
		}
	}
		break;

	case GameMapNode::DIRECTION_DOWN: {
		// set position
		node->setPosition( previousNode->getPositionX(),
		                   previousNode->getPositionY()
		                   - previousNode->getContentSize().height * 0.5f
		                   - (previousNode->getType() == GameMapNode::NODE_FLY ? FLY_DISTANCE : 0)
		                   - node->getContentSize().height * 0.5f );

		// set direction
		switch ( node->getType() ) {
		case GameMapNode::NODE_FORWARD:
		case GameMapNode::NODE_FLY:
			node->setDirection( GameMapNode::DIRECTION_DOWN );
			break;
		case GameMapNode::NODE_TURN_LEFT:
			node->setDirection( GameMapNode::DIRECTION_RIGHT );
			break;
		case GameMapNode::NODE_TURN_RIGHT:
			node->setDirection( GameMapNode::DIRECTION_LEFT );
			break;
		}
	}
		break;

	case GameMapNode::DIRECTION_LEFT: {
		// set position
		node->setPosition( previousNode->getPositionX()
		                   - previousNode->getContentSize().width * 0.5f
		                   - (previousNode->getType() == GameMapNode::NODE_FLY ? FLY_DISTANCE : 0)
		                   - node->getContentSize().width * 0.5f,
		                   previousNode->getPositionY() );

		// set direction
		switch ( node->getType() ) {
		case GameMapNode::NODE_FORWARD:
		case GameMapNode::NODE_FLY:
			node->setDirection( GameMapNode::DIRECTION_LEFT );
			break;
		case GameMapNode::NODE_TURN_LEFT:
			node->setDirection( GameMapNode::DIRECTION_DOWN );
			break;
		case GameMapNode::NODE_TURN_RIGHT:
			node->setDirection( GameMapNode::DIRECTION_UP );
			break;
		}
	}

		break;
	case GameMapNode::DIRECTION_RIGHT: {
		// set position
		node->setPosition( previousNode->getPositionX()
		                   + previousNode->getContentSize().width * 0.5f
		                   + (previousNode->getType() == GameMapNode::NODE_FLY ? FLY_DISTANCE : 0)
		                   + node->getContentSize().width * 0.5f,
		                   previousNode->getPositionY() );

		// set direction
		switch ( node->getType() ) {
		case GameMapNode::NODE_FORWARD:
		case GameMapNode::NODE_FLY:
			node->setDirection( GameMapNode::DIRECTION_RIGHT );
			break;
		case GameMapNode::NODE_TURN_LEFT:
			node->setDirection( GameMapNode::DIRECTION_UP );
			break;
		case GameMapNode::NODE_TURN_RIGHT:
			node->setDirection( GameMapNode::DIRECTION_DOWN );
			break;
		}
	}
		break;

	}
}
}
