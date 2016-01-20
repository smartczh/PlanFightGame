//图片类,动画类，封装HGE有关图片和动画的类
#pragma once
#include "../include/hge.h"
#include "../include/hgesprite.h"
#include "../include/hgeanim.h" 
#include"const data.h"

class Position{//坐标类
public://由于坐标类出现十分频繁，为了使代码更加简洁，把x、y坐标设为public
	Position(float _x=0,float _y=0):x(_x),y(_y){};
	float x;
	float y;
};

class Picture{
public:
	Picture(HGE* hge,char* file_name,Position p,float w,float h);
	//file_name为图片源文件，p代表从该点截取图片，w和h分别代表截取的宽度和长度
	~Picture();
    void draw(Position p,float rot=0);//在屏幕的p点画出该图，图片旋转rot角度，默认为不旋转
	void setZ(float z);//设置图片的前后，以处理图片重叠的情况，z值小的图片将覆盖z值大的图片
	void sethotspot(float x,float y);//设置图片的中心点，图片将以此点作为画图和旋转的依据
	void gethotspot(float *x,float *y);//获取图片的中心点坐标
	void setcolor(int color);//设置图片的颜色
	float texwidth;//图片宽度
	float texheight;//图片长度
private:
    hgeSprite *spr;
	HTEXTURE tex;
};

class Animation{//动画类
public:
	Animation(HGE* hge,char* file_name,int nframes, float FPS, Position p, float w, float h);
	//file_name为用于展示动画的图片源，nframes为总帧数，FPS为每秒展示的帧数，w和h为每帧的宽度和长度
	~Animation();
	Animation(const Animation&);//需采用深复制
	void setZ(float z);//设置z值
	void sethotspot(float x,float y);//设置中心点
	void update(float dt);//不断更新时间，用于处理动画
	void draw(Position p);//在位置P处展现动画
	void setmode(int mode);//设置动画模式，循环或者不循环
    void play();//启动动画
	bool isplaying();//判断动画是否正在播放
private:
	hgeAnimation* ani;
	HTEXTURE tex;
};
