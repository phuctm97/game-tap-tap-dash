#include "TestMapNodeScene.h"
#include "PlayScene/Maps/PlayScene_FlyGameMapNode.h"
#include "PlayScene/Maps/PlayScene_ForwardGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnRightGameMapNode.h"
using namespace cocos2d;

namespace TestScene
{
TestMapNodeScene* TestMapNodeScene::create()
{
	auto p = new TestMapNodeScene();
	if( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE( p );
	return nullptr;
}

cocos2d::Scene* TestMapNodeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TestMapNodeScene::create();
	scene->addChild( layer );
	return scene;
}

bool TestMapNodeScene::init()
{
	if( !Layer::init() )return false;

	// event
	auto listenterKeyboard = EventListenerKeyboard::create();
	listenterKeyboard->onKeyReleased = CC_CALLBACK_2( TestMapNodeScene::onKeyPressed, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenterKeyboard, this );

	// update
	scheduleUpdate();

	return true;
}

void TestMapNodeScene::update( float dt ) {}

void TestMapNodeScene::onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e )
{
	switch( keyCode ) {
	case EventKeyboard::KeyCode::KEY_1:
	{
		removeChildByTag( 1 );

		auto node = PlayScene::ForwardGameMapNode::create();
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
											 Director::getInstance()->getVisibleSize().height * 0.5f );
		node->runAction( RepeatForever::create( RotateBy::create( 1.0f, 360 ) ) );

		CCLOG( "Node size: %f, %f", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
	break;
	case EventKeyboard::KeyCode::KEY_2:
	{
		removeChildByTag( 1 );

		auto node = PlayScene::TurnLeftGameMapNode::create();
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
											 Director::getInstance()->getVisibleSize().height * 0.5f );
		node->runAction( RepeatForever::create( RotateBy::create( 1.0f, 360 ) ) );

		CCLOG( "Node size: %f, %f", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
	break;
	case EventKeyboard::KeyCode::KEY_3:
	{
		removeChildByTag( 1 );

		auto node = PlayScene::TurnRightGameMapNode::create();
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
											 Director::getInstance()->getVisibleSize().height * 0.5f );
		node->runAction( RepeatForever::create( RotateBy::create( 1.0f, 360 ) ) );

		CCLOG( "Node size: %f, %f", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
	break;
	case EventKeyboard::KeyCode::KEY_4:
	{
		removeChildByTag( 1 );

		auto node = PlayScene::FlyGameMapNode::create();
		node->setPosition( Director::getInstance()->getVisibleSize().width * 0.5f,
											 Director::getInstance()->getVisibleSize().height * 0.5f );
		node->runAction( RepeatForever::create( RotateBy::create( 1.0f, 360 ) ) );

		CCLOG( "Node size: %f, %f", node->getContentSize().width, node->getContentSize().height );
		addChild( node, 0, 1 );
	}
	break;
	default: break;

	}
}
}
