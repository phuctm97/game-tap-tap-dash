#include "ToolCreateMapScene.h"
#include "PlayScene/Maps/PlayScene_ForwardGameMapNode.h"
#include "PlayScene/Maps/PlayScene_ForwardGameMapNode2.h"
#include "PlayScene/Maps/PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnLeftGameMapNode2.h"
#include "PlayScene/Maps/PlayScene_TurnRightGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnRightGameMapNode2.h"
#include "PlayScene/Maps/PlayScene_FlyGameMapNode.h"
#include "PlayScene/Maps/PlayScene_FlyGameMapNode2.h"
#include "PlayScene/Maps/PlayScene_ForwardGameMapNodeWithRest.h"
#include "PlayScene/Maps/PlayScene_GameMapGenerator.h"
#include "PlayScene/Maps/PlayScene_TxtGameMapGenerator.h"
using namespace cocos2d;

namespace ToolScene
{
ToolCreateMapScene* ToolCreateMapScene::create( const std::string& fileToSave )
{
	auto p = new ToolCreateMapScene( fileToSave );
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE( p );
	return nullptr;
}

cocos2d::Scene* ToolCreateMapScene::createScene( const std::string& fileToSave )
{
	auto scene = Scene::create();
	auto layer = ToolCreateMapScene::create( fileToSave );
	scene->addChild( layer );
	return scene;
}

ToolCreateMapScene::~ToolCreateMapScene() {}

bool ToolCreateMapScene::init()
{
	if ( !LayerColor::initWithColor( Color4B::WHITE ) ) return false;

	// initial node
	_previousNode = createNode( NODE_FORWARD );
	_previousNode->setPosition( Director::getInstance()->getVisibleSize().width / 2,
	                            Director::getInstance()->getVisibleSize().height / 2 );
	addChild( _previousNode, 0 );
	_recoredCodes.push_back( NODE_FORWARD );

	// display new node
	_currentNodeCode = NODE_FORWARD;
	updateCurrentNode();

	// event
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2( ToolCreateMapScene::onKeyPressed, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerKeyboard, this );

	return true;
}

void ToolCreateMapScene::onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e )
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == EventKeyboard::KeyCode::KEY_BACK )
		Director::getInstance()->end();

	switch ( keyCode ) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
		if ( _currentNodeCode > 0 ) {
			_currentNodeCode--;
			updateCurrentNode();
		}
	}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
		if ( _currentNodeCode < 8 ) {
			_currentNodeCode++;
			updateCurrentNode();
		}
	}
		break;
	case EventKeyboard::KeyCode::KEY_ENTER: {
		acceptCurrentNode();
	}
		break;
	default: break;
	}
}

void ToolCreateMapScene::onExit()
{
	Layer::onExit();

	save();
}

void ToolCreateMapScene::save()
{
	std::vector<int> saveCodes;

	for ( int code: _recoredCodes ) {
		int saveCode = PlayScene::TxtGameMapGenerator::NODE_FORWARD;

		switch ( code ) {
		case NODE_FORWARD: saveCode = PlayScene::TxtGameMapGenerator::NODE_FORWARD;
			break;
		case NODE_FORWARD2: saveCode = PlayScene::TxtGameMapGenerator::NODE_FORWARD2;
			break;
		case NODE_TURN_LEFT: saveCode = PlayScene::TxtGameMapGenerator::NODE_TURN_LEFT;
			break;
		case NODE_TURN_LEFT2: saveCode = PlayScene::TxtGameMapGenerator::NODE_TURN_LEFT2;
			break;
		case NODE_TURN_RIGHT: saveCode = PlayScene::TxtGameMapGenerator::NODE_TURN_RIGHT;
			break;
		case NODE_TURN_RIGHT2: saveCode = PlayScene::TxtGameMapGenerator::NODE_TURN_RIGHT2;
			break;
		case NODE_FLY: saveCode = PlayScene::TxtGameMapGenerator::NODE_FLY;
			break;
		case NODE_FLY2: saveCode = PlayScene::TxtGameMapGenerator::NODE_FLY2;
			break;
		case NODE_FORWARD_WITH_REST: saveCode = PlayScene::TxtGameMapGenerator::NODE_FORWARD_WITH_REST;
			break;
		}

		saveCodes.push_back( saveCode );
	}

	PlayScene::TxtGameMapGenerator::save( _fileToSave, saveCodes );
}

PlayScene::GameMapNode* ToolCreateMapScene::createNode( int code )
{
	switch ( code ) {
	case NODE_FORWARD: return PlayScene::ForwardGameMapNode::create();
	case NODE_FORWARD2: return PlayScene::ForwardGameMapNode2::create();
	case NODE_FORWARD_WITH_REST: return PlayScene::ForwardGameMapNodeWithRest::create( 10, 0.2f );
	case NODE_TURN_LEFT: return PlayScene::TurnLeftGameMapNode::create();
	case NODE_TURN_LEFT2: return PlayScene::TurnLeftGameMapNode2::create();
	case NODE_TURN_RIGHT: return PlayScene::TurnRightGameMapNode::create();
	case NODE_TURN_RIGHT2: return PlayScene::TurnRightGameMapNode2::create();
	case NODE_FLY: return PlayScene::FlyGameMapNode::create();
	case NODE_FLY2: return PlayScene::FlyGameMapNode2::create();
	}

	return nullptr;
}

void ToolCreateMapScene::updateCurrentNode()
{
	removeChildByTag( 1 );

	auto node = createNode( _currentNodeCode );
	addChild( node, 0, 1 );

	PlayScene::GameMapGenerator::placeNode( _previousNode, node );
}

void ToolCreateMapScene::acceptCurrentNode()
{
	// remove display node
	removeChildByTag( 1 );

	// push node into scene and record array
	auto node = createNode( _currentNodeCode );
	addChild( node, 0 );
	_recoredCodes.push_back( _currentNodeCode );

	// place node
	PlayScene::GameMapGenerator::placeNode( _previousNode, node );

	// move layer
	runAction( MoveBy::create( 0.25f, -node->getPosition() + _previousNode->getPosition() ) );

	// update previous node
	_previousNode = node;

	// display new node
	_currentNodeCode = NODE_FORWARD;
	updateCurrentNode();
}
}
