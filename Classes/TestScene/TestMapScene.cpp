#include "TestMapScene.h"
#include "PlayScene/Maps/PlayScene_GameMap.h"
#include "PlayScene/Maps/PlayScene_RandomGameMapGenerator.h"
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

	_gameMap = PlayScene::GameMap::create( PlayScene::RandomGameMapGenerator::create() );
	_gameMap->setScrollSpeed( 1.0f );
	_gameMap->scroll();
	addChild( _gameMap );

	// event
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2( TestMapScene::onTouchBegan, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerTouch, this );

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
	if ( keyCode == EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == EventKeyboard::KeyCode::KEY_BACK )
		Director::getInstance()->end();
}

bool TestMapScene::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e )
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if ( touch->getLocation().x < visibleSize.width * 1 / 3
		&& touch->getLocation().y > visibleSize.height * 1 / 3
		&& touch->getLocation().y < visibleSize.height * 2 / 3 ) {

		// left
		_gameMap->setScrollDirection( PlayScene::GameMap::SCROLL_LEFT );
	}
	else if ( touch->getLocation().x > visibleSize.width * 2 / 3
		&& touch->getLocation().y > visibleSize.height * 1 / 3
		&& touch->getLocation().y < visibleSize.height * 2 / 3 ) {

		// right
		_gameMap->setScrollDirection( PlayScene::GameMap::SCROLL_RIGHT );
	}
	else if ( touch->getLocation().y > visibleSize.height * 2 / 3
		&& touch->getLocation().x > visibleSize.width * 1 / 3
		&& touch->getLocation().x < visibleSize.width * 2 / 3 ) {

		// up
		_gameMap->setScrollDirection( PlayScene::GameMap::SCROLL_UP );
	}
	else if ( touch->getLocation().y < visibleSize.height * 1 / 3
		&& touch->getLocation().x > visibleSize.width * 1 / 3
		&& touch->getLocation().x < visibleSize.width * 2 / 3 ) {

		// down
		_gameMap->setScrollDirection( PlayScene::GameMap::SCROLL_DOWN );
	}

	return true;
}
}
