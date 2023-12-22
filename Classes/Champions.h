#include<iostream>
#include"cocos2d.h"
#include"cocos/ui/UIWidget.h"

#define MAX_MANA 5

USING_NS_CC;
using namespace std;


class Champion 
{
protected:
	//固定值
	int Health;//设定生命值
	int Attack;//设定攻击力
	int Defense;//设定防御力
	bool AttackDistance;//近程/远程攻击
	int cost;//费用（1-5）
	//动态值
	int currentHealth;//当前的生命值
	int currentAttack;//当前的攻击力
	int currentDefense;//当前的防御力
	int Mana;
public:
	//需要的函数
	virtual ~Champion() = 0;
	virtual int AttackDamage() = 0;//计算造成的伤害
	virtual int GetDamage(int dmg) = 0;//计算受到的伤害（需要有一个初始来源的伤害值参数）
	virtual bool Death() = 0;//返回是否死亡
	virtual void TurnStart() = 0;//初始化动态数值
	virtual int getHealth() = 0;
	virtual int getMana() = 0;

};