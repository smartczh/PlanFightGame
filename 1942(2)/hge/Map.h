//��ͼ��
#pragma once
#include "Picture.h"
#include "../include/hgefont.h"
#include"const data.h"

class Map{
public:
	Map(Picture* p,float _ymovespeed);
	void draw();
	void update(int _blood,int _life,int _bigshot);//�ڵ�ͼ�ϸ�����ʾ����Ѫ�����������ʹ�������
	void add_score(int);//�ڵ�ͼ�ϸ��·���
	void clear();
	void set_win();
private:
	bool show_win;//�Ƿ����û�չʾ������ʤ�ˡ�
	Picture* body;//��ͼͼƬ
	Position pos1;//���ڲ�����ͼ�ƶ�Ч��
	Position pos2;//���ڲ�����ͼ�ƶ�Ч��
	float ymovespeed;//��ͼ��ֱ�ƶ����ٶ�
	int score;//����
	int meblood;//Ѫ��
	int melife;//������
	int mebigshot;//������
	hgeFont* ft;//����
	hgeFont* ft2;//����
};
