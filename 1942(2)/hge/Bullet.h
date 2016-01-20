//子弹类
#pragma once
#include "picture.h"
#include"const data.h"

class Bullet{
public:
	Bullet(Picture* p,Position po,float x,float y):body(p),pos(po),xspeed(x),yspeed(y),type(0),hurt(1){};
	//构造函数需要一个picture作为子弹的画面，一个position为子弹的初始位置，xspeed和yspeed分别代表子弹的水平和竖直初始速度
	virtual void draw();//子弹的画方法
	virtual void run(float dt,Position p= Position(-100,-100));//在间隔dt的时间内，run能计算出子弹的下一个位置坐标，从而修改子弹的position
	float getwidth()const;//获得子弹的宽度
	float getheight()const;//获得子弹的长度
	Position getpos()const;//获得子弹的位置坐标
	int get_type()const{return type;};
	int get_hurt()const{return hurt;};
protected:
	float xspeed;//子弹的水平速度
	float yspeed;//子弹的竖直速度
	Position pos;//子弹的位置坐标
	Picture* body;//子弹的画面
	int hurt;//子弹的威力强度
	int type;//子弹的种类
};

class TrackBullet: public Bullet{
public:
	TrackBullet(Picture* p,Position po,float x,float y):Bullet(p,po,x,y),angle(0){type = 1;hurt = track_hurt;};
	virtual void draw();
	virtual void run(float dt,Position p);//让子弹朝着p坐标前进
private:
	float angle;
};