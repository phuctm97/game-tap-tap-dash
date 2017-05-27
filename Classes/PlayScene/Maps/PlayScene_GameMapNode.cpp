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

cocos2d::Point rotatePoint(const cocos2d::Point target, float degree, Point center)
{
	return Point((target.x - center.x)*cosf(CC_DEGREES_TO_RADIANS(degree)) - (target.y - center.y)*sinf(CC_DEGREES_TO_RADIANS(degree)) + center.x,
		(target.y - center.y)*cosf(CC_DEGREES_TO_RADIANS(degree)) + (target.x - center.x)*sinf(CC_DEGREES_TO_RADIANS(degree)) + center.y);
}