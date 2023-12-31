/*Windows：
打开命令提示符（CMD）。
输入 ipconfig 并按回车。
查找 IPv4 地址，这就是你的计算机在局域网中的 IP 地址。*/
#include"../tcpSocket/tcpSocket.h"
#include<iostream>
#include "WarMap.h"
#include "ShopScene.h"
#include"AutoBattle.h"
#include<string>
#include <sstream>
#include"math.h"
USING_NS_CC;
//进入每一轮的时间
#define ROUNDTIME 10.0f
//失败方损失生命值
#define DAMAGE 10
//己方战斗区域所有英雄编号
int fightHerosMap[6][3] = { 0 };
//敌方战斗区域所有英雄编号
int enemyHerosMap[6][3] = { 0 };
extern int NumOfPlayer;
extern bool IsSingle;
extern int win;
//小小英雄移动速度
const float smallHeroSpeed = 256;
extern bool myFirst;//默认情况下是0
const char* ip;
//创建地图场景
Scene* WarMap::createWarMap()
{
    return WarMap::create();
}
//错误抛出
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
//地图场景初始化
bool WarMap::init()
{
    //地图是否完成初始化
    if (!Scene::init())
    {
        return false;
    }
    //初始战斗区域英雄数量为0
    fightHeronums = 0;
    //游戏屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建小小英雄
    smallHero = Sprite::create("littlehero.png");
    smallHero->setPosition(Vec2(32, 32));
    this->addChild(smallHero, 3);
    //容器初始化
    preHero = Sprite::create("001.png");
    for (int i = 0; i < 6; i++) {
        preHerosMap.pushBack(preHero);
    }
    for (int i = 0; i < 18; i++) {
        fightHeros.pushBack(preHero);
    }
    //创建删除英雄的地区
    Sprite* deletePlace = Sprite::create("deleteHero.png");
    deletePlace->setPosition(Vec2(64 * 15 + 32, 32));
    this->addChild(deletePlace, 2);

    //点击监听器的创建
    auto myWarMaplistener = EventListenerTouchOneByOne::create();
    myWarMaplistener->onTouchBegan = CC_CALLBACK_2(WarMap::onTouchBegan, this);
    myWarMaplistener->onTouchMoved = CC_CALLBACK_2(WarMap::onTouchMoved, this);
    myWarMaplistener->onTouchEnded = CC_CALLBACK_2(WarMap::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(myWarMaplistener, this);
    //地图创建
    Sprite* WarMapSprite = Sprite::create("myWarMap.png");
    WarMapSprite->setPosition(Vec2(512, 384));
    this->addChild(WarMapSprite, 0);
    //商店按钮的创建
    auto shopbuttom = MenuItemImage::create(
        "shop.png",
        "shopped.png",
        CC_CALLBACK_1(WarMap::gotoshop, this));
    shopbuttom->setPosition(Vec2(32, 416));
    //调整点击类型
    auto changLabel = MenuItemImage::create("shop.png", "shopped.png", CC_CALLBACK_1(WarMap::changLabel, this));
    changLabel->setPosition(Vec2(15 * 64 + 32, 32+64*4));

    auto aaa = Menu::create(shopbuttom,changLabel, NULL);
    aaa->setPosition(Vec2::ZERO);
    this->addChild(aaa, 1);
    //显示回合数
    roundLabel = Label::createWithSystemFont("", "Count", 24);
    roundLabel->setString(StringUtils::format("Round:%d", round));
    roundLabel->setPosition(Vec2(8 * 64, 11 * 64 + 20));
    this->addChild(roundLabel);
    //倒计时
    countdownSeconds = static_cast<int>(ROUNDTIME) - 2;
    countdownLabel = Label::createWithSystemFont("", "Round", 24);
    countdownLabel->setPosition(Vec2(8*64,11*64));
    this->addChild(countdownLabel);
    schedule(CC_SCHEDULE_SELECTOR(WarMap::updateCountdown), 1.0f, countdownSeconds, 0);
    //状态
    // 
    //跳转至战斗界面
    this->schedule(CC_SCHEDULE_SELECTOR(WarMap::IntoBattle), ROUNDTIME, kRepeatForever, 0);




    return true;
}

void WarMap::updateCountdown(float dt)
{
    // 更新倒计时的显示文字
    countdownLabel->setString(StringUtils::format("Round Time:%d", countdownSeconds));

    // 减少倒计时秒数
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
    //停止倒计时
    //unschedule("Count");

    smallHero->setPosition(Vec2(32, 32));
    if (IsSingle)
        AIenemy(round, enemyHerosMap);
    else if (myFirst == 1) //服务器
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
    else//客户端
    {
        init_Socket();
        SOCKET fd = createClientSocket((const char*)ip);
        std::string sendbuf = convertArrayToString(fightHerosMap, 6, 3);
        std::string recvbuf;
        if (sendData(fd, sendbuf))//发送
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
    
    //回合结束 对商店和资源进行刷新
    if (shopScene) {
        // 如果商店场景可见，清除之前的内容
        if (shopScene->isVisible()) {
            shopScene->removeAllChildren();
            // 切换商店场景的可见性
            shopScene->setVisible(!shopScene->isVisible());
        }

    }
    shopScene->coin = shopScene->coin + 5;
    shopScene->playerSprites.clear();
    shopScene->storeDisplay.clear();
    shopScene->storePicture.clear();
    // 商店随机生成五个角色
    shopScene->randomCreate();

}
//点击开始函数的实现
bool WarMap::onTouchBegan(Touch* touch, Event* event) {
    //获得点击的位置
    Vec2 touchPosition = touch->getLocation();
    //预战斗区域第几号
    int i = 0;
    //点击区域的种类
    touchchose = 0;
    //当点击类型为2时，为移动小小英雄
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
    //否则为在场上创建英雄单位、移动英雄单位站位
    if (touchPosition.x > 3 * 64 && touchPosition.x < 13 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
        //判断预战斗区域位置，如果位置满，则购买无效
        for (i = 0; i < 6; i++) {
            if (preFightHerosMap[i] == 0) {
                break;
            }
        }
        if (i == 6) {
            return false;
        }
        //点击位置为商店区域，在预战斗区域创建点击的英雄，扣除对应的钱的数量
        if (touchPosition.x > 3 * 64 && touchPosition.x < 5 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
            if (shopScene->judgeCanBought[0] == 0 || shopScene->storeDisplay[0] <= 0) {
                return false;
            }
            //在预战斗区域创建英雄
            preHero = createHero(shopScene->storeDisplay[0]);
            preFightHerosMap[i] = shopScene->storeDisplay[0];
            preHerosMap.replace(i, preHero);
            allHerosNums[shopScene->storeDisplay[0] - 1]++;
            //扣除对应的金币
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
        //将英雄放置在预战斗区的位置上
        preHero->setPosition(Vec2(5 * 64 + 64 * i + 32, 160));
        this->addChild(preHero, 2);
        //将英雄升星
        UpGrade();

        return false;
    }
    //如果点击区域为预战斗区域，如果点击区域有英雄，则可进行下一步操作，否则结束
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
    //如果点击区域为战斗区域，如果点击位置存在英雄，则可进行下一步操作，否则结束
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
//在选择到英雄后，对其进行拖动
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
//将英雄拖动后，对拖动后的位置进行判断，如果位置合法，则将英雄置于该位置，否则返回原位置
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
    // 如果商店场景尚未创建，创建它
    if (!shopScene) {
        srand(time(0));
        shopScene = ShopScene::create();
        shopScene->retain(); // 保留商店场景指针
        this->addChild(shopScene, INT_MAX); // INT_MAX 保证商店场景显示在顶端
        shopScene->setVisible(true); // Set visibility to true when first created
        shopScene->displayItems(); // Call displayItems when first created
    }
    else {
        // 如果商店场景可见，清除之前的内容
        if (shopScene->isVisible()) {
            shopScene->removeAllChildren();
        }

        // 切换商店场景的可见性
        shopScene->setVisible(!shopScene->isVisible());

        // 如果商店场景可见，调用商店场景的显示物品方法
        if (shopScene->isVisible()) {
            shopScene->displayItems();
        }
    }
}

//根据编号创建对应的英雄
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
//英雄升星，在每次购买英雄后会进行依次判断，如果某种英雄数量达到3，则自动进行合成操作
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
//改变点击类型
void WarMap::changLabel(Ref* pSender) {
    if (changAction == 1) {
        changAction = 2;
    }
    else {
        changAction = 1;
    }
}