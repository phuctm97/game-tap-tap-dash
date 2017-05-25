#include "PlayScene_GameMapNode.h"
using namespace cocos2d;

namespace PlayScene
{
int GameMapNode::getDirection() const
{
	return _direction;
}

void GameMapNode::setDirection( int direction )
{
	_direction = direction;
}
}
