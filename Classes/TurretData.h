#pragma once

#include"cocos2d.h"

USING_NS_CC;


// TurretData ���ڴ洢��̨��Ϣ
class TurretData :public Ref
{
private:
	std::string _name;       // ��̨����
	int _gold;               // ����������
	std::string _bulletName;  // ��̨�����ӵ���

public:

	// ����TurretData
	static TurretData* create()
	{
		TurretData* sprite = new TurretData();
		if (sprite) 
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	// ˽�г�Ա����������set����ȡget
	void setName(std::string name) {
		_name = name;
	}
	std::string getName() {
		return _name;
	}

	void setGold(int gold) {
		_gold = gold;
	}
	int getGold() {
		return _gold;
	}

	void setBulletName(std::string bulletName) {
		_bulletName = bulletName;
	}
	std::string getBulletName() {
		return _bulletName;
	}
};