#ifndef CHAMPION_H
#define CHAMPION_H


#include"cocos2d.h"
#include"cocos/ui/UIWidget.h"

#define MAX_MANA 5

USING_NS_CC;
using namespace std;


class Champion :public cocos2d::Sprite
{
protected:
	//�̶�ֵ
	int Health;//�趨����ֵ
	int Attack;//�趨������
	int Defense;//�趨������
	int cost;//���ã�1-5��
	//��ֵ̬
	int currentHealth;//��ǰ������ֵ
	int currentAttack;//��ǰ�Ĺ�����
	int currentDefense;//��ǰ�ķ�����
	int Mana;
	// ��ʱ�����
	float attackTimer;  // ���ڼ�¼������ʱ��
	float attackInterval;  // ����������룩
public:

	//��Ҫ�ĺ���
	Sprite* ChampionHero;
	Sprite* Bar1;
	Sprite* Bar2;
	Sprite* HealthBar;
	Sprite* ManaBar;
	Champion();
	bool AttackDistance;//����/Զ�̹���
	virtual ~Champion() = 0;
	void run(Action* action);
	void stop();
	virtual int AttackDamage() = 0;//������ɵ��˺�
	virtual void GetDamage(int dmg) = 0;//�����ܵ����˺�����Ҫ��һ����ʼ��Դ���˺�ֵ������
	virtual bool Death() = 0;//�����Ƿ�����
	virtual void TurnStart() = 0;//��ʼ����̬��ֵ
	virtual int getHealth() = 0;
	virtual int getMana() = 0;
	virtual Vec2 getPosition();
	virtual void setPosition(Vec2 vec2);
	virtual void removeChild(Scene* scene);
	// ��ʼ��ʱ��
	void startAttackTimer();
	// �ж��Ƿ���Թ���
	bool canAttack();
	// �������Ʒ���
	void playMeleeAttackAnimation();
	void playRangedAttackAnimation(const Vec2& attackerPos, const Vec2& targetPos);
	void playHitAnimation();


};
Champion* switchCreate(int ChampionID, Scene* scene, int x, int y);

#endif//CHAMPION_H#pragma once
