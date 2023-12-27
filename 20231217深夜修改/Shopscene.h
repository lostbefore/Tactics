#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class ShopScene : public cocos2d::Layer {
private:
    static cocos2d::Layer* createScene();

    char player[15][8] = { "01.png" ,"02.png","03.png","04.png","05.png","06.png","07.png","08.png","09.png","10.png",
        "11.png" ,"12.png","13.png","14.png","15.png" };

    char playerCanNotBought[15][20] = { "01CanNotBought.png" ,"02CanNotBought.png","03CanNotBought.png","04CanNotBought.png","05CanNotBought.png",
        "06CanNotBought.png","07CanNotBought.png","08CanNotBought.png","09CanNotBought.png","10CanNotBought.png",
        "11CanNotBought.png" ,"12CanNotBought.png","13CanNotBought.png","14CanNotBought.png","15CanNotBought.png" };

    std::string StoreName[15] = {"player1" ,"player2","player3","player4","player5","player6","player7","player8","player9","player10",
        "player11" ,"player12","player13","player14","player15", };

    

    int start = 0;//尚未开始进入新的一轮，start=0

    





public:
    virtual bool init();
    CREATE_FUNC(ShopScene);

    int playercost[15] = { 1,1,1,2,2,2,3,3,3,4,4,4,5,5,5 };
    int coin = 50;

    std:: vector<int> storeDisplay;//商店有五个商品，放五个角色的序号

    std::vector <std::string> storePicture;//商店有五个商品，放五个角色图片名称（png)

    Vector<Sprite*> playerSprites;

    int judgeCanBought[5];

    // 添加商店的具体功能方法
    void displayItems();

    void displayPlayer();

    void newStore(cocos2d::Ref* sender);

    void displayNewBottom();

    void background();

    void randomCreate();

    void displayCoin();

    void deletePlayer(int n); //这里的n指的是删掉商店第几个物品（0<= n <=4)


};

#endif // __SHOP_SCENE_H__
