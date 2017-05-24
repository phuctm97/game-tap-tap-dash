#include "TestMapScene.h"
#include "PlayScene/Maps/PlayScene_ForwardGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnRightGameMapNode.h"
#include "PlayScene/Maps/PlayScene_FlyGameMapNode.h"
using namespace cocos2d;

namespace TestScene
{
TestMapScene* TestMapScene::create()
{
	auto p = new TestMapScene();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE( p );
	return nullptr;
}

cocos2d::Scene* TestMapScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TestMapScene::create();
	scene->addChild( layer );
	return scene;
}

bool TestMapScene::init()
{
	if ( !Layer::init() )return false;

	// event
	auto listenterKeyboard = EventListenerKeyboard::create();
	listenterKeyboard->onKeyReleased = CC_CALLBACK_2( TestMapScene::onKeyPressed, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenterKeyboard, this );

	// update
	scheduleUpdate();

	return true;
}

void TestMapScene::update( float dt ) { }

void TestMapScene::onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e )
{
	// test map node

	switch ( keyCode ) {
	case EventKeyboard::KeyCode::KEY_1: {
		auto forwardMapNode = PlayScene::ForwardGameMapNode::create();
		forwardMapNode->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		forwardMapNode->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                             Director::getInstance()->getVisibleSize().height * 0.5f );
		addChild( forwardMapNode );
	}
		break;
	case EventKeyboard::KeyCode::KEY_2: {
		auto turnLeftMapNode = PlayScene::TurnLeftGameMapNode::create();
		turnLeftMapNode->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		turnLeftMapNode->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                              Director::getInstance()->getVisibleSize().height * 0.5f );
		addChild( turnLeftMapNode );
	}
		break;
	case EventKeyboard::KeyCode::KEY_3: {
		auto turnRightMapNode = PlayScene::TurnRightGameMapNode::create();
		turnRightMapNode->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		turnRightMapNode->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                               Director::getInstance()->getVisibleSize().height * 0.5f );
		addChild( turnRightMapNode );
	}
		break;
	case EventKeyboard::KeyCode::KEY_4: {
		auto flyMapNode = PlayScene::FlyGameMapNode::create();
		flyMapNode->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		flyMapNode->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                         Director::getInstance()->getVisibleSize().height * 0.5f );
		addChild( flyMapNode );
	}
		break;
	default: break;
	}
}
}
