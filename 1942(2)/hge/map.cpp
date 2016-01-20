#include "map.h"
#include<iostream>
using namespace std;

Map::Map(Picture* p,float a):body(p),ymovespeed(a){
	pos1=Position(0,0);
	pos2=Position(0,0);
	pos2.y=-body->texheight;
	ft = new hgeFont("./pictures/font1.fnt");
	ft2 = new hgeFont("./pictures/font1.fnt");
	ft->SetZ((float)0.1);
	ft2->SetZ((float)0.1);
	score = 0;
	meblood = me_blood;
	melife = me_life;
	mebigshot = me_bigshot;
	show_win = false;
}

void Map::clear(){
	score = 0;
	meblood = me_blood;
	melife = me_life;
	mebigshot = me_bigshot;
}

void Map::update(int _blood,int _life,int _bigshot){
    meblood = _blood;
	melife = _life;
	mebigshot = _bigshot;
	show_win = false;
}

void Map::add_score(int type){//根据敌机的强度来加分
	switch(type){
		case 1:score+=enmey1_score;break;
		case 2:score+=enmey2_score;break;
		case 3:score+=enmey3_score;break;
		case 4:score+=boss_score;break;
		default:;
	}
}

void Map::set_win(){
	show_win = true;
}

void Map::draw(){//让Map能动起来的画法
	body->draw(pos1);
	pos1.y+=ymovespeed;
	body->draw(pos2);
	pos2.y+=ymovespeed;
	if(pos1.y>=body->texheight) pos1.y=-pos1.y;
	if(pos2.y>=body->texheight) pos2.y=-pos2.y;
	ft->printf(5,5,HGETEXT_LEFT,"score: %d",score);
	ft->printf(win_width/4,5,HGETEXT_LEFT,"blood: %d",meblood);
	ft->printf(win_width/2,6,HGETEXT_LEFT,"life: %d",melife);
	ft->printf(win_width*3/4,6,HGETEXT_LEFT,"bigshot: %d",mebigshot);
	if(show_win){
		ft2->SetColor(0xffff0000);
		ft2->SetScale(4);
		ft2->printf(win_width/2,win_height/2-ft2->GetHeight(),HGETEXT_CENTER,"Hero!You win!");
	}
}