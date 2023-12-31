# Tactics-金铲铲之战项目说明文档  

> 同济大学软件学院2023年程序设计范式课程期末项目

## 一、项目信息

- 项目选题：**金铲铲之战（2D）**
- 项目GitHub地址：https://github.com/tactics114514/Tactics
- 选用引擎：**Cocos2d-x 4.0**
- 辅助软件：Adobe Photoshop 2022
- 支持平台：Windows
- 可执行文件在Release文件夹中

### 成员及贡献占比

---

| 姓名     | 学号    |  贡献比  | 课程教师   |
| ------   | ------  |  ------- | ------     |
| **张昊宸**   | **2251556** | **20%**      | **朱宏明老师** |
| 谌乐俊杰 | 2250944 | 20%      | 朱宏明老师 |
| 陈晓坤   | 2251875 | 20%      | 赵钦佩老师 |
| 许经宝   | 2251948 | 20%      | 韩丰夏老师 |
| 孙少杰   | 2252088 | 20%      | 朱宏明老师 |


### 成员分工

---

| 姓名     | 任务                                 | 
| :------  | :----------------------------------- |  
| 张昊宸   | 菜单整合与美工，联机，完成答辩PPT | 
| 谌乐俊杰 | 完成商店与资源等内容，完成项目README文档 | 
| 陈晓坤   | 协助卡牌，完成自动战斗等方面 | 
| 许经宝   | 完成地图等方面（包括删除角色，小小英雄） | 
| 孙少杰   | 完成卡牌，战斗特效等内容 | 


### 期末项目进度

---

| 时间段              | 进度                                                     |
| ------------------- | -------------------------------------------------------   |
| 2023.12.01~2023.12.13 | 学习cocos2dx，下载并搭建环境，建立仓库                    |
| 2023.12.14~2023.12.15 | 确定分工          |
| 2023.12.16~2023.12.22 | 完成游戏菜单，地图基础功能，商店与资源            |
| 2023.12.23~2023.12.26 | Debug、实现背景音乐、增加卡牌的类、更新商店资源           |
| 2023.12.27~2023.12.28 | Debug、实现设置按钮、自动战斗 |
| 2023.12.29~2023.12.31 | Debug、实现战斗特效、联机、制作README文档、答辩ppt                      |

