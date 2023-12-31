#ifndef __WARMAP_H__
#define __WARMAP_H__

#include "cocos2d.h"
#include "ShopScene.h"
USING_NS_CC;

class WarMap : public cocos2d::Scene
{
public:
    //��������
    static cocos2d::Scene* createWarMap();
    //��ʼ��
    virtual bool init();
    //�ҷ�����ֵ
    int myHealth = 100;
    //�з�����ֵ
    int enemyHealth = 100;
    //�����ʼ������ƶ����������
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    //���ݱ�Ŵ�����Ӧ��Ӣ��
    Sprite* createHero(int gits);
    //Ӣ������
    void UpGrade();
    //ǰ���̵�
    void gotoshop(cocos2d::Ref* pSender);
    //�ı���״̬
    void changLabel(Ref* pSender);
    //����ս��
    void IntoBattle(float dt);
    //�̵����
    ShopScene* shopScene;

    CREATE_FUNC(WarMap);

private:
    //�غϵ���ʱ
    Label* countdownLabel;
    int countdownSeconds;
    void WarMap::updateCountdown(float dt);
    //�ִ���
    Label* roundLabel;
    int round = 1;
    //���״̬
    int changAction=1;
    //ս����ͼ��Ӣ�۵�x��y����
    int fightHerosMap_X;
    int fightHerosMap_y;
    //Ԥս������Ӣ�۱�Ŵ���
    int preFightHerosMap[6] = { 0 };
    //Ԥս������Ӣ�۵�x����
    int preFightHerosMap_X;
    //�������
    int touchchose;
    //ս������Ӣ������
    int fightHeronums;
    //������������Ӣ�۸���������
    int allHerosNums[45] = { 0 };
    //ָ��Ԥս������Ӣ��ָ��
    Sprite* preHero;
    //ССӢ��
    Sprite* smallHero;
    //����Ԥս������Ӣ������
    Vector<Sprite*> preHerosMap;
    //����ս������Ӣ������
    Vector<Sprite*> fightHeros;
};

#endif // __HELLOWORLD_SCENE_H__#pragma oncence

