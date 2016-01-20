//�ɻ���
#pragma once
#include "Picture.h"
#include "bullet.h"
#include "const data.h"
#include "sound.h"
#include <math.h>

class Logic;

class Plane{
public:
	Plane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int _blood);
	//������pΪ�ɻ������ͼ��bΪ�ɻ��ӵ���ͼ��aΪ�ɻ����ƻ�ʱ�ı�ը������poΪ�ɻ��ĳ�ʼλ�ã�x,y�ֱ����ɻ���ˮƽ��ֱ�ٶȣ�_bloodΪ�ɻ���Ѫ��
	virtual void draw(float rot=0);
	virtual bool hit(Position p,float w,float h,float protect=0);//�ж���������P������ֱ�Ϊh,w��Ŀ���Ƿ���ײ��portectΪ�����̶ȣ�ֵԽ����ײ��ΧԽС��Ĭ��Ϊ0��Ϊ������
	virtual bool destroy();//�ж��Ƿ�ݻ�
	void set_pos(Position p);//���÷ɻ�����
	Position getpos()const{return pos;};//��÷ɻ�����
	float getwidth()const{return body->texwidth;};//��÷ɻ����
	float getheight()const{return body->texheight;};//��÷ɻ�����
	void load_dead_sound(Sound*);//���طɻ�������ʱ����Ч
protected:
	Picture* body;//�ɻ�ͼ��
	Picture* bul;//�ɻ��ӵ�ͼ��
    float xspeed;//�ɻ�ˮƽ�ٶ�
	float yspeed;//�ɻ���ֱ�ٶ�
    Position pos;//�ɻ���������
	int blood;//Ѫ��
	Sound* boom;//�ɻ���ը��Ч
	Animation* explode;//�ɻ���ը����
private:
};

class MePlane :public Plane{
friend class Logic;
public:
	MePlane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int _blood=5,int _life=3);//�ȸ������һ��_life��������ɻ�����������
	virtual void draw(float rot=0,float dt = 0);
	Bullet** create_bullet(float xspeed,float yspeed);//���ڲ����������Ҫ����ٶȵ��ӵ������ڿ��ܲ�������ӵ������ӵ�����new�������ģ����Է���һ��ָ���ӵ�ָ�������ͷԪ��
	TrackBullet** create_track_bullet(int);
	void add_power(int);//���ӷɻ�����
	void add_bigshot(int);//���Ӵ�������
	void load_track_bullet(Picture*);//���ظ��ٵ�ģ��
	void load_fire_sound(Sound*);//���ؿ�����Ч
	virtual bool destroy();
	void clear();
	bool is_hit;
	bool super;
private:
	int life;//��������
	int power;//�ӵ�����ֵ
	int bigshot;//�ɻ��Ĵ���
	Picture* track_bullet;//���ٵ�
	Sound* fire;//�ӵ����������
};

class EnemyPlane :public Plane{
friend class Logic;
public:
	EnemyPlane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):Plane(p,b,a,po,x,y,bl){};
	virtual void draw(float rot=0);
	virtual void move(Position p,float dt);//ÿ��enemyplane���ƶ���ʽ��ͬ��������Ϊ�麯��������Ĭ�ϳ���p�����ƶ���dt���ڼ���ɻ�����
	virtual bool destroy();
	virtual Bullet** create_bullet(int time){return NULL;};//�л���ʱ���Զ������ӵ�������Ĭ�ϲ������ӵ�
	virtual Bullet* create_bullet(float xspeed,float yspeed);//����ָ��Ҫ����ӵ�
protected:
	int type;//�л�����
private:
};

class EnemyPlane1 :public EnemyPlane{//һ��ֻ�ᳯ�����ķ�����У��������ӵ��ķɻ�
public:
	EnemyPlane1(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl);
	EnemyPlane1(EnemyPlane& temp):EnemyPlane(temp),angle(0){};
	virtual void draw(float rot=0);
	virtual void move(Position,float);
	virtual Bullet* create_bullet(float xspeed,float yspeed){return NULL;};
private:
	float angle;//�������ĽǶȣ����ڻ��Ƹõл�ʱʹ��
};

class EnemyPlane2 :public EnemyPlane{//һ��ǰ�����������������ӵ��ķɻ�
public:
	EnemyPlane2(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl);
	EnemyPlane2(EnemyPlane& temp):EnemyPlane(temp){};
	virtual Bullet** create_bullet(int time);
	virtual void move(Position,float);
private:
};

class EnemyPlane3 :public EnemyPlane{//һ��Ѫ���ܸߵķɻ�
public:
	EnemyPlane3(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl);
	EnemyPlane3(EnemyPlane& temp):EnemyPlane(temp){};
    Bullet** create_bullet(int time);
	virtual void move(Position,float);
private:
};

class Boss :public EnemyPlane{
public:
	Boss(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):EnemyPlane(p,b,a,po,x,y,bl){type = 4;};
	Boss(EnemyPlane& temp):EnemyPlane(temp){};
	virtual void move(Position,float);
	//boss���Լ����صķ����ӵ��ķ�ʽ
	virtual Bullet** create_bullet(int time);
	virtual Bullet* create_bullet(float xspeed,float yspeed);
private:
};


