/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"
#include"WarMap.h"
using namespace cocos2d;
using namespace cocos2d::ui;
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /////////////////////////////
    // 3. add your codes below...
    // add a label shows "Hello World"
    // create and initialize a label
    auto label = Label::createWithTTF("Welcome!", "fonts/Marker Felt.ttf", 64);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize / 2);  // ����λ��Ϊ��Ļ����
    sprite->setContentSize(visibleSize);   // ���ô�СΪ��Ļ��С
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        AudioEngine::preload("menumusic.mp3", nullptr);//Ԥ����
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}
class DoubleScene : public cocos2d::Scene
{};
class GameScene : public cocos2d::Scene
{
public:
    virtual bool init() override
    {
        if (!Scene::init())
        {
            return false;
        }
        auto director = cocos2d::Director::getInstance();
        // ��ȡ��Ļ�Ŀɼ���С
        auto visibleSize = director->getVisibleSize();
        // ��ӱ�������
        auto gamebackground = cocos2d::Sprite::create("choicebackground.png");
        gamebackground->setPosition(visibleSize / 2);  // ����λ��Ϊ��Ļ����
        gamebackground->setContentSize(visibleSize);   // ���ô�СΪ��Ļ��С
        this->addChild(gamebackground);
        // ����������Ϸ�˵���
        auto singleItem = cocos2d::MenuItemImage::create("SingleNormal.png", "SingleSelected.png",
            CC_CALLBACK_1(GameScene::singleGameCallback, this));
        singleItem->setScale(0.7f);
        singleItem->setPosition(Vec2(-200, -150));
        // ����������Ϸ�˵���
        auto doubleItem = cocos2d::MenuItemImage::create("DoubleNormal.png", "DoubleSelected.png",
            CC_CALLBACK_1(GameScene::doubleGameCallback, this));
        doubleItem->setScale(0.7f);
        doubleItem->setPosition(Vec2(200, -150));
        // �����˵�
        auto menu = cocos2d::Menu::create(singleItem, doubleItem, nullptr);
        this->addChild(menu);
        return true;
    }
    void singleGameCallback(cocos2d::Ref* sender)
    {
        AudioEngine::stopAll();//ֹͣ��������
        // �л���������Ϸ����
        auto singlegameScene = WarMap::createWarMap();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, singlegameScene, Color3B(0, 255, 255)));
        // �ر���Ϸ
        //cocos2d::Director::getInstance()->end();
    }
    void doubleGameCallback(cocos2d::Ref* sender)
    {
        AudioEngine::stopAll();//ֹͣ��������
        // �л���˫����Ϸ����
        //auto doublegameScene = DoubleScene::create();
        //cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, doublegameScene, Color3B(0, 255, 255)));
        // �ر���Ϸ
        cocos2d::Director::getInstance()->end();
    }
    CREATE_FUNC(GameScene);
};
class LoadingScene : public cocos2d::Scene
{
public:
    virtual bool init() override
    {
        if (!Scene::init())
        {
            return false;
        }
        // ��ӱ�ǩ
        auto label = Label::createWithSystemFont("Warning:Please pay attention to you time spent on the game!", "Arial", 32);
        label->enableShadow();
        label->setPosition(Vec2(500, 500));
        // ��ӱ�ǩ���볡��
        this->addChild(label);
        // ���� LoadingBar
        loadingBar = LoadingBar::create("progressbar.png");
        loadingBar->setPosition(Vec2(512, 384));//���ý�����λ������Ļ����
        loadingBar->setScale(0.7f);//���ý������ߴ�
        loadingBar->setDirection(LoadingBar::Direction::LEFT);//���ý��������ط���
        loadingBar->setPercent(0);//��ʼʱ���������ؽ���Ϊ0
        this->addChild(loadingBar);
        this->schedule(CC_SCHEDULE_SELECTOR(LoadingScene::updateLoadingBar), 0.1f);
        return true;
    }
    // ���� LoadingBar �Ļص�����
    void updateLoadingBar(float dt)
    {
        // ģ���������
        if (progress < 1) // ���ƽ����� [0, 1) ��Χ
        {
            progress += 0.02f;
            // ���� LoadingBar ��ʾ
            loadingBar->setPercent(progress * 100);
        }
        else
            // �������ˣ�ִ�г����л��߼�
            onLoadingComplete();
    }
    // �������˺�ִ�еĲ������л�����
    void onLoadingComplete()
    {
        unschedule(CC_SCHEDULE_SELECTOR(LoadingScene::updateLoadingBar)); // ֹͣ���ȸ���
        // �л�����һ��������GameScene��
        auto gameScene = GameScene::create();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(0, 255, 255)));
    }
    CREATE_FUNC(LoadingScene);
private:
    LoadingBar* loadingBar;
    float progress;
};
class MainMenuScene : public cocos2d::Scene//��Ҫ�˵���
{
public:
    virtual bool init() override
    {
        if (!Scene::init())
        {
            return false;
        }
        // ��ȡ��Ļ�Ŀɼ���С
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        // ��ӱ�������
        auto background = cocos2d::Sprite::create("background.png");
        background->setPosition(visibleSize / 2);  // ����λ��Ϊ��Ļ����
        background->setContentSize(visibleSize);   // ���ô�СΪ��Ļ��С
        this->addChild(background);//��������ǰ������
        // ������ʼ��Ϸ�˵���
        auto startItem = cocos2d::MenuItemImage::create("StartNormal.png", "StartSelected.png",
            CC_CALLBACK_1(MainMenuScene::startGameCallback, this));
        startItem->setScale(0.5f);//���ò˵��ߴ�
        // �����˳���Ϸ�˵���
        auto closeItem = cocos2d::MenuItemImage::create("CloseitemNormal.png", "CloseitemSelected.png",
            CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
        closeItem->setScale(0.5f);//���ò˵��ߴ�
        // �����˵�
        auto menu = cocos2d::Menu::create(startItem, closeItem, nullptr);
        menu->alignItemsVertically(); // ��ֱ���в˵���
        this->addChild(menu);//���˵�������������
        return true;
    }
    // ��ʼ��Ϸ�Ļص�����
    void startGameCallback(cocos2d::Ref* sender)
    {
        // �л�������������
        auto loadingScene = LoadingScene::create();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, loadingScene, Color3B(0, 255, 255)));
    }
    // �˳��˵��Ļص�����
    void menuCloseCallback(cocos2d::Ref* sender)
    {
        // �ر���Ϸ
        cocos2d::Director::getInstance()->end();
        AudioEngine::stopAll();//ֹͣ���ֲ���
    }
    CREATE_FUNC(MainMenuScene);
};
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();
    auto menuScene = MainMenuScene::create();//�����³���
    int backgroundMusicID = AudioEngine::play2d("menumusic.mp3", true);//������Ƶ
    cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, menuScene, Color3B(0, 255, 255)));//�л����³��������˵���
}
