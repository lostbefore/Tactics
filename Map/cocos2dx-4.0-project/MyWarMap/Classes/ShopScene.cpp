#include "ShopScene.h"
#include <iostream>
#include <vector>

USING_NS_CC;
Layer* ShopScene::createScene()
{
    return ShopScene::create();
}

bool ShopScene::init() {
    if (!Layer::init()) {
        return false;
    }

    // ����̵곡���ĳ�ʼ���߼������������������̵�ı�������ť��

    // ������ʾ�̵�
    displayItems();

    return true;
}
//------------------------------------------------------------------//
// ������ʾ�̵�
void ShopScene::displayItems() {
    //��ӳ�̵걳��
    background();
    //չʾ�������
    displayCoin();
    //������������ɫ
    if (start == 0) {
        randomCreate();
    }
    //չʾ���Թ���Ľ�ɫ
    displayPlayer();
    //չʾ���°�ť
    displayNewBottom();

}
//------------------------------------------------------------------//
// ������ʾ�̵걳��
void ShopScene::background() {
    auto spriteStore = Sprite::create("store.png");
    spriteStore->setPosition(Vec2(512, 608));
    this->addChild(spriteStore, 3);
}
//------------------------------------------------------------------//
// ������������ɫ
void ShopScene::randomCreate() {

    while (storeDisplay.size() != 5) {
        int randomMoney = rand() % 100;
        int random;
        if (randomMoney >= 0 && randomMoney <= 39) {
            random = rand() % 3 + 1;
        }
        else if (randomMoney >= 40 && randomMoney <= 69) {
            random = rand() % 3 + 4;
        }
        else if (randomMoney >= 70 && randomMoney <= 84) {
            random = rand() % 3 + 7;
        }
        else if (randomMoney >= 85 && randomMoney <= 94) {
            random = rand() % 3 + 10;
        }
        else if (randomMoney >= 95 && randomMoney <= 99) {
            random = rand() % 3 + 13;
        }
        storeDisplay.push_back(random);//random�ķ�Χ��1-15
        storePicture.push_back(player[random - 1]);
    }
}
//------------------------------------------------------------------//
// ��ʾ�̵�Ľ�ɫ
void ShopScene::displayPlayer() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //�̵��һ����ɫ
    if (storeDisplay[0] != -1) {
        if (coin < playercost[storeDisplay[0] - 1]) {
            auto firstSprite = Sprite::create(playerCanNotBought[storeDisplay[0] - 1]);
            firstSprite->setPosition(Vec2(256, 608));
            this->addChild(firstSprite, 4);
            playerSprites.pushBack(firstSprite);
            judgeCanBought[0] = 0;
        }
        else {
            auto firstSprite = Sprite::create(storePicture[0]);
            firstSprite->setPosition(Vec2(256, 608));
            this->addChild(firstSprite, 4);
            playerSprites.pushBack(firstSprite);
            judgeCanBought[0] = 1;
        }
    }
    else {
        judgeCanBought[0] = 0;
    }
    //�̵�ڶ�����ɫ
    if (storeDisplay[1] != -1) {
        if (coin < playercost[storeDisplay[1] - 1]) {
            auto secondSprite = Sprite::create(playerCanNotBought[storeDisplay[1] - 1]);
            secondSprite->setPosition(Vec2(384, 608));
            this->addChild(secondSprite, 4);
            playerSprites.pushBack(secondSprite);
            judgeCanBought[1] = 0;
        }
        else {
            auto secondSprite = Sprite::create(storePicture[1]);
            secondSprite->setPosition(Vec2(384, 608));
            this->addChild(secondSprite, 4);
            playerSprites.pushBack(secondSprite);
            judgeCanBought[1] = 1;
        }
    }
    else {
        judgeCanBought[1] = 0;
    }
    //�̵��������ɫ
    if (storeDisplay[2] != -1) {
        if (coin < playercost[storeDisplay[2] - 1]) {
            auto thirdSprite = Sprite::create(playerCanNotBought[storeDisplay[2] - 1]);
            thirdSprite->setPosition(Vec2(512, 608));
            this->addChild(thirdSprite, 4);
            playerSprites.pushBack(thirdSprite);
            judgeCanBought[2] = 0;
        }
        else {
            auto thirdSprite = Sprite::create(storePicture[2]);
            thirdSprite->setPosition(Vec2(512, 608));
            this->addChild(thirdSprite, 4);
            playerSprites.pushBack(thirdSprite);
            judgeCanBought[2] = 1;
        }
    }
    else {
        judgeCanBought[2] = 0;
    }
    //�̵���ĸ���ɫ
    if (storeDisplay[3] != -1) {
        if (coin < playercost[storeDisplay[3] - 1]) {
            auto forthSprite = Sprite::create(playerCanNotBought[storeDisplay[3] - 1]);
            forthSprite->setPosition(Vec2(640, 608));
            this->addChild(forthSprite, 4);
            playerSprites.pushBack(forthSprite);
            judgeCanBought[3] = 0;
        }
        else {
            auto forthSprite = Sprite::create(storePicture[3]);
            forthSprite->setPosition(Vec2(640, 608));
            this->addChild(forthSprite, 4);
            playerSprites.pushBack(forthSprite);
            judgeCanBought[3] = 1;
        }
    }
    else {
        judgeCanBought[3] = 0;
    }
    //�̵�������ɫ
    if (storeDisplay[4] != -1) {
        if (coin < playercost[storeDisplay[4] - 1]) {
            auto fifthSprite = Sprite::create(playerCanNotBought[storeDisplay[4] - 1]);
            fifthSprite->setPosition(Vec2(768, 608));
            this->addChild(fifthSprite, 4);
            playerSprites.pushBack(fifthSprite);
            judgeCanBought[4] = 0;
        }
        else {
            auto fifthSprite = Sprite::create(storePicture[4]);
            fifthSprite->setPosition(Vec2(768, 608));
            this->addChild(fifthSprite, 4);
            playerSprites.pushBack(fifthSprite);
            judgeCanBought[4] = 1;
        }
    }
    else {
        judgeCanBought[4] = 0;
    }
}

