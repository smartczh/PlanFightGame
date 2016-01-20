#include "Plane.h"

Plane::Plane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):body(p),bul(b),explode(a),pos(po),xspeed(x),yspeed(y),blood(bl),boom(0){
}

void Plane::draw(float rot){
	body->draw(pos,rot);
}

void Plane::set_pos(Position p){
	pos.x = p.x;
	pos.y = p.y;
}

bool Plane::hit(Position p,float w,float h,float protect){
	bool flag1=p.x - pos.x > -(w + body->texwidth)/2+protect;
	bool flag2=p.x - pos.x < (w+body->texwidth)/2-protect;
	bool flag3=p.y - pos.y > -(h + body->texheight)/2+protect;
	bool flag4=p.y - pos.y < (h+body->texheight)/2-protect;
	if(flag1&&flag2&&flag3&&flag4)
		return true;
	else 
		return false;
}

bool Plane::destroy(){
	if(blood <= 0){
		return true;
	}
	else
		return false;
}

void Plane::load_dead_sound(Sound* temp){
	boom = temp;
}

MePlane::MePlane(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int _blood,int _life):Plane(p,b,a,po,x,y,_blood){
	pos.x=me_pos_x;
	pos.y=me_pos_y;
	life = _life;
	power = 1;
	bigshot = me_bigshot;
	is_hit = false;
	super = true;
}

void MePlane::clear(){
	pos.x=me_pos_x;
	pos.y=me_pos_y;
	power = 1;
	bigshot = me_bigshot;
	blood = me_blood;
	is_hit = false;
	super =true;
}

Bullet** MePlane::create_bullet(float xspeed,float yspeed){
	if(fire)
		fire->play(false,fire_volume);
	float x1 = pos.x ;
	float y1 = pos.y - (bul->texheight+body->texheight)/2;
	Position p1(x1,y1);
	auto head = new Bullet*[power];
	switch(power){
	case 5:{//5发子弹
		float x4 = x1 - 2*bul->texwidth-10;
		float y4 = y1 + 10;
		Position p4(x4,y4);
		float x5 = x1 + 2*bul->texwidth+10;
		float y5 = y4;
		Position p5(x5,y5);
		Bullet* temp4 = new Bullet(bul,p4,xspeed,yspeed);
		Bullet* temp5 = new Bullet(bul,p5,xspeed,yspeed);
		head[4] = temp5;
		head[3] = temp4;
		}
	case 3:{//3发子弹
		float x2 = x1 - bul->texwidth-5;
		float y2 = y1 + 5;
		Position p2(x2,y2);
		float x3 = x1 + bul->texwidth+5;
		float y3 = y2;
		Position p3(x3,y3);
		Bullet* temp2 = new Bullet(bul,p2,xspeed,yspeed);
		Bullet* temp3 = new Bullet(bul,p3,xspeed,yspeed);
		head[2] = temp3;
		head[1] = temp2;
		}
	case 1:{//1发子弹
		Bullet* temp1 = new Bullet(bul,p1,xspeed,yspeed);
		head[0] = temp1;
		return head;
		} 
	default: return 0;
	};
}

TrackBullet** MePlane::create_track_bullet(int number){
	float x1 = pos.x ;
	float y1 = pos.y - (track_bullet->texheight+body->texheight)/2;
	Position p1(x1,y1);
	auto head = new TrackBullet*[number];
	for(int i=0 ;i != number ;i++){
		TrackBullet* temp = new TrackBullet(track_bullet,p1,track_xspeed,track_yspeed);
		head[i] = temp;
	}
	return head;
}

void MePlane::draw(float rot, float dt){
	static bool add_time = false;
	static float time = 0;
	if(super){
		Plane::draw(rot);
		body->setcolor(0xaa00ff00);
		add_time = true;
		if(add_time){
			time += dt;
			if(time >= 3){
				body->setcolor(0xffffffff);
				add_time = false;
				time = 0;
				super = false;
			}
		}	
	}
	else{
		if(life > 0){
			Plane::draw(rot);
			if(is_hit){
				body->setcolor(0xffff0000);
				add_time = true;
				is_hit = false;
			}
			if(add_time){
				time += dt;
				if(time >= 0.3){
					body->setcolor(0xffffffff);
					add_time = false;
					time = 0;
				}
			}
		}
	}
}

void MePlane::add_power(int i){
	power += i;
	if(power >= 5)
		power = 5;//控制最大火力为5
}

void MePlane::add_bigshot(int i){
	bigshot += i;
	if(bigshot >= 7)
		bigshot = 7;
}

void MePlane::load_track_bullet(Picture* p){
	track_bullet = p;
}

void MePlane::load_fire_sound(Sound* temp){
	fire = temp;
}

bool MePlane::destroy(){
	bool flag = Plane::destroy();
	if(flag && boom)
		boom->play(false,boom_volume);
	return flag;
}

void EnemyPlane::draw(float rot){
	Plane::draw(rot);
}

