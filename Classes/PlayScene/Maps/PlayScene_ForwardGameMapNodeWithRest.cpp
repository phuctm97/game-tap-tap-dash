#include "PlayScene_ForwardGameMapNodeWithRest.h"

USING_NS_CC;

PlayScene::ForwardGameMapNodeWithRest* PlayScene::ForwardGameMapNodeWithRest::create(int code, float energy)
{
	auto p = new ForwardGameMapNodeWithRest(code, energy);
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::ForwardGameMapNodeWithRest::init()
{
	if (!Node::init())
		return false;

	if (!initSprite())
		return false;

	if (!initRestSprite())
		return false;

	if (!initLabel())
		return false;

	return true;
}

bool PlayScene::ForwardGameMapNodeWithRest::initSprite()
{

	_sprite = Sprite::create("res/test/forward_b.png");


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

bool PlayScene::ForwardGameMapNodeWithRest::initRestSprite()
{
	_restSprite = Sprite::create("res/test/rest.png");

	if (!_restSprite)
		return false;

	this->addChild(_restSprite);

	// tranformations


	_restSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_restSprite->setPosition(_sprite->getPositionX() + _sprite->getContentSize().width / 2 + _restSprite->getContentSize().width / 2, _sprite->getPositionY());

	_restSprite->setScale(getScale());

	_restSprite->setRotation(getRotation());

	return true;
}

bool PlayScene::ForwardGameMapNodeWithRest::initLabel()
{
	_restCodeLabel = Label::createWithTTF("Test Label", "res/font/Bungee-Regular.ttf", 80);
	if (!_restCodeLabel)
		return false;

	this->addChild(_restCodeLabel);

	_restCodeLabel->setPosition(_restSprite->getPositionX() + _restSprite->getContentSize().width / 2 + _restCodeLabel->getContentSize().width / 2, _restSprite->getPositionY());

	return true;
}

int PlayScene::ForwardGameMapNodeWithRest::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	if ((worldPosition.x >= this->getPositionX() - this->getContentSize().width / 2)
		&& (worldPosition.x <= this->getPositionX() + this->getContentSize().width / 2)
		&& (worldPosition.y >= this->getPositionY() - this->getContentSize().height / 2)
		&& (worldPosition.y <= this->getPositionY() + this->getContentSize().height / 2))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::ForwardGameMapNodeWithRest::getType() const
{
	return NODE_FORWARD;
}
