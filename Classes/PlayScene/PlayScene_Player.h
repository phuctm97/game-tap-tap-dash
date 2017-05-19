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

	int getState() const override;

	void reset( const cocos2d::Vec2& position ) override;

	void run() override;

	void turnLeft() override;

	void turnRight() override;

	void fly() override;

	void die() override;

private:
	bool initSprite();

	bool initEvents();
	
	bool initContent();
};

}

#endif //!__PLAYER_H__
