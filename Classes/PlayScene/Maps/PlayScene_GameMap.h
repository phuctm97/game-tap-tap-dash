#ifndef __PLAY_SCENE_GAME_MAP_H__
#define __PLAY_SCENE_GAME_MAP_H__
#include "PlayScene_IGameMap.h"

namespace PlayScene
{
class GameMap : public IGameMap
{
public:
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
};
}

#endif //!__PLAY_SCENE_GAME_MAP_H__
