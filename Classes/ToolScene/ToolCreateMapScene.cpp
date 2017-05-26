#include "ToolCreateMapScene.h"
#include "PlayScene/Maps/PlayScene_ForwardGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene/Maps/PlayScene_TurnRightGameMapNode.h"
#include "PlayScene/Maps/PlayScene_FlyGameMapNode.h"
#include "PlayScene/Maps/PlayScene_GameMapGenerator.h"
#include <iterator>
using namespace cocos2d;

namespace ToolScene
{
ToolCreateMapScene* ToolCreateMapScene::create( const std::string& fileToSave )
{
	auto p = new ToolCreateMapScene();
	if ( p && p->init( fileToSave ) ) {
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

bool ToolCreateMapScene::init( const std::string& fileToSave )
{
	if ( !Layer::init() ) return false;

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
		if ( _currentNodeCode < 3 ) {
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

void ToolCreateMapScene::save() {}

PlayScene::GameMapNode* ToolCreateMapScene::createNode( int code )
{
	switch ( code ) {
	case NODE_FORWARD: return PlayScene::ForwardGameMapNode::create();
	case NODE_TURN_LEFT: return PlayScene::TurnLeftGameMapNode::create();
	case NODE_TURN_RIGHT: return PlayScene::TurnRightGameMapNode::create();
	case NODE_FLY: return PlayScene::FlyGameMapNode::create();
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
