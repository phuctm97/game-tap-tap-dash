#include "PlayScene_TurnLeftGameMapNode.h"

USING_NS_CC;

PlayScene::TurnLeftGameMapNode* PlayScene::TurnLeftGameMapNode::create()
{
	auto p = new TurnLeftGameMapNode();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::TurnLeftGameMapNode::init()
{
	if (!Node::init())
		return false;

	if (!initSprite())
		return false;

	if (!initNavigator())
		return false;

	return true;
}

bool PlayScene::TurnLeftGameMapNode::initSprite()
{
	_sprite = Sprite::create("res/blank.png");
	

	if (!_sprite)
		return false;

	this->addChild(_sprite);

	// synchronize transformations

	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_sprite->setPosition(0, 0);

	_sprite->setScale(getScale());

	_sprite->setRotation(getRotation());

	setContentSize(_sprite->getContentSize());

	return true;
}

bool PlayScene::TurnLeftGameMapNode::initNavigator()
{
	_navigator = Sprite::create("navi_left.png");

	if (!_navigator)
		return false;

	this->addChild(_navigator, 1);

	// synchronize transformations

	_navigator->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_navigator->setPosition(0, 0);

	_navigator->setScale(getScale());

	_navigator->setRotation(getRotation());

	setContentSize(_navigator->getContentSize());

	return true;
}

int PlayScene::TurnLeftGameMapNode::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	if ((worldPosition.x >= this->getPositionX() - this->getContentSize().width / 2)
		&& (worldPosition.x <= this->getPositionX() + this->getContentSize().width / 2)
		&& (worldPosition.y >= this->getPositionY() - this->getContentSize().height / 2)
		&& (worldPosition.y <= this->getPositionY() + this->getContentSize().height / 2))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::TurnLeftGameMapNode::getType() const
{
	return NODE_TURN_LEFT;
}

