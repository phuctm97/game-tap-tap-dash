#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "PlayScene_IPlayer.h"

namespace PlayScene
{

class Player : public IPlayer
{
private:
	cocos2d::Sprite* _sprite;

	int _state;

public:
	Player()
		: _state( -1 ), _sprite( nullptr ) {}

	static Player* create();

	bool init() override;

	void update( float dt ) override;

	int getState() override;

	int idle() override;

	int runToLeft() override;

	int runToRight() override;

	int die() override;

private:
	bool initSprite();

	bool initContent();

	bool initEvents();
};

}

#endif //!__PLAYER_H__
