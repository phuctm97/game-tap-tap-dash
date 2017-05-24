#include "TestPlayerScene.h"
#include "PlayScene/Players/PlayScene_Player.h"
using namespace cocos2d;

namespace TestScene
{
TestPlayerScene* TestPlayerScene::create()
{
	auto p = new TestPlayerScene();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE( p );
	return nullptr;
}

cocos2d::Scene* TestPlayerScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TestPlayerScene::create();
	scene->addChild( layer );
	return scene;
}

bool TestPlayerScene::init()
{
	if ( !Layer::init() )return false;

	// player
	_player = PlayScene::Player::create();
	_player->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_player->setPosition( Director::getInstance()->getVisibleSize().width / 2,
												Director::getInstance()->getVisibleSize().height / 2 );
	addChild( _player );

	// event
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2( TestPlayerScene::onKeyPressed, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerKeyboard, this );
	
	// update
	scheduleUpdate();

	return true;
}

void TestPlayerScene::update( float dt )
{
	CCLOG( "Player state: %d", _player->getState() );
}

void TestPlayerScene::onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e )
{
	switch( keyCode ) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW : {
		_player->turnLeft();
	} break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
		_player->turnRight();
	} break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW: {
		_player->fly();
	} break;
	case EventKeyboard::KeyCode::KEY_ESCAPE: {
		Director::getInstance()->end();
	} break;
	default: break;
	}
}
}
