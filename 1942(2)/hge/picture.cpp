#pragma once
#include "picture.h"

Picture::Picture(HGE* hge,char* file_name,Position p,float w,float h)
		:texwidth(w),texheight(h){
		tex = hge->Texture_Load(file_name);
		if(tex)
	        spr = new hgeSprite(tex,p.x,p.y,w,h);
}

Picture::~Picture(){
	delete spr;
}

void Picture::draw(Position p,float rot){
	spr->RenderEx(p.x, p.y, rot);
}

void Picture::setZ(float z){
	spr->SetZ(z);
}

void Picture::sethotspot(float x,float y){
	spr->SetHotSpot(x,y);
}

void Picture::gethotspot(float* x,float* y){
	spr->GetHotSpot(x,y);
}

void Picture::setcolor(int color){
	spr->SetColor(color);
}

Animation::Animation(HGE* hge,char* file_name, int nframes, float FPS, Position p, float w, float h){
	tex = hge->Texture_Load(file_name);
	if(tex)
		ani = new hgeAnimation(tex, nframes, FPS, p.x, p.y, w, h);
};

Animation::Animation(const Animation& a){
	tex = a.tex;
	float x,y,w,h,hotspot_x,hotspot_y;
	a.ani->GetTextureRect(&x,&y,&w,&h);
	ani = new hgeAnimation(tex ,a.ani->GetFrames() ,a.ani->GetSpeed(), x, y, w, h);
	a.ani->GetHotSpot(&hotspot_x,&hotspot_y);
	ani->SetHotSpot(hotspot_x,hotspot_y);
}

Animation::~Animation(){
	delete ani;
}

void Animation::setZ(float z){
	ani->SetZ(z);
}

void Animation::sethotspot(float x,float y){
	ani->SetHotSpot(x,y);
}

void Animation::update(float dt){
	ani->Update(dt);
}

void Animation::draw(Position p){
	ani->Render(p.x, p.y);
}

void Animation::setmode(int mode){
	ani->SetMode(mode);
}

void Animation::play(){
	ani->Play();
}

bool Animation::isplaying(){
	return ani->IsPlaying();
}