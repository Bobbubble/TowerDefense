

#include"GameScene.h"
#include"ui/CocosGUI.h"



using namespace ui;
USING_NS_CC;

static int monsterCount = 5;   // ÿһ�����ֶ��ٹ���
static int currentLevel = 1;  // ��ǰ�ؿ�


#define DEBUG
// ���ݹؿ���Ŵ�����Ϸ�ؿ�����
Scene* GameScene::createSceneWithLevel(int selectLevel)
{   // ��ùؿ����
	currentLevel = selectLevel;

	auto scene = Scene::create();
	
	auto layer = GameScene::create();
	layer->setName("layer"); // �������
	scene->addChild(layer);
	return scene;
}
// �ؿ�������ʼ��
bool GameScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	// ��ȡ��Ļ���
	screenSize = Director::getInstance()->getVisibleSize();
	_screenWidth = screenSize.width;
	_screenHeight = screenSize.height;
#ifdef DEBUG
	CCLOG("screenWidth:  %lf, screenHeight:  %lf", _screenWidth, _screenHeight);
#endif // DEBUG

	//****************** ��ȡ�ؿ����� ***************
	

	// rapidjson ����
	rapidjson::Document document;

	// ���ݴ��ݵĹؿ�ֵselectLevel��ö�Ӧ�Ĺؿ������ļ�
	std::string filePath = FileUtils::getInstance()->
		fullPathForFilename(StringUtils::format("CarrotGuardRes/level_%d.data", currentLevel)); 
	// ======����tmx���ļ�·�������⣬ԭ�����������������������ţ��ʸ���level__1.tmx

#ifdef DEBUG
	CCLOG("File Path: %s", filePath.c_str());
#endif // DEBUG

	// ��ȡ�ļ�����
	std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);

#ifdef DEBUG
	if (contentStr.empty()) {
		CCLOG("Error: File content is empty.");
	}
#endif // DEBUG

	// ����contentStr��json���ݣ����浽document��
	document.Parse<0>(contentStr.c_str());

#ifdef DEBUG
	if (document.Parse<0>(contentStr.c_str()).HasParseError()) {
		CCLOG("Error: JSON parse error. Code: %u",
			   document.GetParseError());
	}
#endif // DEBUG


// ����Ƿ���� tilefile����
#ifdef DEBUG
	if (document.HasMember("tileFile") && document["tileFile"].IsString()) {
		const char* tileFileValue = document["tileFile"].GetString();
		if (tileFileValue) {
			_tileFile = tileFileValue;
		} else {
			CCLOG("Error: empty string.");
		}
	} else {
		CCLOG("Error: not string.");
	}
#endif // DEBUG
	//***************���йؿ���ʼ��******************
	//
	// 1. ��ȡ��ͼ�ļ�
	_tileFile = document["tileFile"].GetString();
	// 2. ��ȡ���ﲨ��
	_number = document["number"].GetInt();
	// 3. ��ǰ������ֵ�����
	_currentCount = 0;
	// 4. ��ǰ���ﲨ��
	_currNum = 1;
	// 5. ��ʼ���������
	_goldValue = 200;
	// ���ؾ���֡�������ӵ�������ܲ�  =========����Ӧ��Ϊ��Թؿ����ݼ���
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("CarrotGuardRes/TBList.plist");
	spriteFrameCache->addSpriteFramesWithFile("CarrotGuardRes/Monsters.plist");
	spriteFrameCache->addSpriteFramesWithFile("CarrotGuardRes/Carrots.plist");

	// ����TMXTiledMap ��ȡ��Ƭ��ͼ
	_tileMap = TMXTiledMap::create(_tileFile);
	//********************************************************************
	//Fix incorrect rendering of tilemaps with csv data on windows
	// https://github.com/cocos2d/cocos2d-x/pull/20483/files
	// ���windows�¼��ص�ͼ���⣡��������������
	//********************************************************************


    // ���ó��������Ĵ�СΪ���ڴ�С
    //this->setContentSize(size);
	// ������Ƭ��ͼ��ʹ������������Ļ
	_tileMap->setScaleX(screenSize.width / _tileMap->getContentSize().width);
    _tileMap->setScaleY(screenSize.height / _tileMap->getContentSize().height);
	// �ѵ�ͼê���λ�ö�����Ϊԭ�㣬ʹ��ͼ���½�����Ļ���½Ƕ���
	_tileMap->setAnchorPoint(Vec2::ZERO);
	_tileMap->setPosition(Vec2::ZERO);
	_tileMap->setName("_tileMap"); // �������
	this->addChild(_tileMap, 1);

