#include "PlayScene_TurnRightGameMapNode.h"

USING_NS_CC;

PlayScene::TurnRightGameMapNode* PlayScene::TurnRightGameMapNode::create()
{
	auto p = new TurnRightGameMapNode();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::TurnRightGameMapNode::init()
{
	if (!Node::init())
		return false;

	if (!initSprite())
		return false;

	return true;
}

bool PlayScene::TurnRightGameMapNode::initSprite()
{
	_sprite = Sprite::create("res/test/blank.png");

	if (!_sprite)
		return false;

	this->addChild(_sprite);

	// synchronize transformations

	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_sprite->setPosition(0, 0);

	_sprite->setScale(getScale());

	_sprite->setRotation(getRotation());

	setContentSize(_sprite->getContentSize());

	_navigator = Sprite::create("res/test/right.png");

	if (!_navigator)
		return false;

	_sprite->addChild(_navigator);

	_navigator->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_navigator->setPosition(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2);

	_navigator->setScale(_sprite->getScale());

	_navigator->setRotation(_sprite->getRotation());

	return true;
}



int PlayScene::TurnRightGameMapNode::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	if ((worldPosition.x >= this->getPositionX() - this->getContentSize().width / 2)
		&& (worldPosition.x <= this->getPositionX() + this->getContentSize().width / 2)
		&& (worldPosition.y >= this->getPositionY() - this->getContentSize().height / 2)
		&& (worldPosition.y <= this->getPositionY() + this->getContentSize().height / 2))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::TurnRightGameMapNode::getType() const
{
	return NODE_TURN_RIGHT;
}

