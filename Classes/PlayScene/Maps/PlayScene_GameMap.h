#ifndef __PLAY_SCENE_GAME_MAP_H__
#define __PLAY_SCENE_GAME_MAP_H__

#include "PlayScene_GameMapGenerator.h"

namespace PlayScene
{
class GameMap : public cocos2d::Node
{
private:
	cocos2d::Vector<GameMapNode*> _activeNodes;

	IGameMapGenerator* _generator;

public:
	enum
	{
		NONE,
		TURN_LEFT,
		TURN_RIGHT,
		FLY
	};

	GameMap( IGameMapGenerator* generator )
		: _generator( generator ) {}

	~GameMap();

	static GameMap* create( IGameMapGenerator* generator );

	bool init() override;

	void setSpeed( int speed );

	void scroll();

	GameMapNode* getCurrentNode() const;

	GameMapNode* nextNode();

	bool isEnd() const;

	int getNextControl() const;

	void reset( const cocos2d::Vec2& position );

	void stop();

private:
	bool initGraphics();

	bool initContent();

	bool initEvents();

	void generateInitialNodes();
};
}

#endif //!__PLAY_SCENE_GAME_MAP_H__
