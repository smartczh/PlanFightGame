//ͼƬ��,�����࣬��װHGE�й�ͼƬ�Ͷ�������
#pragma once
#include "../include/hge.h"
#include "../include/hgesprite.h"
#include "../include/hgeanim.h" 
#include"const data.h"

class Position{//������
public://�������������ʮ��Ƶ����Ϊ��ʹ������Ӽ�࣬��x��y������Ϊpublic
	Position(float _x=0,float _y=0):x(_x),y(_y){};
	float x;
	float y;
};

class Picture{
public:
	Picture(HGE* hge,char* file_name,Position p,float w,float h);
	//file_nameΪͼƬԴ�ļ���p����Ӹõ��ȡͼƬ��w��h�ֱ�����ȡ�Ŀ�Ⱥͳ���
	~Picture();
    void draw(Position p,float rot=0);//����Ļ��p�㻭����ͼ��ͼƬ��תrot�Ƕȣ�Ĭ��Ϊ����ת
	void setZ(float z);//����ͼƬ��ǰ���Դ���ͼƬ�ص��������zֵС��ͼƬ������zֵ���ͼƬ
	void sethotspot(float x,float y);//����ͼƬ�����ĵ㣬ͼƬ���Դ˵���Ϊ��ͼ����ת������
	void gethotspot(float *x,float *y);//��ȡͼƬ�����ĵ�����
	void setcolor(int color);//����ͼƬ����ɫ
	float texwidth;//ͼƬ���
	float texheight;//ͼƬ����
private:
    hgeSprite *spr;
	HTEXTURE tex;
};

class Animation{//������
public:
	Animation(HGE* hge,char* file_name,int nframes, float FPS, Position p, float w, float h);
	//file_nameΪ����չʾ������ͼƬԴ��nframesΪ��֡����FPSΪÿ��չʾ��֡����w��hΪÿ֡�Ŀ�Ⱥͳ���
	~Animation();
	Animation(const Animation&);//��������
	void setZ(float z);//����zֵ
	void sethotspot(float x,float y);//�������ĵ�
	void update(float dt);//���ϸ���ʱ�䣬���ڴ�����
	void draw(Position p);//��λ��P��չ�ֶ���
	void setmode(int mode);//���ö���ģʽ��ѭ�����߲�ѭ��
    void play();//��������
	bool isplaying();//�ж϶����Ƿ����ڲ���
private:
	hgeAnimation* ani;
	HTEXTURE tex;
};
