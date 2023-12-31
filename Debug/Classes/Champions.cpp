#include"Champions.h"
#include<iostream>
USING_NS_CC;

float Champion::getHealth() { return Health; }
float Champion::getcurrentHealth() { return currentHealth; }



void Champion::GetDamage(float atk)
{
	int dmg = 0;
	atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
	currentHealth = currentHealth - dmg;
	float HealthScale = currentHealth / Health;
	HealthBar->setScaleX(HealthScale);
	HealthLabel->setString(StringUtils::format("%d/%d", int(currentHealth), int(Health)));
}

bool Champion::Death()
{
	return(currentHealth <= 0);
}

Vec2  Champion::getPosition()
{
	return ChampionHero->getPosition();
}
void Champion::removeChild(Scene* scene)
{
	scene->removeChild(ChampionHero);
	scene->removeChild(Bar1);
	scene->removeChild(Bar2);
	scene->removeChild(ManaBar);
	scene->removeChild(HealthBar);
	scene->removeChild(HealthLabel);


}
void Champion::setPosition(Vec2 vec2)
{
	HealthBar->setAnchorPoint(Vec2(0, 0));
	ManaBar->setAnchorPoint(Vec2(0, 0));
	ChampionHero->setPosition(vec2);
	Bar1->setPosition(Vec2(vec2.x, vec2.y + 33));
	Bar2->setPosition(Vec2(vec2.x, vec2.y + 35));
	ManaBar->setPosition(Vec2(vec2.x - 32, vec2.y + 32));
	HealthBar->setPosition(Vec2(vec2.x - 32, vec2.y + 34));
	HealthLabel->setPosition(Vec2(vec2.x - 32, vec2.y + 35));


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

void Champion::playMeleeAttackAnimation(Scene* scene)
{
	// 获取当前对象的位置
	auto actionAnime = Sprite::create();
	Vec2 vec2 = ChampionHero->getPosition();
	actionAnime->setPosition(vec2);
	scene->addChild(actionAnime, 4);

	// 创建动画
	auto meleeAttackAnimation = Animation::create();
	meleeAttackAnimation->setDelayPerUnit(0.08f);

	meleeAttackAnimation->addSpriteFrameWithFile("attack01.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack02.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack03.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack04.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack05.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack06.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack07.png");
	meleeAttackAnimation->addSpriteFrameWithFile("attack08.png");

	auto meleeAttackAction = Animate::create(meleeAttackAnimation);
	auto removeAction = RemoveSelf::create();
	actionAnime->runAction(Sequence::create(meleeAttackAction, removeAction, nullptr));


}
float Champion::AttackDamage()
{
	if (Mana >= MAX_MANA)
	{
		Mana = 0;
		skill();
	}
	else
	{
		Mana++;
		reset_skill();
	}
	float ManaScale = Mana / MAX_MANA;
	ManaBar->setScaleX(ManaScale);
	return currentAttack;
	return 0;
}


Sprite* Champion::create1(Scene* scene, int x, int y)
{
	ChampionHero = Sprite::create(FileName);
	Bar1 = Sprite::create("bar.png");
	Bar2 = Sprite::create("bar.png");
	HealthBar = Sprite::create("health.png");
	ManaBar = Sprite::create("mana.png");
	HealthLabel = Label::createWithSystemFont("", "Health", 10);
	ChampionHero->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 3) + 32));
	Bar1->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
	Bar2->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
	ManaBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 1));
	HealthBar->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 3));
	HealthLabel->setPosition(Vec2(64 * (x + 5) + 32, 64 * (y + 4) + 4));
	scene->addChild(ChampionHero, 2);
	scene->addChild(Bar1, 2);
	scene->addChild(Bar2, 2);
	scene->addChild(HealthBar, 3);
	scene->addChild(ManaBar, 3);
	scene->addChild(HealthLabel, 4);


	return create();
}




void Champion::playRangedAttackAnimation(Scene* scene, const Vec2& targetPos)
{
	// 创建法球精灵
	auto projectile = Sprite::create("attack5.png");
	Vec2 vec2 = ChampionHero->getPosition();
	projectile->setPosition(vec2);
	scene->addChild(projectile, 4);

	// 计算飞行时间
	float distance = vec2.distance(targetPos);
	float duration = 0.5f;

	// 创建飞行动作
	auto moveAction = MoveTo::create(duration, targetPos);

	// 创建完成后移除法球的动作
	auto removeAction = RemoveSelf::create();

	// 创建动作序列
	auto projectileAction = Sequence::create(moveAction, removeAction, nullptr);
	int audioId = cocos2d::AudioEngine::play2d("far.wav");
	// 运行动作
	projectile->runAction(projectileAction);
}

