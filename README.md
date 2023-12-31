# Tactics-金铲铲之战项目说明文档  

> 同济大学软件学院2023年程序设计范式课程期末项目

## 一、项目信息

- 项目选题：**金铲铲之战（2D）**
- 项目GitHub地址：https://github.com/tactics114514/Tactics
- 选用引擎：**Cocos2d-x 4.0**
- 辅助软件：Adobe Photoshop 2022
- 支持平台：Windows

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
| 谌乐俊杰 | 完成商店与资源等内容，完成项目readme文档 | 
| 陈晓坤   | 协助卡牌，完成自动战斗等方面 | 
| 许经宝   | 完成地图等方面（包括删除角色，小小英雄） | 
| 孙少杰   | 完成卡牌，战斗特效等内容 | 


### 期末项目进度

---

| 时间段              | 进度                                                  |
| ------------------- | ---------------------------------------------------   |
| 2023.12.01~2023.12.13 | 学习cocos2dx，下载并搭建环境，建立仓库                    |
| 2023.12.14~2023.12.15 | 确定分工          |
| 2023.12.16~2023.12.22 | 完成游戏菜单，地图基础功能，商店与资源            |
| 2023.12.23~2023.12.26 | Debug、实现背景音乐、增加卡牌的类、更新商店资源           |
| 2023.12.27~2023.12.28 | Debug、实现设置按钮、自动战斗 |
| 2023.12.29~2023.12.31 | Debug、实现战斗特效、联机、制作readme文档、答辩ppt                    |

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
    - [x] 支持创建房间和加入房间的功能（输入相同IP相当于进入房间）
    - [x] 支持练习模式，玩家可以和AI玩家对弈
    - [x] 支持联机模式，支持2个玩家联机对战
    - [x] 地图界面显示对方和自己的游戏得分
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
 

   ## 四、项目的技术难点+踩坑+解决方案与过程


   ---
   请大家想一想


   ## 五、亮点+加分项

   ---
   请大家想一想


   ## 六、游戏说明文档
   ---
   ### 游戏说明
   《金铲铲之战》是一款自动战斗类游戏，
   每局比赛由两名玩家共同进行一场各自为战的博弈对抗，玩家通过“招兵买马”，
   “融合英雄”，“排兵布阵”，成为最终立于战场上的赢家！

   ### 游戏玩法
   进入游戏菜单，可选择两种游戏模式：单机模式，联机模式。进入比赛，你将会得到20金币。每轮回合前，你将有10秒的时间，
   在商店购买角色卡牌（商店上展示5张卡牌。费用有1-5金币，金币为1的卡牌，出现概率为40%，金币为2
   的卡牌，出现概率为30%，金币为3的卡牌，出现概率为15%，金币为4的卡牌，出现概率为10%，金币为5的卡牌，
   出现概率为5%。若商店里没有自己想要的卡牌，你可以花费2金币更新资源。另外，每回合会增加5金币），
   排兵布阵（添加，删除，移动战斗角色），另外还有小小英雄，升星规则（3张同星可以升星，最高3星），等你去探索！回合准备10秒种结束，将进入战斗界面，
   进行自动战斗，战斗画面提供红蓝血条显示英雄的HP，若一方“杀死”另一方所有英雄，该方胜利，加分，另一方失败，减分。
   游戏结束，退回菜单界面。
   #### 单机模式

   玩家单击单机模式按钮后，自行排兵布阵，回合准备结束，进入战斗阶段，我方英雄与电脑AI自动对战。
   如果对方角色全被打败则我方该回合获胜，反之电脑获胜。

   #### 联机模式  

   玩家单击联机模式按钮后，输出IP地址，待匹配相同IP地址的另一名玩家同样单击联机模式后，
   同时跳转至地图界面。自行排兵布阵，回合准备结束，进入战斗阶段，我方英雄与另一方英雄自动对战。
   如果对方角色全被打败则我方该回合获胜，反之对方获胜。
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
|  在地图画面，拖动英雄卡牌          |            移动英雄位置                       |
|   在地图画面，将英雄卡牌移动至右下角的垃圾箱图标处             |删除该英雄 |

   ### 卡牌属性
   等会再做

   ### 游戏画面
   等会再做

   ## 七、致谢+联系我们

   这个不急
