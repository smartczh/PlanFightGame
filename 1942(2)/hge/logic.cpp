
#include "Logic.h"

Logic::Logic(){
	time = 0;
	sta.dt = 0;
	lose = false;
	win = false;
	escape = false;
	stop = false;
}

Logic::~Logic(){//析构函数把所有动态分配的内存释放
	for(auto iter=enemy_type.begin();iter!= enemy_type.end();iter++)
		delete *iter;
	for(auto iter=enemy.begin();iter!= enemy.end();iter++)
		delete *iter;
	for(auto iter=enemy_bullets.begin();iter!= enemy_bullets.end();iter++)
		delete *iter;
	for(auto iter=me_bullets.begin();iter!= me_bullets.end();iter++)
		delete *iter;
}

void Logic::attach(Map* temp){
    background=temp;
}

void Logic::attach(MePlane* temp){
	me=temp;
}

void Logic::attach(EnemyPlane* e){
	enemy_type.push_back(e);
}

void Logic::attach(Thing* temp){
	thing_type.push_back(temp);
}

bool Logic::out(Position pos,float w,float h){//判断目标是否超出窗口范围
	bool flag = false;
	if(pos.x + w/2 < 0)
		flag=true;
	if(pos.x - w/2 > win_width)
		flag=true;
	if(pos.y + h/2 < 0)
		flag=true;
	if(pos.y - h/2 > win_height)
		flag=true;
	return flag;
}

void Logic::delete_out(){//把超出窗口范围的物体消除
	for(auto iter=enemy.begin();iter!= enemy.end();)
		if(out((*iter)->getpos(),(*iter)->getwidth(),(*iter)->getheight())){
			delete *iter;
			iter = enemy.erase(iter);
		}
		else
			iter++;
	for(auto iter=enemy_bullets.begin();iter!= enemy_bullets.end();)
		if(out((*iter)->getpos(),(*iter)->getwidth(),(*iter)->getheight())){
			delete *iter;
			iter = enemy_bullets.erase(iter);
		}
		else
			iter++;
	for(auto iter=me_bullets.begin();iter!= me_bullets.end();)
		if(out((*iter)->getpos(),(*iter)->getwidth(),(*iter)->getheight())){
			delete *iter;
			iter = me_bullets.erase(iter);
		}
		else
			iter++;
}

void Logic::move_me_Plane(){//根据按键控制主机
	float _xspeed = me->xspeed;
	float _yspeed = me->yspeed;
	if(sta.slow){
		_xspeed *=slow_ratio ;
		_yspeed *=slow_ratio;
	}
	float dx=0,dy=0;
	if (sta.left) dx-=_xspeed*sta.dt;  
	if (sta.right) dx+=_xspeed*sta.dt;  
	if (sta.up) dy-=_yspeed*sta.dt;  
	if (sta.down) dy+=_yspeed*sta.dt;  

	me->pos.x+=dx; 
	me->pos.y+=dy;  
	if(me->pos.x - me->body->texwidth/2 <= 0)
		me->pos.x = me->body->texwidth/2;
	if(me->pos.x + me->body->texwidth/2 >= win_width)
		me->pos.x = win_width - me->body->texwidth/2;
	if(me->pos.y  - me->body->texheight/2 <= 0)
		me->pos.y = me->body->texheight/2;
	if(me->pos.y + me->body->texheight/2 >= win_height)
		me->pos.y=win_height - me->body->texheight/2;

	dx=0;
	dy=0;
}

void Logic::run_me_bullets(){//根据按键控制主机子弹
	static int i=0;
	unsigned int j=0;
	vector <Bullet*>::iterator iter=me_bullets.begin();
	while(iter!=me_bullets.end()){
		if((*iter)->get_type() == 1){
			if(j < enemy.size())
				(*iter)->run(sta.dt,enemy[j]->getpos());
			else
				(*iter)->run(sta.dt);
			j++;
		}
		else{
			(*iter)->run(sta.dt);
		}
		iter++;
	}

	if(sta.shot&&i%4==1&&!me->destroy()){
		auto head = me->create_bullet(0,-mebulletyspeed);
		switch(me->power){
		case 5:{
			auto temp5 = *(head+4);
			auto temp4 = *(head+3);
			me_bullets.push_back(temp5);
			me_bullets.push_back(temp4);
		}
		case 3:{
			auto temp3 = *(head+2);
			auto temp2 = *(head+1);
			me_bullets.push_back(temp3);
			me_bullets.push_back(temp2);
	    }
		case 1:{
			Bullet* temp1 = *head;
			me_bullets.push_back(temp1);
	    }
		default:;
		};
	}

	if(sta.big_shot&& !me->destroy() && me->bigshot>0 && i%3==1){
		me->bigshot--;
		auto head = me->create_track_bullet(big_shot_number);
		for(int i =0 ; i != big_shot_number ; i++)
			me_bullets.push_back(head[i]);
	}
	i++;
}

