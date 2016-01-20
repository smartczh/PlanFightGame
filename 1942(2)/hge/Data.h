#include "Plane.h"
#include "map.h"
#include "GUI.h"
#include "Logic.h"
#include"sound.h"
#include "menuitem.h"
Picture* instrucition;//展示如何操作的图片
Picture* picture_map;//地图图片
Sound* music;//背景音乐
hgeFont* ft;//字体
hgeFont* ft2;//字体

Picture* picture_meplane;//主机图片

Picture* picture_mebullet;//主机子弹图片
Picture* picture_metrack;//主机跟踪弹图片
Sound* me_fire;//主机开火声音
Picture* picture_enemy2bullet;//敌机2的子弹图片
Picture* picture_enemy3bullet;//敌机3的子弹图片
//敌机图片
Picture* picture_enemy1;
Picture* picture_enemy2;
Picture* picture_enemy3;
Picture* picture_boss;
Sound* boom;//爆炸音效
//物品图片
Picture* picture_power;
Picture* picture_big;
//飞机
MePlane *me;
EnemyPlane* e1;
EnemyPlane* e2;
EnemyPlane* e3;
EnemyPlane* boss;

Map* background;

Animation* explodeme;//爆炸动画
Thing* power;//加火力的物品
Thing* big;//飞机的大招物品

GUI* gui;
Logic* lo;
//初始化
void init_data(){
	ft = new hgeFont("./pictures/font1.fnt");
	ft ->SetZ((float)0.1);
	ft2 = new hgeFont("./pictures/font2.fnt");
	ft2 ->SetZ((float)0.1);

	instrucition = new Picture(gui->hge,"./pictures/instruction.png",Position(0,0),800,700);
	picture_map = new Picture(gui->hge,"./pictures/map1.jpg",Position(0,0),800,1920);
	picture_map->setZ((float)0.9);
	picture_power = new Picture(gui->hge,"./pictures/pow.png",Position(0,0),48,48);
	picture_power->setZ((float)0.6);
	picture_power->sethotspot(24,24);
	picture_big = new Picture(gui->hge,"./pictures/big1.png",Position(0,0),48,48);
	picture_big->setZ((float)0.6);
	picture_big->sethotspot(24,24);

	picture_meplane = new Picture(gui->hge,"./pictures/ship5.png",Position(0,0),64,64);
	picture_meplane->setZ((float)0.45);
	picture_meplane->sethotspot(32, 32);
	picture_mebullet = new Picture(gui->hge,"./pictures/mebullet.png",Position(0,0),8,12);
	picture_mebullet->setZ((float)0.4);
	picture_mebullet->sethotspot(4,6);
	picture_metrack = new Picture(gui->hge,"./pictures/track_bullet.png",Position(0,0),16,32);
	picture_metrack->setZ((float)0.4);
	picture_metrack->sethotspot(8,16);

	explodeme = new Animation(gui->hge,"./pictures/explode1.png",28,14,Position(0,0),64,64);
	explodeme->setmode(HGEANIM_NOLOOP);
	explodeme->setZ((float)0.3);
	explodeme->sethotspot(32,32);

	picture_enemy2bullet = new Picture(gui->hge,"./pictures/enemybullet.png",Position(0,0),18,18);
	picture_enemy2bullet->setZ((float)0.4);
	picture_enemy2bullet->sethotspot(9, 9);
	picture_enemy3bullet = new Picture(gui->hge,"./pictures/enemybullet.png",Position(0,0),18,18);
	picture_enemy3bullet->setZ((float)0.4);
	picture_enemy3bullet->sethotspot(9, 9);

	picture_enemy1 = new Picture(gui->hge,"./pictures/ship1.png",Position(10,0),44,64);
	picture_enemy1->setZ((float)0.5);
	picture_enemy1->sethotspot(22, 32);
	picture_enemy2 = new Picture(gui->hge,"./pictures/ship2.png",Position(0,0),64,64);
	picture_enemy2->setZ((float)0.5);
	picture_enemy2->sethotspot(32, 32);
	picture_enemy3 = new Picture(gui->hge,"./pictures/ship3.png",Position(0,0),64,64);
	picture_enemy3->setZ((float)0.5);
	picture_enemy3->sethotspot(32, 32);
	picture_boss = new Picture(gui->hge,"./pictures/boss.png",Position(0,0),280,84);
	picture_boss->setZ((float)0.5);
	picture_boss->sethotspot(140,42);

	me_fire = new Sound(gui->hge,"./sounds/me_fire2.ogg");
	boom = new Sound(gui->hge,"./sounds/boom.wav");
	music = new Sound(gui->hge,"./sounds/Pacific Rim.mp3");
	music->play(1);

	background = new Map(picture_map,map_ymovespeed);
	power = new Thing(picture_power,Position(0,0),1);
	big = new Thing(picture_big,Position(0,0),2);
	me = new MePlane(picture_meplane,picture_mebullet,explodeme,Position(me_pos_x,me_pos_y),meplane_xspeed,meplane_yspeed,me_blood,me_life);
	me->load_fire_sound(me_fire);
	me->load_track_bullet(picture_metrack);
	me->load_dead_sound(boom);
	e1 = new EnemyPlane1(picture_enemy1,picture_mebullet,explodeme,Position(0,0),enemyplane1_xspeed,enemyplane1_yspeed,enemy1_blood);
	e1->load_dead_sound(boom);
	e2 = new EnemyPlane2(picture_enemy2,picture_enemy2bullet,explodeme,Position(0,0),enemyplane2_xspeed,enemyplane2_yspeed,enemy2_blood);
	e2->load_dead_sound(boom);
	e3 = new EnemyPlane3(picture_enemy3,picture_enemy3bullet,explodeme,Position(0,0),enemyplane3_xspeed,enemyplane3_yspeed,enemy3_blood);
	e3->load_dead_sound(boom);
	boss = new Boss(picture_boss,picture_enemy2bullet,explodeme,Position(0,0),boss_xspeed,boss_yspeed,boss_blood);
	boss->load_dead_sound(boom);


	lo->attach(background);
	lo->attach(me);
	lo->attach(e1);
	lo->attach(e2);
	lo->attach(e3);
	lo->attach(boss);
	lo->attach(power);
	lo->attach(big);

	gui->load_ins(instrucition);

	gui->menu->AddCtrl(new hgeGUIMenuItem(1,ft,win_width/2,200,0.0f,"Play"));
	gui->menu->AddCtrl(new hgeGUIMenuItem(2,ft,win_width/2,280,0.2f,"Instructions"));
	gui->menu->AddCtrl(new hgeGUIMenuItem(3,ft,win_width/2,360,0.2f,"Replay"));
	gui->menu->AddCtrl(new hgeGUIMenuItem(7,ft,win_width/2,440,0.4f,"Exit"));
	gui->menu->AddCtrl(new hgeGUIMenuItem(4,ft,win_width/2,200,0.2f,"Go on"));
	gui->menu->AddCtrl(new hgeGUIMenuItem(5,ft,win_width/2,280,0.2f,"Save"));
	gui->menu->AddCtrl(new hgeGUIMenuItem(6,ft,win_width/2,360,0.2f,"Back"));
	gui->menu->ShowCtrl(4,false);
	gui->menu->ShowCtrl(5,false);
	gui->menu->ShowCtrl(6,false);

	gui->menu->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->menu->SetFocus(1);
}