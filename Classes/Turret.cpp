#include "Turret.h"
#include"GameScene.h"
#define DEBUG
 void Turret::ShootAtMonster(Monster* target) {
	// ��������ת��Ƕ�
	Vec2 targetPos = target->getPosition();
	Vec2 turretPos = getPosition();
	float angle = CC_RADIANS_TO_DEGREES(turretPos.getAngle(targetPos));
	// ����������ת
	this->getChildByName("turret")->setRotation(angle);
	// �����������ӵ�
	//////////////////////
}

 void Turret::update(float dt) {
	 // ��ȡ��ǰ����
	 auto Scene = Director::getInstance()->getRunningScene();
	 // ��ȡ layer ����
	 auto layer = dynamic_cast<GameScene*>(Scene->getChildByName("layer"));
	 const auto& monsters = layer->getMonsters();
	 for (const auto& monster : monsters) {
		 float distance = getPosition().distance(monster->getPosition());
#ifdef DEBUG
		 CCLOG("distance=%f", distance);
#endif // DEBUG

		 // ����Ƿ��������
		 if (distance <= _range) {
			 // ������������
			 ShootAtMonster(monster);
			 break; // ׷���ǰ�Ĺ����ֻ׷һ��
		 }
	 }
 }
