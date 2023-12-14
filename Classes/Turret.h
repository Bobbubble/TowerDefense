#pragma once

#include"cocos2d.h"
#include"SpriteBase.h"
#include"Bullet.h"

USING_NS_CC;


// ��̨��
class Turret :public SpriteBase {
private:
	std::string _bulletName;   // ��Ӧ���ӵ���
	bool _select = false;      // �����Ƿ񱻰���
	Bullet* _bullet;           //  �����������ڵ�����

public:
	static Turret* create(const std::string& filename) {
		Turret* sprite = new Turret();
		if (sprite && sprite->initWithFile(filename)) {
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	static Turret* createWithSpriteFrameName(const std::string& filename) {
		Turret* sprite = new Turret();
		if (sprite && sprite->initWithFile(filename)) {
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	// set get

	void setBulletName(std::string bulletName) {
		_bulletName = bulletName;
	}
	std::string getBulletName() {
		return _bulletName;
	}

	void setSelect(bool select) {
		_select = select;
	}
	bool getSelect() {
		return _select;
	}

	void setBullet(Bullet* bullet) {
		_bullet = bullet;
	}
	Bullet* getBullet() {
		return _bullet;
	}
};