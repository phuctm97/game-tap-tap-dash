#include "PlayScene_GameMapNode.h"

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
