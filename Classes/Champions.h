#include<iostream>
#include"cocos2d.h"
#include"cocos/ui/UIWidget.h"

#define MAX_MANA 5

USING_NS_CC;
using namespace std;


class Champion 
{
protected:
	//�̶�ֵ
	int Health;//�趨����ֵ
	int Attack;//�趨������
	int Defense;//�趨������
	bool AttackDistance;//����/Զ�̹���
	int cost;//���ã�1-5��
	//��ֵ̬
	int currentHealth;//��ǰ������ֵ
	int currentAttack;//��ǰ�Ĺ�����
	int currentDefense;//��ǰ�ķ�����
	int Mana;
public:
	//��Ҫ�ĺ���
	virtual ~Champion() = 0;
	virtual int AttackDamage() = 0;//������ɵ��˺�
	virtual int GetDamage(int dmg) = 0;//�����ܵ����˺�����Ҫ��һ����ʼ��Դ���˺�ֵ������
	virtual bool Death() = 0;//�����Ƿ�����
	virtual void TurnStart() = 0;//��ʼ����̬��ֵ
	virtual int getHealth() = 0;
	virtual int getMana() = 0;

};