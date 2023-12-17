#pragma once

#include"cocos2d.h"
#include"PointDelegate.h"
#include"TurretData.h"
#include"MonsterData.h"
#include"json/document.h"
#include"Monster.h"
#include"Turret.h"
#include"Bullet.h"


USING_NS_CC;

// ��Ϸ�߼�
class GameScene :public Layer
{
protected:
	Size screenSize;           // ��ȡ��Ļsize 
	TMXTiledMap* _tileMap;   // ��ͼ
	TMXLayer* _collidable;   // �ϰ���
	std::string _tileFile;   // �ؿ���ͼ����
	int _number;             // �ؿ����ﲨ��
	int _currentCount;       // ��ǰ��������
	int _currNum;            // ��ǰ���ﲨ��
	int _goldValue;          // ��ҵ�ǰ�������
	Sprite* _carrot;          // �ܲ�
	int carrotHealth = 5;     // ֱ������Ӱɣ��ܲ�������ֵ
	float _screenWidth, _screenHeight;  //��Ļ���

	Vector<MonsterData*> _monsterDatas;   // ��ǰ�ؿ�������Ϣ
	Vector<TurretData*> _turretDatas;     // ��ǰ�ؿ���̨��Ϣ
	Vector<PointDelegate*> _pathPoints;   // ��¼��Ч·����

	Label* _numberLabel;                  // ��ʾ���ﲨ��
	Label* _curNumberLabel;               // ��ʾ��ǰ���ﲨ��
	Label* _goldLabel;                    // ��ʾ��ǰ��ҽ��

	Vector<Monster*>_monsterVector;       // �洢���ֹ��Ｏ��
	bool _isFinish = false;               // ���й����Ƿ�ȫ������

	int isTurretAble[15][10];               // �ɽ�����̨��λ�õ�ͼ
	Vector<Monster*> _currentMonsters;       // �����ִ�Ĺ���
	Vector<Turret*> _currentTurrets;         // �����ִ�Ĺ���

public:

	// ���ݹؿ���Ŵ�����Ϸ�ؿ�����
	static Scene* createSceneWithLevel(int selectLevel);
	// �ؿ�������ʼ��
	virtual bool init();
	// ������¼�,���ڴ�����̨
	void onMouseDown(EventMouse* event);
	// TMX point ->Screen
    // ��ͼ��������ת������Ļ����
	Vec2 TMXPosToLocation(Vec2 pos);
	// Screen ->TMX point
	// ��Ļ����ת���ɵ�ͼ��������	
	Vec2 LocationToTMXPos(Vec2 pos);
	// ���ɹ���
	void generateMonsters();

	void generateMonsterWave();

	//getCarrotHealth
	int getCarrotHealth() {
		return carrotHealth;
	}
	// �й��ﵽ���յ㣬���ܲ�����˺������ж���Ϸ�Ƿ�ʧ��
	void HurtCarrot() {
		carrotHealth--;
        // �ж���Ϸ�Ƿ����
        if (carrotHealth<=0) {// ��<=0 ����д
            // ��Ϸ�����߼���������ʾ��Ϸ�������桢������Ϸ��
            // ����ֻ��һ��ʾ��������Ҫ����ʵ�����ʵ��
            CCLOG("Game Over!");
        }
        else {
			if (_carrot != nullptr) {
				_carrot->setSpriteFrame(StringUtils::format("Carrot_%d.png", carrotHealth));
			}
    
        }
	}
	// ��������ɾ�����Ϲ���
	void removeMonster(Monster* monster) {
		_currentMonsters.eraseObject(monster);
	}
	// ����ִ����
	const Vector<Monster*>& getMonsters()const {
		return _currentMonsters;
	}

	virtual void update(float dt) override;

	CREATE_FUNC(GameScene);
};

