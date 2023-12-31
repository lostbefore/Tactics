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
    sprite->setPosition(visibleSize / 2);  // 设置位置为屏幕中心
    sprite->setContentSize(visibleSize);   // 设置大小为屏幕大小
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        AudioEngine::preload("menumusic.mp3", nullptr);//预加载
        this->addChild(sprite, 0);
    }
    return true;
}
class DoubleGame : public cocos2d::Scene//设置类
{
public:
    cocos2d::ui::TextField* textField;
    virtual bool init() override
    {
        if (!Scene::init())
        {
            return false;
        }
        // 获取屏幕的可见大小
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        // 添加背景精灵
        auto background = cocos2d::Sprite::create("DoubleGameground.png");
        background->setPosition(visibleSize / 2);  // 设置位置为屏幕中心
        background->setContentSize(visibleSize);   // 设置大小为屏幕大小
        this->addChild(background);//加入至当前场景中
        //创建ip输入位置
        textField = cocos2d::ui::TextField::create("Enter IP Address", "Bell MT", 66);
        textField->setMaxLength(50); // 设置最大输入长度
        textField->setAnchorPoint(Vec2(0.5, 0.5));
        textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
        textField->setPlaceHolderColor(Color3B::BLACK); // 设置占位符颜色
        textField->setCursorChar('|'); // 设置输入时的光标
        textField->setColor(Color3B::BLACK); // 设置输入的文本颜色
        textField->setTouchSize(Size(200, 40)); // 设置输入框的可触摸区域大小
        textField->setTextHorizontalAlignment(TextHAlignment::LEFT); // 文本水平对齐方式
        textField->setTextVerticalAlignment(TextVAlignment::CENTER); // 文本垂直对齐方式
        textField->setCursorEnabled(true); // 启用光标
        textField->setCursorPosition(0); // 设置光标初始位置
        this->addChild(textField);
        // 创建用户菜单项
        auto ServerItem = cocos2d::MenuItemImage::create("Server.png", "Server.png",
            CC_CALLBACK_1(DoubleGame::ServerCallback, this));
        ServerItem->setScale(0.3f);//设置菜单尺寸
        // 设置服务器菜单项的位置
        ServerItem->setAnchorPoint(Vec2(0, 0));
        ServerItem->setPosition(Vec2(-510,-300));
        // 创建开始游戏菜单项
        auto startItem = cocos2d::MenuItemImage::create("StartNormal.png", "StartSelected.png",
            CC_CALLBACK_1(DoubleGame::startGameCallback, this));
        startItem->setAnchorPoint(Vec2(0,0));
        startItem->setScale(0.3f);//设置菜单尺寸
        // 设置开始游戏菜单项的位置
        startItem->setPosition(Vec2(-150, -200));
        // 创建菜单
        auto menu = cocos2d::Menu::create(ServerItem, startItem, nullptr);
        this->addChild(menu);//将菜单加入至场景中
        return true;
    }
    // 建立服务器的回调函数
    void ServerCallback(cocos2d::Ref* sender)
    {
        myFirst = 0;
        textField->setCursorEnabled(false); // 停用光标
        ip = textField->getString().c_str();//将输入值赋值给ip
    }
    // 开始双人游戏的回调函数
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
class Settingcode : public cocos2d::Scene//设置类
{
public:
    virtual bool init() override
    {
        if (!Scene::init())
        {
            return false;
        }
        // 获取屏幕的可见大小
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        // 添加背景精灵
        auto background = cocos2d::Sprite::create("Settingground.png");
        background->setPosition(visibleSize / 2);  // 设置位置为屏幕中心
        background->setContentSize(visibleSize);   // 设置大小为屏幕大小
        this->addChild(background);//加入至当前场景中
        // 创建停止播放音乐菜单项
        auto musicItem = cocos2d::MenuItemImage::create("MusicNormal.png", "MusicSelected.png",
            CC_CALLBACK_1(Settingcode::MusicCallback, this));
        musicItem->setScale(0.5f);//设置菜单尺寸
        // 创建离开设置菜单项
        auto leaveItem = cocos2d::MenuItemImage::create("LeaveNormal.png", "LeaveSelected.png",
            CC_CALLBACK_1(Settingcode::LeaveSettingsCallback, this));
        leaveItem->setScale(0.5f);//设置菜单尺寸
        // 创建退出游戏菜单项
        auto closeItem = cocos2d::MenuItemImage::create("CloseSettingNormal.png", "CloseSettingSelected.png",
            CC_CALLBACK_1(Settingcode::menuCloseCallback, this));
        closeItem->setScale(0.5f);//设置菜单尺寸
        // 创建菜单
        auto menu = cocos2d::Menu::create(musicItem, leaveItem, closeItem, nullptr);
        menu->alignItemsVertically(); // 垂直排列菜单项
        this->addChild(menu);//将菜单加入至场景中
        return true;
    }
    // 停止播放音乐的回调函数
    void MusicCallback(cocos2d::Ref* sender)
    {
        AudioEngine::AudioState state = AudioEngine::getState(backgroundMusicID);
        if (state == AudioEngine::AudioState::PLAYING)
            //停止音乐播放
            AudioEngine::AudioEngine::pause(backgroundMusicID);
        else
            AudioEngine::resume(backgroundMusicID);

    }
    // 退出设置的回调函数
    void LeaveSettingsCallback(cocos2d::Ref* sender)
    {
        auto gameScene = GameScene::create();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(0, 255, 255)));
    }
    // 退出菜单的回调函数
    void menuCloseCallback(cocos2d::Ref* sender)
    {
        // 关闭游戏
        cocos2d::Director::getInstance()->end();
        AudioEngine::stop(backgroundMusicID);//停止音乐播放
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
    // 获取屏幕的可见大小
    auto visibleSize = director->getVisibleSize();
    // 添加背景精灵
    auto gamebackground = cocos2d::Sprite::create("choicebackground.png");
    gamebackground->setPosition(visibleSize / 2);  // 设置位置为屏幕中心
    gamebackground->setContentSize(visibleSize);   // 设置大小为屏幕大小
    this->addChild(gamebackground);
    // 创建单人游戏菜单项
    auto singleItem = cocos2d::MenuItemImage::create("SingleNormal.png", "SingleSelected.png",
        CC_CALLBACK_1(GameScene::singleGameCallback, this));
    singleItem->setScale(0.7f);
    singleItem->setPosition(Vec2(-200, -150));
    // 创建联机游戏菜单项
    auto doubleItem = cocos2d::MenuItemImage::create("DoubleNormal.png", "DoubleSelected.png",
        CC_CALLBACK_1(GameScene::doubleGameCallback, this));
    doubleItem->setScale(0.7f);
    doubleItem->setPosition(Vec2(200, -150));
    // 创建进入菜单菜单项
    auto settingItem = cocos2d::MenuItemImage::create("SettingNormal.png", "SettingSelected.png",
        CC_CALLBACK_1(GameScene::SettingCallback, this));
    settingItem->setScale(0.5f);
    settingItem->setPosition(Vec2(440, -320));
    // 创建菜单
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
    AudioEngine::stop(backgroundMusicID);//停止音乐播放
    // 切换到单人游戏场景
    IsSingle = 1;
    auto singlegameScene = WarMap::createWarMap();
    cocos2d::Director::getInstance()->pushScene(TransitionFade::create(0.5, singlegameScene, Color3B(0, 255, 255)));
}
void GameScene::doubleGameCallback(cocos2d::Ref* sender)//创建双人游戏准备区域
{
    AudioEngine::stop(backgroundMusicID);//停止音乐播放
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
        // 添加标签
        // 获取屏幕的可见大小
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        // 添加背景精灵
        auto background = cocos2d::Sprite::create("loadingbackground.png");
        background->setPosition(visibleSize / 2);  // 设置位置为屏幕中心
        background->setContentSize(visibleSize);   // 设置大小为屏幕大小
        this->addChild(background);//加入至当前场景中
        auto label = Label::createWithSystemFont("Warning:Please pay attention to you time spent on the game!", "Arial", 32);
        label->enableShadow();
        label->setPosition(Vec2(500, 300));
        label->setColor(Color3B(135, 206, 250));
        // 添加标签进入场景
        this->addChild(label);
        // 创建 LoadingBar
        loadingBar = LoadingBar::create("progressbar.png");
        loadingBar->setPosition(Vec2(512, 100));//设置进度条位置在屏幕中央
        loadingBar->setScaleX(1.0f);
        loadingBar->setScaleY(0.3f);//设置进度条尺寸
        loadingBar->setDirection(LoadingBar::Direction::LEFT);//设置进度条加载方向
        loadingBar->setPercent(0);//开始时进度条加载进度为0
        this->addChild(loadingBar);
        this->schedule(CC_SCHEDULE_SELECTOR(LoadingScene::updateLoadingBar), 0.1f);
        return true;
    }
    // 更新 LoadingBar 的回调函数
    void updateLoadingBar(float dt)
    {
        // 模拟进度增加
        if (progress < 1) // 限制进度在 [0, 1) 范围
        {
            progress += 0.02f;
            // 更新 LoadingBar 显示
            loadingBar->setPercent(progress * 100);
        }
        else
            // 进度满了，执行场景切换逻辑
            onLoadingComplete();
    }
    // 进度满了后执行的操作，切换场景
    void onLoadingComplete()
    {
        unschedule(CC_SCHEDULE_SELECTOR(LoadingScene::updateLoadingBar)); // 停止进度更新
        // 切换到下一个场景（GameScene）
        auto gameScene = GameScene::create();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(0, 255, 255)));
    }
    CREATE_FUNC(LoadingScene);