#ifdef DEBUG
	// ����Ƿ�ɹ����ص�ͼ
	if (_tileMap) {
		// ��ȡ "collidable" ��
		_collidable = _tileMap->getLayer("collidable");

		// ����Ƿ�ɹ���ȡ "collidable" ��
		if (_collidable) {
			// �������� _collidable
		} else {
			CCLOG("Error: 'collidable' layer not found in the TMX map.");
		}
	} else {
		CCLOG("Error: Failed to load TMX map.");
	}
#endif // DEBUG

	// ��ȡ�ϰ��㣬�����ϰ�������
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(true);  // ========================= �����ĳ�false,û��Ҫ�ģ����ǵ���Ҫ����ɹ���������ʱ��˵
	// ==============��δ�����ã������Ҿ���ֱ��������
	// ��ʼ���ɽ�����������
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			isTurretAble[i][j] = 0;
		}
	}
	// ���ϰ���λ����Ϊ1,��ʾ���ܽ�������
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			if (_collidable->getTileGIDAt(Vec2(i, j)) != 0) {// ====�е������
				isTurretAble[i][j] = 1;
			}
		}
	}

	// ��ùؿ��趨�Ĺ���
	const rapidjson::Value& monsterArray = document["monsters"];
	for (int i = 0; i < monsterArray.Size(); i++) {
		// ���ÿһ�ֹ���name��lifeValue,gold
		std::string name = monsterArray[i]["name"].GetString();
		int lifeValue = monsterArray[i]["lifeValue"].GetInt();
		int gold = monsterArray[i]["gold"].GetInt();
		// �����ݴ���MonsterData������
		auto monsterData = MonsterData::create();
		monsterData->setName(name);
		monsterData->setLifeValue(lifeValue);
		monsterData->setGold(gold);
		// ���䴫���ؿ����Ｏ����
		_monsterDatas.pushBack(monsterData);
	}
	// ��ȡ�ؿ��趨����̨
	const rapidjson::Value& turretArray = document["turrets"];
	for (int i = 0; i < turretArray.Size(); i++) {
		// ��ȡ��̨����
		std::string name = turretArray[i]["name"].GetString();
		int gold = turretArray[i]["gold"].GetInt();
		std::string bulletName = turretArray[i]["bulletName"].GetString();
		// �����ݴ���TurretData������
		auto turretData = TurretData::create();
		turretData->setName(name);
		turretData->setGold(gold);
		turretData->setBulletName(bulletName);
		// ���䴫���ؿ���̨���ݼ�����
		_turretDatas.pushBack(turretData);

	}
	// ���ﾭ����·��
	const rapidjson::Value& pathtArray = document["path"];
	for (int i = 0; i < pathtArray.Size(); i++) {
		// 1. ��ȡÿ�����ﾭ����·��x,y
		int x = pathtArray[i]["x"].GetInt();
		int y = pathtArray[i]["y"].GetInt();
		// ������ͼ����
		Vec2 tilePoint = Vec2(x, y);
		// ����ͼ����ת������Ļ����
		Vec2 locationPoint = TMXPosToLocation(tilePoint);

		// Point���ܼ̳�Ref��Vector���ܴ洢
		auto pointDelegate = PointDelegate::create(locationPoint.x, locationPoint.y);

		// ��ÿ������浽·��������
		_pathPoints.pushBack(pointDelegate);
	}

	// ���Carrot ����
	auto carrotObject = _tileMap->getObjectGroup("carrotObject");

	// ���carrot��ͼ���󣬼�carrotλ��
	ValueMap carrotValueMap = carrotObject->getObject("carrot");
	int carrotX = carrotValueMap.at("x").asInt();
	int carrotY = carrotValueMap.at("y").asInt();

#ifdef DEBUG
	CCLOG("carrotX: %d,  carrotY: %d",carrotX,carrotY );
