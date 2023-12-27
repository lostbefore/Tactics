#ifndef __AutoBattle_H__
#define __AutoBattle_H__

#include<list>
#include "cocos2d.h"
#include"Champions.h"
USING_NS_CC;

class AutoBattle : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createAutoBattle();

    virtual bool init();
    void AutoBattle::update(float dt);
    CREATE_FUNC(AutoBattle);
private:
    void Attack(list<Champion*>& myList, list<Champion*>& enemyList);
    list<Champion*> myList, enemyList;
};
void AIenemy(int level, int enemyHerosMap[6][3]);//up to 15
/*
class Player{
public:
    int Health=100;
    int Map[6][3] = { 0 };
}

*/


#endif // __HELLOWORLD_SCENE_H__#pragma oncence
