#ifndef __INTRO_SCENE_MAIN_LAYER_H__
#define __INTRO_SCENE_MAIN_LAYER_H__

#include <cocos2d.h>

namespace IntroScene
{
class MainLayer : public cocos2d::Layer
{
public:
	static MainLayer* create();

	bool init() override;

	void reset();
};
}

#endif //!__INTRO_SCENE_MAIN_LAYER_H__
