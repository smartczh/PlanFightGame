//�����࣬��װHGE�ﴦ����������
#pragma once
#include "../include/hge.h"

class Sound{
public:
	Sound(HGE* hge ,char* filename);
	void play(bool loop=0,int volume=100);//����������Ĭ��loop = 0����ѭ����Ĭ��volume = 100���������
private:
	HEFFECT snd;
};

