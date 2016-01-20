//�ӵ���
#pragma once
#include "picture.h"
#include"const data.h"

class Bullet{
public:
	Bullet(Picture* p,Position po,float x,float y):body(p),pos(po),xspeed(x),yspeed(y),type(0),hurt(1){};
	//���캯����Ҫһ��picture��Ϊ�ӵ��Ļ��棬һ��positionΪ�ӵ��ĳ�ʼλ�ã�xspeed��yspeed�ֱ�����ӵ���ˮƽ����ֱ��ʼ�ٶ�
	virtual void draw();//�ӵ��Ļ�����
	virtual void run(float dt,Position p= Position(-100,-100));//�ڼ��dt��ʱ���ڣ�run�ܼ�����ӵ�����һ��λ�����꣬�Ӷ��޸��ӵ���position
	float getwidth()const;//����ӵ��Ŀ��
	float getheight()const;//����ӵ��ĳ���
	Position getpos()const;//����ӵ���λ������
	int get_type()const{return type;};
	int get_hurt()const{return hurt;};
protected:
	float xspeed;//�ӵ���ˮƽ�ٶ�
	float yspeed;//�ӵ�����ֱ�ٶ�
	Position pos;//�ӵ���λ������
	Picture* body;//�ӵ��Ļ���
	int hurt;//�ӵ�������ǿ��
	int type;//�ӵ�������
};

class TrackBullet: public Bullet{
public:
	TrackBullet(Picture* p,Position po,float x,float y):Bullet(p,po,x,y),angle(0){type = 1;hurt = track_hurt;};
	virtual void draw();
	virtual void run(float dt,Position p);//���ӵ�����p����ǰ��
private:
	float angle;
};