#ifndef __TEST_PLAYER_SCENE_H__
#define __TEST_PLAYER_SCENE_H__

#include <cocos2d.h>
#include "PlayScene/Players/PlayScene_IPlayer.h"

namespace TestScene
{
class TestPlayerScene : public cocos2d::Layer
{
private:
	PlayScene::IPlayer* _player;

public:
	TestPlayerScene()
		: _player( nullptr ) {}

	static TestPlayerScene* create();

	static cocos2d::Scene* createScene();

	bool init() override;
};
}

#endif //!__TEST_PLAYER_SCENE_H__
