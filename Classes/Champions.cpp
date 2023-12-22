#include"Champions.h"
#include<iostream>
using namespace std;




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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth+10 <=Health? currentHealth= currentHealth + 10: currentHealth =Health;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 20 <= Health ? currentHealth = currentHealth + 20 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 50 <= Health ? currentHealth = currentHealth + 50 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 10 <= Health ? currentHealth = currentHealth + 10 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 20 <= Health ? currentHealth = currentHealth + 20 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 50 <= Health ? currentHealth = currentHealth + 50 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 15 <= Health ? currentHealth = currentHealth + 15 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 25 <= Health ? currentHealth = currentHealth + 25 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentHealth + 60 <= Health ? currentHealth = currentHealth + 60 : currentHealth = Health;
		}
		else
		{
			Mana++;
		}
	}

	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentAttack = currentAttack * 10;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentAttack = currentAttack * 10;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentAttack = currentAttack * 10;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentAttack = currentAttack * 10;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentAttack = currentAttack * 10;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		if (Mana >= MAX_MANA)
		{
			Mana = 0;
			currentAttack = currentAttack * 10;
		}
		else
		{
			Mana++;
		}
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
		return currentAttack;
	}
	int GetDamage(int atk)
	{
		int dmg = 0;
		atk - currentDefense >= 1 ? dmg = atk - currentDefense : dmg = 1;
		currentHealth = currentHealth - dmg;
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
};




