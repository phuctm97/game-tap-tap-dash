#include "PlayScene_GameMapNode.h"
using namespace cocos2d;

namespace PlayScene
{
int GameMapNode::getDirection() const
{
	return _direction;
}

bool GameMapNode::isRestNode() const
{
	return _isRestNode;
}

void GameMapNode::decreaseRestCode()
{
	_restCode--;
}

int GameMapNode::getRestCode() const
{
	return _restCode;
}

float GameMapNode::getRestEnergy() const
{
	return _restEnergy;
}

void GameMapNode::setDirection( int direction )
{
	_direction = direction;
}
}
