#ifndef __TEST_MAP_SCENE_H__
#define __TEST_MAP_SCENE_H__

#include <cocos2d.h>

namespace TestScene
{
class TestMapScene : public cocos2d::Layer
{
private:

public:
	TestMapScene() {}

	static TestMapScene* create();

	static cocos2d::Scene* createScene();

	bool init() override;
};
}

#endif //!__TEST_MAP_SCENE_H__