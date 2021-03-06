#ifndef __PLAY_SCENE_GAME_MAP_NODE_H__
#define __PLAY_SCENE_GAME_MAP_NODE_H__

#include <cocos2d.h>

namespace PlayScene
{
	class GameMapNode : public cocos2d::Node
	{
	private:
		int _direction;

	protected:

		bool _isRestNode;

		int _restCode;

		float _restEnergy;

	public:
		enum
		{
			POSITION_INSIDE,
			POSITION_OUTSIDE,

			NODE_FORWARD,
			NODE_TURN_LEFT,
			NODE_TURN_RIGHT,
			NODE_FLY,

			DIRECTION_UP,
			DIRECTION_DOWN,
			DIRECTION_LEFT,
			DIRECTION_RIGHT
		};

		GameMapNode(bool isRestNode = false, int restCode = -1, float restEnergy = 0)
			: _direction(DIRECTION_UP), _isRestNode(isRestNode), _restCode(restCode), _restEnergy(restEnergy) {}

		virtual int checkPositionInside(const cocos2d::Vec2& worldPosition) = 0;

		virtual int getType() const = 0;

		int getDirection() const;

		bool isRestNode() const;

		virtual void decreaseRestCode() = 0;

		int getRestCode() const;

		float getRestEnergy() const;

		void setDirection(int direction);

		virtual void highLightNavi() = 0;

		virtual void unHighLightNavi() = 0;
	};
}

cocos2d::Point rotatePoint(const cocos2d::Point target, float degree, cocos2d::Point center);

#endif //!__PLAY_SCENE_GAME_MAP_NODE_H__
