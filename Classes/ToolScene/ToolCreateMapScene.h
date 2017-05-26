#ifndef __TOOL_CREATE_MAP_SCENE_H__
#define __TOOL_CREATE_MAP_SCENE_H__

#include <cocos2d.h>
#include "PlayScene/Maps/PlayScene_GameMapNode.h"

namespace ToolScene
{
class ToolCreateMapScene : public cocos2d::Layer
{
private:
	enum
	{
		NODE_FORWARD = 0,
		NODE_TURN_LEFT = 1,
		NODE_TURN_RIGHT = 2,
		NODE_FLY = 3
	};

	int _currentNodeCode;
	PlayScene::GameMapNode* _previousNode;

	std::vector<int> _recoredCodes;

public:
	static ToolCreateMapScene* create( const std::string& fileToSave );

	static cocos2d::Scene* createScene( const std::string& fileToSave );

	ToolCreateMapScene()
		: _currentNodeCode( NODE_FORWARD ),
		  _previousNode( nullptr ) {}

	~ToolCreateMapScene();

	bool init( const std::string& fileToSave );

	void onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e ) override;

	void onExit() override;

	void save();

	static PlayScene::GameMapNode* createNode( int code );

	void updateCurrentNode();

	void acceptCurrentNode();
};
}

#endif //!__TOOL_CREATE_MAP_SCENE_H__