#endif // DEBUG


	// �����ܲ�
	_carrot = Sprite::createWithSpriteFrameName(StringUtils::format("Carrot_%d.png", carrotHealth));
	//_carrot = Sprite::create("carrot.png");
	_carrot ->setScale(0.4);
	_carrot->setPosition(carrotX, carrotY);
	_carrot->setName("carrot"); // �������
	_tileMap->addChild(_carrot, 2);


	// =========������Ļ����
	// ע����Ļ���ݵĸ��ڵ�Ӧ����scece ����������Ƭ��ͼ����Ϊ��Ƭ��ͼ���������ţ�
	// �������Ƭ��ͼ���ӽڵ������Ļ��setposition ��������ţ���������Ļ��������
	// 1. ��ʾ�����˶��ٲ�����
	_curNumberLabel = Label::createWithSystemFont(StringUtils::format("%d", _currNum), "Arial", 32);
	_curNumberLabel->setColor(Color3B::RED);
	_curNumberLabel->setPosition(_screenWidth * 0.45, _screenHeight * 0.95);
	//_tileMap->addChild(_curNumberLabel);
	this->addChild(_curNumberLabel,2);
	// 2. һ���ж��ٲ�����
	_numberLabel = Label::createWithSystemFont(StringUtils::format("/%dtimes", _number), "Arial", 32);
	_numberLabel->setColor(Color3B::BLUE);
	_numberLabel->setPosition(_screenWidth * 0.55, _screenHeight * 0.95);
	this->addChild(_numberLabel,2);
	// 3. ���Ͻǽ������
	//auto gold = Sprite::create("");// ===============
	//gold->setPosition(50, _screenHeight * 0.96);
	//_tileMap->addChild(gold, 2);

	_goldLabel = Label::createWithSystemFont(StringUtils::format("gold: %d", _goldValue), "Arial-BoldMT", 32);
	_goldLabel->setColor(Color3B::BLUE);
	_goldLabel->setPosition(100, _screenHeight * 0.95);
	_goldLabel->enableOutline(Color4B::WHITE, 2);
	this->addChild(_goldLabel,2);


	// ��ʼ��Ϸʱ������ʱ
	Label* label1 = Label::createWithSystemFont("1", "Arial-BoldMT", 150);
	Label* label2 = Label::createWithSystemFont("2", "Arial-BoldMT", 150);
	Label* label3 = Label::createWithSystemFont("3", "Arial-BoldMT", 150);
	label1->setColor(Color3B::BLUE);
	label2->setColor(Color3B::BLUE);
	label3->setColor(Color3B::BLUE);
	label1->setPosition(_screenWidth / 2, _screenHeight / 2);
	label2->setPosition(_screenWidth / 2, _screenHeight / 2);
	label3->setPosition(_screenWidth / 2, _screenHeight / 2);
	
	// ����label����ʾ
	label1->setVisible(false);
	label2->setVisible(false);
	label3->setVisible(false);
	
	this->addChild(label1,2);
	this->addChild(label2,2);
	this->addChild(label3,2);

	// ���õ���sequence����
	auto countdown = Sequence::create(CallFunc::create([=] {
		label3->setVisible(true);
		}), DelayTime::create(1), CallFunc::create([=] {
			this->removeChild(label3);
			}), CallFunc::create([=] {
				label2->setVisible(true);
				}), DelayTime::create(1), CallFunc::create([=] {
					this->removeChild(label2);
					}), CallFunc::create([=] {
						label1->setVisible(true);
						}), DelayTime::create(1), CallFunc::create([=] {
							this->removeChild(label1);
							// ��Ϸ��ѭ��
							scheduleUpdate();
							}) ,NULL);


	this->runAction(countdown);


#ifdef DEBUG
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif // DEBUG
	// ****************����update()
	// ע�͵�����ҲûӰ�죬�����ٿ���ÿһ֡��������ô����
	//scheduleUpdate();



	// ******************���ɹ���
	generateMonsters();



	return true;
}
// *******************************************���������
void GameScene::onMouseDown(EventMouse* event)
{
	// ��ȡ�����������
	Vec2 clickPos = event->getLocation();
	//��OpenGL����ϵת��Ϊ��Ļ����ϵ
	Vec2 screenPos = Director::getInstance()->convertToUI(clickPos);
	// ע����������λ��
	// ���������OpenGL����ϵ�����Ͻ�0��0����Ļ�������½�0,0
	Vec2 mapPos = LocationToTMXPos(screenPos);
	// ת����TMX��ͼ����
	int mapX = (int)(mapPos.x), mapY = (int)(mapPos.y);
	// ��ͼ�Ͽ��Խ���ʱ
	if (isTurretAble[mapX][mapY] == 0) {
		isTurretAble[mapX][mapY] = 2; // ��������������
		// �ȹ̶���ƿ�ӣ������ٸ�
		std::string name = (*(_turretDatas.begin()))->getName();
		auto turret = Turret::createWithSpriteFrameName(name);
		_currentTurrets.pushBack(turret);
		turret->setName(name);
		//�ɵ�ͼ������ת��Ϊ��Ļ���꣬��֤ͬһ��ͼ���꽨��ʱ��Ļ������ͬ
		screenPos = TMXPosToLocation(mapPos);
		turret->setPosition(screenPos);
		turret->init();
		this->addChild(turret, 10);
	}

}



