#pragma once
#include"map.h"
#include"Plane.h"
#include"thing.h"
#include"const data.h"
#include<utility>
#include<vector>
using namespace std;
class GUI;
class Logic{
	friend class GUI;//GUI类会使用logic类的成员，所以设置为友元
public:
	Logic();
	~Logic();
	bool caculate();//各种计算，包括敌机行进，子弹行进，飞机是否摧毁等等，里面有许多私有函数调用
	//将需要的地图，主机，敌机，物品加入到逻辑当中来
	void attach(Map*);
	void attach(MePlane*);
	void attach(EnemyPlane*);
	void attach(Thing*);
private:
	float time;//记录游行进行了多久
	bool lose;//主机是否被摧毁
	bool win;//记录是否获胜
	bool stop;//记录是否暂停
	bool escape;//是否退出游戏
	class status{//由用户传递过来的信息而改变的状态类
	public:
		float dt;//记录每帧调用时长
		//通过GUI类来产生以下的布尔值，用于处理主机的行动
		bool left;
		bool right;
		bool up;
		bool down;
		bool shot;
		bool slow;
		bool big_shot;
	};

	status sta;//用户按键状态
	//这些指针所指向的对象（地图，主机，敌机，子弹，物品）作为逻辑处理的主体
    Map* background;
	MePlane* me;
	vector<EnemyPlane*>enemy_type;
	vector<EnemyPlane*>enemy;
	vector<Bullet*>enemy_bullets;
	vector<Bullet*>me_bullets;
	vector<pair<Animation*,Position>*>explode;
	vector<Thing*>thing_type;
	vector<Thing*>things;
	//处理主机的函数
	void run_me();
	void move_me_Plane();
	void run_me_bullets();
	void eat_thing();
	//处理敌机的函数
	void create_enemy(float time);
	void create_enemy_bullet();
	void run_enemy();
	void run_enemy_bullets();
	//处理物品的函数
	void create_things(Position);
	void run_things(float);
	//处理爆炸的函数
	void add_to_explode(Animation*,Position);
	void update_explode();
	//清除被击毁的飞机和被获得的物品，同时清除所有超出窗口范围的东西
	void swap_enemy();
	void swap_me();
	bool out(Position p,float w,float h);
	void delete_out();
	
	void set_result(float time);//判断是否胜利或者失败
	void clear(); //清理逻辑，以备重新开始
};

extern GUI* gui;