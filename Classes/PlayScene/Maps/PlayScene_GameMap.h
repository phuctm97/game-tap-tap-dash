#ifndef __PLAY_SCENE_GAME_MAP_H__
#define __PLAY_SCENE_GAME_MAP_H__
#include "PlayScene_IGameMap.h"
#include "PlayScene_IGameMapGenerator.h"

namespace PlayScene
{
class GameMap : public IGameMap
{
private:
	cocos2d::Vector<GameMapNode*> _activeNodes;

	IGameMapGenerator* _generator;

public:
	GameMap( IGameMapGenerator* generator )
		: _generator( generator ) {}

	~GameMap();

	static GameMap* create( IGameMapGenerator* generator );

	bool init() override;

	void setSpeed( int speed ) override;

	void scroll() override;

	GameMapNode* getCurrentNode() const override;

	GameMapNode* nextNode() override;

	bool isEnd() const override;

	int getNextControl() const override;

	void reset( const cocos2d::Vec2& position ) override;

	void stop() override;
private:
	bool initGraphics();

	bool initContent();

	bool initEvents();

	void generateInitialNodes();
};
}

#endif //!__PLAY_SCENE_GAME_MAP_H__
