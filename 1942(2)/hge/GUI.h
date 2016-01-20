#pragma once
#include "Logic.h"
#include"const data.h"
#include "../include/hgegui.h"
#include"../include/hgeguictrls.h"

bool FrameFunc();
bool RenderFunc();

class GUI{
public:
    GUI(Logic*);
	~GUI();
	bool framefunc();
    bool renderfunc();
	void load_ins(Picture*);//����˵��ͼƬ
	HGE* hge;
	hgeGUI* menu;//�˵���
private:
	vector<Logic::status>condition;//����ÿ֡״̬�Ա�д���д��
	float dt;//ÿ֡ʱ���
	bool start;//�ж��Ƿ�ʼ��Ϸ
	bool show_ins;//�ж��Ƿ�չʾ˵��ͼƬ
	bool replay;//�Ƿ�ط�
	unsigned int for_replay;//�ط�����Ҫ�ĸ�������ֵ
	Picture* ins;//˵��ͼƬ
	Logic* lo;//ӵ��һ��ָ���߼����ָ���Ա�������߼�����
	void update_state();//ͨ��HGE�ڻ���û������룬����Щ������Ϣ���ݸ��߼����Թ��䴦���Ӷ����߼�������ȫHGE��ʵ�ָ���
	void draw();//����˵�����Ϸ�Ļ��ƣ������game_draw()
	void game_draw();//����������Ϸ�Ļ��ƣ���GUI�ｫ�߼���ĳ�Աȫ���ڴ����л��ƣ��Ӷ�ʵ���߼���GUI�ķ���
	void set_menu_state();//����ÿ���˵��ռ��״̬
};

extern GUI* gui;