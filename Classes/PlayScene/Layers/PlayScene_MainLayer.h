#ifndef __PLAY_SCENE_MAIN_LAYER_H__
#define __PLAY_SCENE_MAIN_LAYER_H__

#include <cocos2d.h>
#include "../Players/PlayScene_IPlayer.h"
#include "PlayScene/Maps/PlayScene_GameMap.h"

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

	GameMap* _map;

	int _state;

	float _gameSpeed;

	cocos2d::Sprite* _house;
	cocos2d::Sprite* _bus;

public:
	MainLayer( IPlayer* player, GameMap* map )
		: _player( player ), _map( map ),
		  _house( nullptr ),
		  _state( WAIT_FOR_PLAY ), _gameSpeed( 0 ) {}

	~MainLayer();

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

	void setGameSpeed( float speed );

	void startIntroCut();

	void postIntroCut0();

	void postIntroCut1();

	void postIntroCut2();
};
}

#endif //!__PLAY_SCENE_MAIN_LAYER_H__
