#ifndef __PLAY_SCENE_MAIN_LAYER_H__
#define __PLAY_SCENE_MAIN_LAYER_H__

#include <cocos2d.h>
#include "../Players/PlayScene_IPlayer.h"
#include "../Maps/PlayScene_IGameMap.h"

namespace PlayScene
{
class MainLayer : public cocos2d::Layer
{
	enum
	{
		WAIT_FOR_PLAY,
		PLAYING,
		PAUSED,
		GAME_OVER
	};

private:
	IPlayer* _player;

	IGameMap* _map;

	int _state;

	int _speed;

public:
	MainLayer( IPlayer* player, IGameMap* map )
		: _player( player ), _map( map ), _state( WAIT_FOR_PLAY ), _speed( 2 ) {}

	static MainLayer* create( IPlayer* player, IGameMap* map );

	bool init() override;

	void initGraphics();

	void initGame();
	
	void initEvents();

	bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e ) override;

	void onKeyReleased( cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e ) override;

	void reset();

	void startGame();

	void winGame();

	void loseGame();

	void update( float dt ) override;
};
}

#endif //!__PLAY_SCENE_MAIN_LAYER_H__
