#pragma once
#include <iostream>
using namespace std;
const float map_ymovespeed=2; //��ͼ���ƶ��ٶ�

const float win_width=800;//���ڿ��
const float win_height=700;//���ڸ߶�

const int me_blood = 5;//������Ѫ��
const int me_life = 3;//��������������
const int me_bigshot = 3;//������ʼ������
const float meplane_xspeed = 700;//������x,y������ƶ��ٶ�
const float meplane_yspeed = 700;
const float me_pos_x=win_width/2;//�����տ�ʼ���ֵ�λ��
const float me_pos_y=win_height/2;
const float mebulletyspeed = 800;//�����ӵ��ĳ�ʼ�ٶ�
const float track_xspeed = 0;//���ٵ��ٶ�
const float track_yspeed = -500;
const int track_hurt = 15;//���ٵ��˺�
const int big_shot_number = 4;//���ٵ�����
const float me_protect = 20;//����������ײ�����̶�
const float slow_ratio = float(0.4);//shift���ļ���Ч��
const int fire_volume = 50;//������������
//�л�����
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
//Boss����
const float boss_xspeed = 50;
const float boss_yspeed = 50;
const int boss_blood = 2500;
const int boss_score = 10000;

const int boom_volume = 50;//��ը����

const float pi=(float)3.14159;//����pi
