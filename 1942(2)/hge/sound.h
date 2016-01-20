//声音类，封装HGE里处理声音的类
#pragma once
#include "../include/hge.h"

class Sound{
public:
	Sound(HGE* hge ,char* filename);
	void play(bool loop=0,int volume=100);//播放声音，默认loop = 0即不循环，默认volume = 100即最大音量
private:
	HEFFECT snd;
};

