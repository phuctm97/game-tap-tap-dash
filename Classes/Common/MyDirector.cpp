#include "MyDirector.h"
#include "PlayScene/PlayScene_Player.h"
#include "PlayScene/PlayScene_MainLayer.h"
using namespace cocos2d;

MyDirector* MyDirector::_instance = nullptr;

MyDirector::MyDirector()
	: _playScene( nullptr )
{
	createPlayScene();
}

MyDirector::~MyDirector()
{
	CC_SAFE_RELEASE( _playScene );
}

MyDirector* MyDirector::getInstance()
{
	if ( _instance == nullptr ) {
		_instance = new MyDirector();
	}
	return _instance;
}

cocos2d::Scene* MyDirector::getPlayScene() const
{
	return _playScene;
}

cocos2d::Scene* MyDirector::resetPlayScene() const
{
	auto mainLayer = static_cast<PlayScene::MainLayer*>(_playScene->getChildByName( "mainLayer" ));
	mainLayer->reset();

	return _playScene;
}

void MyDirector::end()
{
	release();

	Director::getInstance()->end();
}

void MyDirector::createPlayScene()
{
	_playScene = Scene::create();
	_playScene->retain();

	auto mainLayer = PlayScene::MainLayer::create( PlayScene::Player::create() );
	_playScene->addChild( mainLayer, 0, "mainLayer" );
}