#ifndef __PLAY_SCENE_GAME_MAP_NODE_H__
#define __PLAY_SCENE_GAME_MAP_NODE_H__

#include <cocos2d.h>

namespace PlayScene
{
class GameMapNode : public cocos2d::Node
{
private:
	int _direction;

	bool _isRestNode;

	int _restCode;

	float _restEnergy;

public:
	enum
	{
		POSITION_INSIDE,
		POSITION_OUTSIDE,

		NODE_FORWARD,
		NODE_TURN_LEFT,
		NODE_TURN_RIGHT,
		NODE_FLY,

		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	GameMapNode()
		: _direction( DIRECTION_UP ), _isRestNode( false ), _restCode( -1 ), _restEnergy( 0 ) {}

	virtual int checkPositionInside( const cocos2d::Vec2& worldPosition ) = 0;

	virtual int getType() const = 0;

	int getDirection() const;

	bool isRestNode() const;

	void decreaseRestCode();

	int getRestCode() const;

	float getRestEnergy() const;

	void setDirection( int direction );
};
}

#endif //!__PLAY_SCENE_GAME_MAP_NODE_H__
