#include "TestMapScene.h"
using namespace cocos2d;

namespace TestScene
{
TestMapScene* TestMapScene::create()
{
	auto p = new TestMapScene();
	if( p && p->init() ) {
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
	if( !Layer::init() )return false;

	return true;
}
}
