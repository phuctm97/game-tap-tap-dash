#include "PlayScene_FlyGameMapNode.h"

USING_NS_CC;

PlayScene::FlyGameMapNode* PlayScene::FlyGameMapNode::create()
{
	auto p = new FlyGameMapNode();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return nullptr;
}

bool PlayScene::FlyGameMapNode::init()
{
	if (!Node::init())
		return false;

	if (!initSprite())
		return false;

	return true;
}

bool PlayScene::FlyGameMapNode::initSprite()
{
	_sprite = Sprite::create("res/play-scene/map/fly_b.png");

	if (!_sprite)
		return false;

	this->addChild(_sprite);

	// synchronize transformations

	setContentSize(_sprite->getContentSize());

	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_sprite->setPosition(getContentSize()*0.5f);

	_sprite->setScale(getScale());

	_sprite->setRotation(getRotation());



	_navigator = Sprite::create("res/play-scene/map/fly.png");

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


int PlayScene::FlyGameMapNode::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	Point rotatedPoint = rotatePoint(worldPosition, -1 * this->getRotation(), this->getPosition());

	Rect originRect = Rect(this->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() - this->getContentSize().height / 2, this->getContentSize().width, this->getContentSize().height);

	if (originRect.containsPoint(rotatedPoint))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::FlyGameMapNode::getType() const
{
	return NODE_FLY;
}

void PlayScene::FlyGameMapNode::highLightNavi()
{
	_navigator->setColor(Color3B::YELLOW);
}

void PlayScene::FlyGameMapNode::unHighLightNavi()
{
	_navigator->setColor(cocos2d::Color3B::WHITE);
}

