#include "WarMap.h"
#include "ShopScene.h"
#include"AutoBattle.h"
USING_NS_CC;
#define ROUNDTIME 10.0f
#define DAMAGE 10
int fightHerosMap[6][3] = { 0 };
int enemyHerosMap[6][3] = { 0 };
extern int NumOfPlayer;
extern bool IsSingle;
extern int win;
Scene* WarMap::createWarMap()
{
    return WarMap::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool WarMap::init()
{
    //增添round=当前回合数，可进行显示
    //增添myhealth和enemyhealth，可进行显示
    if (!Scene::init())
    {
        return false;
    }
    
    fightHeronums = 0;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    preHero = Sprite::create("001.png");
    for (int i = 0; i < 6; i++) {
        preHerosMap.pushBack(preHero);
    }
    for (int i = 0; i < 18; i++) {
        fightHeros.pushBack(preHero);
    }
  
    auto myWarMaplistener = EventListenerTouchOneByOne::create();
    myWarMaplistener->onTouchBegan = CC_CALLBACK_2(WarMap::onTouchBegan, this);
    myWarMaplistener->onTouchMoved = CC_CALLBACK_2(WarMap::onTouchMoved, this);
    myWarMaplistener->onTouchEnded = CC_CALLBACK_2(WarMap::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(myWarMaplistener, this);


    Sprite* WarMapSprite = Sprite::create("myWarMap.png");
    WarMapSprite->setPosition(Vec2(512, 384));
    this->addChild(WarMapSprite, 0);



    auto shopbuttom = MenuItemImage::create(
        "shop.png",
        "shopped.png",
        CC_CALLBACK_1(WarMap::gotoshop, this));

    if (shopbuttom == nullptr ||
        shopbuttom->getContentSize().width <= 0 ||
        shopbuttom->getContentSize().height <= 0)
    {
        problemLoading("'shop.png' and 'shopped.png'");
    }
    else
    {       
        shopbuttom->setPosition(Vec2(32,416));
    }
    auto aaa = Menu::create(shopbuttom, NULL);
    aaa->setPosition(Vec2::ZERO);
    this->addChild(aaa, 1);
    this->schedule(CC_SCHEDULE_SELECTOR(WarMap::IntoBattle), ROUNDTIME, kRepeatForever, 0);
    return true;
}
void WarMap::IntoBattle(float dt)
{
    CCLOG("Scheduled function called every 10 second");
    /*
    测试
    AIenemy(round, fightHerosMap);
    AIenemy(round, enemyHerosMap);
    */
    if (IsSingle)
        AIenemy(round, enemyHerosMap);
    else {
        //在此实现联机传输数据，双方的Health，map和myFirst（一方为1一方为0）；
    }
    Scene* BattleScene = AutoBattle::createAutoBattle();
    cocos2d::Director::getInstance()->pushScene(TransitionFade::create(0.5, BattleScene, Color3B(0, 255, 255)));;;
    if (win == 1)
        enemyHealth -= DAMAGE;
    else if (win == -1)
        myHealth -= DAMAGE;
    if (myHealth <= 0 || enemyHealth <= 0) {
        //游戏结束，可增加动画（胜利/失败）
        scheduleOnce([=](float dt) {
            Director::getInstance()->popScene();
            }, 2.0f, "exit_key");
    }
    round++;
    //回合结束 对商店和资源进行刷新

}
bool WarMap::onTouchBegan(Touch* touch, Event* event) {
    Vec2 touchPosition = touch->getLocation();
    int i = 0;
    touchchose = 0;
  
    if (touchPosition.x > 3 * 64 && touchPosition.x < 13 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
        for (i = 0; i < 6; i++) {
            if (preFightHerosMap[i] == 0) {
                break;
            }
        }
        if (i == 6) {
            return false;
        }
        
        if (touchPosition.x > 3 * 64 && touchPosition.x < 5 * 64 && touchPosition.y>8 * 64 && touchPosition.y < 11 * 64) {
            if (shopScene->judgeCanBought[0] == 0 || shopScene->storeDisplay[0] <= 0) {
                return false;
            }

            preHero = createHero(shopScene->storeDisplay[0]);
            preFightHerosMap[i] = shopScene->storeDisplay[0];
            preHerosMap.replace(i, preHero);
            allHerosNums[shopScene->storeDisplay[0] - 1]++;

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

        
        preHero->setPosition(Vec2(5 * 64 + 64 * i + 32, 160));
        this->addChild(preHero, 2);
        UpGrade();

        return false;
    }
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

void WarMap::onTouchEnded(Touch* touch, Event* event) {
    Vec2 vec2 = preHero->getPosition();
    int x = vec2.x / 64;
    int y = vec2.y / 64;
    if (touchchose == 1) {
        if (y > 2 && y < 6 && x>4 && x < 11) {
            if (fightHerosMap[x - 5][y - 3] == 0&&fightHeronums< MAX_HERO) {
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

void WarMap::UpGrade() {
    int j = 0;
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