void Champion::playHitAnimation()//调用受击动画时，要用aimIt->ChampionHero->playHitAnimation()才行（之前不行就是函数设计和调用不一致）
{
	// 创建受击动画
	auto hitAction = Sequence::create(
		// 变红效果
		TintTo::create(0.1f, 255, 0, 0),  // 变红
		DelayTime::create(0.3f),           // 保持红色状态0.25秒
		TintTo::create(0.1f, 255, 255, 255),  // 恢复原色
		nullptr
	);

	// 播放动画
	this->ChampionHero->runAction(hitAction);
}
class Annie1 :public Champion
{
public:
	Annie1()
	{
		Health = 10;
		Attack = 3;
		Defense = 1;
		AttackDistance = 0;
		cost = 1;
		currentHealth = Health;
		currentAttack = Attack;
		currentDefense = Defense;
		Mana = 0;
		FileName = "001.png";
	}
	void skill() {

		currentAttack = currentAttack * 2;
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
		FileName = "002.png";
	}
	void skill() {

		float cure = 0.3 * Health;
		currentHealth + cure <= Health ? currentHealth = currentHealth + cure : currentHealth = Health;
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
		FileName = "003.png";
	}
	void skill() {
		currentAttack = currentAttack * 2;
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
		FileName = "004.png";
	}
	void skill() {
		currentAttack = currentAttack * 2;
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
		FileName = "005.png";
	}
	void skill() {
		currentDefense = currentDefense * 3;
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
		FileName = "006.png";
	}
	void skill() {
		float cure = 0.3 * Health;
		currentHealth + cure <= Health ? currentHealth = currentHealth + cure : currentHealth = Health;
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
		FileName = "007.png";
	}
	void skill() {
		currentAttack = currentAttack * 3;
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
		FileName = "008.png";
	}
	void skill() {
		currentAttack = currentAttack * 3;
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
		FileName = "009.png";
	}
	void skill() {
		float cure = 0.3 * Health;
		currentHealth + cure <= Health ? currentHealth = currentHealth + cure : currentHealth = Health;
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
		FileName = "010.png";
	}
	void skill() {
		currentAttack = currentAttack * 4;
		float cure = 0.3 * Health;
		currentHealth + cure <= Health ? currentHealth = currentHealth + cure : currentHealth = Health;
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
		FileName = "011.png";
	}
	void skill() {
		currentAttack = currentAttack * 6;
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
		FileName = "012.png";
	}
	void skill() {
		currentAttack = currentAttack * 4;
		currentDefense = currentDefense * 2;
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
		FileName = "013.png";
	}
	void skill() {
		currentAttack = currentAttack * 10;
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
		FileName = "014.png";
	}
	void skill() {
		currentAttack = currentAttack * 10;
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
		FileName = "015.png";
	}
	void skill() {
		currentDefense = currentDefense * 4;
		float cure = 0.4 * Health;
		currentHealth + cure <= Health ? currentHealth = currentHealth + cure : currentHealth = Health;
	}
};
class Annie2 :public Annie1
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
		FileName = "016.png";
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
		FileName = "017.png";
	}
	void skill() {
		float cure = 0.3 * Health;
		currentHealth + cure <= Health ? currentHealth = currentHealth + cure : currentHealth = Health;
	}

};
class Yasuo2 :public Yasuo1
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
		FileName = "018.png";
	}


};
class Jinx2 :public Jinx1
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
		FileName = "019.png";
	}


};
class Gwen2 :public Gwen1
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

		FileName = "020.png";
	}


};
class Neeko2 :public Neeko1
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
		FileName = "021.png";
	}
};
class Zeri2 :public Zeri1
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
		FileName = "022.png";
	}


};
class Fiora2 :public Fiora1
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

		FileName = "023.png";
	}

};
class Morde2 :public Morde1
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
		FileName = "024.png";
	}
};
class Akali2 :public Akali1
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
		FileName = "025.png";
	}

};
class Thresh2 :public Thresh1
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
		FileName = "026.png";
	}

};
class Viego2 :public Viego1
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
		FileName = "027.png";
	}

};
class Aatrox2 :public Aatrox1
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
		FileName = "028.png";
	}
};
class Zoe2 :public Zoe1
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
		FileName = "029.png";
	}
};
class Panth2 :public Panth1
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
		FileName = "030.png";
	}

};
class Annie3 :public Annie1
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
		FileName = "031.png";
	}


};
class Garen3 :public Garen1
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
		FileName = "032.png";
	}


};
class Yasuo3 :public Yasuo1
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
		FileName = "033.png";
	}

};
class Jinx3 :public Jinx1
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
		FileName = "034.png";
	}

};
class Gwen3 :public Gwen1
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
		FileName = "035.png";
	}
};
class Neeko3 :public Neeko1
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
		FileName = "036.png";
	}


};
class Zeri3 :public Zeri1
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
		FileName = "037.png";
	}

};
class Fiora3 :public Fiora1
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
		FileName = "038.png";
	}

};
class Morde3 :public Morde1
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
		FileName = "039.png";
	}

};
class Akali3 :public Akali1
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
		FileName = "040.png";
	}

};
class Thresh3 :public Thresh1
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
		FileName = "041.png";
	}

};
class Viego3 :public Viego1
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
		FileName = "042.png";
	}
};
class Aatrox3 :public Aatrox1
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
		FileName = "043.png";
	}
};
class Zoe3 :public Zoe1
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
		FileName = "044.png";
	}
};
class Panth3 :public Panth1
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
		FileName = "045.png";
	}

};

