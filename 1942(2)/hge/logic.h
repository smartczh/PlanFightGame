#pragma once
#include"map.h"
#include"Plane.h"
#include"thing.h"
#include"const data.h"
#include<utility>
#include<vector>
using namespace std;
class GUI;
class Logic{
	friend class GUI;//GUI���ʹ��logic��ĳ�Ա����������Ϊ��Ԫ
public:
	Logic();
	~Logic();
	bool caculate();//���ּ��㣬�����л��н����ӵ��н����ɻ��Ƿ�ݻٵȵȣ����������˽�к�������
	//����Ҫ�ĵ�ͼ���������л�����Ʒ���뵽�߼�������
	void attach(Map*);
	void attach(MePlane*);
	void attach(EnemyPlane*);
	void attach(Thing*);
private:
	float time;//��¼���н����˶��
	bool lose;//�����Ƿ񱻴ݻ�
	bool win;//��¼�Ƿ��ʤ
	bool stop;//��¼�Ƿ���ͣ
	bool escape;//�Ƿ��˳���Ϸ
	class status{//���û����ݹ�������Ϣ���ı��״̬��
	public:
		float dt;//��¼ÿ֡����ʱ��
		//ͨ��GUI�����������µĲ���ֵ�����ڴ����������ж�
		bool left;
		bool right;
		bool up;
		bool down;
		bool shot;
		bool slow;
		bool big_shot;
	};

	status sta;//�û�����״̬
	//��Щָ����ָ��Ķ��󣨵�ͼ���������л����ӵ�����Ʒ����Ϊ�߼����������
    Map* background;
	MePlane* me;
	vector<EnemyPlane*>enemy_type;
	vector<EnemyPlane*>enemy;
	vector<Bullet*>enemy_bullets;
	vector<Bullet*>me_bullets;
	vector<pair<Animation*,Position>*>explode;
	vector<Thing*>thing_type;
	vector<Thing*>things;
	//���������ĺ���
	void run_me();
	void move_me_Plane();
	void run_me_bullets();
	void eat_thing();
	//����л��ĺ���
	void create_enemy(float time);
	void create_enemy_bullet();
	void run_enemy();
	void run_enemy_bullets();
	//������Ʒ�ĺ���
	void create_things(Position);
	void run_things(float);
	//����ը�ĺ���
	void add_to_explode(Animation*,Position);
	void update_explode();
	//��������ٵķɻ��ͱ���õ���Ʒ��ͬʱ������г������ڷ�Χ�Ķ���
	void swap_enemy();
	void swap_me();
	bool out(Position p,float w,float h);
	void delete_out();
	
	void set_result(float time);//�ж��Ƿ�ʤ������ʧ��
	void clear(); //�����߼����Ա����¿�ʼ
};

extern GUI* gui;