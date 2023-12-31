/*Windows��
��������ʾ����CMD����
���� ipconfig �����س���
���� IPv4 ��ַ���������ļ�����ھ������е� IP ��ַ��*/
#include"../tcpSocket/tcpSocket.h"
#include<iostream>
#include "WarMap.h"
#include "ShopScene.h"
#include"AutoBattle.h"
#include<string>
#include <sstream>
#include"math.h"
USING_NS_CC;
//����ÿһ�ֵ�ʱ��
#define ROUNDTIME 10.0f
//ʧ�ܷ���ʧ����ֵ
#define DAMAGE 10
//����ս����������Ӣ�۱��
int fightHerosMap[6][3] = { 0 };
//�з�ս����������Ӣ�۱��
int enemyHerosMap[6][3] = { 0 };
extern int NumOfPlayer;
extern bool IsSingle;
extern int win;
//ССӢ���ƶ��ٶ�
const float smallHeroSpeed = 256;
extern bool myFirst;//Ĭ���������0
const char* ip;
//������ͼ����
Scene* WarMap::createWarMap()
{
    return WarMap::create();
}
//�����׳�
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
//��ͼ������ʼ��
bool WarMap::init()
{
    //��ͼ�Ƿ���ɳ�ʼ��
    if (!Scene::init())
    {
        return false;
    }
    //��ʼս������Ӣ������Ϊ0
    fightHeronums = 0;
    //��Ϸ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����ССӢ��
    smallHero = Sprite::create("littlehero.png");
    smallHero->setPosition(Vec2(32, 32));
    this->addChild(smallHero, 3);
    //������ʼ��
    preHero = Sprite::create("001.png");
    for (int i = 0; i < 6; i++) {
        preHerosMap.pushBack(preHero);
    }
    for (int i = 0; i < 18; i++) {
        fightHeros.pushBack(preHero);
    }
    //����ɾ��Ӣ�۵ĵ���
    Sprite* deletePlace = Sprite::create("deleteHero.png");
    deletePlace->setPosition(Vec2(64 * 15 + 32, 32));
    this->addChild(deletePlace, 2);

    //����������Ĵ���
    auto myWarMaplistener = EventListenerTouchOneByOne::create();
    myWarMaplistener->onTouchBegan = CC_CALLBACK_2(WarMap::onTouchBegan, this);
    myWarMaplistener->onTouchMoved = CC_CALLBACK_2(WarMap::onTouchMoved, this);
    myWarMaplistener->onTouchEnded = CC_CALLBACK_2(WarMap::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(myWarMaplistener, this);
    //��ͼ����
    Sprite* WarMapSprite = Sprite::create("myWarMap.png");
    WarMapSprite->setPosition(Vec2(512, 384));
    this->addChild(WarMapSprite, 0);
    //�̵갴ť�Ĵ���
    auto shopbuttom = MenuItemImage::create(
        "shop.png",
        "shopped.png",
        CC_CALLBACK_1(WarMap::gotoshop, this));
    shopbuttom->setPosition(Vec2(32, 416));
    //�����������
    auto changLabel = MenuItemImage::create("shop.png", "shopped.png", CC_CALLBACK_1(WarMap::changLabel, this));
    changLabel->setPosition(Vec2(15 * 64 + 32, 32+64*4));

    auto aaa = Menu::create(shopbuttom,changLabel, NULL);
    aaa->setPosition(Vec2::ZERO);
    this->addChild(aaa, 1);
    //��ʾ�غ���
    roundLabel = Label::createWithSystemFont("", "Count", 24);
    roundLabel->setString(StringUtils::format("Round:%d", round));
    roundLabel->setPosition(Vec2(8 * 64, 11 * 64 + 20));
    this->addChild(roundLabel);
    //����ʱ
    countdownSeconds = static_cast<int>(ROUNDTIME) - 2;
    countdownLabel = Label::createWithSystemFont("", "Round", 24);
    countdownLabel->setPosition(Vec2(8*64,11*64));
    this->addChild(countdownLabel);
    schedule(CC_SCHEDULE_SELECTOR(WarMap::updateCountdown), 1.0f, countdownSeconds, 0);
    //״̬
    // 
    //��ת��ս������
    this->schedule(CC_SCHEDULE_SELECTOR(WarMap::IntoBattle), ROUNDTIME, kRepeatForever, 0);




    return true;
}

void WarMap::updateCountdown(float dt)
{
    // ���µ���ʱ����ʾ����
    countdownLabel->setString(StringUtils::format("Round Time:%d", countdownSeconds));

    // ���ٵ���ʱ����
    countdownSeconds--;
}
std::string convertArrayToString(int array[][3], int M, int N)
{
    std::string result;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            result += std::to_string(array[i][j]) + " ";
        }
    }
    return result;
}
void convertStringToDynamicArray(std::string input, int M, int N, int result[6][3])
{
    std::istringstream iss(input);
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            iss >> result[i][j];
        }
    }
}
void WarMap::IntoBattle(float dt)
{
    CCLOG("Scheduled function called every 10 second");
    //ֹͣ����ʱ
    //unschedule("Count");

    smallHero->setPosition(Vec2(32, 32));
    if (IsSingle)
        AIenemy(round, enemyHerosMap);
    else if (myFirst == 1) //������
    {
        std::string sendbuf = convertArrayToString(fightHerosMap, 6, 3);
        std::string recvbuf;
        init_Socket();
        SOCKET serfd = createServerSocket();
        SOCKET clifd = accept(serfd, NULL, NULL);
        if (clifd != INVALID_SOCKET)
        {
            recvbuf = receiveData(clifd);
            sendData(clifd, sendbuf);
        }
        convertStringToDynamicArray(recvbuf, 6, 3, enemyHerosMap);
        closesocket(clifd);
        closesocket(serfd);
        close_Socket();
    }
    else//�ͻ���
    {
        init_Socket();
        SOCKET fd = createClientSocket((const char*)ip);
        std::string sendbuf = convertArrayToString(fightHerosMap, 6, 3);
        std::string recvbuf;
        if (sendData(fd, sendbuf))//����
        {
            std::string recvbuf = receiveData(fd);
            convertStringToDynamicArray(recvbuf, 6, 3, enemyHerosMap);
        }
        closesocket(fd);
        close_Socket();
    }
    Scene* BattleScene = AutoBattle::createAutoBattle();
    cocos2d::Director::getInstance()->pushScene(TransitionFade::create(0.5, BattleScene, Color3B(0, 255, 255)));;;
    if (win == 1)
        enemyHealth -= DAMAGE;
    else if (win == -1)
        myHealth -= DAMAGE;
    if (myHealth <= 0 || enemyHealth <= 0) {
        Sprite* result;
        if (win == 1) {
            result = Sprite::create("win.png");
        }
        else
            result = Sprite::create("lose.png");
        result->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(result, 5);
        scheduleOnce([=](float dt) {
            Director::getInstance()->popScene();
            }, 2.0f, "exit_key");
    }
    round++;
    roundLabel->setString(StringUtils::format("Round:%d", round));
    countdownLabel->setString(StringUtils::format("Round Time:%d", round));
    countdownSeconds = static_cast<int>(ROUNDTIME) - 2;
    schedule(CC_SCHEDULE_SELECTOR(WarMap::updateCountdown), 1.0f, countdownSeconds, 0);
    
    //�غϽ��� ���̵����Դ����ˢ��
    if (shopScene) {
        // ����̵곡���ɼ������֮ǰ������
        if (shopScene->isVisible()) {
            shopScene->removeAllChildren();
            // �л��̵곡���Ŀɼ���
            shopScene->setVisible(!shopScene->isVisible());
        }

    }
    shopScene->coin = shopScene->coin + 5;
    shopScene->playerSprites.clear();
    shopScene->storeDisplay.clear();
    shopScene->storePicture.clear();
    // �̵�������������ɫ
    shopScene->randomCreate();

}
//�����ʼ������ʵ��
bool WarMap::onTouchBegan(Touch* touch, Event* event) {
    //��õ����λ��
    Vec2 touchPosition = touch->getLocation();
    //Ԥս������ڼ���
    int i = 0;
    //������������
    touchchose = 0;
    //���������Ϊ2ʱ��Ϊ�ƶ�ССӢ��
    if (changAction == 2) {
        Vec2 smallHeroPosition = smallHero->getPosition();
        float length = (touchPosition.x - smallHeroPosition.x) * (touchPosition.x - smallHeroPosition.x) +
                       (touchPosition.y - smallHeroPosition.y) * (touchPosition.y - smallHeroPosition.y);
        float time = (pow(length, 0.5)) / smallHeroSpeed;
        MoveTo* moveto = MoveTo::create(time, touchPosition);
        Sequence* seq = Sequence::create(moveto, NULL);
        smallHero->runAction(seq);
        return false;
    }
    //����Ϊ�ڳ��ϴ���Ӣ�۵�λ���ƶ�Ӣ�۵�λվλ
    if (touchPosition.x > 3 * 64 && touchPosition.x < 13 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
        //�ж�Ԥս������λ�ã����λ������������Ч
        for (i = 0; i < 6; i++) {
            if (preFightHerosMap[i] == 0) {
                break;
            }
        }
        if (i == 6) {
            return false;
        }
        //���λ��Ϊ�̵�������Ԥս�����򴴽������Ӣ�ۣ��۳���Ӧ��Ǯ������
        if (touchPosition.x > 3 * 64 && touchPosition.x < 5 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
            if (shopScene->judgeCanBought[0] == 0 || shopScene->storeDisplay[0] <= 0) {
                return false;
            }
            //��Ԥս�����򴴽�Ӣ��
            preHero = createHero(shopScene->storeDisplay[0]);
            preFightHerosMap[i] = shopScene->storeDisplay[0];
            preHerosMap.replace(i, preHero);
            allHerosNums[shopScene->storeDisplay[0] - 1]++;
            //�۳���Ӧ�Ľ��
            shopScene->coin = shopScene->coin - shopScene->playercost[shopScene->storeDisplay[0] - 1];
            shopScene->storeDisplay[0] = -1;
            shopScene->deletePlayer(0);
        }
        else if (touchPosition.x > 5 * 64 && touchPosition.x < 7 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
            if (shopScene->judgeCanBought[1] == 0 || shopScene->storeDisplay[1] <= 0) {
                return false;
            }

            preHero = createHero(shopScene->storeDisplay[1]);
            preFightHerosMap[i] = shopScene->storeDisplay[1];
            preHerosMap.replace(i, preHero);
            allHerosNums[shopScene->storeDisplay[1] - 1]++;

            shopScene->coin = shopScene->coin - shopScene->playercost[shopScene->storeDisplay[1] - 1];
            shopScene->storeDisplay[1] = -1;
            shopScene->deletePlayer(1);
        }
        else if (touchPosition.x > 7 * 64 && touchPosition.x < 9 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
            if (shopScene->judgeCanBought[2] == 0 || shopScene->storeDisplay[2] <= 0) {
                return false;
            }

            preHero = createHero(shopScene->storeDisplay[2]);
            preFightHerosMap[i] = shopScene->storeDisplay[2];
            preHerosMap.replace(i, preHero);
            allHerosNums[shopScene->storeDisplay[2] - 1]++;

            shopScene->coin = shopScene->coin - shopScene->playercost[shopScene->storeDisplay[2] - 1];
            shopScene->storeDisplay[2] = -1;
            shopScene->deletePlayer(2);
        }
        else if (touchPosition.x > 9 * 64 && touchPosition.x < 11 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
            if (shopScene->judgeCanBought[3] == 0 || shopScene->storeDisplay[3] <= 0) {
                return false;
            }

            preHero = createHero(shopScene->storeDisplay[3]);
            preFightHerosMap[i] = shopScene->storeDisplay[3];
            preHerosMap.replace(i, preHero);
            
            allHerosNums[shopScene->storeDisplay[3] - 1]++;

            shopScene->coin = shopScene->coin - shopScene->playercost[shopScene->storeDisplay[3] - 1];
            shopScene->storeDisplay[3] = -1;
            shopScene->deletePlayer(3);
        }
        else if (touchPosition.x > 11 * 64 && touchPosition.x < 13 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
            if (shopScene->judgeCanBought[4] == 0 || shopScene->storeDisplay[4] <= 0) {
                return false;
            }

            preHero = createHero(shopScene->storeDisplay[4]);
            preFightHerosMap[i] = shopScene->storeDisplay[4];
            preHerosMap.replace(i, preHero);
            allHerosNums[shopScene->storeDisplay[4] - 1]++;

            shopScene->coin = shopScene->coin - shopScene->playercost[shopScene->storeDisplay[4] - 1];
            shopScene->storeDisplay[4] = -1;
            shopScene->deletePlayer(4);
        }
        else {
            return false;
        }
        //��Ӣ�۷�����Ԥս������λ����
        preHero->setPosition(Vec2(5 * 64 + 64 * i + 32, 160));
        this->addChild(preHero, 2);
        //��Ӣ������
        UpGrade();

        return false;
    }
    //����������ΪԤս������������������Ӣ�ۣ���ɽ�����һ���������������
    else if (touchPosition.x > 320 && touchPosition.x < 704 && touchPosition.y>128 && touchPosition.y < 182) {
        preFightHerosMap_X = touchPosition.x / 64 - 5;
        if (preFightHerosMap[preFightHerosMap_X] != 0) {
            preHero = preHerosMap.at(preFightHerosMap_X);
        }
        else {
            return false;
        }
        touchchose = 1;
    }
    //����������Ϊս������������λ�ô���Ӣ�ۣ���ɽ�����һ���������������
    else if (touchPosition.x > 5 * 64 && touchPosition.x < 11 * 64 && touchPosition.y>3 * 64 && touchPosition.y < 6 * 64) {
        fightHerosMap_X = touchPosition.x / 64;
        fightHerosMap_y = touchPosition.y / 64;
        if (fightHerosMap[fightHerosMap_X - 5][fightHerosMap_y - 3] != 0) {
            preHero = fightHeros.at((fightHerosMap_X - 5) + (fightHerosMap_y - 3) * 6);
        }
        else {
            return false;
        }

        touchchose = 2;
    }
    else {
        return false;
    }
    return true;
}
//��ѡ��Ӣ�ۺ󣬶�������϶�
void WarMap::onTouchMoved(Touch* touch, Event* event) {
    if (touchchose != 0) {
        Vec2 vec2 = touch->getDelta();
        Vec2 position = touch->getLocation();
        int x = (vec2.x + position.x) / 64;
        int y = (vec2.y + position.y) / 64;

        preHero->setPosition(Vec2(64 * x + 32, 64 * y + 32));
    }
    return;
}
//��Ӣ���϶��󣬶��϶����λ�ý����жϣ����λ�úϷ�����Ӣ�����ڸ�λ�ã����򷵻�ԭλ��
void WarMap::onTouchEnded(Touch* touch, Event* event) {
    Vec2 vec2 = preHero->getPosition();
    int x = vec2.x / 64;
    int y = vec2.y / 64;
    if (x == 15 && y == 0) {
        if (touchchose == 1) {
            preFightHerosMap[preFightHerosMap_X] = 0;
            preHero->removeFromParent();

        }
        else if (touchchose == 2) {
            fightHerosMap[fightHerosMap_X - 5][fightHerosMap_y - 3] = 0;
            preHero->removeFromParent();

        }
        return;
    }
    if (touchchose == 1) {
        if (y > 2 && y < 6 && x>4 && x < 11) {
            if (fightHerosMap[x - 5][y - 3] == 0&&fightHeronums<18) {
                fightHerosMap[x - 5][y - 3] = preFightHerosMap[preFightHerosMap_X];
                preFightHerosMap[preFightHerosMap_X] = 0;
                fightHeros.replace((x-5) + (y-3) * 6, preHero);
                preHero->setPosition(Vec2(64 * x + 32, 64 * y + 32));
                fightHeronums++;
                return;
            }           
        }
        preHero->setPosition(Vec2(64 * (5 + preFightHerosMap_X) + 32, 160));
    }
    else if (touchchose == 2) {
        if (y > 2 && y < 6 && x>4 && x < 11) {
            if (fightHerosMap[x - 5][y - 3] == 0) {
                fightHerosMap[x - 5][y - 3] = fightHerosMap[fightHerosMap_X - 5][fightHerosMap_y - 3];
                fightHerosMap[fightHerosMap_X - 5][fightHerosMap_y - 3] = 0;
                fightHeros.replace((x - 5) + (y - 3) * 6, preHero);
                preHero->setPosition(Vec2(64 * x + 32, 64 * y + 32));
                return;
            }
        }
        else if (y == 2 && x > 4 && x < 11) {
            if (preFightHerosMap[x - 5] == 0) {
                preFightHerosMap[x - 5] = fightHerosMap[fightHerosMap_X - 5][fightHerosMap_y - 3];
                fightHerosMap[fightHerosMap_X - 5][fightHerosMap_y - 3] = 0;
                preHerosMap.replace(x - 5, preHero);
                preHero->setPosition(Vec2(64 * x + 32, 160));
                fightHeronums--;
                return;
            }
        }
        preHero->setPosition(Vec2(64 * fightHerosMap_X + 32, 64 * fightHerosMap_y + 32));
    }
    

}

