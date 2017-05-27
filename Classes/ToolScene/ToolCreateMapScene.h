#ifndef __TOOL_CREATE_MAP_SCENE_H__
#define __TOOL_CREATE_MAP_SCENE_H__

#include <cocos2d.h>
#include "PlayScene/Maps/PlayScene_GameMapNode.h"

namespace ToolScene
{
class ToolCreateMapScene : public cocos2d::LayerColor
{
private:
	enum
	{
		NODE_TURN_LEFT = 0,
		NODE_TURN_LEFT2 = 1,
		NODE_FORWARD = 2,
		NODE_FORWARD2 = 3,
		NODE_FORWARD_WITH_REST = 4,
		NODE_FLY = 5,
		NODE_FLY2 = 6,
		NODE_TURN_RIGHT = 7,
		NODE_TURN_RIGHT2 = 8
	};

	int _currentNodeCode;
	PlayScene::GameMapNode* _previousNode;

	std::vector<int> _recoredCodes;
	std::string _fileToSave;

public:
	static ToolCreateMapScene* create( const std::string& fileToSave );

	static cocos2d::Scene* createScene( const std::string& fileToSave );

	ToolCreateMapScene( const std::string& fileToSave )
		: _currentNodeCode( NODE_FORWARD ),
		  _previousNode( nullptr ),
		  _fileToSave( fileToSave ) {}

	~ToolCreateMapScene();

	bool init() override;

	void onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e ) override;

	void onExit() override;

	void save();

	static PlayScene::GameMapNode* createNode( int code );

	void updateCurrentNode();

	void acceptCurrentNode();
};
}

#endif //!__TOOL_CREATE_MAP_SCENE_H__
