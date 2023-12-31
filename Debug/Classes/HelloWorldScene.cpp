#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"
#include"WarMap.h"
#include"AutoBattle.h"
using namespace cocos2d;
using namespace cocos2d::ui;
extern const char* ip;
USING_NS_CC;
int NumOfPlayer = 2;
bool IsSingle;
int backgroundMusicID;
extern bool myFirst;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
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
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = Label::createWithTTF("Welcome!", "fonts/Marker Felt.ttf", 64);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        this->addChild(label, 1);
    }
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
        this->addChild(sprite, 0);
    }
    return true;
}
class DoubleGame : public cocos2d::Scene//������
{
public:
    cocos2d::ui::TextField* textField;
    virtual bool init() override
    {
        if (!Scene::init())
        {
            return false;
        }
        // ��ȡ��Ļ�Ŀɼ���С
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        // ��ӱ�������
        auto background = cocos2d::Sprite::create("DoubleGameground.png");
        background->setPosition(visibleSize / 2);  // ����λ��Ϊ��Ļ����
        background->setContentSize(visibleSize);   // ���ô�СΪ��Ļ��С
        this->addChild(background);//��������ǰ������
        //����ip����λ��
        textField = cocos2d::ui::TextField::create("Enter IP Address", "Bell MT", 66);
        textField->setMaxLength(50); // ����������볤��
        textField->setAnchorPoint(Vec2(0.5, 0.5));
        textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
        textField->setPlaceHolderColor(Color3B::BLACK); // ����ռλ����ɫ
        textField->setCursorChar('|'); // ��������ʱ�Ĺ��
        textField->setColor(Color3B::BLACK); // ����������ı���ɫ
        textField->setTouchSize(Size(200, 40)); // ���������Ŀɴ��������С
        textField->setTextHorizontalAlignment(TextHAlignment::LEFT); // �ı�ˮƽ���뷽ʽ
        textField->setTextVerticalAlignment(TextVAlignment::CENTER); // �ı���ֱ���뷽ʽ
        textField->setCursorEnabled(true); // ���ù��
        textField->setCursorPosition(0); // ���ù���ʼλ��
        this->addChild(textField);
        // �����û��˵���
        auto ServerItem = cocos2d::MenuItemImage::create("Server.png", "Server.png",
            CC_CALLBACK_1(DoubleGame::ServerCallback, this));
        ServerItem->setScale(0.3f);//���ò˵��ߴ�
        // ���÷������˵����λ��
        ServerItem->setAnchorPoint(Vec2(0, 0));
        ServerItem->setPosition(Vec2(-510,-300));
        // ������ʼ��Ϸ�˵���
        auto startItem = cocos2d::MenuItemImage::create("StartNormal.png", "StartSelected.png",
            CC_CALLBACK_1(DoubleGame::startGameCallback, this));
        startItem->setAnchorPoint(Vec2(0,0));
        startItem->setScale(0.3f);//���ò˵��ߴ�
        // ���ÿ�ʼ��Ϸ�˵����λ��
        startItem->setPosition(Vec2(-150, -200));
        // �����˵�
        auto menu = cocos2d::Menu::create(ServerItem, startItem, nullptr);
        this->addChild(menu);//���˵�������������
        return true;
    }
    // �����������Ļص�����
    void ServerCallback(cocos2d::Ref* sender)
    {
        myFirst = 0;
        textField->setCursorEnabled(false); // ͣ�ù��
        ip = textField->getString().c_str();//������ֵ��ֵ��ip
    }
    // ��ʼ˫����Ϸ�Ļص�����
    void startGameCallback(cocos2d::Ref* sender)
    {
        IsSingle = 0;
        auto singlegameScene = WarMap::createWarMap();
        cocos2d::Director::getInstance()->pushScene(TransitionFade::create(0.5, singlegameScene, Color3B(0, 255, 255)));
    }
    CREATE_FUNC(DoubleGame);
};
class GameScene : public cocos2d::Scene
{
public:
    virtual bool init();
    void SettingCallback(cocos2d::Ref* sender);
    void singleGameCallback(cocos2d::Ref* sender);
    void doubleGameCallback(cocos2d::Ref* sender);
    CREATE_FUNC(GameScene);
};
class Settingcode : public cocos2d::Scene//������
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
        auto background = cocos2d::Sprite::create("Settingground.png");
        background->setPosition(visibleSize / 2);  // ����λ��Ϊ��Ļ����
        background->setContentSize(visibleSize);   // ���ô�СΪ��Ļ��С
        this->addChild(background);//��������ǰ������
        // ����ֹͣ�������ֲ˵���
        auto musicItem = cocos2d::MenuItemImage::create("MusicNormal.png", "MusicSelected.png",
            CC_CALLBACK_1(Settingcode::MusicCallback, this));
        musicItem->setScale(0.5f);//���ò˵��ߴ�
        // �����뿪���ò˵���
        auto leaveItem = cocos2d::MenuItemImage::create("LeaveNormal.png", "LeaveSelected.png",
            CC_CALLBACK_1(Settingcode::LeaveSettingsCallback, this));
        leaveItem->setScale(0.5f);//���ò˵��ߴ�
        // �����˳���Ϸ�˵���
        auto closeItem = cocos2d::MenuItemImage::create("CloseSettingNormal.png", "CloseSettingSelected.png",
            CC_CALLBACK_1(Settingcode::menuCloseCallback, this));
        closeItem->setScale(0.5f);//���ò˵��ߴ�
        // �����˵�
        auto menu = cocos2d::Menu::create(musicItem, leaveItem, closeItem, nullptr);
        menu->alignItemsVertically(); // ��ֱ���в˵���
        this->addChild(menu);//���˵�������������
        return true;
    }
    // ֹͣ�������ֵĻص�����
    void MusicCallback(cocos2d::Ref* sender)
    {
        AudioEngine::AudioState state = AudioEngine::getState(backgroundMusicID);
        if (state == AudioEngine::AudioState::PLAYING)
            //ֹͣ���ֲ���
            AudioEngine::AudioEngine::pause(backgroundMusicID);
        else
            AudioEngine::resume(backgroundMusicID);

    }
    // �˳����õĻص�����
    void LeaveSettingsCallback(cocos2d::Ref* sender)
    {
        auto gameScene = GameScene::create();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(0, 255, 255)));
    }
    // �˳��˵��Ļص�����
    void menuCloseCallback(cocos2d::Ref* sender)
    {
        // �ر���Ϸ
        cocos2d::Director::getInstance()->end();
        AudioEngine::stop(backgroundMusicID);//ֹͣ���ֲ���
    }
    CREATE_FUNC(Settingcode);
};
bool GameScene::init()
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
    // ��������˵��˵���
    auto settingItem = cocos2d::MenuItemImage::create("SettingNormal.png", "SettingSelected.png",
        CC_CALLBACK_1(GameScene::SettingCallback, this));
    settingItem->setScale(0.5f);
    settingItem->setPosition(Vec2(440, -320));
    // �����˵�
    auto menu = cocos2d::Menu::create(singleItem, doubleItem, settingItem, nullptr);
    this->addChild(menu);
    return true;
}
void GameScene::SettingCallback(cocos2d::Ref* sender)
{
    auto settingScene = Settingcode::create();
    cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, settingScene, Color3B(0, 255, 255)));
}
void GameScene::singleGameCallback(cocos2d::Ref* sender)
{
    AudioEngine::stop(backgroundMusicID);//ֹͣ���ֲ���
    // �л���������Ϸ����
    IsSingle = 1;
    auto singlegameScene = WarMap::createWarMap();
    cocos2d::Director::getInstance()->pushScene(TransitionFade::create(0.5, singlegameScene, Color3B(0, 255, 255)));
}
void GameScene::doubleGameCallback(cocos2d::Ref* sender)//����˫����Ϸ׼������
{
    AudioEngine::stop(backgroundMusicID);//ֹͣ���ֲ���
    IsSingle = 0;
    auto doublegamehomeScene = DoubleGame::create();
    cocos2d::Director::getInstance()->pushScene(TransitionFade::create(0.5, doublegamehomeScene, Color3B(0, 255, 255)));
}
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
        // ��ȡ��Ļ�Ŀɼ���С
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        // ��ӱ�������
        auto background = cocos2d::Sprite::create("loadingbackground.png");
        background->setPosition(visibleSize / 2);  // ����λ��Ϊ��Ļ����
        background->setContentSize(visibleSize);   // ���ô�СΪ��Ļ��С
        this->addChild(background);//��������ǰ������
        auto label = Label::createWithSystemFont("Warning:Please pay attention to you time spent on the game!", "Arial", 32);
        label->enableShadow();
        label->setPosition(Vec2(500, 300));
        label->setColor(Color3B(135, 206, 250));
        // ��ӱ�ǩ���볡��
        this->addChild(label);
        // ���� LoadingBar
        loadingBar = LoadingBar::create("progressbar.png");
        loadingBar->setPosition(Vec2(512, 100));//���ý�����λ������Ļ����
        loadingBar->setScaleX(1.0f);
        loadingBar->setScaleY(0.3f);//���ý������ߴ�
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
        AudioEngine::stop(backgroundMusicID);//ֹͣ���ֲ���
    }
    CREATE_FUNC(MainMenuScene);
};
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    auto menuScene = MainMenuScene::create();//�����³���
    backgroundMusicID = AudioEngine::play2d("menumusic.mp3", true);//������Ƶ
    cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, menuScene, Color3B(0, 255, 255)));//�л����³��������˵���
}
