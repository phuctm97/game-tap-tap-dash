#include "MyDirector.h"

using namespace cocos2d;

MyDirector* MyDirector::_instance = nullptr;

MyDirector::MyDirector()
	: _introScene( nullptr ), _playScene( nullptr )
{
	createIntroScene();

	createPlayScene();
}

MyDirector::~MyDirector()
{
	CC_SAFE_RELEASE( _playScene );

	CC_SAFE_RELEASE( _introScene );
}

MyDirector* MyDirector::getInstance()
{
	if ( _instance == nullptr ) {
		_instance = new MyDirector();
	}
	return _instance;
}

cocos2d::Scene* MyDirector::getIntroScene() const
{
	return _introScene;
}

cocos2d::Scene* MyDirector::resetIntroScene() const
{
	auto mainLayer = static_cast<IntroScene::MainLayer*>(_introScene->getChildByName( "a" ));
	mainLayer->reset();

	return _introScene;
}

cocos2d::Scene* MyDirector::getLevelScene() const { throw "not implemented"; }

cocos2d::Scene* MyDirector::resetLevelScene() const { throw "not implemented"; }

cocos2d::Scene* MyDirector::getPlayScene() const
{
	return _playScene;
}

PlayScene::MainLayer* MyDirector::getPlaySceneMainLayer() const
{
	return static_cast<PlayScene::MainLayer*>(_playScene->getChildByName( "a" ));
}

cocos2d::Scene* MyDirector::resetPlayScene() const
{
	auto mainLayer = static_cast<PlayScene::MainLayer*>(_playScene->getChildByName( "a" ));
	mainLayer->reset();

	return _playScene;
}

void MyDirector::end()
{
	release();

	Director::getInstance()->end();
}

void MyDirector::createIntroScene()
{
	_introScene = Scene::create();
	_introScene->retain();

	auto mainLayer = IntroScene::MainLayer::create();
	_introScene->addChild( mainLayer, 0, "a" );
}

void MyDirector::createLevelScene() { throw "not implemented"; }

void MyDirector::createPlayScene()
{
	_playScene = Scene::create();
	_playScene->retain();

	auto player = PlayScene::Player::create();
	auto generator = PlayScene::TxtGameMapGenerator::create( "res/data/level-1.txt" );
	auto gameMap = PlayScene::GameMap::create( generator );

	auto mainLayer = PlayScene::MainLayer::create( player, gameMap );
	_playScene->addChild( mainLayer, 0, "a" );
}
