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

	int _currentNodeIndex;

	int _nextControlNodeIndex;

	GameMapGenerator* _generator;

	bool _scrolling;

	float _scrollSpeed;

	int _scrollDirection;

	bool _pushedTail;

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

	GameMap( GameMapGenerator* generator )
		: _generator( generator ),
		  _scrolling( false ),
		  _scrollDirection( SCROLL_UP ),
		  _scrollSpeed( 0 ),
		  _pushedTail( false ),
		  _currentNodeIndex( 0 ), _nextControlNodeIndex( -1 ) {}

	~GameMap();

	static GameMap* create( GameMapGenerator* generator );

	bool init() override;

	void update( float dt ) override;

	void setScrollSpeed( float speed );

	void setScrollDirection( int direction );

	void scroll();

	void stop();

	GameMapNode* getCurrentNode() const;

	GameMapNode* getBusStopNode() const;

	GameMapNode* nextNode();

	int nextControl();

	int getCurrentNodeIndex() const;

	GameMapNode* getNode( int index ) const;

	bool isEnd() const;

	bool isPushedTail() const;

	void reset( const cocos2d::Vec2& position );

private:
	bool initGraphics();

	bool initContent();

	bool initEvents();

	void generateInitialNodes( const cocos2d::Vec2& initialPosition );

	void pushNewNode();

	void pushTail();

	int findNextControlNode() const;

	cocos2d::Vec2 calculateScrollVector() const;

	bool checkNodeOutOfView( GameMapNode* node ) const;

	void doScroll();

};
}

#endif //!__PLAY_SCENE_GAME_MAP_H__
