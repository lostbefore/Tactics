#include"Champions.h"
#include<iostream>
USING_NS_CC;

Vec2  Champion:: getPosition() 
{
	return ChampionHero->getPosition();
}
void Champion::setPosition(Vec2 vec2) 
{
	ChampionHero->setPosition(vec2);
	Bar1->setPosition(Vec2(vec2.x,vec2.y+1));
	Bar2->setPosition(Vec2(vec2.x, vec2.y + 3));
	ManaBar->setPosition(Vec2(vec2.x, vec2.y + 1));
	HealthBar->setPosition(Vec2(vec2.x, vec2.y + 3));
}
Champion::~Champion()
{
	// 实现可能需要的清理工作
}
Champion::Champion() : attackTimer(0.0f), attackInterval(1.0f) {}
// 开始计时器
void Champion::startAttackTimer()
{
	attackTimer = 0.0f;  // 重置计时器
}
// 判断是否可以攻击
bool Champion::canAttack()
{
	attackTimer += Director::getInstance()->getDeltaTime();  // 更新计时器

	if (attackTimer >= attackInterval)
	{
		attackTimer = 0.0f;  // 重置计时器
		return true;  // 可以攻击
	}

	return false;  // 未达到攻击间隔，不能攻击
}

void Champion::playMeleeAttackAnimation()
{
	auto meleeAttackAnimation = Animation::create();
	meleeAttackAnimation->setDelayPerUnit(0.15f); // 每帧间隔0.15秒

	// 添加逐帧动画帧
	meleeAttackAnimation->addSpriteFrameWithFile("attack1.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack2.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack3.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack4.png");

	// 创建动作
	auto meleeAttackAction = Animate::create(meleeAttackAnimation);

	// 运行动作
	this->runAction(meleeAttackAction);
}

void Champion::playRangedAttackAnimation(const Vec2& attackerPos, const Vec2& targetPos)
{
	// 创建法球精灵
	auto projectile = Sprite::create("attack5.png");
	this->getParent()->addChild(projectile); // 将法球添加到与角色同一层次的父节点

	// 设置法球初始位置
	projectile->setPosition(attackerPos);

	// 计算飞行时间
	float distance = attackerPos.distance(targetPos);
	float duration = 0.5f;

	// 创建飞行动作
	auto moveAction = MoveTo::create(duration, targetPos);

	// 创建完成后移除法球的动作
	auto removeAction = RemoveSelf::create();

	// 创建动作序列
	auto projectileAction = Sequence::create(moveAction, removeAction, nullptr);

	// 运行动作
	projectile->runAction(projectileAction);
}

