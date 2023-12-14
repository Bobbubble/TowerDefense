#include "LevelManager.h"
#include"ui/CocosGUI.h"

using namespace ui;


Scene* LevelManager::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelManager::create();
    scene->addChild(layer);

    return scene;
}

bool LevelManager::init()
{
	if (!Layer::init()) {
		return false;
	}

	// ��ȡ���ڴ�С
	Size winsize = Director::getInstance()->getVisibleSize();
	// ��ȡGL��Դ��
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// ��ӹرհ�ť
	auto CloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(LevelManager::menuCloseCallback, this));


	    // ���ðڷ�λ��
	CloseItem->setPosition(Vec2(origin.x + winsize.width - CloseItem->getContentSize().width / 2, origin.y + CloseItem->getContentSize().height / 2));
    
	// �����˵�
	auto menu = Menu::create(CloseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);	

	//Ĭ��ѡ���һ��,�����±��0��ʼ
	_SelectLevelIndex = 0;

	// ������ҳ����
	auto PageView = PageView::create();

	PageView->setContentSize(Size(480.0f, 320.0f));
	PageView->setPosition(Vec2((winsize.width - PageView->getContentSize().width) / 2.0f, (winsize.height - PageView->getContentSize().height) * 0.6));

	// ѭ�����3��layout�ؿ�ͼƬ
	for (int i = 0; i < 3; i++) {
		Layout* layout = Layout::create();
		layout->cocos2d::Node::setContentSize(Size(480.0f, 320.0f));
		// ����imageview
		ImageView* imageView = ImageView::create("");
		imageView->setContentSize(Size(480.0f, 320.0f));
		imageView->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
		layout->addChild(imageView);
		// ��i��ʾ��λ�����layout
		PageView->insertPage(layout, i);
	}
	// ����¼������� =========================
	PageView->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {

		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}


		});




	return false;
}

void LevelManager::menuCloseCallback(Ref* pSender)
{
}
