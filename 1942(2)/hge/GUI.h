#pragma once
#include "Logic.h"
#include"const data.h"
#include "../include/hgegui.h"
#include"../include/hgeguictrls.h"

bool FrameFunc();
bool RenderFunc();

class GUI{
public:
    GUI(Logic*);
	~GUI();
	bool framefunc();
    bool renderfunc();
	void load_ins(Picture*);//载入说明图片
	HGE* hge;
	hgeGUI* menu;//菜单类
private:
	vector<Logic::status>condition;//存入每帧状态以备写入和写出
	float dt;//每帧时间差
	bool start;//判断是否开始游戏
	bool show_ins;//判断是否展示说明图片
	bool replay;//是否回放
	unsigned int for_replay;//回放中需要的辅助计数值
	Picture* ins;//说明图片
	Logic* lo;//拥有一个指向逻辑类的指针成员来进行逻辑计算
	void update_state();//通过HGE在获得用户的输入，把这些输入信息传递给逻辑类以供其处理，从而将逻辑类与完全HGE的实现隔离
	void draw();//负责菜单和游戏的绘制，会调用game_draw()
	void game_draw();//负责整个游戏的绘制，在GUI里将逻辑类的成员全部在窗口中绘制，从而实现逻辑与GUI的分离
	void set_menu_state();//设置每个菜单空间的状态
};

extern GUI* gui;