void Logic::eat_thing(){
	auto iter = things.begin();
	while(iter != things.end()){
		if(me->hit((*iter)->getpos(),(*iter)->getwidth(),(*iter)->getheight())){
			switch((*iter)->get_type()){
			case 1:
				me->add_power(2);
			case 2:
				me->add_bigshot(1);
			}
		iter = things.erase(iter);
		}
		else
			iter++;
	}
}

void Logic::run_me(){
	move_me_Plane();
	run_me_bullets();
	eat_thing();
}

void Logic::create_enemy(float t){//生产敌机的逻辑
	t*=50;
	int flag=(int)t;
	if(flag%100==0 && flag<=1500){
		EnemyPlane1* temp = new EnemyPlane1(*enemy_type[0]);
		EnemyPlane1* temp1 = new EnemyPlane1(*enemy_type[0]);
		temp->set_pos(Position(-temp->getwidth()/2,-temp->getheight()/2));
		temp1->set_pos(Position(win_width+temp1->getwidth()/2,-temp->getheight()/2));
		enemy.push_back(temp);
		enemy.push_back(temp1);
	}

	if(flag%400==0 && flag>400 && flag<=3200){
		EnemyPlane2* temp = new EnemyPlane2(*enemy_type[1]);
		EnemyPlane2* temp1 = new EnemyPlane2(*enemy_type[1]);
		EnemyPlane2* temp2 = new EnemyPlane2(*enemy_type[1]);
		temp->set_pos(Position(win_width/2,-temp->getheight()/2));
		temp1->set_pos(Position(win_width/4,-temp->getheight()/2));
		temp2->set_pos(Position(win_width*3/4,-temp->getheight()/2));
		enemy.push_back(temp);
		enemy.push_back(temp1);
		enemy.push_back(temp2);
	}

	if(flag%100==0&&flag>1000 && flag<=3600){
		EnemyPlane3* temp1 = new EnemyPlane3(*enemy_type[2]);
		EnemyPlane3* temp2 = new EnemyPlane3(*enemy_type[2]);
		int range = int(win_width - temp1->getwidth());
		float start = temp1->getwidth()/2;
		temp1->set_pos(Position(start+rand()%range,-temp1->getheight()/2));
		temp2->set_pos(Position(start+rand()%range,-temp2->getheight()/2));
		enemy.push_back(temp1);
		enemy.push_back(temp2);
	}

	if(flag == 3600){
		Boss* temp = new Boss(*enemy_type[3]);
		temp->set_pos(Position(win_width/2,-temp->getheight()/2));
		enemy.push_back(temp);
	}
}

void Logic::create_enemy_bullet(){//生产敌机子弹的逻辑
	int flag=(int)(time*50);

	vector<EnemyPlane*>::iterator iter = enemy.begin();
	while(iter != enemy.end()){
		auto head = (*iter)->create_bullet(flag);
		if(head){
			switch((*iter)->type){
				case 1: break;
				case 4:{
					for(int i=0;i<10;i++){
						enemy_bullets.push_back(head[i]);
					}
					break;
				}
				case 3:{
					auto temp2 = head[2];
					auto temp3 = head[1];
					enemy_bullets.push_back(temp3);
					enemy_bullets.push_back(temp2);
				}
				case 2:{
					auto temp1 = head[0];
					enemy_bullets.push_back(temp1);
					break;
				}
			};
		}
		iter++;
	}
}

void Logic::create_things(Position p){//生产掉落物品
	if(rand()%7 == 0){
		auto temp = new Thing(*thing_type[0]);
		temp->set_pos(p);
		things.push_back(temp);
		return;//直接return,如果防止同时出现两个物品
	}
	if(rand()%8 == 0){
		auto temp = new Thing(*thing_type[1]);
		temp->set_pos(p);
		things.push_back(temp);
		return; 
	}
}

void Logic::run_enemy_bullets(){
	create_enemy_bullet();
	vector<Bullet*>::iterator iter = enemy_bullets.begin();
	while(iter != enemy_bullets.end()){
		(*iter)->run(sta.dt);
		iter++;
	}
}

void Logic::run_enemy(){
	create_enemy(time);
	vector<EnemyPlane*>::iterator iter = enemy.begin();
	while(iter != enemy.end()){
		(*iter)->move(me->pos,sta.dt);
		iter++;
	}
	run_enemy_bullets();
}

void Logic::run_things(float t){
	auto iter = things.begin();
	while(iter != things.end()){
		(*iter)->move(sta.dt);
		iter++;
	}
}

