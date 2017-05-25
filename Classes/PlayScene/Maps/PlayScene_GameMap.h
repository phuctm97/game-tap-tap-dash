#ifndef __PLAY_SCENE_GAME_MAP_H__
#define __PLAY_SCENE_GAME_MAP_H__
#include "PlayScene_IGameMap.h"
#include "PlayScene_IGameMapGenerator.h"

namespace PlayScene
{
class GameMap : public IGameMap
{
private:
	cocos2d::Vector<IGameMapNode*> _activeNodes;

	IGameMapGenerator* _generator;

public:
	GameMap( IGameMapGenerator* generator = nullptr )
		: _generator( generator ) {}

	static GameMap* create();

	bool init() override;

	void setSpeed( int speed ) override;

	void scroll() override;

	IGameMapNode* getCurrentNode() const override;

	IGameMapNode* nextNode() override;

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
