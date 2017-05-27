#include "AppDelegate.h"
#include "TestScene/TestPlayerScene.h"
#include "TestScene/TestMapScene.h"
#include "TestScene/TestMapNodeScene.h"
#include "ToolScene/ToolCreateMapScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size( 1080, 1920 );
static cocos2d::Size smallResolutionSize = cocos2d::Size( 540, 960 );
static cocos2d::Size mediumResolutionSize = cocos2d::Size( 720, 1280 );
static cocos2d::Size largeResolutionSize = cocos2d::Size( 1080, 1920 );

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs( glContextAttrs );
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if ( !glview ) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect( "Tap Tap Dash", cocos2d::Rect( 0, 0, mediumResolutionSize.width, mediumResolutionSize.height ) );
#else
		glview = GLViewImpl::create( "Tap Tap Dash" );
#endif
		director->setOpenGLView( glview );
	}

	// Set the design resolution
	glview->setDesignResolutionSize( designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT );

	register_all_packages();

	// run
	director->runWithScene( TestScene::TestPlayerScene::createScene() );

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
