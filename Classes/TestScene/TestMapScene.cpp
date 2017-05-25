#include "TestMapScene.h"
#include "PlayScene/Maps/PlayScene_GameMap.h"
#include "PlayScene/Maps/PlayScene_RandomGameMapGenerator.h"
#include "PlayScene/Maps/PlayScene_FlyGameMapNode.h"
#include "PlayScene/Maps/PlayScene_ForwardGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnRightGameMapNode.h"
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
	switch ( keyCode ) {
	case EventKeyboard::KeyCode::KEY_1: {
		removeChildByTag( 1 );

		auto node = PlayScene::ForwardGameMapNode::create();
		node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                   Director::getInstance()->getVisibleSize().height * 0.5f );
		
		CCLOG( "Node size: %d, %d", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
		break;
	case EventKeyboard::KeyCode::KEY_2: {
		removeChildByTag( 1 );

		auto node = PlayScene::TurnLeftGameMapNode::create();
		node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                   Director::getInstance()->getVisibleSize().height * 0.5f );
		CCLOG( "Node size: %d, %d", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
		break;
	case EventKeyboard::KeyCode::KEY_3: {
		removeChildByTag( 1 );
		
		auto node = PlayScene::TurnRightGameMapNode::create();
		node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                   Director::getInstance()->getVisibleSize().height * 0.5f );
		CCLOG( "Node size: %d, %d", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
		break;
	case EventKeyboard::KeyCode::KEY_4: {
		removeChildByTag( 1 );
		
		auto node = PlayScene::FlyGameMapNode::create();
		node->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
		                   Director::getInstance()->getVisibleSize().height * 0.5f );
		CCLOG( "Node size: %d, %d", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
		break;
	default: break;
	}
}
}
