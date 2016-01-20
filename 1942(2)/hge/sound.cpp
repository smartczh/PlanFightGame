
#include"sound.h"
#include "GUI.h"
Sound::Sound(HGE* hge,char* filename){
	snd = hge->Effect_Load(filename);
}

void Sound::play(bool loop, int volume){
	gui->hge-> Effect_PlayEx(snd,volume,0,1.0,loop);
}
	