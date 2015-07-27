#pragma once
#include <HAPI_lib.h>
#include "enitityboss.h"
class CBossGun :
	public CEnitityBoss
{
public:
	CBossGun(void);//constructor
	~CBossGun(void);//destructor
	void update();
private:
	//both used for firing missiles*/
	int lastshot;
	int currenttime;
};

