#include "GameMenuScene.h"
#include"ui/CocosGUI.h"

using namespace ui;



Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

bool GameMenu::init()
{
	if (!Layer::init()) {
		return false;
	}

	// ��ȡ���ڴ�С
	Size winsize = Director::getInstance()->getVisibleSize();
	// ��ȡGL��Դ��
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���������ӵ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RESOURCESPLIST);

	// ��ӹرհ�ť
	auto CloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameMenu::MenuCloseCallback, this));


	    // ���ðڷ�λ��
	CloseItem->setPosition(Vec2(origin.x + winsize.width - CloseItem->getContentSize().width / 2, origin.y + CloseItem->getContentSize().height / 2));

	// �����˵�
	auto menu = Menu::create(CloseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// ������ʼ��ť
	auto StartButton = Button::create("");
	StartButton->setPosition(Vec2(winsize.width * 30 / 100.0, winsize.height * 25 / 100.0));

	    // ��Ӵ�������
	StartButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {

		});

	this->addChild(StartButton, 1);

	// ����ѡ��ؿ���ť
	auto SelectButton = Button::create("");
	SelectButton->setPosition(Vec2(winsize.width * 70 / 100.0, winsize.height * 25 / 100.0));

		// ��Ӵ�������
	SelectButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {

		});

	this->addChild(SelectButton, 1);


	//
	auto BgSprite = Sprite::create("");
	BgSprite->setPosition(Vec2(winsize.width / 2, winsize.height / 2));

	this->addChild(BgSprite);

	return true;



}

void GameMenu::MenuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
