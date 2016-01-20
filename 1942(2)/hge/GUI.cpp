#include "GUI.h"
#include<fstream>
using namespace std;

bool FrameFunc(){
	return gui->framefunc();
}

bool RenderFunc(){
	return gui->renderfunc();
}

bool GUI::renderfunc(){
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0); 
	draw();
	hge->Gfx_EndScene();
	return false;
}

void GUI::draw(){
	if(start || replay)//如果是开始游戏或者回放游戏，就在窗口上绘制游戏界面
		game_draw();
	if(!start || lo->stop || lo->win || lo->lose){//如果游戏没有开始或者是游戏胜利、失败、暂停，就绘制菜单
		gui->menu->Render();
		if(show_ins)
			ins->draw(Position(0,0));
	}
}

void GUI::game_draw(){//在GUI里将逻辑类的成员全部在窗口中绘制，从而实现逻辑与GUI的分离
	lo->background->draw();
	lo->me->draw(0,lo->sta.dt);
	vector<EnemyPlane*>::iterator iter1 = lo->enemy.begin();
	while(iter1!=lo->enemy.end()){
		(*iter1)->draw();
		iter1++;
	}
	vector<Bullet*>::iterator iter2 = lo->me_bullets.begin();
	while(iter2!=lo->me_bullets.end()){
		(*iter2)->draw();
		iter2++;
	}
	vector<Bullet*>::iterator iter3 = lo->enemy_bullets.begin();
	while(iter3!=lo->enemy_bullets.end()){
		(*iter3)->draw();
		iter3++;
	}
	auto iter4 = lo->explode.begin();
	while(iter4 != lo->explode.end()){
		(*iter4)->first->draw((*iter4)->second);
		iter4++;
	}

	auto iter5 = lo->things.begin();
	while(iter5 != lo->things.end()){
		(*iter5)->draw();
		iter5++;
	}
}

bool GUI::framefunc(){
	dt = hge->Timer_GetDelta();
	if(hge->Input_GetKeyState(HGEK_ESCAPE)){
		return true;
	}
	set_menu_state();
	int id;
	id = menu->Update(dt);
	switch(id){
	case 3:{//replay
		ifstream fin;
		fin.open("gamesave.dat",ios_base::in|ios_base::binary);
		if(fin){
			condition.clear();
			while(!fin.eof()){
				Logic::status temp;
				fin.read((char*)&temp,sizeof temp);
				condition.push_back(temp);
			}
		}
		else
			break;
		fin.close();
		replay = true;
		for_replay = 0;
		   }
	case 1://play
		gui->menu->ShowCtrl(1,false);
		gui->menu->ShowCtrl(2,false);
		gui->menu->ShowCtrl(3,false);
		gui->menu->ShowCtrl(7,false);
		start = true;
		show_ins = false;
		srand(1);
		break;
	case 2://instruction
		if(!show_ins)
			show_ins = true;
		else
			show_ins = false;
		break;
	case 4://go on
		lo->stop = false;
		gui->menu->ShowCtrl(4,false);
		gui->menu->ShowCtrl(5,false);
		gui->menu->ShowCtrl(6,false);
		gui->menu->ShowCtrl(7,false);
		break;
	case 5:{//save
		ofstream fout;
		fout.open("gamesave.dat",ios_base::out|ios_base::binary);
		if(fout){
		for(int i=0; i!=condition.size(); i++){
			fout.write((char*)&condition[i],sizeof condition[i]); 
		}
		}
		fout.close();
		break;
		   }
	case 6://back
		gui->menu->ShowCtrl(1,true);
		gui->menu->ShowCtrl(2,true);
		gui->menu->ShowCtrl(3,true);
		gui->menu->ShowCtrl(7,true);
		gui->menu->ShowCtrl(4,false);
		gui->menu->ShowCtrl(5,false);
		gui->menu->ShowCtrl(6,false);
		gui->menu->SetFocus(1);
		lo->clear();
		start = false;
		replay = false;
		break;
	case 7:
		return true;
	};

	if((start ||replay) &&  !lo->stop){
		update_state();
		return lo->caculate();
	}

	return false;
}

void GUI::set_menu_state(){
	if(lo->stop){
		gui->menu->ShowCtrl(4,true);//go on
		gui->menu->ShowCtrl(5,true);//save
		gui->menu->ShowCtrl(6,true);//back
		gui->menu->ShowCtrl(7,true);//exit
	}

	if(lo->win || lo->lose ){
		if(!replay)
			gui->menu->ShowCtrl(5,true);//save
		gui->menu->ShowCtrl(6,true);//back
		gui->menu->ShowCtrl(7,true);//exit
	}
}

void GUI::update_state(){//根据用户的输入传递信息给Logic
	if(replay){
		if(for_replay<condition.size()){
			lo->sta = condition[for_replay];
		}
		for_replay++;
	}
	else{
		lo->stop = hge->Input_GetKeyState(HGEK_P);
		lo->sta.dt = dt;
		if(lo->escape != true)
			lo->escape=hge->Input_GetKeyState(HGEK_ESCAPE);
		lo->sta.up=hge->Input_GetKeyState(HGEK_UP);
		lo->sta.down=hge->Input_GetKeyState(HGEK_DOWN);
		lo->sta.left=hge->Input_GetKeyState(HGEK_LEFT);
		lo->sta.right=hge->Input_GetKeyState(HGEK_RIGHT);
		lo->sta.shot =hge->Input_GetKeyState(HGEK_Z);
		lo->sta.big_shot = hge->Input_GetKeyState(HGEK_X);
		lo->sta.slow =hge->Input_GetKeyState(HGEK_SHIFT);
		condition.push_back(lo->sta);
	}
}

GUI::GUI(Logic* log){
	hge = hgeCreate(HGE_VERSION);
	menu = new hgeGUI();
	lo = log;
	start = false;
	show_ins = false;
	replay = false;
	for_replay= 0;
	hge -> System_SetState(HGE_SCREENWIDTH, int(win_width));//将屏幕宽度设置为win_width 
	hge -> System_SetState(HGE_SCREENHEIGHT, int(win_height));//将屏幕高度设置为win_height
	hge -> System_SetState(HGE_FRAMEFUNC, FrameFunc);// 设置帧函数FrameFunc
	hge -> System_SetState(HGE_RENDERFUNC,RenderFunc);//设置绘制函数为RenderFunc函数 
	hge -> System_SetState(HGE_WINDOWED,true);// 设置窗口模式
	hge -> System_SetState(HGE_USESOUND, true);// 设置是否使用声音
	hge -> System_SetState(HGE_TITLE, "GAME");// 设置标题为"Plane-Battle-Game"
	hge -> System_SetState(HGE_ZBUFFER,true);//开启深度缓冲。范围只在0.0-1.0之间
	hge -> System_SetState(HGE_SHOWSPLASH, false); // 用于去除LOGO
	hge -> System_SetState(HGE_FPS, 50); //设置FPS	
}

GUI::~GUI(){
	hge->System_Shutdown();
	hge->Release();
	delete menu;
}

void GUI::load_ins(Picture* p){
	ins = p;
}


