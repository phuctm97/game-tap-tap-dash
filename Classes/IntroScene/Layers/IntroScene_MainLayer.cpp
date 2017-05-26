#include "IntroScene_MainLayer.h"
using namespace cocos2d;
using namespace cocos2d::ui;
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
	
	if (!initGraphics()) return false;

	if (!initEvents()) return false;

	return true;
}

bool MainLayer::initGraphics()
{

	background = Sprite::create("res/background.jpg");
	background->setContentSize(Director::getInstance()->getVisibleSize());
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(Vec2::ZERO);
	addChild(background);

	logo = Sprite::create("res/Logo.png");
	logo->setContentSize(Size(Director::getInstance()->getVisibleSize().width
		, Director::getInstance()->getVisibleSize().height*0.3));
	logo->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	logo->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height*0.7));
	background->addChild(logo);

	btnStart = Button::create("res/btnPlay.png", "res/btnPlay2.png");
	btnStart->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	btnStart->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height/2));
	background->addChild(btnStart);

	btnFb = Button::create("res/iconfacebook.png", "res/iconfacebook2.png");
	btnFb->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	btnFb->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.3,
		Director::getInstance()->getVisibleSize().height*0.1));
	background->addChild(btnFb);

	sound = CheckBox::create("res/soundOff.png", "res/soundOn.png", "res/soundOn.png", "res/soundOff.png", "res/soundOff.png");
	sound->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sound->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.7,
		Director::getInstance()->getVisibleSize().height*0.1));
	background->addChild(sound);


	
	return true;
}

bool MainLayer::initEvents()
{
	btnStart->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(MyDirector::getInstance()->getLevelScene());
			
		}
	});
	btnFb->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			// do something
		}
	});
	sound->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			if (sound->getSelectedState() == true)
			{

			}
			else
			{
			}
			
		}
	});
	return true;
}

void MainLayer::reset()
{
	
}
}
