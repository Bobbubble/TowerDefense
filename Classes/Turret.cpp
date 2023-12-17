#include "Turret.h"
#include"GameScene.h"
#define DEBUG
 void Turret::ShootAtMonster(Monster* target) {
	// ��������ת��Ƕ�
	Vec2 targetPos = target->getPosition();
	Vec2 turretPos = getPosition();
	// ���Ǽ������������ļнǣ�����
	//float angle = turretPos.getAngle(targetPos);// ��λ�ǻ���
	// ���治��
	// ת����������� 
	targetPos.x -= turretPos.x;
	targetPos.y -= turretPos.y;
	// Ĭ����������ǹ������ָ����ô��׼����Ϊ��0��1����
	turretPos = Vec2(0, 1);
	// ��ת��Ϊ�Ƕ�
	float angle=CC_RADIANS_TO_DEGREES(turretPos.getAngle(targetPos));
	// ����������ת
	//setRotation ����ʹ�õ�����ʱ����ת������ϵ����������
	// ����-1.0*angle �ǶԵģ���Ҳ��֪��Ϊʲô
	this->getChildByName("turret")->setRotation(-1.0*angle);
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
