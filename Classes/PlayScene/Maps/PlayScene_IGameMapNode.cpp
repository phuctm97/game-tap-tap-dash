#include "PlayScene_IGameMapNode.h"

namespace PlayScene
{
int IGameMapNode::getDirection() const
{
	return _direction;
}

void IGameMapNode::setDirection( int direction )
{
	_direction = direction;
}
}
