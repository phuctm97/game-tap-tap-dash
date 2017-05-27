#ifndef __PLAY_SCENE_MAIN_LAYER_H__
#define __PLAY_SCENE_MAIN_LAYER_H__

#include <cocos2d.h>
#include "../Players/PlayScene_IPlayer.h"
#include "PlayScene/Maps/PlayScene_GameMap.h"

namespace PlayScene
{
class MainLayer : public cocos2d::LayerColor
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

	GameMap* _map;

	cocos2d::Sprite* _background;

	int _state;

	int _speed;

	int _timeToStart;
	cocos2d::Label* _labelTimeToStart;

public:
	MainLayer( IPlayer* player, GameMap* map )
		: _player( player ), _map( map ), _labelTimeToStart( nullptr ), _background( nullptr ),
		  _state( WAIT_FOR_PLAY ), _speed( 2 ), _timeToStart( 0 ) {}

	static MainLayer* create( IPlayer* player, GameMap* map );

	bool init() override;

	void initGraphics();

	void initGame();

	void initEvents();

	bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* e ) override;

	void updateMapScrollDirection() const;

	void onKeyReleased( cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e ) override;

	void reset();

	void startGame();

	void interactGame() const;

	void winGame();

	void loseGame();

	void onPassedNode( GameMapNode* node ) const;

	void update( float dt ) override;

	void setSpeed( float speed ) const;

	void startCountdownTimeToStart();

	void stopCountdownTimeToStart();

	void countdownTimeToStart( float dt );
};
}

#endif //!__PLAY_SCENE_MAIN_LAYER_H__
