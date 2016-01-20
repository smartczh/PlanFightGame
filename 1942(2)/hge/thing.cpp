
#include"Thing.h"

Thing::Thing(Picture* p,Position po,int _type){
	body = p;
	pos = po;
	time = 0;//��Ʒ����ʱ��ʼ��ʱ����ʼʱ��Ϊ0
	type = _type;
}

Thing::Thing(const Thing& temp){
	body = temp.body;
	pos = temp.pos;
	type = temp.type;
	time = 0;
	float hotspot_x,hotspot_y;
	temp.body->gethotspot(&hotspot_x,&hotspot_y);
	body->sethotspot(hotspot_x,hotspot_y);
}

void Thing::draw(){
	body->draw(pos);
}

void Thing::move(float dt){//��Ʒ������������ķ�ʽmove
	time+=dt;
	float s = 5*time*time;
	pos.y += s;
}

void Thing::set_pos(Position p){
	pos = p;
}