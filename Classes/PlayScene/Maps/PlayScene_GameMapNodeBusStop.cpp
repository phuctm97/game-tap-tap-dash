#include "PlayScene_GameMapNodeBusStop.h"

USING_NS_CC;

PlayScene::GameMapNodeBusStop* PlayScene::GameMapNodeBusStop::create()
{
	auto p = new GameMapNodeBusStop();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::GameMapNodeBusStop::init()
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

bool PlayScene::GameMapNodeBusStop::initSprite()
{

	_sprite = Sprite::create("res/play-scene/map/forward_rest.png");


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

bool PlayScene::GameMapNodeBusStop::initRestSprite()
{
	_restSprite = Sprite::create("res/play-scene/map/busstop.png");

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

bool PlayScene::GameMapNodeBusStop::initLabel()
{
	_restCodeLabel = Label::createWithTTF("Bus Stop", "res/font/Bungee-Regular.ttf", 80);
	if (!_restCodeLabel)
		return false;

	this->addChild(_restCodeLabel);

	_restCodeLabel->setPosition(_restSprite->getPositionX() + _restSprite->getContentSize().width / 2 + _restCodeLabel->getContentSize().width / 2, _restSprite->getPositionY());

	return true;
}

int PlayScene::GameMapNodeBusStop::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	Point rotatedPoint = rotatePoint(worldPosition, -1 * this->getRotation(), this->getPosition());

	Rect originRect = Rect(this->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() - this->getContentSize().height / 2, this->getContentSize().width, this->getContentSize().height);

	if (originRect.containsPoint(rotatedPoint))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::GameMapNodeBusStop::getType() const
{
	return NODE_FORWARD;
}

void PlayScene::GameMapNodeBusStop::decreaseRestCode()
{

}
