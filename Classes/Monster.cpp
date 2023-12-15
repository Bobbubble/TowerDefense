#include"Monster.h"


/*
	int _lifeValue;        // ����ֵ
	LoadingBar* _HP;       // Ѫ��
	float _HPInterval;     //  Ѫ��������
	Vector<PointDelegate*> _pathPoints;   // ��¼��Ч·����
	int _gold=10;         // ��������õĽ��
	float _speed=100;        // �ƶ��ٶ�
*/
void Monster::startMoving()
{   Vector<FiniteTimeAction*> moveActions;
	for (auto pathPoint : _pathPoints) {
		// ��Ŀ������ת����vec2
		Vec2 targetPos;
		targetPos.x = pathPoint->getX();
		targetPos.y = pathPoint->getY();
		// ����һ�� MoveTo ������ʹ�����ƶ���Ŀ��λ��
		auto moveAction = MoveTo::create(0.5, targetPos);
		moveActions.pushBack(moveAction);
		
	}
	// ʹ�� Sequence ������ MoveTo ������������
    auto sequence = Sequence::create(moveActions);
    // ִ�ж�������
    runAction(sequence);
}
