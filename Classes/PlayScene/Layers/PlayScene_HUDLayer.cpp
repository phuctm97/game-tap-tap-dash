#include "PlayScene_HUDLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace PlayScene
{

	HudLayer* PlayScene::HudLayer::create()
	{
		HudLayer* p = new HudLayer();
		if (p && p->init()) {
			p->autorelease();
			return p;
		}
		CC_SAFE_DELETE(p);
		return nullptr;
	}

	void PlayScene::HudLayer::setScore(int score)
	{
		_score = score;
		lbScore->setString("Score :  " + std::to_string(score));
	}

	bool PlayScene::HudLayer::init()
	{
		if (!Layer::init()) return false;

		if (!initGraphics()) return false;

		if (!initEvents()) return false;

		return true;
	}

	bool PlayScene::HudLayer::initGraphics()
	{
		panelScore = Sprite::create("res/blank.png");
		panelScore->setTextureRect(Rect(0, 0, Director::getInstance()->getVisibleSize().width,
			Director::getInstance()->getVisibleSize().height*0.05));
		panelScore->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		panelScore->setColor(Color3B::MAGENTA);
		panelScore->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));
		addChild(panelScore);

		lbScore = Label::create();
		lbScore->setString("Score : " + std::to_string(_score));
		lbScore->setContentSize(Size(panelScore->getContentSize().width*0.3,panelScore->getContentSize().height*0.9));
		lbScore->setSystemFontSize(30.0f);
		lbScore->setSystemFontName("Arial");
		lbScore->setTextColor(Color4B::BLUE);
		lbScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		lbScore->setPosition(Vec2(panelScore->getContentSize().width*0.1, panelScore->getContentSize().height*0.5));
		panelScore->addChild(lbScore);

		btnPause = Button::create("res/btnPause.png", "res/btnPause2.png");
		btnPause->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		btnPause->setPosition(Vec2(panelScore->getContentSize().width*0.9,
			panelScore->getContentSize().height/2));
		panelScore->addChild(btnPause);

		pauselayer = PauseLayer::create();
		pauselayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		pauselayer->setPosition(Vec2::ZERO);
		addChild(pauselayer);
		pauselayer->setVisible(false);



		return true;
	}

	bool PlayScene::HudLayer::initEvents()
	{
		btnPause->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				pauselayer->setVisible(true);
			}
		});

		return true;
	}
}