## 二、实现的功能点
- 功能
    - [x] 有初始界面和设置界面
    - [x] 1v1地图
    - [x] 支持背景音效
    - [x] 支持多种类型的卡牌
    - [x] 支持购买卡牌
    - [x] 支持刷新商店卡牌
    - [x] 支持卡牌升级功能
    - [x] 支持小小英雄的移动
    - [x] 场上卡牌支持红蓝血条，蓝条满时可以释放技能
    - [x] 支持攻击，被攻击动画特效
    - [x] 支持“创建加入房间"的功能（输入相同IP相当于进入房间）
    - [x] 支持练习模式（即单人模式），玩家可以和AI玩家对弈
    - [x] 支持联机模式，支持2个玩家联机对战
    - [x] 地图界面显示回合倒计时和回合数
    - [x] 回合结束可显示游戏胜利，失败


  ## 三、游戏整体结构设计

  ### 项目划分

  ---

  我们将游戏拆分为三个部分：数据机制、地图与商店设计、美工菜单与动画特效。

  数据机制：建立卡牌的相关的类，存储与战斗有关的卡牌各种数据，创建
  战斗场景。其中需要运用类和类的继承，多态等面向对象编程的知识，着重考察OOP知识

  地图与商店设计：创建地图的场景，在地图场景添上商店的图层。
  其中也需要运用类和类的继承，多态等面向对象编程的知识，着重考察学生掌握cocos2dx的程度。

  美工菜单与动画特效：建立菜单的场景，其中也需要运用类和类的继承，多态等面向对象编程的知识，
  另外需要提升游戏外观，完成攻击动画等特效，着重考察掌握cocos2dx的程度与审美观。

  
  ### 类的设计及继承关系

  ---
  ![继承.png](https://s2.loli.net/2023/12/31/Cs4Sz8gHZfTWymh.png)
 
 简单解释：

 Champion : 卡牌英雄

 Annie 1 ...Panth 3 : 具体的卡牌英雄（数字对应星级）

 WarMap : 游戏地图（排兵布阵状态）

 AutoMap : 自动战斗地图

 HelloWorld: 开始界面/菜单界面

 ShopScene: 商店图层

   ## 四、项目的技术难点+解决方案与过程


   ---
   ### 1、角色类的设计以及封装

   角色类基于精灵类创建，且封装有众多功能，包括：设定角色生命值等各项属性、
   封装角色行为函数，例如进行攻击、收到伤害、释放技能，与此同时角色类内封装了卡
   牌的血条蓝条显示，卡牌的战斗动画并提供接口，使得战斗中可以调用不同类型的精灵动
   画，极大提升了游戏界面的美观性。

   ### 2、不同场景之间的切换与衔接

   由于用户购买角色、选择角色位置以及角色自动战斗的场景不同，
   且具体负责每个场景的开发成员不同，因此各个成员之间的沟通以及如
   何保证场景切换时角色的各项属性不发生改变是本项目难点。同时由于本题
   要实现联机功能，而联机传输的数据应尽量简洁，才能提高联机模式下程
   序运行的效率。因此最终决定采用int类型二维数组表示不同角色位于地
   图上的不同位置，提高了传输效率且不具有二义性。


   ## 五、亮点

   ### 商店随机生成角色


   使用了randomCreate函数来随机生成五个角色，通过设定不同的金币范围，
   实现了不同概率的角色生成。这样的设计使得商店的内容看起来更加多样化。

   ```c++
    void ShopScene::randomCreate() {
      while (storeDisplay.size() != 5) {
        int randomMoney = rand() % 100;
        int random;
        if (randomMoney >= 0 && randomMoney <= 39) {
            random = rand() % 3 + 1;
        }
        else if (randomMoney >= 40 && randomMoney <= 69) {
            random = rand() % 3 + 4;
        }
        else if (randomMoney >= 70 && randomMoney <= 84) {
            random = rand() % 3 + 7;
        }
        else if (randomMoney >= 85 && randomMoney <= 94) {
            random = rand() % 3 + 10;
        }
        else if (randomMoney >= 95 && randomMoney <= 99) {
            random = rand() % 3 + 13;
        }
        storeDisplay.push_back(random);//random的范围是1-15
        storePicture.push_back(player[random - 1]);
      }
    }
  ```
  ### 使用迭代器
  在自动战斗中，迭代器用于遍历 myList 和 enemyList 的元素。代码根据迭代器指向的元素检查条件并执行操作。
  迭代器提供了一定程度的安全性，防止直接访问底层内存，减少内存相关错误的风险。
  迭代器提供了一种方便的方法来遍历容器的元素，提供了诸如 begin()、end()、++、-- 等，简化了迭代元素的过程。
  
  在很多地方使用了 auto 关键字，例如 auto visibleSize = 
  Director::getInstance()->getVisibleSize();，这样可以让编译器自动推断变量的类型，
  提高代码的可读性


  ```c++
    for (auto myIt = myList.begin(); myIt != myList.end(); myIt++) {
        if (enemyList.empty())
            return;
        Champion* myHero = *myIt;
        auto aimIt = enemyList.end();
        float minDis = MAX_DISTANCE, nowDis = MAX_DISTANCE;
        Vec2 myPos;
        Vec2 enemyPos;
        myPos = myHero->getPosition();
        for (auto enemyIt = enemyList.begin(); enemyIt != enemyList.end(); enemyIt++) {
            enemyPos = (*enemyIt)->getPosition();
            nowDis = DistanceCalc(myPos, enemyPos);
            if (nowDis < minDis) {
                minDis = nowDis;
                aimIt = enemyIt;
            }
        }
  ```
  ### 使用lambda表达式

  ```c++
    scheduleOnce([=](float dt) {
    this->scheduleUpdate();
    }, 2.0f, "exit_key");
  ```
  这里使用了lambda表达式 [=](float dt)，其中 [=] 表示捕获外部作用域的所有变量，
  而 (float dt) 是lambda函数的参数列表。在lambda函数体内，执行了 this->scheduleUpdate()，
  即在2秒后调度更新函数。
  ```c++
    scheduleOnce([=](float dt) {
    Director::getInstance()->popScene();
    }, 2.0f, "exit_key");
  ```
  这里同样使用了lambda表达式 [=](float dt)，在lambda函数体内执行了 
  Director::getInstance()->popScene()，即在2秒后弹出当前场景，返回上一个场景。

  ### 其他

  界面精致优美、程序几乎不会出现崩溃的情况。




   ## 六、游戏说明文档
   ---
   ### 游戏说明
   《金铲铲之战》是一款自动战斗类游戏，
   每局比赛由两名玩家共同进行一场各自为战的博弈对抗，玩家通过“招兵买马”，
   “融合英雄”，“排兵布阵”，成为最终立于战场上的赢家！

   ---

   ### 游戏玩法
   进入游戏菜单，可选择两种游戏模式：单机模式，联机模式。进入比赛，你将会得到10金币。每轮回合前，你将有10秒的时间，
   在商店购买角色卡牌（商店上展示5张卡牌。费用有1-5金币，金币为1的卡牌，出现概率为40%，金币为2
   的卡牌，出现概率为30%，金币为3的卡牌，出现概率为15%，金币为4的卡牌，出现概率为10%，金币为5的卡牌，
   出现概率为5%。若商店里没有自己想要的卡牌，你可以花费2金币更新资源。另外，每回合会增加5金币），
   排兵布阵（添加，删除，移动战斗角色），另外还有小小英雄，升星规则（3张同星可以升星，最高3星），等你去探索！回合准备10秒种结束，将进入战斗界面，
   进行自动战斗，战斗画面提供红蓝血条显示英雄的HP等属性，若一方“杀死”另一方所有英雄，该方胜利，另一方失败。
   游戏结束，将会退回菜单界面。

   #### 单机模式

   玩家单击单机模式按钮后，自行排兵布阵，回合准备结束，进入战斗阶段，我方英雄与电脑AI自动对战。
   如果对方角色全被打败则我方该回合获胜，反之电脑获胜。

   #### 联机模式  

   玩家单击联机模式按钮后，输出IP地址，待匹配相同IP地址的另一名玩家同样单击联机模式后，
   同时跳转至地图界面。自行排兵布阵，回合准备结束，进入战斗阶段，我方英雄与另一方英雄自动对战。
   如果对方角色全被打败则我方该回合获胜，反之对方获胜。

   ---

   ### 基本操作
  |              操作              |                            效果                            |
  | :----------------------------: | :--------------------------------------------------------: |
  | 点击“开始游戏”按钮             |     进入菜单                         |
  | 点击“单机模式”按钮             |     进入单机模式游戏                          |
  | 点击“联机模式”按钮             |     进入联机模式游戏                                        |
  | 点击“设置”按钮             |控制背景音乐播放 |
  | 在地图画面，点击左侧的宝石按钮（商店没显示）     |     显示商店                                 |
  | 在地图画面，点击左侧的宝石按钮（商店已显示）     |      退出商店|
  | 点击商店旁边的宝石按钮              |              刷新商店资源                   |
  | 点击商店显示的英雄    |         购买英雄                             |
  | 在地图画面，点击右下方的宝石按钮     |              启动小小英雄                            |
  | 在地图画面，拖动英雄卡牌          |            移动英雄位置                       |
  | 在地图画面，将英雄卡牌移动至右下角的垃圾箱图标处             |删除该英雄 |

  ---

   ### 卡牌属性（关注Champion类）

   #### 固定值：

   Health（生命值）：卡牌的最大生命值。

   Attack（攻击力）：卡牌的基础攻击力。

   Defense（防御力）：卡牌的基础防御力。

   cost（费用）：卡牌的费用，通常在1到5之间。

   #### 动态值：

   currentHealth（当前生命值）：卡牌当前的生命值。

   currentAttack（当前攻击力）：卡牌当前的攻击力。

   currentDefense（当前防御力）：卡牌当前的防御力。

   Mana（法力值）：卡牌当前的法力值。

   #### 计时器相关：

   attackTimer（攻击计时器）：用于记录上一次攻击的时间。

   attackInterval（攻击间隔）：两次攻击之间的时间间隔。


   ---


   ### 游戏画面（重点）

   #### 开始进入游戏

   ![QQ20231231-153332.gif](https://s2.loli.net/2023/12/31/lkfTXwEC4qiUxBj.gif)

   #### 选择单机模式

   ![QQ20231231-15418.gif](https://s2.loli.net/2023/12/31/OIF49GyeVAl2mZ8.gif)

   #### 选择联机模式

   ![QQ20231231-155213.gif](https://s2.loli.net/2023/12/31/RSi5QhYIFkytgpc.gif)

   #### 商店+排兵布阵

   ![QQ20231231-155942 _1_.gif](https://s2.loli.net/2023/12/31/XAwFeCnWNojbzUg.gif)

   #### 自动战斗

   ![QQ20231231-1693.gif](https://s2.loli.net/2023/12/31/cZwyzbdBDNYUHQA.gif)

   ---

   ## 七、联系我们

   张昊宸 1583100797@qq.com

   谌乐俊杰 eugeo1212@gmail.com

   陈晓坤 1762977362@qq.com

   许经宝 1055536420@qq.com

   孙少杰 2890166974@qq.com


   >2023.12.31 完结
