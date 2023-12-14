#pragma once


#include"cocos2d.h"
#include"SpriteBase.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

// Monster��
class Monster : public SpriteBase {
private:
	int _lifeValue;        // ����ֵ
	LoadingBar* _HP;       // Ѫ��
	float _HPInterval;     //  Ѫ��������

public:
	static Monster* create(const std::string& filename) {
		Monster* sprite = new Monster();
		if (sprite && sprite->initWithFile(filename)) {
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	static Monster* createWithSpriteFrameName(const std::string& filename) {
		Monster* sprite = new Monster();
		if (sprite && sprite->initWithFile(filename)) {
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

};
