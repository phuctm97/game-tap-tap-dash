#ifndef __MY_DIRECTOR_H__
#define __MY_DIRECTOR_H__

#include <cocos2d.h>

class MyDirector : cocos2d::Ref
{
	// Static instance
private:
	static MyDirector* _instance;
public:
	static MyDirector* getInstance();

private:
	cocos2d::Scene* _playScene;

public:
	MyDirector();

	~MyDirector();

	cocos2d::Scene* getPlayScene() const;

	cocos2d::Scene* resetPlayScene() const;

	void end();

private:
	void createPlayScene();
};

#endif //!__MY_DIRECTOR_H__
