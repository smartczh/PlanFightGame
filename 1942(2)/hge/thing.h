//击毁敌机后可能掉落的物品类
#pragma once
#include"picture.h"

class Thing{
public:
	Thing(Picture*,Position,int);
	Thing(const Thing&);
	void move(float dt);//计算dt时间过后物品所处位置的坐标
	void draw();
	void set_pos(Position);//改变物品的坐标
	Position getpos()const{return pos;};//获得物品的坐标
	int get_type()const{return type;};//获得物品种类标识
	float getwidth()const{return body->texwidth;};//获得物品图像的宽度
	float getheight()const{return body->texheight;};//获得物品图像的长度
private:
	Picture* body;//物品的图像
	Position pos;//物品的坐标
	int type;//物品的类别
	float time;//从物品出现已经经历过的时间，用于计算物品的位置
};