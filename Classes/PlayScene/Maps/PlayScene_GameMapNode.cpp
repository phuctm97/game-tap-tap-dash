#include "PlayScene_GameMapNode.h"

USING_NS_CC;

PlayScene::GameMapNode* PlayScene::GameMapNode::create()
{
	auto p = new GameMapNode();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	return nullptr;
}

bool PlayScene::GameMapNode::init()
{
	if (!initSprite())
		return false;

	return true;
}

bool PlayScene::GameMapNode::initSprite()
{
	imgNode = Sprite::create("res/blank.png");

	if (!imgNode)
		return false;

	this->addChild(imgNode);

	// synchronize transformations

	imgNode->setAnchorPoint(Point::ANCHOR_MIDDLE);

	imgNode->setPosition(0, 0);

	imgNode->setScale(getScale());

	imgNode->setRotation(getRotation());

	setContentSize(imgNode->getContentSize());
	
	return true;
}

int PlayScene::GameMapNode::checkPositionInside(const cocos2d::Vec2& worldPosition)
{
	if ((worldPosition.x >= this->getPositionX() - this->getContentSize().width / 2)
		&& (worldPosition.x <= this->getPositionX() + this->getContentSize().width / 2)
		&& (worldPosition.y >= this->getPositionY() - this->getContentSize().height / 2)
		&& (worldPosition.y <= this->getPositionY() + this->getContentSize().height / 2))

		return 1;

	return 0;
}

