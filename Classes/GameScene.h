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
	TMXTiledMap* _tileMap;   // ��ͼ
	TMXLayer* _collidable;   // �ϰ���
	std::string _tileFile;   // �ؿ���ͼ����
	int _number;             // �ؿ����ж��ٲ���
	int _currentCount;       // ��ǰ��������
	int _currNum;            // ��ǰ���ﲨ��
	int _goldValue;          // ��ҵ�ǰ�������
	Sprite* _carrot;          // �ܲ�
	float _screenWidth, _screenHeight;  //��Ļ���
	int _count;              // ��Ϸ������;
	int _delivery;            // ���ֹ���ȡģϵ�� ������

	Vector<MonsterData*> _monsterDatas;   // ��ǰ�ؿ�������Ϣ
	Vector<TurretData*> _turretDatas;     // ��ǰ�ؿ���̨��Ϣ
	Vector<PointDelegate*> _pathPoints;   // ��¼��Ч·����

	Label* _numberLabel;                  // ��ʾ���ﲨ��
	Label* _curNumberLabel;               // ��ʾ��ǰ���ﲨ��
	Label* _goldLabel;                    // ��ʾ��ǰ��ҽ��

	Vector<Monster*>_monsterVector;       // �洢���ֹ��Ｏ��
	bool _isFinish = false;               // ���й����Ƿ�ȫ������

public:

	// ѡ��ǰ�ؿ�����������ͨ���ؿ���
	static Scene* createSceneWithLevel(int selectLevel);

	virtual bool init();

	void onMouseDown(EventMouse* event);


	// TMP ->OPEN GL
	Vec2 locationForTilePos(Vec2 pos);
	// OPEN ->tmp
	Vec2 titleCoordForPosition(Vec2 position);

	CREATE_FUNC(GameScene);
};

