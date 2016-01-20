#pragma once
#include <iostream>
using namespace std;
const float map_ymovespeed=2; //地图的移动速度

const float win_width=800;//窗口宽度
const float win_height=700;//窗口高度

const int me_blood = 5;//主机的血量
const int me_life = 3;//主机的生命数量
const int me_bigshot = 3;//主机初始大招数
const float meplane_xspeed = 700;//主机的x,y方向的移动速度
const float meplane_yspeed = 700;
const float me_pos_x=win_width/2;//主机刚开始出现的位置
const float me_pos_y=win_height/2;
const float mebulletyspeed = 800;//主机子弹的初始速度
const float track_xspeed = 0;//跟踪弹速度
const float track_yspeed = -500;
const int track_hurt = 15;//跟踪弹伤害
const int big_shot_number = 4;//跟踪弹数量
const float me_protect = 20;//对主机的碰撞保护程度
const float slow_ratio = float(0.4);//shift键的减速效果
const int fire_volume = 50;//主机开火音量
//敌机参数
const float enemyplane1_xspeed=50;
const float enemyplane1_yspeed=180;
const int enemy1_blood = 2;
const int enmey1_score = 100;

const float enemyplane2_xspeed=0;
const float enemyplane2_yspeed=80;
const float enemy2bulletyspeed=200;
const int enemy2_blood = 15;
const int enmey2_score = 500;

const float enemyplane3_xspeed=100;
const float enemyplane3_yspeed=110;
const float enemy3bulletyspeed=150;
const float enemy3bulletxspeed=140;
const int enemy3_blood = 20;
const int enmey3_score = 600;
//Boss参数
const float boss_xspeed = 50;
const float boss_yspeed = 50;
const int boss_blood = 2500;
const int boss_score = 10000;

const int boom_volume = 50;//爆炸音量

const float pi=(float)3.14159;//常数pi