void Logic::add_to_explode(Animation* a,Position p){
	auto temp = new Animation(*a);
	temp->setmode(HGEANIM_NOLOOP);
	temp->play();
	auto temp1 = new pair<Animation*,Position>(temp,p);
	explode.push_back(temp1);
}

void Logic::swap_me(){//判断主机是否被敌机击中
	if(me->life>0 &&!me->destroy()&&!me->super){//如果已经没有生命值则不需要再判断主机是否被击中了
		vector<EnemyPlane*>::iterator iter1 = enemy.begin();//先判断是否与敌机相撞
		while(iter1 != enemy.end()){
			if(me->hit((*iter1)->pos,(*iter1)->body->texwidth,(*iter1)->body->texheight,me_protect)){
				me->blood = 0;
				add_to_explode(me->explode,me->getpos());
				if((*iter1)->type!=4){
					add_to_explode((*iter1)->explode,(*iter1)->getpos());
					iter1 = enemy.erase(iter1);
				}
				me->destroy();
				me->life--;
				if(me->life > 0){
					me->pos = Position(me_pos_x,me_pos_y);
					me->clear();
				}
				break;
				return;
			}
			iter1++;
		}

		vector<Bullet*>::iterator iter2 = enemy_bullets.begin();
		while(iter2 != enemy_bullets.end()){
			if(me->hit((*iter2)->getpos(),(*iter2)->getwidth(),(*iter2)->getheight(),me_protect)){
				me->blood-= (*iter2)->get_hurt();
				me->is_hit = 1;
				iter2 = enemy_bullets.erase(iter2);
				if(me->destroy()){
					add_to_explode(me->explode,me->getpos());
					me->life--;
					if(me->life > 0){
						me->pos = Position(me_pos_x,me_pos_y);
						me->clear();
						return;
					}
					break;
				}
			}
			else
				iter2++;
		}
	}
}

void Logic::swap_enemy(){//判断敌机是否被主机子弹击中
	vector <Bullet*>::iterator iter1=me_bullets.begin();
	bool flag = false;
	while(iter1 != me_bullets.end()){
		flag = false;
		vector<EnemyPlane*>::iterator iter2 = enemy.begin();
		while(iter2 != enemy.end()){
			if((*iter2)->hit((*iter1)->getpos(),(*iter1)->getwidth(),(*iter1)->getheight())){
				flag = true;
				(*iter2)->blood -= (*iter1)->get_hurt();
				iter1 = me_bullets.erase(iter1);
				if((*iter2)->destroy()){
					background->add_score((*iter2)->type);
					create_things((*iter2)->pos);
					add_to_explode((*iter2)->explode,(*iter2)->getpos());
					free(*iter2);
					iter2 = enemy.erase(iter2);
				}
				break;
			}
			else
				iter2++;	
		}
		if(!flag)
			iter1++;
	}	
}

void Logic::update_explode(){
	auto iter = explode.begin();
	while(iter != explode.end()){
		(*iter)->first->update(sta.dt);
		if(!(*iter)->first->isplaying())
			iter = explode.erase(iter);
		else
			iter++;
	}
}

void Logic::set_result(float t){
	t*=50;
	int flag=(int)t;
	if(me->life <= 0 && explode.empty())
		lose = true;
	if(flag>3600 && enemy.empty()){
		background->set_win();
		win = true;
	}
}

bool Logic::caculate()
{
	time +=sta.dt;
	if (escape) return true;
	run_me();
	run_enemy();
	run_things(sta.dt);
	swap_me();
	swap_enemy();
	update_explode();
	delete_out();
	background->update(me->blood,me->life,me->bigshot);
	set_result(time);
	return false;
}

void Logic::clear(){
	for(auto iter=enemy.begin();iter!= enemy.end();){
		delete *iter;
		iter = enemy.erase(iter);
	}
	for(auto iter=enemy_bullets.begin();iter!= enemy_bullets.end();){
		delete *iter;
		iter = enemy_bullets.erase(iter);
	}
	for(auto iter=me_bullets.begin();iter!= me_bullets.end();){
		delete *iter;
		iter = me_bullets.erase(iter);
	}
	for(auto iter=explode.begin();iter!= explode.end();){
		delete *iter;
		iter = explode.erase(iter);
	}
	for(auto iter=things.begin();iter!= things.end();){
		delete *iter;
		iter = things.erase(iter);
	}
	time = 0;
	sta.dt=0;
	sta.left = false;
	sta.right = false;
	sta.up = false;
	sta.down = false;
	sta.shot = false;
	sta.slow = false;
	sta.big_shot = false;
	stop = false;
	lose = false;
	win = false;
	escape = false;
	me->clear();
	background->clear();
	me->life = me_life;
}