void EnemyPlane::move(Position p ,float dt){
	if(pos.x < p.x){
		pos.x += xspeed*dt;
		if(pos.x > p.x)
			pos.x = p.x;
	}
	if(pos.x > p.x){
		pos.x -= xspeed*dt;
		if(pos.x < p.x)
			pos.x = p.x;
	}
	if(pos.y < p.y){
		pos.y += yspeed*dt;
		if(pos.y > p.y)
			pos.y = p.y;
	}
	if((pos.y > p.y)){
		pos.y -= yspeed*dt;
		if(pos.y < p.y)
			pos.y = p.y;
	}
}

Bullet* EnemyPlane::create_bullet(float xspeed,float yspeed){
	float x = pos.x ;
	float y = pos.y + (bul->texheight+body->texheight)/2;
	Position p(x,y);
	Bullet* temp = new Bullet(bul,p,xspeed,yspeed);
	return temp;
}

bool EnemyPlane::destroy(){
	bool flag = Plane::destroy();
	if(flag && boom)
		boom->play(false,boom_volume);
	return flag;
}

EnemyPlane1::EnemyPlane1(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):EnemyPlane(p,b,a,po,x,y,bl),angle(0){
	type = 1;
}

void EnemyPlane1::draw(float rot){
	 EnemyPlane::draw(angle);
 }

void EnemyPlane1::move(Position p,float dt){
	angle = atan((pos.x-p.x)/(p.y-pos.y));
	if(p.y < pos.y && p.x <= pos.x)
		angle+=pi;
	if(p.y < pos.y && p.x>= pos.x)
		angle-=pi;
	float speed = sqrt( xspeed*xspeed + yspeed*yspeed );
	if(pos.x < p.x){
		pos.x -= speed*dt*sin(angle);
		if(pos.x > p.x)
			pos.x = p.x;
	}
	if(pos.x > p.x){
		pos.x -= speed*dt*sin(angle);
		if(pos.x < p.x)
			pos.x = p.x;
	}
	if(pos.y < p.y){
		pos.y += speed*dt*cos(angle);
		if(pos.y > p.y)
			pos.y = p.y;
	}
	if((pos.y > p.y)){
		pos.y += speed*dt*cos(angle);
		if(pos.y < p.y)
			pos.y = p.y;
	}
}

EnemyPlane2::EnemyPlane2(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):EnemyPlane(p,b,a,po,x,y,bl){
	type = 2;
}

Bullet** EnemyPlane2::create_bullet(int time){
	if(time%40 == 0){
		auto temp = new Bullet*[1];
		*temp = EnemyPlane::create_bullet(0,enemy2bulletyspeed);
		return temp;
	}
	else 
		return NULL;
}

void EnemyPlane2::move(Position p,float dt){
	EnemyPlane::move(Position(pos.x,win_height*2),dt);
}

EnemyPlane3::EnemyPlane3(Picture* p,Picture* b,Animation* a,Position po,float x,float y,int bl):EnemyPlane(p,b,a,po,x,y,bl){
	type = 3;
}

Bullet** EnemyPlane3::create_bullet(int time){
	if(time%60 == 0){
		auto head = new Bullet*[3];
		head[0] = EnemyPlane::create_bullet(0,enemy3bulletyspeed);
		head[1] = EnemyPlane::create_bullet(enemy3bulletxspeed,enemy3bulletyspeed);
		head[2] = EnemyPlane::create_bullet(-enemy3bulletxspeed,enemy3bulletyspeed);
		return head;
	}
	else 
		return NULL;
}

void EnemyPlane3::move(Position p,float dt){
	EnemyPlane::move(Position(pos.x,win_height*2),dt);
}

void Boss::move(Position p, float dt){
	static bool left = true;
	static bool right = false;
	if(pos.y <= body->texheight){
		pos.y += yspeed*dt;
		return ;
	}
	if(left){
		pos.x -= xspeed*dt;
		if(pos.x <= body->texwidth/2){
			left = false;
			right = true;
		}
	}
	if(right){
		pos.x += xspeed*dt;
		if(pos.x >= win_width - body->texwidth/2){
			right = false;
			left = true;
		}
	}
}

Bullet** Boss::create_bullet(int time){
	if(time%50 ==0){
		auto head = new Bullet*[10];
		for(int i=0;i<5;i++)
			head[i] = Boss::create_bullet((float)0,(float)50+rand()%50);
		for(int i=5;i<10;i++)
			head[i] = Boss::create_bullet(rand()%100-(float)50,rand()%50+(float)50);
		return head;
	}
	else 
		return NULL;
}

Bullet* Boss::create_bullet(float xspeed,float yspeed){
	float y = pos.y + (bul->texheight+body->texheight)/2;
	float x = pos.x - body->texwidth/2 + rand()%(int)(body->texwidth);
	Position p(x,y);
	Bullet* temp = new Bullet(bul,p,xspeed,yspeed);
	return temp;
}