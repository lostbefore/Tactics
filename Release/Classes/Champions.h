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
	//�̶�ֵ
	float Health;//�趨����ֵ
	float Attack;//�趨������
	float Defense;//�趨������
	int cost;//���ã�1-5��
	//��ֵ̬
	float currentHealth;//��ǰ������ֵ
	float currentAttack;//��ǰ�Ĺ�����
	float currentDefense;//��ǰ�ķ�����
	float Mana;
	// ��ʱ�����
	float attackTimer;  // ���ڼ�¼������ʱ��
	float attackInterval;  // ����������룩
public:
	string FileName = "";
	//��Ҫ�ĺ���
	Sprite* ChampionHero;
	Sprite* Bar1;
	Sprite* Bar2;
	Sprite* HealthBar;
	Sprite* ManaBar;
	Label* HealthLabel;
	Champion();
	bool AttackDistance;//����/Զ�̹���
	Sprite* Champion::create1(Scene* scene, int x, int y);
	virtual void skill() = 0;
	virtual void reset_skill() {
		currentAttack = Attack;
		currentDefense = Defense;
	}
	virtual ~Champion() = 0;
	float AttackDamage();//������ɵ��˺�
	void GetDamage(float dmg);//�����ܵ����˺�����Ҫ��һ����ʼ��Դ���˺�ֵ������
	bool Death();//�����Ƿ�����
	Vec2 getPosition();
	void setPosition(Vec2 vec2);
	void removeChild(Scene* scene);
	// ��ʼ��ʱ��
	void startAttackTimer();
	// �ж��Ƿ���Թ���
	bool canAttack();
	// �������Ʒ���
	void playMeleeAttackAnimation(Scene* scene);
	void playRangedAttackAnimation(Scene* scene, const Vec2& targetPos);
	void playHitAnimation();
	float getcurrentHealth();
	float getHealth();



};
Champion* switchCreate(int ChampionID, Scene* scene, int x, int y);





#endif//CHAMPION_H
