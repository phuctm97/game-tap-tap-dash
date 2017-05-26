#ifndef __TEST_MAP_NODE_SCENE_H__
#define __TEST_MAP_NODE_SCENE_H__

#include <cocos2d.h>

namespace TestScene
{
class TestMapNodeScene : public cocos2d::Layer
{
private:
	int _touchTimes;

public:
	TestMapNodeScene()
		: _touchTimes( 0 ) {}

	static TestMapNodeScene* create();

	static cocos2d::Scene* createScene();

	bool init() override;

	void update( float dt ) override;

	void onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e ) override;

	bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e ) override;
};
}

#endif //!__TEST_MAP_NODE_SCENE_H__