//------------------------------------------------------------------//
// ��ʾ�̵��ˢ�°�ť
void ShopScene::displayNewBottom() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //�̵��ǩ

    //�̵갴ťͼƬ
    auto NewButtom = MenuItemImage::create(
        "refresh.png",
        "refreshed.png",
        CC_CALLBACK_1(ShopScene::newStore, this));//���°�ť���ͻ����ˢ�º���
    auto refreshLabel = Label::createWithSystemFont("Refresh", "Berlin Sans FB Demi", 30);
    if (coin < 2) {
        refreshLabel->setColor(Color3B(255, 0, 0));
    }
    refreshLabel->setPosition(Vec2(940, 480));
    this->addChild(refreshLabel, 4);
    NewButtom->setPosition(Vec2(864, 480));
    auto Buttom = Menu::create(NewButtom, NULL);
    Buttom->setPosition(Vec2::ZERO);
    this->addChild(Buttom, 4);
}

//------------------------------------------------------------------//
//ˢ��(����ˢ�°�ť�ͻᴥ���������...)
void ShopScene::newStore(cocos2d::Ref* sender) {
    if (coin >= 2) {
        coin = coin - 2;
        displayCoin();
        playerSprites.clear();
        storeDisplay.clear();
        storePicture.clear();
        // ������н���
        this->removeAllChildren();
        randomCreate();
        displayCoin();
        background();
        displayPlayer();
        displayNewBottom();
    }
}
//------------------------------------------------------------------//
//չʾ�������
void ShopScene::displayCoin() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto coinLabel = Label::createWithSystemFont("", "Berlin Sans FB Demi", 30);
    coinLabel->setColor(Color3B(184, 115, 51));
    coinLabel->setString(StringUtils::format("Coins: %d", coin));
    coinLabel->setPosition(Vec2(940, 540));
    this->addChild(coinLabel, 4);
}

//------------------------------------------------------------------//
//�ѹ���ɾ������
void ShopScene::deletePlayer(int n) {
    if (n >= 0 && n < playerSprites.size()) {
        Sprite* deletePicture;
        deletePicture = playerSprites.at(n);
        deletePicture->removeFromParentAndCleanup(true);
    }
    storeDisplay[n] = -1;
    judgeCanBought[n] = -1;
    displayCoin();
    // ������н���
    this->removeAllChildren();
    displayCoin();
    background();
    displayPlayer();
    displayNewBottom();
}