void Champion::playHitAnimation()
{
	// 创建受击动画
	auto hitAction = Sequence::create(
		// 变红效果
		TintTo::create(0.25f, 255, 0, 0),  // 变红
		DelayTime::create(0.25f),           // 保持红色状态0.25秒
		TintTo::create(0.25f, 255, 255, 255),  // 恢复原色
		nullptr
	);

	// 播放动画
	this->runAction(hitAction);
}
class Annie1 :public Champion 
{
public:
	Annie1() 
	{
		Health=10;
		Attack=3;
		Defense=1;
		AttackDistance=0;
		cost=1;
		currentHealth=Health;
		currentAttack=Attack;
		currentDefense=Defense;
		Mana=0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int getHealth() 
	{
		return currentHealth;
	}
	
	int getMana() 
	{
		return Mana;
	}
	auto create1(Scene* scene,int x,int y)
	{
		ChampionHero = Sprite::create("001.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4)+1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);

		
		return Annie1::create();
	}

		
};
class Garen1 :public Champion
{
public:
	Garen1()
	{
		Health = 25;
		Attack = 2;
		Defense = 2;
		AttackDistance = 1;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 10 <= Health ? currentHealth = currentHealth + 10 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("002.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Garen1::create();
	}
};
class Yasuo1 :public Champion
{
public:
	Yasuo1()
	{
		Health = 15;
		Attack = 3;
		Defense = 2;
		AttackDistance = 1;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("003.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Yasuo1::create();
	}
};
class Jinx1 :public Champion
{
public:
	Jinx1()
	{
		Health = 15;
		Attack = 3;
		Defense = 1;
		AttackDistance = 0;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("004.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Jinx1::create();
	}
};
class Gwen1 :public Champion
{
public:
	Gwen1()
	{
		Health = 20;
		Attack = 2;
		Defense = 3;
		AttackDistance = 1;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if(canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentDefense = currentDefense * 3;
			}
			else
			{
				currentDefense = Defense;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("005.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Gwen1::create();
	}
};
class Neeko1 :public Champion
{
public:
	Neeko1()
	{
		Health = 25;
		Attack = 2;
		Defense = 2;
		AttackDistance = 1;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 10 <= Health ? currentHealth = currentHealth + 10 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("006.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Neeko1::create();
	}
};
class Zeri1 :public Champion
{
public:
	Zeri1()
	{
		Health = 15;
		Attack = 4;
		Defense = 2;
		AttackDistance = 0;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 3;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("007.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Zeri1::create();
	}
};
class Fiora1 :public Champion
{
public:
	Fiora1()
	{
		Health = 20;
		Attack = 4;
		Defense = 2;
		AttackDistance = 1;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 3;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("008.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Fiora1::create();
	}
};
class Morde1 :public Champion
{
public:
	Morde1()
	{
		Health = 25;
		Attack = 3;
		Defense = 3;
		AttackDistance = 1;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 15 <= Health ? currentHealth = currentHealth + 15 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("009.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Morde1::create();
	}
};
class Akali1 :public Champion
{
public:
	Akali1()
	{
		Health = 20;
		Attack = 5;
		Defense = 2;
		AttackDistance = 1;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 4;
				if (currentHealth + 10 >= Health)
					currentHealth = Health;
				else
					currentHealth += 10;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("010.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Akali1::create();
	}
};
class Thresh1 :public Champion
{
public:
	Thresh1()
	{
		Health = 15;
		Attack = 4;
		Defense = 2;
		AttackDistance = 0;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentAttack = currentAttack * 6;
		}
		else
		{
			currentAttack = Attack;
			Mana++;
		}
		float ManaScale = Mana / MAX_MANA;
		ManaBar->setScaleX(ManaScale);
		return currentAttack;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("011.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Thresh1::create();
	}
};
class Viego1 :public Champion
{
public:
	Viego1()
	{
		Health = 25;
		Attack = 4;
		Defense = 2;
		AttackDistance = 1;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 4;
				currentDefense = currentDefense * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("012.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Viego1::create();
	}
};
class Aatrox1 :public Champion
{
public:
	Aatrox1()
	{
		Health = 25;
		Attack = 6;
		Defense = 3;
		AttackDistance = 1;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack()) {
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 10;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("013.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Aatrox1::create();
	}
};
class Zoe1 :public Champion
{
public:
	Zoe1()
	{
		Health = 20;
		Attack = 7;
		Defense = 2;
		AttackDistance = 0;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 10;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("014.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Zoe1::create();
	}
};
class Panth1 :public Champion
{
public:
	Panth1()
	{
		Health = 30;
		Attack = 6;
		Defense = 4;
		AttackDistance = 1;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentDefense = currentDefense * 4;
				if (currentHealth + 20 >= Health)
					currentHealth = Health;
				else
					currentHealth += 20;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("015.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Panth1::create();
	}
};
class Annie2 :public Champion
{
public:
	Annie2()
	{
		Health = 25;
		Attack = 6;
		Defense = 2;
		AttackDistance = 0;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("016.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Annie2::create();
	}
};
class Garen2 :public Champion
{
public:
	Garen2()
	{
		Health = 55;
		Attack = 5;
		Defense = 5;
		AttackDistance = 1;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 20 <= Health ? currentHealth = currentHealth + 20 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("017.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Garen2::create();
	}
};
class Yasuo2 :public Champion
{
public:
	Yasuo2()
	{
		Health = 40;
		Attack = 6;
		Defense = 4;
		AttackDistance = 1;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("018.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Yasuo2::create();
	}
};
class Jinx2 :public Champion
{
public:
	Jinx2()
	{
		Health = 30;
		Attack = 7;
		Defense = 2;
		AttackDistance = 0;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("019.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Jinx2::create();
	}
};
class Gwen2 :public Champion
{
public:
	Gwen2()
	{
		Health = 45;
		Attack = 6;
		Defense = 5;
		AttackDistance = 1;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentDefense = currentDefense * 3;
			}
			else
			{
				currentDefense = Defense;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("020.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Gwen2::create();
	}
};
class Neeko2 :public Champion
{
public:
	Neeko2()
	{
		Health = 60;
		Attack = 6;
		Defense = 5;
		AttackDistance = 1;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 20 <= Health ? currentHealth = currentHealth + 20 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("021.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Neeko2::create();
	}
};
class Zeri2 :public Champion
{
public:
	Zeri2()
	{
		Health = 40;
		Attack = 7;
		Defense = 4;
		AttackDistance = 0;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 3;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("022.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Zeri2::create();
	}
};
class Fiora2 :public Champion
{
public:
	Fiora2()
	{
		Health = 45;
		Attack = 7;
		Defense = 4;
		AttackDistance = 1;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 3;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("023.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Fiora2::create();
	}
};
class Morde2 :public Champion
{
public:
	Morde2()
	{
		Health = 60;
		Attack = 5;
		Defense = 6;
		AttackDistance = 1;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 25 <= Health ? currentHealth = currentHealth + 25 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("024.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Morde2::create();
	}
};
class Akali2 :public Champion
{
public:
	Akali2()
	{
		Health = 50;
		Attack = 10;
		Defense = 4;
		AttackDistance = 1;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 4;
				if (currentHealth + 25 >= Health)
					currentHealth = Health;
				else
					currentHealth += 25;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("025.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Akali2::create();
	}
};
class Thresh2 :public Champion
{
public:
	Thresh2()
	{
		Health = 30;
		Attack = 9;
		Defense = 4;
		AttackDistance = 0;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 6;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("026.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Thresh2::create();
	}
};
class Viego2 :public Champion
{
public:
	Viego2()
	{
		Health = 60;
		Attack = 9;
		Defense = 5;
		AttackDistance = 1;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 4;
				currentDefense = currentDefense * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("027.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Viego2::create();
	}
};
class Aatrox2 :public Champion
{
public:
	Aatrox2()
	{
		Health = 60;
		Attack = 13;
		Defense = 7;
		AttackDistance = 1;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 10;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("028.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Aatrox2::create();
	}
};
class Zoe2 :public Champion
{
public:
	Zoe2()
	{
		Health = 45;
		Attack = 14;
		Defense = 5;
		AttackDistance = 0;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 10;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("029.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Zoe2::create();
	}
};
class Panth2 :public Champion
{
public:
	Panth2()
	{
		Health = 65;
		Attack = 12;
		Defense = 8;
		AttackDistance = 1;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentDefense = currentDefense * 4;
				if (currentHealth + 45 >= Health)
					currentHealth = Health;
				else
					currentHealth += 45;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("030.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Panth2::create();
	}
};
class Annie3 :public Champion
{
public:
	Annie3()
	{
		Health = 50;
		Attack = 10;
		Defense = 3;
		AttackDistance = 0;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("031.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Annie3::create();
	}
};
class Garen3 :public Champion
{
public:
	Garen3()
	{
		Health = 80;
		Attack = 8;
		Defense = 7;
		AttackDistance = 1;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 50 <= Health ? currentHealth = currentHealth + 50 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("032.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Garen3::create();
	}
};
class Yasuo3 :public Champion
{
public:
	Yasuo3()
	{
		Health = 65;
		Attack = 10;
		Defense = 6;
		AttackDistance = 1;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("033.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Yasuo3::create();
	}
};
class Jinx3 :public Champion
{
public:
	Jinx3()
	{
		Health = 55;
		Attack = 11;
		Defense = 4;
		AttackDistance = 0;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("034.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Jinx3::create();
	}
};
class Gwen3 :public Champion
{
public:
	Gwen3()
	{
		Health = 70;
		Attack = 9;
		Defense = 8;
		AttackDistance = 1;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentDefense = currentDefense * 3;
			}
			else
			{
				currentDefense = Defense;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("035.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Gwen3::create();
	}
};
class Neeko3 :public Champion
{
public:
	Neeko3()
	{
		Health = 85;
		Attack = 8;
		Defense = 7;
		AttackDistance = 1;
		cost = 2;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 50 <= Health ? currentHealth = currentHealth + 50 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("036.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Neeko3::create();
	}
};
class Zeri3 :public Champion
{
public:
	Zeri3()
	{
		Health = 60;
		Attack = 13;
		Defense = 4;
		AttackDistance = 0;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 3;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("037.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Zeri3::create();
	}
};
class Fiora3 :public Champion
{
public:
	Fiora3()
	{
		Health = 70;
		Attack = 12;
		Defense = 6;
		AttackDistance = 1;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 3;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("038.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Fiora3::create();
	}
};
class Morde3 :public Champion
{
public:
	Morde3()
	{
		Health = 90;
		Attack = 8;
		Defense = 9;
		AttackDistance = 1;
		cost = 3;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}

	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentHealth + 60 <= Health ? currentHealth = currentHealth + 60 : currentHealth = Health;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}

	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}

	bool Death()
	{
		return(currentHealth <= 0);
	}

	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("039.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Morde3::create();
	}
};
class Akali3 :public Champion
{
public:
	Akali3()
	{
		Health = 80;
		Attack = 18;
		Defense = 7;
		AttackDistance = 1;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 4;
				if (currentHealth + 40 >= Health)
					currentHealth = Health;
				else
					currentHealth += 40;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("040.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Akali3::create();
	}
};
class Thresh3 :public Champion
{
public:
	Thresh3()
	{
		Health = 65;
		Attack = 16;
		Defense = 5;
		AttackDistance = 0;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 6;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("041.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Thresh3::create();
	}
};
class Viego3 :public Champion
{
public:
	Viego3()
	{
		Health = 90;
		Attack = 17;
		Defense = 7;
		AttackDistance = 1;
		cost = 4;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 4;
				currentDefense = currentDefense * 2;
			}
			else
			{
				currentAttack = Attack;
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("042.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Viego3::create();
	}
};
class Aatrox3 :public Champion
{
public:
	Aatrox3()
	{
		Health = 95;
		Attack = 22;
		Defense = 10;
		AttackDistance = 1;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 10;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("043.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Aatrox3::create();
	}
};
class Zoe3 :public Champion
{
public:
	Zoe3()
	{
		Health = 100;
		Attack = 20;
		Defense = 12;
		AttackDistance = 0;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentAttack = currentAttack * 10;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("044.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Zoe3::create();
	}
};
class Panth3 :public Champion
{
public:
	Panth3()
	{
		Health = 100;
		Attack = 20;
		Defense = 12;
		AttackDistance = 1;
		cost = 5;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int AttackDamage()
	{
		if (canAttack())
		{
			if (Mana >= MAX_MANA)
			{
				Mana = 0;
				currentDefense = currentDefense * 4;
				if (currentHealth + 70 >= Health)
					currentHealth = Health;
				else
					currentHealth += 70;
			}
			else
			{
				Mana++;
			}
			float ManaScale = Mana / MAX_MANA;
			ManaBar->setScaleX(ManaScale);
			startAttackTimer();  // 开始攻击计时器
			return currentAttack;
		}
		return 0;
	}
	void GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
		float HealthScale = currentHealth / Health;
		ManaBar->setScaleX(HealthScale);
	}
	bool Death()
	{
		return(currentHealth <= 0);
	}
	void TurnStart()
	{
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
	}
	int getHealth()
	{
		return currentHealth;
	}

	int getMana()
	{
		return Mana;
	}
	auto create1(Scene* scene, int x, int y)
	{
		ChampionHero = Sprite::create("045.png");
		Bar1 = Sprite::create("bar.png");
		Bar2 = Sprite::create("bar.png");
		HealthBar = Sprite::create("health.png");
		ManaBar = Sprite::create("mana.png");
		ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
		Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
		HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
		scene->addChild(ChampionHero, 2);
		scene->addChild(Bar1, 2);
		scene->addChild(Bar2, 2);
		scene->addChild(HealthBar, 3);
		scene->addChild(ManaBar, 3);


		return Panth3::create();
	}
};

auto switchCreate(int ChampionID, Scene* scene, int x, int y)
{
	switch (ChampionID)
	{
		case 1:
		{
			Annie1 annie1Instance;
			return annie1Instance.create1(scene, x, y);
			break;
		}
		case 2:
		{
			Garen1 garen1Instance;
			return garen1Instance.create1(scene, x, y);
			break;
		}
		case 3:
		{
			Yasuo1 yasuo1Instance;
			return yasuo1Instance.create1(scene, x, y);
			break;
		}
		case 4:
		{
			Jinx1 jinx1Instance;
			return jinx1Instance.create1(scene, x, y);
			break;
		}
		case 5:
		{
			Gwen1 gwen1Instance;
			return gwen1Instance.create1(scene, x, y);
			break;
		}
		case 6:
		{
			Neeko1 neeko1Instance;
			return neeko1Instance.create1(scene, x, y);
			break;
		}
		case 7:
		{
			Zeri1 zeri1Instance;
			return zeri1Instance.create1(scene, x, y);
			break;
		}
		case 8:
		{
			Fiora1 fiora1Instance;
			return fiora1Instance.create1(scene, x, y);
			break;
		}
		case 9:
		{
			Morde1 morde1Instance;
			return morde1Instance.create1(scene, x, y);
			break;
		}
		case 10:
		{
			Akali1 akali1Instance;
			return akali1Instance.create1(scene, x, y);
			break;
		}
		case 11:
		{
			Thresh1 thresh1Instance;
			return thresh1Instance.create1(scene, x, y);
			break;
		}
		case 12:
		{
			Viego1 viego1Instance;
			return viego1Instance.create1(scene, x, y);
			break;
		}
		case 13:
		{
			Aatrox1 aatrox1Instance;
			return aatrox1Instance.create1(scene, x, y);
			break;
		}
		case 14:
		{
			Zoe1 zoe1Instance;
			return zoe1Instance.create1(scene, x, y);
			break;
		}
		case 15:
		{
			Panth1 panth1Instance;
			return panth1Instance.create1(scene, x, y);
			break;
		}
		case 16:
		{
			Annie2 annie2Instance;
			return annie2Instance.create1(scene, x, y);
			break;
		}
		case 17:
		{
			Garen2 garen2Instance;
			return garen2Instance.create1(scene, x, y);
			break;
		}
		case 18:
		{
			Yasuo2 yasuo2Instance;
			return yasuo2Instance.create1(scene, x, y);
			break;
		}
		case 19:
		{
			Jinx2 jinx2Instance;
			return jinx2Instance.create1(scene, x, y);
			break;
		}
		case 20:
		{
			Gwen2 gwen2Instance;
			return gwen2Instance.create1(scene, x, y);
			break;
		}
		case 21:
		{
			Neeko2 neeko2Instance;
			return neeko2Instance.create1(scene, x, y);
			break;
		}
		case 22:
		{
			Zeri2 zeri2Instance;
			return zeri2Instance.create1(scene, x, y);
			break;
		}
		case 23:
		{
			Fiora2 fiora2Instance;
			return fiora2Instance.create1(scene, x, y);
			break;
		}
		case 24:
		{
			Morde2 morde2Instance;
			return morde2Instance.create1(scene, x, y);
			break;
		}
		case 25:
		{
			Akali2 akali2Instance;
			return akali2Instance.create1(scene, x, y);
			break;
		}
		case 26:
		{
			Thresh2 thresh2Instance;
			return thresh2Instance.create1(scene, x, y);
			break;
		}
		case 27:
		{
			Viego2 viego2Instance;
			return viego2Instance.create1(scene, x, y);
			break;
		}
		case 28:
		{
			Aatrox2 aatrox2Instance;
			return aatrox2Instance.create1(scene, x, y);
			break;
		}
		case 29:
		{
			Zoe2 zoe2Instance;
			return zoe2Instance.create1(scene, x, y);
			break;
		}
		case 30:
		{
			Panth2 panth2Instance;
			return panth2Instance.create1(scene, x, y);
			break;
		}
		case 31:
		{
			Annie3 annie3Instance;
			return annie3Instance.create1(scene, x, y);
			break;
		}
		case 32:
		{
			Garen3 garen3Instance;
			return garen3Instance.create1(scene, x, y);
			break;
		}
		case 33:
		{
			Yasuo3 yasuo3Instance;
			return yasuo3Instance.create1(scene, x, y);
			break;
		}
		case 34:
		{
			Jinx3 jinx3Instance;
			return jinx3Instance.create1(scene, x, y);
			break;
		}
		case 35:
		{
			Gwen3 gwen3Instance;
			return gwen3Instance.create1(scene, x, y);
			break;
		}
		case 36:
		{
			Neeko3 neeko3Instance;
			return neeko3Instance.create1(scene, x, y);
			break;
		}
		case 37:
		{
			Zeri3 zeri3Instance;
			return zeri3Instance.create1(scene, x, y);
			break;
		}
		case 38:
		{
			Fiora3 fiora3Instance;
			return fiora3Instance.create1(scene, x, y);
			break;
		}
		case 39:
		{
			Morde3 morde3Instance;
			return morde3Instance.create1(scene, x, y);
			break;
		}
		case 40:
		{
			Akali3 akali3Instance;
			return akali3Instance.create1(scene, x, y);
			break;
		}
		case 41:
		{
			Thresh3 thresh3Instance;
			return thresh3Instance.create1(scene, x, y);
			break;
		}
		case 42:
		{
			Viego3 viego3Instance;
			return viego3Instance.create1(scene, x, y);
			break;
		}
		case 43:
		{
			Aatrox3 aatrox3Instance;
			return aatrox3Instance.create1(scene, x, y);
			break;
		}
		case 44:
		{
			Zoe3 zoe3Instance;
			return zoe3Instance.create1(scene, x, y);
			break;
		}
		case 45:
		{
			Panth3 panth3Instance;
			return panth3Instance.create1(scene, x, y);
			break;
		}
		default:
			break;

	}

}



