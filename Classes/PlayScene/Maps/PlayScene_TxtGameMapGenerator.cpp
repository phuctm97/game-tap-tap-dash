#include "PlayScene_TxtGameMapGenerator.h"
#include <fstream>
#include "PlayScene_ForwardGameMapNode.h"
#include "PlayScene_TurnLeftGameMapNode.h"
#include "PlayScene_TurnRightGameMapNode.h"
#include "PlayScene_FlyGameMapNode.h"
#include "PlayScene_FlyGameMapNode2.h"
#include "PlayScene_ForwardGameMapNodeWithRest.h"
using namespace cocos2d;

namespace PlayScene
{
TxtGameMapGenerator* TxtGameMapGenerator::create( const std::string& fileToSave )
{
	auto p = new TxtGameMapGenerator();
	if ( p ) {
		p->load( fileToSave );
		p->autorelease();
		return p;
	}

	return nullptr;
}

GameMapNode* TxtGameMapGenerator::nextNode()
{
	if ( _codeIt == _codes.cend() )
		return nullptr;

	auto codeIt = _codeIt;
	++_codeIt;

	switch ( *codeIt ) {
	case NODE_FORWARD: return ForwardGameMapNode::create();
	case NODE_TURN_LEFT: return TurnLeftGameMapNode::create();
	case NODE_TURN_RIGHT: return TurnRightGameMapNode::create();
	case NODE_FLY: return FlyGameMapNode::create();
	case NODE_FLY2: return FlyGameMapNode2::create();
	case NODE_FORWARD_WITH_REST: return ForwardGameMapNodeWithRest::create( 10, 0 );
	}

	return nullptr;
}

void TxtGameMapGenerator::reset()
{
	_codeIt = _codes.cbegin();
}

void TxtGameMapGenerator::load( const std::string& fileName )
{
	_codes.clear();

	std::string path = FileUtils::getInstance()->fullPathForFilename( fileName );

	ssize_t size = 0;
	char* pBuffer = reinterpret_cast<char*>(FileUtils::getInstance()->getFileData( path.c_str(), "rt", &size ));

	std::stringstream stream( pBuffer );
	while ( !stream.eof() ) {
		std::string code;
		stream >> code;

		if ( code == "n" ) _codes.push_back( NODE_FORWARD );
		else if ( code == "n2" ) _codes.push_back( NODE_FORWARD2 );
		else if ( code == "l" ) _codes.push_back( NODE_TURN_LEFT );
		else if ( code == "l2" ) _codes.push_back( NODE_TURN_LEFT2 );
		else if ( code == "r" ) _codes.push_back( NODE_TURN_RIGHT );
		else if ( code == "r2" ) _codes.push_back( NODE_TURN_RIGHT2 );
		else if ( code == "f" ) _codes.push_back( NODE_FLY );
		else if ( code == "f2" ) _codes.push_back( NODE_FLY2 );
		else if ( code == "nr" ) _codes.push_back( NODE_FORWARD_WITH_REST );
		else _codes.push_back( NODE_FORWARD );
	}

	if ( pBuffer ) {
		free( pBuffer );
	}

	reset();
}

void TxtGameMapGenerator::save( const std::string& fileName, const std::vector<int>& codes )
{
	std::fstream fstream;
	fstream.open( fileName, std::ios::out );

	for ( int code : codes ) {
		switch ( code ) {
		case NODE_FORWARD: fstream << "n";
			break;
		case NODE_FORWARD2: fstream << "n2";
			break;
		case NODE_TURN_LEFT: fstream << "l";
			break;
		case NODE_TURN_LEFT2: fstream << "l2";
			break;
		case NODE_TURN_RIGHT: fstream << "r";
			break;
		case NODE_TURN_RIGHT2: fstream << "r2";
			break;
		case NODE_FLY: fstream << "f";
			break;
		case NODE_FLY2: fstream << "f2";
			break;
		case NODE_FORWARD_WITH_REST: fstream << "nr";
			break;
		}
		fstream << std::endl;
	}

	fstream.close();
}
}
