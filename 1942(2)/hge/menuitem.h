//²Ëµ¥°´¼üÀà
#include "..\include\hge.h"
#include "..\include\hgegui.h"
#include "..\include\hgefont.h"
#include "..\include\hgecolor.h"


class hgeGUIMenuItem : public hgeGUIObject
{
public:
	hgeGUIMenuItem(int id, hgeFont *fnt, float x, float y, float delay, char *title);

	virtual void	Render();
	virtual void	Update(float dt);

	virtual bool	IsDone();
	virtual void	Focus(bool bFocused);

	virtual bool	KeyClick(int key, int chr);

private:
	hgeFont		*fnt;
	float		delay;
	char		*title;

	hgeColor	scolor, dcolor, scolor2, dcolor2, sshadow, dshadow;
	hgeColor	color, shadow;
	float		soffset, doffset, offset;
	float		timer, timer2;
};
