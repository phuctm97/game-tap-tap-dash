#include "PlayScene_ForwardGameMapNode.h"

USING_NS_CC;

PlayScene::ForwardGameMapNode* PlayScene::ForwardGameMapNode::create()
{
	auto p = new ForwardGameMapNode();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::ForwardGameMapNode::init()
{
	if (!Node::init())
		return false;

	if (!initSprite())
		return false;

	return true;
}

bool PlayScene::ForwardGameMapNode::initSprite()
{

	_sprite = Sprite::create("res/play-scene/map/forward_b.png");


	if (!_sprite)
		return false;

	this->addChild(_sprite);

	// synchronize transformations

	setContentSize(_sprite->getContentSize());

	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_sprite->setPosition(getContentSize()*0.5f);

	_sprite->setScale(getScale());

	_sprite->setRotation(getRotation());

	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	return true;
}

int PlayScene::ForwardGameMapNode::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	Point rotatedPoint = rotatePoint(worldPosition, -1 * this->getRotation(), this->getPosition());

	Rect originRect = Rect(this->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() - this->getContentSize().height / 2, this->getContentSize().width, this->getContentSize().height);

	if (originRect.containsPoint(rotatedPoint))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::ForwardGameMapNode::getType() const
{
	return NODE_FORWARD;
}