void WarMap::gotoshop(Ref* pSender) {
    // ����̵곡����δ������������
    if (!shopScene) {
        srand(time(0));
        shopScene = ShopScene::create();
        shopScene->retain(); // �����̵곡��ָ��
        this->addChild(shopScene, INT_MAX); // INT_MAX ��֤�̵곡����ʾ�ڶ���
        shopScene->setVisible(true); // Set visibility to true when first created
        shopScene->displayItems(); // Call displayItems when first created
    }
    else {
        // ����̵곡���ɼ������֮ǰ������
        if (shopScene->isVisible()) {
            shopScene->removeAllChildren();
        }

        // �л��̵곡���Ŀɼ���
        shopScene->setVisible(!shopScene->isVisible());

        // ����̵곡���ɼ��������̵곡������ʾ��Ʒ����
        if (shopScene->isVisible()) {
            shopScene->displayItems();
        }
    }
}

//���ݱ�Ŵ�����Ӧ��Ӣ��
Sprite* WarMap::createHero(int gits) {
    Sprite* heros;
    if (gits == 1) {
        heros = Sprite::create("001.png");
    }
    else if (gits == 2) {
        heros = Sprite::create("002.png");
    }
    else if (gits == 3) {
        heros = Sprite::create("003.png");
    }
    else if (gits == 4) {
        heros = Sprite::create("004.png");
    }
    else if (gits == 5) {
        heros = Sprite::create("005.png");
    }
    else if (gits == 6) {
        heros = Sprite::create("006.png");
    }
    else if (gits == 7) {
        heros = Sprite::create("007.png");
    }
    else if (gits == 8) {
        heros = Sprite::create("008.png");
    }
    else if (gits == 9) {
        heros = Sprite::create("009.png");
    }
    else if (gits == 10) {
        heros = Sprite::create("010.png");
    }
    else if (gits == 11) {
        heros = Sprite::create("011.png");
    }
    else if (gits == 12) {
        heros = Sprite::create("012.png");
    }
    else if (gits == 13) {
        heros = Sprite::create("013.png");
    }
    else if (gits == 14) {
        heros = Sprite::create("014.png");
    }
    else if (gits == 15) {
        heros = Sprite::create("015.png");
    }
    else if (gits == 16) {
        heros = Sprite::create("016.png");
    }
    else if (gits == 17) {
        heros = Sprite::create("017.png");
    }
    else if (gits == 18) {
        heros = Sprite::create("018.png");
    }
    else if (gits == 19) {
        heros = Sprite::create("019.png");
    }
    else if (gits == 20) {
        heros = Sprite::create("020.png");
    }
    else if (gits == 21) {
        heros = Sprite::create("021.png");
    }
    else if (gits == 22) {
        heros = Sprite::create("022.png");
    }
    else if (gits == 23) {
        heros = Sprite::create("023.png");
    }
    else if (gits == 24) {
        heros = Sprite::create("024.png");
    }
    else if (gits == 25) {
        heros = Sprite::create("025.png");
    }
    else if (gits == 26) {
        heros = Sprite::create("026.png");
    }
    else if (gits == 27) {
        heros = Sprite::create("027.png");
    }
    else if (gits == 28) {
        heros = Sprite::create("028.png");
    }
    else if (gits == 29) {
        heros = Sprite::create("029.png");
    }
    else if (gits == 30) {
        heros = Sprite::create("030.png");
    }
    else if (gits == 31) {
        heros = Sprite::create("031.png");
    }
    else if (gits == 32) {
        heros = Sprite::create("032.png");
    }
    else if (gits == 33) {
        heros = Sprite::create("033.png");
    }
    else if (gits == 34) {
        heros = Sprite::create("034.png");
    }
    else if (gits == 35) {
        heros = Sprite::create("035.png");
    }
    else if (gits == 36) {
        heros = Sprite::create("036.png");
    }
    else if (gits == 37) {
        heros = Sprite::create("037.png");
    }
    else if (gits == 38) {
        heros = Sprite::create("038.png");
    }
    else if (gits == 39) {
        heros = Sprite::create("039.png");
    }
    else if (gits == 40) {
        heros = Sprite::create("040.png");
    }
    else if (gits == 41) {
        heros = Sprite::create("041.png");
    }
    else if (gits == 42) {
        heros = Sprite::create("042.png");
    }
    else if (gits == 43) {
        heros = Sprite::create("043.png");
    }
    else if (gits == 44) {
        heros = Sprite::create("044.png");
    }
    else if (gits == 45) {
        heros = Sprite::create("045.png");
    }
    else {
        heros = nullptr;
    }
    return heros;
}
//Ӣ�����ǣ���ÿ�ι���Ӣ�ۺ����������жϣ����ĳ��Ӣ�������ﵽ3�����Զ����кϳɲ���
void WarMap::UpGrade() {
    int j=0;
    for (int i = 0; i < 30; i++) {
        if (allHerosNums[i] >= 3) {
            for (int m = 0; m < 6; m++) {
                if (preFightHerosMap[m] == i + 1) {
                    preFightHerosMap[m] = 0;
                    preHero = preHerosMap.at(m);
                    this->removeChild(preHero);
                    j = m;
                }
            }
            for (int x = 0; x < 6; x++) {
                for (int y = 0; y < 3; y++) {
                    if (fightHerosMap[x][y] == i + 1) {
                        fightHerosMap[x][y] = 0;
                        preHero = fightHeros.at(x + 6 * y);
                        fightHeronums--;
                        this->removeChild(preHero);
                    }
                }
            }
            preFightHerosMap[j] = i + 1 + 15;
            preHero = createHero(i + 16);
            preHerosMap.replace(j, preHero);
            preHero->setPosition(Vec2(64 * (5 + j) + 32, 160));
            this->addChild(preHero, 2);
            allHerosNums[i] = 0;
            allHerosNums[i + 15]++;
        }
    }
}
//�ı�������
void WarMap::changLabel(Ref* pSender) {
    if (changAction == 1) {
        changAction = 2;
    }
    else {
        changAction = 1;
    }
}