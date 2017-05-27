#include "PlayScene_FlyGameMapNode2.h"

USING_NS_CC;

PlayScene::FlyGameMapNode2* PlayScene::FlyGameMapNode2::create()
{
	auto p = new FlyGameMapNode2();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::FlyGameMapNode2::init()
{
	if (!Node::init())
		return false;

	if (!initSprite())
		return false;

	return true;
}

bool PlayScene::FlyGameMapNode2::initSprite()
{
	_sprite = Sprite::create("res/test/fly_b_2.png");

	if (!_sprite)
		return false;

	this->addChild(_sprite);

	// synchronize transformations

	setContentSize(_sprite->getContentSize());

	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_sprite->setPosition(getContentSize()*0.5f);

	_sprite->setScale(getScale());

	_sprite->setRotation(getRotation());



	_navigator = Sprite::create("res/test/fly.png");

	if (!_navigator)
		return false;

	this->addChild(_navigator);

	// synchronize transformations

	_navigator->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_navigator->setPosition(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2);

	_navigator->setScale(getScale());

	_navigator->setRotation(getRotation());

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	return true;
}


int PlayScene::FlyGameMapNode2::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	if ((worldPosition.x >= this->getPositionX() - this->getContentSize().width / 2)
		&& (worldPosition.x <= this->getPositionX() + this->getContentSize().width / 2)
		&& (worldPosition.y >= this->getPositionY() - this->getContentSize().height / 2)
		&& (worldPosition.y <= this->getPositionY() + this->getContentSize().height / 2))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::FlyGameMapNode2::getType() const
{
	return NODE_FLY;
}