// TMX point ->Screen
// ��ͼ��������ת������Ļ����
Vec2 GameScene::TMXPosToLocation(Vec2 pos)
{   // ע�� * _tileMap->getScale() ������
	int x = (int)(pos.x * (_tileMap->getTileSize().width*_tileMap->getScale() / CC_CONTENT_SCALE_FACTOR()));
	float pointHeight = _tileMap->getTileSize().height*_tileMap->getScale() / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((_tileMap->getMapSize().height * pointHeight) - (pos.y * pointHeight));
	// �����������ת����ת�����Ͻ�eg: (0,0)->(0,640)   // window��Ϸ��Ļ����(960,640)
	// �����ٽ���ת���ɸ��ӵ�����
	x += (_tileMap->getTileSize().width * _tileMap->getScale() / CC_CONTENT_SCALE_FACTOR()) / 2;
	y-=(_tileMap->getTileSize().width * _tileMap->getScale() / CC_CONTENT_SCALE_FACTOR()) / 2;
#ifdef DEBUG
	CCLOG("x: %lf , y: %lf ",pos.x,pos.y);
	CCLOG("Screen.x: %d, Screen.y: %d", x, y);
#endif // DEBUG



	return Vec2(x, y);

}

// Screen ->TMX point
// ��Ļ����ת���ɵ�ͼ��������
Vec2 GameScene::LocationToTMXPos(Vec2 pos)
{
	int x = (int)(pos.x) / (_tileMap->getTileSize().width*_tileMap->getScale() / CC_CONTENT_SCALE_FACTOR());
	float pointHeight = _tileMap->getTileSize().height*_tileMap->getScale() / CC_CONTENT_SCALE_FACTOR(); 

	//int y = (int)((_tileMap->getMapSize().height*_tileMap->getScale() * pointHeight-pos.y )/ pointHeight);
	int y = (int)((screenSize.height - pos.y) / pointHeight);

#ifdef DEBUG
	CCLOG("x: %lf , y: %lf ",pos.x,pos.y);
	CCLOG("TMX.x: %d, TMX.y: %d", x, y);
#endif // DEBUG
	return Vec2(x, y);
}
/* ���ɹ���
 static int monsterCount = 5;   // ÿһ�����ֶ��ٹ���
int _number;             // �ؿ����ﲨ��
int _currentCount;       // ��ǰ��������,��ǰ�����ѳ��ֶ��ٹ���
int _currNum;            // ��ǰ���ﲨ��
Vector<MonsterData*> _monsterDatas;   // ��ǰ�ؿ�������Ϣ
Vector<PointDelegate*> _pathPoints;   // ��¼��Ч·����
bool _isFinish = false;               // ���й����Ƿ�ȫ������
*/
// ====================================
// ���ɺ�����bug�����г�ʼ��ʾ���⣬������˵�����ܾ���
// ÿһ���ļ����ͬһ�����ɼ���������������⣬eg 3.0f,1.0f ǰ����ֻ������2��
// �������������һ���ֵ�����ʱ����5.0f
void GameScene::generateMonsters() {
    _currNum = 1;

    this->schedule([=](float dt) {
        if (_currNum <=_number ) {
			_curNumberLabel->setString(StringUtils::format("%d", _currNum));
            generateMonsterWave();
            _currNum++;
        } else {
            unschedule("generateMonsters");
        }
    }, 5.0f, "generateMonsters");
}

void GameScene::generateMonsterWave() {
    _currentCount = 0;

    this->schedule([=](float dt) {
        if (_currentCount < monsterCount) {
			// ===========ʹ�� point to point��������ĵ�
            auto monster = Monster::createWithSpriteFrameName((*(_monsterDatas.begin()))->getName());
			_currentMonsters.pushBack(monster);
#ifdef DEBUG
			CCLOG("monster++");
#endif // DEBUG
			// ê����Ϊ����
			monster->setAnchorPoint(Vec2(0.5f, 0.5f));
            monster->setPointPath(_pathPoints); // ����·��������
            this->addChild(monster,10);
			monster->startMoving();

            _currentCount++;
        } else {
            unschedule("generateMonsterWave");
        }
    }, 1.0f, monsterCount, 0, "generateMonsterWave");
}

// �й��ﵽ���յ㣬���ܲ�����˺������ж���Ϸ�Ƿ�ʧ��

void GameScene::HurtCarrot() {
	carrotHealth--;
	// �ж���Ϸ�Ƿ����
	if (carrotHealth <= 0) {// ��<=0 ����д
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

void GameScene::removeMonster(Monster* monster) {
	_currentMonsters.eraseObject(monster);
}

void GameScene::update(float dt)
{
	Vector<Monster*> monstersToRemove;
	for (auto monster : _currentMonsters) {
		if (monster->getLifeValue() <= 0) {
			
			_goldValue += monster->getGold();
			monstersToRemove.pushBack(monster);
		}
	}
	// �ڵ��������Ĺ�����ɾ��Ԫ���ǲ���ȫ�ģ���Ϊ�ᵼ�µ�����ʧЧ
	for (auto monster : monstersToRemove) {
		monster->removeFromParent();
		_currentMonsters.eraseObject(monster);
	}
	_goldLabel ->setString(StringUtils::format("gold: %d", _goldValue));
}
