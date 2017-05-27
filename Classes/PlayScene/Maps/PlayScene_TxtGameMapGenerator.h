#ifndef __PLAY_SCENE_TXT_GAME_MAP_GENERATOR_H__
#define __PLAY_SCENE_TXT_GAME_MAP_GENERATOR_H__

#include "PlayScene_GameMapGenerator.h"

namespace PlayScene
{
class TxtGameMapGenerator : public GameMapGenerator
{
private:
	std::vector<int> _codes;

	std::vector<int>::const_iterator _codeIt;

public:
	static TxtGameMapGenerator* create( const std::string& fileToSave );

	enum
	{
		NODE_FORWARD,
		NODE_TURN_LEFT,
		NODE_TURN_RIGHT,
		NODE_FLY,
		NODE_FLY2,
		NODE_FORWARD_WITH_REST
	};

	GameMapNode* nextNode() override;

	void reset() override;

	void load( const std::string& fileName );

	static void save( const std::string& fileName, const std::vector<int>& codes );
};
}

#endif //!__PLAY_SCENE_TXT_GAME_MAP_GENERATOR_H__
