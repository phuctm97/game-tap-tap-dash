#include "IntroScene_MainLayer.h"
using namespace cocos2d;

namespace IntroScene
{
MainLayer* MainLayer::create()
{
	MainLayer* p = new MainLayer();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE( p );
	return nullptr;
}

bool MainLayer::init()
{
	if( !Layer::init() ) return false;

	return true;
}

void MainLayer::reset()
{
	
}
}
