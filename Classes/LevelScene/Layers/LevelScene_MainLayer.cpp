#include "LevelScene_MainLayer.h"
#include "Common/MyDirector.h"
using namespace cocos2d;
using namespace cocos2d::ui;

#define MENU_ITEMS_COLS 3
#define MENU_ITEMS_ROWS 4
#define MENU_ITEMS_PAGE (MENU_ITEMS_COLS*MENU_ITEMS_ROWS)
#define MENU_ITEMS_TOTAL 30

#define MENU_PAGES ((MENU_ITEMS_TOTAL/MENU_ITEMS_PAGE)+1)
#define MENU_FRACTION (Vec2(0.8f,0.8f))
#define MENU_ANCHOR (Vec2(0.5f,0.5f))

namespace LevelScene
{
MainLayer* MainLayer::create()
{
	MainLayer* p = new MainLayer();
	if ( p && p->init() ) {
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool MainLayer::init()
{
	if ( !Layer::init() ) return false;

	if ( !initGraphics() ) return false;

	if ( !initEvents() ) return false;

	return true;
}

void MainLayer::reset() { }

cocos2d::Vec2 MainLayer::calculatePosition( int itemNum )
{
	Size scrSize = Size( Director::getInstance()->getVisibleSize().width,
	                     Director::getInstance()->getVisibleSize().height );
	float Xs = scrSize.width;
	float Ys = scrSize.height;
	int gRows = MENU_ITEMS_ROWS;
	int gCols = MENU_ITEMS_COLS;
	int gBins = gRows * gCols;
	float Xb = MENU_FRACTION.x * Xs / gCols;
	float Yb = MENU_FRACTION.y * Ys / gRows;
	float Xa = MENU_ANCHOR.x * Xs;
	float Ya = MENU_ANCHOR.y * Ys;
	int page = itemNum / gBins;

	int binCol = itemNum % gCols;
	int binRow = (itemNum - page * gBins) / gCols;

	float xPos = binCol * Xb + Xb / 2 + Xa - MENU_FRACTION.x * Xs / 2 + page * Xs;
	float yPos = Ya - binRow * Yb - Yb / 2 + MENU_FRACTION.y * Ys / 2;

	return Vec2( xPos, yPos );
}

void MainLayer::createLevelGrid()
{
	for ( int num = 0; num < MENU_ITEMS_TOTAL; num++ ) {
		_btnLevel = Button::create( "res/btnLevelNor.png", "btnLevelSelected.png" );
		_btnLevel->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
		_btnLevel->setPosition( calculatePosition( num ) );
		_btnLevel->setTag( num + 1 );
		_background->addChild( _btnLevel );
	}
}

bool MainLayer::initGraphics()
{
	_background = Sprite::create( "res/background.jpg" );
	_background->setContentSize( Size( Director::getInstance()->getVisibleSize().width * MENU_PAGES
	                                   , Director::getInstance()->getVisibleSize().height ) );
	_background->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_background->setPosition( Vec2::ZERO );
	addChild( _background );

	_panelStart = Sprite::create( "res/blank.png" );
	_panelStart->setTextureRect( Rect( 0, 0, Director::getInstance()->getVisibleSize().width,
	                                   Director::getInstance()->getVisibleSize().height * 0.1f ) );
	_panelStart->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_panelStart->setColor( Color3B::BLUE );
	_panelStart->setPosition( Vec2::ZERO );
	addChild( _panelStart, 1 );

	_btnStart = Button::create( "res/btnPlay.png", "res/btnPlay2.png" );
	_btnStart->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnStart->setPosition( Vec2( Director::getInstance()->getVisibleSize().width / 2,
	                              _panelStart->getContentSize().height / 2 ) );
	_panelStart->addChild( _btnStart );

	_btnNext = Button::create( "res/btnNext.png", "res/btnNext2.png" );
	_btnNext->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnNext->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.8f,
	                             _panelStart->getContentSize().height / 2 ) );
	_panelStart->addChild( _btnNext );

	_btnPrev = Button::create( "res/btnPre.png", "res/btnPre2.png" );
	_btnPrev->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	_btnPrev->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.2f,
	                             _panelStart->getContentSize().height / 2 ) );
	_panelStart->addChild( _btnPrev );
	_btnPrev->setVisible( false );
	createLevelGrid();

	return true;
}

bool MainLayer::initEvents()
{
	_btnStart->addTouchEventListener( CC_CALLBACK_2(MainLayer::onBtnStartClicked, this) );

	_btnLevel->addTouchEventListener( CC_CALLBACK_2( MainLayer::onBtnLevelClicked, this ) );

	_btnNext->addTouchEventListener( CC_CALLBACK_2( MainLayer::onBtnNextClicked, this ) );

	_btnPrev->addTouchEventListener( CC_CALLBACK_2(MainLayer::onBtnPrevClicked, this ) );

	return true;
}

void MainLayer::onBtnStartClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		Director::getInstance()->replaceScene( MyDirector::getInstance()->getPlayScene() );
	}
}

void MainLayer::onBtnLevelClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {}
}

void MainLayer::onBtnNextClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {

		if ( _page < MENU_PAGES - 1 ) {
			MoveBy* movebyRight = MoveBy::create( 0.2f, Vec3( -Director::getInstance()->getVisibleSize().width, 0, 0 ) );
			_background->runAction( movebyRight );
			_btnNext->setVisible( true );
			_btnPrev->setVisible( true );
			_page++;
		}
		if ( _page == MENU_PAGES - 1 )
			_btnNext->setVisible( false );

	}
}

void MainLayer::onBtnPrevClicked( cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type )
{
	if ( type == Widget::TouchEventType::ENDED ) {
		if ( _page > 0 ) {
			MoveBy* movebyLeft = MoveBy::create( 0.2f, Vec3( Director::getInstance()->getVisibleSize().width, 0, 0 ) );
			_background->runAction( movebyLeft );
			_btnPrev->setVisible( true );
			_btnNext->setVisible( true );
			_page--;
			if ( _page == 0 )
				_btnPrev->setVisible( false );
		}

	}
}
}
