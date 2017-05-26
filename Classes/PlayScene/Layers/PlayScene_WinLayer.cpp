#include "PlayScene/Layers/PlayScene_WinLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace PlayScene
{
	WinLayer * PlayScene::WinLayer::create()
	{
		WinLayer* p = new WinLayer();
		if (p && p->init()) {
			p->autorelease();
			return p;
		}
		CC_SAFE_DELETE(p);
		return nullptr;
	}


	bool PlayScene::WinLayer::init()
	{
		if (!Layer::init()) return false;

		if (!initGraphics()) return false;

		if (!initEvents()) return false;

		return true;
	}

	bool PlayScene::WinLayer::initGraphics()
	{
		btnContinue = Button::create("res/btnContinue.png", "res/btnContinue2.png", "res/btnContinue2.png");
		btnContinue->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		btnContinue->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2
			, Director::getInstance()->getVisibleSize().height / 2));
		addChild(btnContinue);

		btnToMenu = Button::create("res/btnToMenu.png", "res/btnToMenu2.png", "res/btnToMenu2.png");
		btnToMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		btnToMenu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2
			, Director::getInstance()->getVisibleSize().height*0.55));
		addChild(btnToMenu);

		return true;
	}

	bool PlayScene::WinLayer::initEvents()
	{
		btnContinue->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				//next level
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