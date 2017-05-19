#ifndef __MAIN_LAYER_H__
#define __MAIN_LAYER_H__

#include <cocos2d.h>
#include "PlayScene_IPlayer.h"

namespace PlayScene
{
class MainLayer : public cocos2d::Layer
{
private:
	bool _playing;

	IPlayer* _player;
public:
	MainLayer( IPlayer* player )
		: _playing( false ), _player( player ) {}

	static MainLayer* create( IPlayer* player );

	bool init() override;

	void reset();

	void initGraphics();

	void initEvents();

	void initGame();

	void update( float dt ) override;

	bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e ) override;

	void onKeyReleased( cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e ) override;

	void startGame();

	void stopGame();
};
}

#endif //!__MAIN_LAYER_H__
