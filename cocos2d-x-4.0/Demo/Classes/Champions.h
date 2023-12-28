#ifndef CHAMPION_H
#define CHAMPION_H


#include"cocos2d.h"
#include"cocos/ui/UIWidget.h"
#include "audio/include/AudioEngine.h"

#define MAX_MANA 5.0f

USING_NS_CC;
using namespace std;



class Champion :public cocos2d::Sprite
{
protected:
	//固定值
	float Health;//设定生命值
	float Attack;//设定攻击力
	float Defense;//设定防御力
	int cost;//费用（1-5）
	//动态值
	float currentHealth;//当前的生命值
	float currentAttack;//当前的攻击力
	float currentDefense;//当前的防御力
	float Mana;
	// 计时器相关
	float attackTimer;  // 用于记录攻击的时间
	float attackInterval;  // 攻击间隔（秒）
public:
	
	//需要的函数
	Sprite* ChampionHero;
	Sprite* Bar1;
	Sprite* Bar2;
	Sprite* HealthBar;
	Sprite* ManaBar;
	Sprite* actionAnimation;
	Champion();
	bool AttackDistance;//近程/远程攻击
	virtual ~Champion() = 0;
	void run(Action* action);
	void stop();
	virtual int AttackDamage() = 0;//计算造成的伤害
	void GetDamage(int dmg) ;//计算受到的伤害（需要有一个初始来源的伤害值参数）
	bool Death();//返回是否死亡
	Vec2 getPosition();
	void setPosition(Vec2 vec2);
	void removeChild(Scene* scene);
	// 开始计时器
	void startAttackTimer();
	// 判断是否可以攻击
	bool canAttack();
	// 动画控制方法
	void playMeleeAttackAnimation(Scene* scene);
	void playRangedAttackAnimation(Scene* scene, const Vec2& targetPos);
	void playHitAnimation();
	
	
};
Champion* switchCreate(int ChampionID, Scene* scene, int x, int y);





#endif//CHAMPION_H
