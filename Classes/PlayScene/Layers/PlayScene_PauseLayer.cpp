#include "PlayScene_PauseLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;


namespace PlayScene
{
	PauseLayer * PlayScene::PauseLayer::create()
	{
		PauseLayer* p = new PauseLayer();
		if (p && p->init()) {
			p->autorelease();
			return p;
		}
		CC_SAFE_DELETE(p);
		return nullptr;
	}

	bool PlayScene::PauseLayer::init()
	{
		if (!Layer::init()) return false;

		if (!initGraphics()) return false;

		if (!initEvents()) return false;

		return true;
	}

	bool PlayScene::PauseLayer::initGraphics()
	{
		lbPause = Label::createWithSystemFont("Pause", "Arial", 200);
		lbPause->setContentSize(Size(Director::getInstance()->getVisibleSize().width / 4,
			Director::getInstance()->getVisibleSize().height / 8));
		lbPause->setTextColor(Color4B::WHITE);
		lbPause->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		lbPause->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2
			, Director::getInstance()->getVisibleSize().height*0.7));
		addChild(lbPause);

		btnResume = Button::create("res/btnResume.png", "res/btnResume2.png", "res/btnResume2.png");
		btnResume->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		btnResume->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2
			, Director::getInstance()->getVisibleSize().height/2));
		addChild(btnResume);

		btnToMenu = Button::create("res/btnToMenu.png", "res/btnToMenu2.png", "res/btnToMenu2.png");
		btnToMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		btnToMenu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2
			, Director::getInstance()->getVisibleSize().height*0.55));
		addChild(btnToMenu);

		return true;
	}

	bool PlayScene::PauseLayer::initEvents()
	{
		btnResume->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				//resume game
				//tat

				this->setVisible(false);
			}
		});

		btnToMenu->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{

				Director::getInstance()->replaceScene(MyDirector::getInstance()->getIntroScene());

			}
		});
		return true;
	}


}