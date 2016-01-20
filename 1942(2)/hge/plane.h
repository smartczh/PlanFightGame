//飞机类
#pragma once
#include "Picture.h"
#include "bullet.h"
#include "const data.h"
#include "sound.h"
#include <math.h>

class Logic;

class Plane{
public:
	Plane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int _blood);
	//参数：p为飞机主体的图像，b为飞机子弹的图像，a为飞机被破坏时的爆炸动画，po为飞机的初始位置，x,y分别代表飞机的水平竖直速度，_blood为飞机的血量
	virtual void draw(float rot=0);
	virtual bool hit(Position p,float w,float h,float protect=0);//判断与在坐标P处长宽分别为h,w的目标是否相撞，portect为保护程度，值越大碰撞范围越小，默认为0则为不保护
	virtual bool destroy();//判断是否摧毁
	void set_pos(Position p);//设置飞机坐标
	Position getpos()const{return pos;};//获得飞机坐标
	float getwidth()const{return body->texwidth;};//获得飞机宽度
	float getheight()const{return body->texheight;};//获得飞机长度
	void load_dead_sound(Sound*);//加载飞机被击毁时的音效
protected:
	Picture* body;//飞机图像
	Picture* bul;//飞机子弹图像
    float xspeed;//飞机水平速度
	float yspeed;//飞机竖直速度
    Position pos;//飞机所处坐标
	int blood;//血量
	Sound* boom;//飞机爆炸音效
	Animation* explode;//飞机爆炸动画
private:
};

class MePlane :public Plane{
friend class Logic;
public:
	MePlane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int _blood=5,int _life=3);//比父类多了一个_life，它代表飞机的生命数量
	virtual void draw(float rot=0,float dt = 0);
	Bullet** create_bullet(float xspeed,float yspeed);//用于产生如参数所要求的速度的子弹，由于可能产生多个子弹，而子弹都是new所产生的，所以返回一个指向子弹指针的数组头元素
	TrackBullet** create_track_bullet(int);
	void add_power(int);//增加飞机火力
	void add_bigshot(int);//增加大招数量
	void load_track_bullet(Picture*);//加载跟踪弹模型
	void load_fire_sound(Sound*);//加载开火音效
	virtual bool destroy();
	void clear();
	bool is_hit;
	bool super;
private:
	int life;//生命数量
	int power;//子弹火力值
	int bigshot;//飞机的大招
	Picture* track_bullet;//跟踪弹
	Sound* fire;//子弹射出的声音
};

class EnemyPlane :public Plane{
friend class Logic;
public:
	EnemyPlane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):Plane(p,b,a,po,x,y,bl){};
	virtual void draw(float rot=0);
	virtual void move(Position p,float dt);//每种enemyplane的移动方式不同，所以设为虚函数，父类默认朝向p坐标移动，dt用于计算飞机坐标
	virtual bool destroy();
	virtual Bullet** create_bullet(int time){return NULL;};//敌机按时间自动产生子弹，父类默认不产生子弹
	virtual Bullet* create_bullet(float xspeed,float yspeed);//产生指定要求的子弹
protected:
	int type;//敌机种类
private:
};

class EnemyPlane1 :public EnemyPlane{//一种只会朝主机的方向飞行，不发射子弹的飞机
public:
	EnemyPlane1(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl);
	EnemyPlane1(EnemyPlane& temp):EnemyPlane(temp),angle(0){};
	virtual void draw(float rot=0);
	virtual void move(Position,float);
	virtual Bullet* create_bullet(float xspeed,float yspeed){return NULL;};
private:
	float angle;//与主机的角度，用于绘制该敌机时使用
};

class EnemyPlane2 :public EnemyPlane{//一种前进缓慢，缓慢发射子弹的飞机
public:
	EnemyPlane2(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl);
	EnemyPlane2(EnemyPlane& temp):EnemyPlane(temp){};
	virtual Bullet** create_bullet(int time);
	virtual void move(Position,float);
private:
};

class EnemyPlane3 :public EnemyPlane{//一种血量很高的飞机
public:
	EnemyPlane3(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl);
	EnemyPlane3(EnemyPlane& temp):EnemyPlane(temp){};
    Bullet** create_bullet(int time);
	virtual void move(Position,float);
private:
};

class Boss :public EnemyPlane{
public:
	Boss(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):EnemyPlane(p,b,a,po,x,y,bl){type = 4;};
	Boss(EnemyPlane& temp):EnemyPlane(temp){};
	virtual void move(Position,float);
	//boss有自己独特的发射子弹的方式
	virtual Bullet** create_bullet(int time);
	virtual Bullet* create_bullet(float xspeed,float yspeed);
private:
};


