//地图类
#pragma once
#include "Picture.h"
#include "../include/hgefont.h"
#include"const data.h"

class Map{
public:
	Map(Picture* p,float _ymovespeed);
	void draw();
	void update(int _blood,int _life,int _bigshot);//在地图上更新显示主机血量、生命数和大招数量
	void add_score(int);//在地图上更新分数
	void clear();
	void set_win();
private:
	bool show_win;//是否向用户展示“您获胜了”
	Picture* body;//地图图片
	Position pos1;//用于产生地图移动效果
	Position pos2;//用于产生地图移动效果
	float ymovespeed;//地图竖直移动的速度
	int score;//分数
	int meblood;//血量
	int melife;//生命数
	int mebigshot;//大招数
	hgeFont* ft;//字体
	hgeFont* ft2;//字体
};
