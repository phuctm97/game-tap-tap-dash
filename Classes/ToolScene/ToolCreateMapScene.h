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
		NODE_FORWARD = 1,
		NODE_FORWARD_WITH_REST = 2,
		NODE_FLY = 3,
		NODE_FLY2 = 4,
		NODE_TURN_RIGHT = 5
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
