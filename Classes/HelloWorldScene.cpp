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
    sprite->setPosition(visibleSize / 2);  // 设置位置为屏幕中心
    sprite->setContentSize(visibleSize);   // 设置大小为屏幕大小
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        AudioEngine::preload("menumusic.mp3", nullptr);//预加载
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
        // 创建菜单
        auto menu = cocos2d::Menu::create(singleItem, doubleItem, nullptr);
        this->addChild(menu);
        return true;
    }
    void singleGameCallback(cocos2d::Ref* sender)
    {
        AudioEngine::stopAll();//停止播放音乐
        // 切换到单人游戏场景
        auto singlegameScene = WarMap::createWarMap();
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, singlegameScene, Color3B(0, 255, 255)));
        // 关闭游戏
        //cocos2d::Director::getInstance()->end();
    }
    void doubleGameCallback(cocos2d::Ref* sender)
    {
        AudioEngine::stopAll();//停止播放音乐
        // 切换到双人游戏场景
        //auto doublegameScene = DoubleScene::create();
        //cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, doublegameScene, Color3B(0, 255, 255)));
        // 关闭游戏
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
        // 添加标签
        auto label = Label::createWithSystemFont("Warning:Please pay attention to you time spent on the game!", "Arial", 32);
        label->enableShadow();
        label->setPosition(Vec2(500, 500));
        // 添加标签进入场景
        this->addChild(label);
        // 创建 LoadingBar
        loadingBar = LoadingBar::create("progressbar.png");
        loadingBar->setPosition(Vec2(512, 384));//设置进度条位置在屏幕中央
        loadingBar->setScale(0.7f);//设置进度条尺寸
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
        AudioEngine::stopAll();//停止音乐播放
    }
    CREATE_FUNC(MainMenuScene);
};
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();
    auto menuScene = MainMenuScene::create();//创建新场景
    int backgroundMusicID = AudioEngine::play2d("menumusic.mp3", true);//播放音频
    cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(0.5, menuScene, Color3B(0, 255, 255)));//切换至新场景（主菜单）
}
