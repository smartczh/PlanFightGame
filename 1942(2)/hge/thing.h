//���ٵл�����ܵ������Ʒ��
#pragma once
#include"picture.h"

class Thing{
public:
	Thing(Picture*,Position,int);
	Thing(const Thing&);
	void move(float dt);//����dtʱ�������Ʒ����λ�õ�����
	void draw();
	void set_pos(Position);//�ı���Ʒ������
	Position getpos()const{return pos;};//�����Ʒ������
	int get_type()const{return type;};//�����Ʒ�����ʶ
	float getwidth()const{return body->texwidth;};//�����Ʒͼ��Ŀ��
	float getheight()const{return body->texheight;};//�����Ʒͼ��ĳ���
private:
	Picture* body;//��Ʒ��ͼ��
	Position pos;//��Ʒ������
	int type;//��Ʒ�����
	float time;//����Ʒ�����Ѿ���������ʱ�䣬���ڼ�����Ʒ��λ��
};