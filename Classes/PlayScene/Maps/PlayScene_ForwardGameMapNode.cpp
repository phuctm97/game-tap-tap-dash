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

	this->setAnchorPoint(Vec2(0, 0));

	return true;
}

bool PlayScene::ForwardGameMapNode::initSprite()
{

	_sprite = Sprite::create("res/test/blank.png");


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
	if ((worldPosition.x >= this->getPositionX() - this->getContentSize().width / 2)
		&& (worldPosition.x <= this->getPositionX() + this->getContentSize().width / 2)
		&& (worldPosition.y >= this->getPositionY() - this->getContentSize().height / 2)
		&& (worldPosition.y <= this->getPositionY() + this->getContentSize().height / 2))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::ForwardGameMapNode::getType() const
{
	return NODE_FORWARD;
}
