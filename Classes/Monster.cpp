#include"Monster.h"
#include"GameScene.h"

#define DEBUG
/*
	int _lifeValue;        // ����ֵ
	LoadingBar* _HP;       // Ѫ��
	float _HPInterval;     //  Ѫ��������
	Vector<PointDelegate*> _pathPoints;   // ��¼��Ч·����
	int _gold=10;         // ��������õĽ��
	float _speed=100;        // �ƶ��ٶ�
*/
void Monster::startMoving()
{   
    Vector<FiniteTimeAction*> moveActions;
    int mark = 1;
	for (auto pathPoint : _pathPoints) {
		// ��Ŀ������ת����vec2
		Vec2 targetPos;
		targetPos.x = pathPoint->getX();
		targetPos.y = pathPoint->getY();
        // �ڵ�һ��·��λ�ã������ó�ʼλ��
        if (mark == 1) {
            this->setPosition(targetPos);
            mark--;
            continue;
        }
		// ����һ�� MoveTo ������ʹ�����ƶ���Ŀ��λ��
		auto moveAction = MoveTo::create(0.5, targetPos);
		moveActions.pushBack(moveAction);
		
	}
	// ʹ�� Sequence ������ MoveTo ������������
    auto sequence = Sequence::create(moveActions);
	
    // �ڶ���������ɺ�ִ�лص����Ƴ�����
	// �ص�����ִ�е����յ��߼���carrot ��Ѫ���ж���Ϸ�Ƿ����
    auto callback = CallFunc::create([this]() {
        // ��ȡ��ǰ����
        auto Scene = Director::getInstance()->getRunningScene();

        if (Scene) {
            // ��ȡ layer ����
            auto layer = dynamic_cast<GameScene*>(Scene->getChildByName("layer"));
#ifdef DEBUG
            if (layer == nullptr) {
                CCLOG("not found layer");
            }
#endif // DEBUG
            // ��ȡtilemap
			auto _tileMap = dynamic_cast<TMXTiledMap*>(layer->getChildByName("_tileMap"));
#ifdef DEBUG
            if (_tileMap == nullptr) {
                CCLOG("not found _tileMap");
            }
#endif // DEBUG
            // ��ȡcarrot
            auto carrot=dynamic_cast<Sprite*>(_tileMap->getChildByName("carrot"));
#ifdef DEBUG
            if (carrot == nullptr) {
                CCLOG("not found carrot");
            }
#endif // DEBUG           

            if (carrot) {
                // ִ�е����յ���߼���������� Carrot ������ֵ
                layer->HurtCarrot();
            }
        // *******�Ƴ�����
        // �ӳ����Ƴ�
        removeFromParent();
        // ���ִ�����������Ƴ�
        layer->removeMonster(this);
        
        }
		
    });

    // ʹ�� s ͬʱִ�ж������кͻص�
    auto s = Sequence::create(sequence, callback, nullptr);

    // ���� Spawn ����
    runAction(s);
}
