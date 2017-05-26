#ifndef __TEST_MAP_SCENE_H__
#define __TEST_MAP_SCENE_H__

#include <cocos2d.h>

namespace PlayScene
{
class GameMap;
}

namespace TestScene
{
class TestMapScene : public cocos2d::Layer
{
private:
	PlayScene::GameMap* _gameMap;

public:
	TestMapScene()
		: _gameMap( nullptr ) {}

	static TestMapScene* create();

	static cocos2d::Scene* createScene();

	bool init() override;

	void update( float dt ) override;

	void onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e ) override;

	bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e ) override;
};
}

#endif //!__TEST_MAP_SCENE_H__
