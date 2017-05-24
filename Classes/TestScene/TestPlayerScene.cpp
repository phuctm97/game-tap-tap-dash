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

	_player = PlayScene::Player::create();
	_player->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_player->setPosition( Director::getInstance()->getVisibleSize().width / 2,
												Director::getInstance()->getVisibleSize().height / 2 );
	addChild( _player );

	return true;
}
}
