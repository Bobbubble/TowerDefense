#pragma once

#include"cocos2d.h"
#include"LevelData.h"


USING_NS_CC;
// �ؿ�������
class LevelManager:public Layer
{
protected:
	int _SelectLevelIndex;


public:
	static Scene* createScene();
	virtual bool init();
	// ѡ�����Ļص�
	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(LevelManager);

};