private:
    LoadingBar* loadingBar;
    float progress;
};
class MainMenuScene : public cocos2d::Scene//主要菜单类
{
public:
    virtual bool init() override
    {
        if (!Scene::init())
        {
            return false;
        }
        // 获取屏幕的可见大小
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        // 添加背景精灵
        auto background = cocos2d::Sprite::create("background.png");
        background->setPosition(visibleSize / 2);  // 设置位置为屏幕中心
        background->setContentSize(visibleSize);   // 设置大小为屏幕大小
        this->addChild(background);//加入至当前场景中
        // 创建开始游戏菜单项
        auto startItem = cocos2d::MenuItemImage::create("StartNormal.png", "StartSelected.png",
            CC_CALLBACK_1(MainMenuScene::startGameCallback, this));
        startItem->setScale(0.5f);//设置菜单尺寸
        // 创建退出游戏菜单项
        auto closeItem = cocos2d::MenuItemImage::create("CloseitemNormal.png", "CloseitemSelected.png",
            CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
        closeItem->setScale(0.5f);//设置菜单尺寸
        // 创建菜单
        auto menu = cocos2d::Menu::create(startItem, closeItem, nullptr);
        menu->alignItemsVertically(); // 垂直排列菜单项
        this->addChild(menu);//将菜单加入至场景中
        return true;
    }
    // 开始游戏的回调函数
    void startGameCallback(cocos2d::Ref* sender)
    {
        // 切换到进度条场景
        auto loadingScene = LoadingScene::create();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, loadingScene, Color3B(0, 255, 255)));
    }
    // 退出菜单的回调函数
    void menuCloseCallback(cocos2d::Ref* sender)
    {
        // 关闭游戏
        cocos2d::Director::getInstance()->end();
        AudioEngine::stop(backgroundMusicID);//停止音乐播放
    }
    CREATE_FUNC(MainMenuScene);
};
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    auto menuScene = MainMenuScene::create();//创建新场景
    backgroundMusicID = AudioEngine::play2d("menumusic.mp3", true);//播放音频
    cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, menuScene, Color3B(0, 255, 255)));//切换至新场景（主菜单）
}
