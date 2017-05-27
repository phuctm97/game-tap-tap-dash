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
	_sprite = Sprite::create("res/test/right_b.png");

	if (!_sprite)
		return false;

	this->addChild(_sprite);

	// synchronize transformations

	setContentSize(_sprite->getContentSize());

	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_sprite->setPosition(getContentSize()*0.5f);

	_sprite->setScale(getScale());

	_sprite->setRotation(getRotation());

	setContentSize(_sprite->getContentSize());

	_navigator = Sprite::create("res/test/right.png");

	if (!_navigator)
		return false;

	this->addChild(_navigator);

	_navigator->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_navigator->setPosition(_sprite->getContentSize().width / 2, _sprite->getContentSize().height / 2);

	_navigator->setScale(_sprite->getScale());

	_navigator->setRotation(_sprite->getRotation());

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	return true;
}



int PlayScene::TurnRightGameMapNode::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	Point rotatedPoint = rotatePoint(worldPosition, -1 * this->getRotation(), this->getPosition());

	Rect originRect = Rect(this->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() - this->getContentSize().height / 2, this->getContentSize().width, this->getContentSize().height);

	if (originRect.containsPoint(rotatedPoint))
		return POSITION_INSIDE;

	return POSITION_OUTSIDE;
}

int PlayScene::TurnRightGameMapNode::getType() const
{
	return NODE_TURN_RIGHT;
}

void PlayScene::TurnRightGameMapNode::highLightNavi()
{
	_navigator->setColor(Color3B::YELLOW);
}

void PlayScene::TurnRightGameMapNode::unHighLightNavi()
{
	_navigator->setColor(Color3B::WHITE);
}

