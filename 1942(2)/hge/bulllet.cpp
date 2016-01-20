#include"bullet.h"

void Bullet::draw(){
	body->draw(pos);
}

void Bullet::run(float dt,Position p){
	pos.x+=xspeed*dt;
	pos.y+=yspeed*dt;
}

float Bullet::getheight()const{
	return body->texheight;
}

float Bullet::getwidth()const{
	return body->texwidth;
}

Position Bullet::getpos()const{
	return pos;
}

void TrackBullet::draw(){
	body->draw(pos,angle);
}

void TrackBullet::run(float dt,Position p){
	if(p.x == -100 && p.y == -100){
		Bullet::run(dt,p);
		return;
	}
	angle = -pi + atan((pos.x-p.x)/(p.y-pos.y));
	if(p.y < pos.y && p.x <= pos.x)
		angle+=pi;
	if(p.y < pos.y && p.x>= pos.x)
		angle-=pi;
	float speed = sqrt( xspeed*xspeed + yspeed*yspeed );
	if(pos.x < p.x){
		pos.x += speed*dt*sin(angle);
		if(pos.x > p.x)
			pos.x = p.x;
	}
	if(pos.x > p.x){
		pos.x += speed*dt*sin(angle);
		if(pos.x < p.x)
			pos.x = p.x;
	}
	if(pos.y < p.y){
		pos.y -= speed*dt*cos(angle);
		if(pos.y > p.y)
			pos.y = p.y;
	}
	if((pos.y > p.y)){
		pos.y -= speed*dt*cos(angle);
		if(pos.y < p.y)
			pos.y = p.y;
	}
}

