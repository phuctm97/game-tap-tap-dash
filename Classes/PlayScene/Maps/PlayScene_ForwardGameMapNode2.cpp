#include "PlayScene_ForwardGameMapNode2.h"

USING_NS_CC;

PlayScene::ForwardGameMapNode2* PlayScene::ForwardGameMapNode2::create()
{
	auto p = new ForwardGameMapNode2();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::ForwardGameMapNode2::init()
{
	if (!Node::init())
		return false;

	if (!initSprite())
		return false;

	return true;
}

bool PlayScene::ForwardGameMapNode2::initSprite()
{

	_sprite = Sprite::create("res/test/forward_b_2.png");


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

int PlayScene::ForwardGameMapNode2::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	Point rotatedPoint = rotatePoint(worldPosition, -1 * this->getRotation(), this->getPosition());

	Rect originRect = Rect(this->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() - this->getContentSize().height / 2, this->getContentSize().width, this->getContentSize().height);

	if (originRect.containsPoint(rotatedPoint))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::ForwardGameMapNode2::getType() const
{
	return NODE_FORWARD;
}
