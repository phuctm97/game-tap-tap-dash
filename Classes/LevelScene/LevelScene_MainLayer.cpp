#include "LevelScene_MainLayer.h"
#include "iostream"
using namespace cocos2d;
using namespace cocos2d::ui;
namespace LevelScene
{
	MainLayer* MainLayer::create()
	{
		MainLayer* p = new MainLayer();
		if (p && p->init()) {
			p->autorelease();
			return p;
		}
		CC_SAFE_DELETE(p);
		return nullptr;
	}

	bool MainLayer::init()
	{
		if (!Layer::init()) return false;

		if (!initGraphics()) return false;

		if (!initEvents()) return false;

		return true;
	}

	cocos2d::Vec2 MainLayer::CalculatePosition(int itemNum)
	{
		Size scrSize = Size(Director::getInstance()->getVisibleSize().width, 
							Director::getInstance()->getVisibleSize().height);
		float Xs = scrSize.width;
		float Ys = scrSize.height;
		int gRows = MENU_ITEMS_ROWS;
		int gCols = MENU_ITEMS_COLS;
		int gBins = gRows*gCols;
		float Xb = MENU_FRACTION.x*Xs / gCols;
		float Yb = MENU_FRACTION.y*Ys / gRows;
		float Xa = MENU_ANCHOR.x * Xs;
		float Ya = MENU_ANCHOR.y * Ys;
		int page = itemNum / gBins;

		int binCol = itemNum % gCols;
		int binRow = (itemNum - page*gBins) / gCols;

		float xPos = binCol * Xb + Xb / 2 + Xa - MENU_FRACTION.x*Xs / 2 + page * Xs;
		float yPos = Ya - binRow*Yb - Yb / 2 + MENU_FRACTION.y * Ys / 2;

		

		return Vec2(xPos,yPos);
	}

	void MainLayer::CreateLevelGrid()
	{
		for (int num = 0; num < MENU_ITEMS_TOTAL; num++)
		{
			btnLevel = Button::create("res/btnLevelNor.png", "btnLevelSelected.png");
			btnLevel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			btnLevel->setPosition(CalculatePosition(num));
			btnLevel->setTag(num + 1);
			background->addChild(btnLevel);
		}
	}

	

	bool MainLayer::initGraphics()
	{
		background = Sprite::create("res/background.jpg");
		background->setContentSize(Size(Director::getInstance()->getVisibleSize().width*MENU_PAGES
									, Director::getInstance()->getVisibleSize().height));
		background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		background->setPosition(Vec2::ZERO);
		addChild(background);

		panelStart = Sprite::create("res/blank.png");
		panelStart->setTextureRect(Rect(0, 0, Director::getInstance()->getVisibleSize().width,
			Director::getInstance()->getVisibleSize().height*0.1));
		panelStart->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		panelStart->setColor(Color3B::BLUE);
		panelStart->setPosition(Vec2::ZERO);
		addChild(panelStart, 1);

		btnStart = Button::create("res/btnPlay.png", "res/btnPlay2.png");
		btnStart->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		btnStart->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
			panelStart->getContentSize().height/2));
		panelStart->addChild(btnStart);

		btnNext = Button::create("res/btnNext.png", "res/btnNext2.png");
		btnNext->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		btnNext->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.8,
			panelStart->getContentSize().height / 2));
		panelStart->addChild(btnNext);

		btnPrev = Button::create("res/btnPre.png", "res/btnPre2.png");
		btnPrev->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		btnPrev->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.2,
			panelStart->getContentSize().height / 2));
		panelStart->addChild(btnPrev);
		btnPrev->setVisible(false);
		CreateLevelGrid();


		return true;
	}


	bool MainLayer::initEvents()
	{
		btnStart->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				Director::getInstance()->replaceScene(MyDirector::getInstance()->getPlayScene());
			}
		});

		btnLevel->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				
				}
		});

		btnNext->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				
				if (page < MENU_PAGES -1)
				{
					MoveBy* movebyRight = MoveBy::create(0.2f, Vec3(-Director::getInstance()->getVisibleSize().width, 0, 0));
					background->runAction(movebyRight);
					btnNext->setVisible(true);
					btnPrev->setVisible(true);
					page++;
				}
				if(page == MENU_PAGES - 1)
					btnNext->setVisible(false);
				
				
			}
		});

		btnPrev->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				if (page > 0)
				{
					MoveBy* movebyLeft = MoveBy::create(0.2f, Vec3(Director::getInstance()->getVisibleSize().width, 0, 0));
					background->runAction(movebyLeft);
					btnPrev->setVisible(true);
					btnNext->setVisible(true);
					page--;
					if(page == 0)
						btnPrev->setVisible(false);
				}

				
			}
		});

		return true;
	}
}