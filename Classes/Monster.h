#pragma once


#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"PointDelegate.h"
#include"GameScene.h"

USING_NS_CC;
using namespace ui;

// Monster��
class Monster : public Sprite {
private:
	int _lifeValue=10;        // ����ֵ
	LoadingBar* _HP;       // Ѫ��
	float _HPInterval;     //  Ѫ��������
	Vector<PointDelegate*> _pathPoints;   // ��¼��Ч·����
	int _gold=10;         // ��������õĽ��
	float _speed=10;        // �ƶ��ٶ�

public:
	// ʹ�þ���֡����
	static Monster* createWithSpriteFrameName(const std::string& filename) {
		Monster* sprite = new Monster();
		if (sprite && sprite->initWithSpriteFrameName(filename)) {
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;		
	}


	// set get 
	void setLifeValue(int lifeValue) {
		_lifeValue = lifeValue;
	}
	int getLifeValue() {
		return _lifeValue;
	}

	void setHP(LoadingBar* HP) {
		_HP = HP;
	}
	LoadingBar* getHP() {
		return _HP;
	}

	void setHPInterval(float HPInterval) {
		_HPInterval = HPInterval;
	}
	float getHPInterval() {
		return _HPInterval;
	}

	void setPointPath(Vector<PointDelegate*> &pathPoints) {
		_pathPoints = pathPoints;
	}
	// ����get����

	// monster�ƶ�
	void startMoving();


};