Champion* switchCreate(int ChampionID, Scene* scene, int x, int y)
{
	switch (ChampionID)
	{
	case 1:
	{
		Annie1* annie1Instance = new Annie1();
		annie1Instance->create1(scene, x, y);
		return annie1Instance;
	}
	case 2:
	{
		Garen1* garen1Instance = new Garen1();
		garen1Instance->create1(scene, x, y);
		return garen1Instance;
	}
	case 3:
	{
		Yasuo1* yasuo1Instance = new Yasuo1();
		yasuo1Instance->create1(scene, x, y);
		return yasuo1Instance;
	}
	case 4:
	{
		Jinx1* jinx1Instance = new Jinx1();
		jinx1Instance->create1(scene, x, y);
		return jinx1Instance;
	}
	case 5:
	{
		Gwen1* gwen1Instance = new Gwen1();
		gwen1Instance->create1(scene, x, y);
		return gwen1Instance;
	}
	case 6:
	{
		Neeko1* neeko1Instance = new Neeko1();
		neeko1Instance->create1(scene, x, y);
		return neeko1Instance;
	}
	case 7:
	{
		Zeri1* zeri1Instance = new Zeri1();
		zeri1Instance->create1(scene, x, y);
		return zeri1Instance;
	}
	case 8:
	{
		Fiora1* fiora1Instance = new Fiora1();
		fiora1Instance->create1(scene, x, y);
		return fiora1Instance;
	}
	case 9:
	{
		Morde1* morde1Instance = new Morde1();
		morde1Instance->create1(scene, x, y);
		return morde1Instance;
	}
	case 10:
	{
		Akali1* akali1Instance = new Akali1();
		akali1Instance->create1(scene, x, y);
		return akali1Instance;
	}
	case 11:
	{
		Thresh1* thresh1Instance = new Thresh1();
		thresh1Instance->create1(scene, x, y);
		return thresh1Instance;
	}
	case 12:
	{
		Viego1* viego1Instance = new Viego1();
		viego1Instance->create1(scene, x, y);
		return viego1Instance;
	}
	case 13:
	{
		Aatrox1* aatrox1Instance = new Aatrox1();
		aatrox1Instance->create1(scene, x, y);
		return aatrox1Instance;
	}
	case 14:
	{
		Zoe1* zoe1Instance = new Zoe1();
		zoe1Instance->create1(scene, x, y);
		return zoe1Instance;
	}
	case 15:
	{
		Panth1* panth1Instance = new Panth1();
		panth1Instance->create1(scene, x, y);
		return panth1Instance;
	}
	case 16:
	{
		Annie2* annie2Instance = new Annie2();
		annie2Instance->create1(scene, x, y);
		return annie2Instance;
	}
	case 17:
	{
		Garen2* garen2Instance = new Garen2();
		garen2Instance->create1(scene, x, y);
		return garen2Instance;
	}
	case 18:
	{
		Yasuo2* yasuo2Instance = new Yasuo2();
		yasuo2Instance->create1(scene, x, y);
		return yasuo2Instance;
	}
	case 19:
	{
		Jinx2* jinx2Instance = new Jinx2();
		jinx2Instance->create1(scene, x, y);
		return jinx2Instance;
	}
	case 20:
	{
		Gwen2* gwen2Instance = new Gwen2();
		gwen2Instance->create1(scene, x, y);
		return gwen2Instance;
	}
	case 21:
	{
		Neeko2* neeko2Instance = new Neeko2();
		neeko2Instance->create1(scene, x, y);
		return neeko2Instance;
	}
	case 22:
	{
		Zeri2* zeri2Instance = new Zeri2();
		zeri2Instance->create1(scene, x, y);
		return zeri2Instance;
	}
	case 23:
	{
		Fiora2* fiora2Instance = new Fiora2();
		fiora2Instance->create1(scene, x, y);
		return fiora2Instance;
	}
	case 24:
	{
		Morde2* morde2Instance = new Morde2();
		morde2Instance->create1(scene, x, y);
		return morde2Instance;
	}
	case 25:
	{
		Akali2* akali2Instance = new Akali2();
		akali2Instance->create1(scene, x, y);
		return akali2Instance;
	}
	case 26:
	{
		Thresh2* thresh2Instance = new Thresh2();
		thresh2Instance->create1(scene, x, y);
		return thresh2Instance;
	}
	case 27:
	{
		Viego2* viego2Instance = new Viego2();
		viego2Instance->create1(scene, x, y);
		return viego2Instance;
	}
	case 28:
	{
		Aatrox2* aatrox2Instance = new Aatrox2();
		aatrox2Instance->create1(scene, x, y);
		return aatrox2Instance;
	}
	case 29:
	{
		Zoe2* zoe2Instance = new Zoe2();
		zoe2Instance->create1(scene, x, y);
		return zoe2Instance;
	}
	case 30:
	{
		Panth2* panth2Instance = new Panth2();
		panth2Instance->create1(scene, x, y);
		return panth2Instance;
	}
	case 31:
	{
		Annie3* annie3Instance = new Annie3();
		annie3Instance->create1(scene, x, y);
		return annie3Instance;
	}
	case 32:
	{
		Garen3* garen3Instance = new Garen3();
		garen3Instance->create1(scene, x, y);
		return garen3Instance;
	}
	case 33:
	{
		Yasuo3* yasuo3Instance = new Yasuo3();
		yasuo3Instance->create1(scene, x, y);
		return yasuo3Instance;
	}
	case 34:
	{
		Jinx3* jinx3Instance = new Jinx3();
		jinx3Instance->create1(scene, x, y);
		return jinx3Instance;
	}
	case 35:
	{
		Gwen3* gwen3Instance = new Gwen3();
		gwen3Instance->create1(scene, x, y);
		return gwen3Instance;
	}
	case 36:
	{
		Neeko3* neeko3Instance = new Neeko3();
		neeko3Instance->create1(scene, x, y);
		return neeko3Instance;
	}
	case 37:
	{
		Zeri3* zeri3Instance = new Zeri3();
		zeri3Instance->create1(scene, x, y);
		return zeri3Instance;
	}
	case 38:
	{
		Fiora3* fiora3Instance = new Fiora3();
		fiora3Instance->create1(scene, x, y);
		return fiora3Instance;
	}
	case 39:
	{
		Morde3* morde3Instance = new Morde3();
		morde3Instance->create1(scene, x, y);
		return morde3Instance;
	}
	case 40:
	{
		Akali3* akali3Instance = new Akali3();
		akali3Instance->create1(scene, x, y);
		return akali3Instance;
	}
	case 41:
	{
		Thresh3* thresh3Instance = new Thresh3();
		thresh3Instance->create1(scene, x, y);
		return thresh3Instance;
	}
	case 42:
	{
		Viego3* viego3Instance = new Viego3();
		viego3Instance->create1(scene, x, y);
		return viego3Instance;
	}
	case 43:
	{
		Aatrox3* aatrox3Instance = new Aatrox3();
		aatrox3Instance->create1(scene, x, y);
		return aatrox3Instance;
	}
	case 44:
	{
		Zoe3* zoe3Instance = new Zoe3();
		zoe3Instance->create1(scene, x, y);
		return zoe3Instance;
	}
	case 45:
	{
		Panth3* panth3Instance = new Panth3();
		panth3Instance->create1(scene, x, y);
		return panth3Instance;
	}




	default:
		break;

	}
	return NULL;
}