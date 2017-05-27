#ifndef __MY_DIRECTOR_H__
#define __MY_DIRECTOR_H__

#include <cocos2d.h>
#include "PlayScene/Players/PlayScene_Player.h"
#include "PlayScene/Layers/PlayScene_MainLayer.h"
#include "PlayScene/Maps/PlayScene_TxtGameMapGenerator.h"
#include "IntroScene/Layers/IntroScene_MainLayer.h"

class MyDirector : cocos2d::Ref
{
	// Static instance
private:
	static MyDirector* _instance;
public:
	static MyDirector* getInstance();

private:
	cocos2d::Scene* _introScene;
	cocos2d::Scene* _levelScene;
	cocos2d::Scene* _playScene;

public:
	MyDirector();

	~MyDirector();

	cocos2d::Scene* getIntroScene() const;

	cocos2d::Scene* resetIntroScene() const;

	cocos2d::Scene* getLevelScene() const;

	cocos2d::Scene* resetLevelScene() const;

	cocos2d::Scene* getPlayScene() const;

	PlayScene::MainLayer* getPlaySceneMainLayer() const;

	cocos2d::Scene* resetPlayScene() const;

	void end();

private:
	void createIntroScene();
	
	void createLevelScene();

	void createPlayScene();
};

#endif //!__MY_DIRECTOR_H__
