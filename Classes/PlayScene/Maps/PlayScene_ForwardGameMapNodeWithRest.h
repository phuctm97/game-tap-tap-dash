#ifndef __PLAY_SCENE_FORWARD_GAME_MAP_NODE_WITH_REST_H__
#define __PLAY_SCENE_FORWARD_GAME_MAP_NODE_WITH_REST_H__

#include <cocos2d.h>
#include "PlayScene_GameMapNode.h"

namespace PlayScene
{
class ForwardGameMapNodeWithRest : public GameMapNode
{
public:
	ForwardGameMapNodeWithRest( int restCode = -1, float restEnergy = 0.0f )
		: GameMapNode( true, restCode, restEnergy ),
		  _sprite( nullptr ), _restSprite( nullptr ), _restCodeLabel( nullptr ) {}

	static ForwardGameMapNodeWithRest* create( int code, float energy );

	bool init() override;

	bool initSprite();

	bool initRestSprite();

	bool initLabel();

	int checkPositionInside( const cocos2d::Vec2& worldPosition ) override;

	int getType() const override;

private:
	cocos2d::Sprite* _sprite;
	cocos2d::Sprite* _restSprite;
	cocos2d::Label* _restCodeLabel;
};
}

#endif //!__PLAY_SCENE_FORWARD_GAME_MAP_NODE_H__
