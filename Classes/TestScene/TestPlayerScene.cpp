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
	addChild( _player );

	// event
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2( TestPlayerScene::onTouchBegan, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerTouch, this );

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
	if ( keyCode == EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == EventKeyboard::KeyCode::KEY_BACK )
		Director::getInstance()->end();
}

bool TestPlayerScene::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e )
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if ( _player->getState() == PlayScene::IPlayer::IDLE ) {
		_player->run();
	}
	else if ( touch->getLocation().x < visibleSize.width * 1 / 3
		&& touch->getLocation().y > visibleSize.height * 1 / 3
		&& touch->getLocation().y < visibleSize.height * 2 / 3 ) {

		// left
		_player->turnLeft();
	}
	else if ( touch->getLocation().x > visibleSize.width * 2 / 3
		&& touch->getLocation().y > visibleSize.height * 1 / 3
		&& touch->getLocation().y < visibleSize.height * 2 / 3 ) {

		// right
		_player->turnRight();
	}
	else if ( touch->getLocation().y > visibleSize.height * 2 / 3
		&& touch->getLocation().x > visibleSize.width * 1 / 3
		&& touch->getLocation().x < visibleSize.width * 2 / 3 ) {

		// up
		_player->fly();
	}
	else if ( touch->getLocation().y < visibleSize.height * 1 / 3
		&& touch->getLocation().x > visibleSize.width * 1 / 3
		&& touch->getLocation().x < visibleSize.width * 2 / 3 ) {

		// down
	}

	return true;
}
}
