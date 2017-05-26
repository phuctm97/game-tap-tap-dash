#ifndef __PLAY_SCENE_GAME_MAP_H__
#define __PLAY_SCENE_GAME_MAP_H__

#include "PlayScene_GameMapGenerator.h"
#include <vector>

namespace PlayScene
{
class GameMap : public cocos2d::Node
{
private:
	std::vector<GameMapNode*> _activeNodes;

	std::vector<GameMapNode*>::const_iterator _currentNodeIt;

	int _nextControl;

	IGameMapGenerator* _generator;

	bool _scrolling;
	
	float _scrollSpeed;

	int _scrollDirection;

public:
	enum
	{
		NONE,
		TURN_LEFT,
		TURN_RIGHT,
		FLY,

		SCROLL_UP,
		SCROLL_DOWN,
		SCROLL_LEFT,
		SCROLL_RIGHT
	};

	GameMap( IGameMapGenerator* generator )
		: _generator( generator ),
		  _scrolling( false ), _scrollDirection( SCROLL_UP ), _scrollSpeed( 0 ),
		  _nextControl( NONE ) {}

	~GameMap();

	static GameMap* create( IGameMapGenerator* generator );

	bool init() override;

	void update( float dt ) override;

	void setScrollSpeed( float speed );

	void setScrollDirection( int direction );

	void scroll();

	GameMapNode* getCurrentNode() const;

	GameMapNode* nextNode();

	int getNextControl() const;

	bool isEnd() const;

	void reset( const cocos2d::Vec2& position );

	void stop();

private:
	bool initContent();

	bool initEvents();

	void generateInitialNodes();

	cocos2d::Vec2 calculateScrollVector() const;

	void doScroll();
};
}

#endif //!__PLAY_SCENE_GAME_MAP_H__
