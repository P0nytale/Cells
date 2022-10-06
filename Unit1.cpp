//---------------------------------------------------------------------------

#include <vcl.h>

#include "Unit1.h"
#include "ABOUT.h"
#include <windows.h>
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#define WIDTH_MAX 1920
#define HEIGHT_MAX 1080
#define BORDER 60

#define GREEN 	0
#define RED     1
#define YELLOW  2
#define PURPLE  3
#define AGREEN  4
#define ARED    5
#define AYELLOW 6
#define APURPLE 7
#define EMPTY	8

#pragma hdrstop

#include "CellsLib.h"
#include "Patterns.h"

unsigned char world[HEIGHT_MAX+2*BORDER][WIDTH_MAX+2*BORDER] = {0};
unsigned char w2[HEIGHT_MAX+2*BORDER][WIDTH_MAX+2*BORDER] = {0};
MyPoint pat_selected[WIDTH_MAX*HEIGHT_MAX] = {0};
int pat_selected_n = 0;

unsigned int nb[HEIGHT_MAX+2*BORDER][WIDTH_MAX+2*BORDER] = {0};
unsigned char all[HEIGHT_MAX+2*BORDER][WIDTH_MAX+2*BORDER] = {0};

int arad1 = 1, arad2 = 1, arad3 = 1, arad4 = 1;

int sums[8] = {0};
int sum = 0, asum = 0;
int coll1 = 0, coll2 = 0, coll3 = 0, coll4 = 0;
int r = 100;

int gen = 0, frames = 0;
int gen_ms = 1000/50, gen_k = 1;

#include "NewGen.h"
#include "DrawWorld.h"

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	CELL_SIZE = 3;
	arad_recalc();
	WIDTH = PaintBox1->Width/CELL_SIZE;
	HEIGHT = PaintBox1->Height/CELL_SIZE;

	bmp = new Graphics::TBitmap();
	bmp->PixelFormat = pf24bit;		// формат цвета
	bmp->SetSize(PaintBox1->Width, PaintBox1->Height);

	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);
	AnsiString exe_dir = buffer;
	bmp_dir = exe_dir + "\\BMP";
	ForceDirectories(bmp_dir);
	paint_fn_recalc();
	(Form1->*paint)();

	TrackBar1Change(NULL);
	TrackBar2Change(NULL);
	TrackBar3Change(NULL);
	TrackBar4Change(NULL);
	Button3Click(NULL); //Clear world;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	delete bmp;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ NEXT GEN ++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	CheckBox1->Checked ? NewGen2_RandVer() : NewGen2();
	(Form1->*paint)();
}
//---------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ CLEAR WORLD +++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	coll1 = coll2 = coll3 = coll4 = gen = 0;
	for (int y = 0; y < HEIGHT_MAX + 2*BORDER; y++)
		for(int x = 0; x < WIDTH_MAX + 2*BORDER; x++)
		{
			world[y][x] = EMPTY;
			nb[y][x] = all[y][x] = 0;
		}
	sum = asum = sums[GREEN] = sums[RED] = sums[YELLOW] = sums[PURPLE] = sums[AGREEN] = sums[ARED] = sums[AYELLOW] = sums[APURPLE] = 0;
	(Form1->*paint)();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ CELL_SIZE +++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TForm1::arad_recalc()
{
	switch(CELL_SIZE)
	{
		case 1: arad1 = 10; arad2 = 20; arad3 = 30; arad4 = 60; break;
		case 2: arad1 = 10; arad2 = 20; arad3 = 30; arad4 = 50; break;
		case 3: arad1 = 5; arad2 = 10; arad3 = 20; arad4 = 35; break;
		case 4: arad1 = 5; arad2 = 10; arad3 = 15; arad4 = 25; break;
		case 8: arad1 = 3; arad2 = 5; arad3 = 10; arad4 = 15; break;
		case 16: arad1 = 1; arad2 = 2; arad3 = 4; arad4 = 6; break;
	}
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	switch(CELL_SIZE)
	{
		case 1: CELL_SIZE = 2; break;
		case 2: CELL_SIZE = 3; break;
		case 3: CELL_SIZE = 4; break;
		case 4: CELL_SIZE = 8; break;
		case 8: CELL_SIZE = 16; break;
		case 16: CELL_SIZE = 1; break;
	}
	HEIGHT = PaintBox1->Height/CELL_SIZE;
	WIDTH = PaintBox1->Width/CELL_SIZE;
	Button5->Caption = AnsiString("Cell Size: ") + CELL_SIZE;

	NewGen2_RecalcAll();
	arad_recalc();
	paint_fn_recalc();
	(Form1->*paint)();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ FULLSCREEN ++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	static bool fullscreen = false;
	static TWindowState window_state_last = Form1->WindowState;

	if(fullscreen)
	{
		Form1->BorderStyle = bsSizeable;
		Form1->WindowState = window_state_last;

		PaintBox1->SetBounds(0, 0, Form1->ClientWidth - GroupBox5->Width, Form1->ClientHeight);
		bmp->SetSize(PaintBox1->Width, PaintBox1->Height);
		HEIGHT = PaintBox1->Height/CELL_SIZE;
		WIDTH = PaintBox1->Width/CELL_SIZE;
		Button6->Caption = "Fullscreen";
		fullscreen = false;
	} else
	{
		window_state_last = Form1->WindowState;
		Form1->BorderStyle = bsNone;
		Form1->WindowState = wsNormal;
		Form1->WindowState = wsMaximized;

		GroupBox5->Top = 0; GroupBox5->Left = Screen->Width - GroupBox5->Width;
		PaintBox1->SetBounds(0, 0, Screen->Width, Screen->Height);
		bmp->SetSize(PaintBox1->Width, PaintBox1->Height);
		HEIGHT = PaintBox1->Height/CELL_SIZE;
		WIDTH = PaintBox1->Width/CELL_SIZE;
		Button6->Caption = "Exit Fullscreen";
		fullscreen = true;
	}
	(Form1->*paint)();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ RESIZE FORM +++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::FormResize(TObject *Sender)
{
	if(Form1->ClientHeight < GroupBox5->Height) Form1->ClientHeight = GroupBox5->Height;
	if(Form1->ClientWidth < (GroupBox5->Width << 1)) Form1->ClientWidth = (GroupBox5->Width << 1);
	GroupBox5->Left = Form1->ClientWidth - GroupBox5->Width;
	GroupBox5->Top = 0;

	PaintBox1->SetBounds(0, 0, Form1->ClientWidth - GroupBox5->Width, Form1->ClientHeight);
	bmp->SetSize(PaintBox1->Width, PaintBox1->Height);
	HEIGHT = PaintBox1->Height/CELL_SIZE;
	WIDTH = PaintBox1->Width/CELL_SIZE;
}
//---------------------------------------------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ TIMERS, PAINTING ++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	static TStopwatch sw;

	//Автоподстройка таймера
	if(sw.ElapsedMilliseconds < gen_ms && Timer1->Interval < 1000) Timer1->Interval++;
	else if(sw.ElapsedMilliseconds > gen_ms && Timer1->Interval > 10) Timer1->Interval--;
	sw = TStopwatch::StartNew();
	if(CheckBox3->Checked)
		for(int i = 0; i < gen_k; i++)
			CheckBox1->Checked ? NewGen2_RandVer() : NewGen2();

	if(Form1->WindowState == wsMaximized || CheckBox3->Checked) (Form1->*paint)();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
	if(!(Form1->WindowState == wsMaximized)) (Form1->*paint)();
}
//---------------------------------------------------------------------------

void TForm1::paint_fn_recalc()
{
	if(CheckBox2->Checked) CheckBox4->Checked ? paint = &TForm1::draw3_world : paint = &TForm1::draw2_world;
	else if(CELL_SIZE > 2 && CheckBox5->Checked) paint = &TForm1::draw_world_grid;
	else paint = &TForm1::draw_world;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	static int gen_last = gen;
	static int frames_last = frames;

	if(frames >= frames_last) Label1->Caption = AnsiString( EMA1( ((frames - frames_last)<<1) )) + " (" + TrackBar3->Position + ")";
	if(gen >= gen_last) Label34->Caption = AnsiString( EMA2( (gen - gen_last)<<1 )) + " (" + (TrackBar3->Position*TrackBar4->Position) + ")";
	Label3->Caption = gen;

	Label10->Caption = sums[GREEN]; Label11->Caption = sums[RED];
	Label12->Caption = sums[YELLOW]; Label13->Caption = sums[PURPLE];
	Label15->Caption = sum;

	Label21->Caption = sums[AGREEN]; Label22->Caption = sums[ARED];
	Label23->Caption = sums[AYELLOW]; Label24->Caption = sums[APURPLE];
	Label25->Caption = asum;

	Label30->Caption = coll1; Label31->Caption = coll2;
	Label32->Caption = coll3; Label33->Caption = coll4;

	Label39->Caption = AnsiString (EMA3 ( float(sum)*10000/(WIDTH*HEIGHT) ) / 100.0) + " %";
	Label40->Caption = AnsiString (EMA4 ( float(asum)*10000/(WIDTH*HEIGHT) ) / 100.0)  + " %";

	gen_last = gen; frames_last = frames;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ MOUSE DRAWING +++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MyPoint *pat_ptr = NULL;
int pattern_n = 0;
bool click = false;
int rotate = 0;
bool mirror = false;
MyPoint sel_start = {0}, sel_end = {0};

void TForm1::world_fill(unsigned char color)
{
	TPoint cur;
	GetCursorPos(&cur);
	cur = PaintBox1->ScreenToClient(cur);

	for(int i = 0; i < pattern_n; i++)
	{
		int x, y, tmp;
		y = pat_ptr[i].y; x = pat_ptr[i].x;
		switch(rotate)
		{
			case 1: tmp = x; x = -y; y = tmp; break;
			case 2: x = -x; y = -y; break;
			case 3: tmp = x; x = y; y = -tmp; break;
		}
		if(mirror) x = -x;
		world[BORDER + cur.y/CELL_SIZE + y][BORDER + cur.x/CELL_SIZE + x] = color;
	}
	NewGen2_RecalcAll();
	(Form1->*paint)();
}

void TForm1::w2_clr()
{
	for(int y = BORDER; y < HEIGHT + BORDER; y++)
		for(int x = BORDER; x < WIDTH + BORDER; x++)
			w2[y][x] = 0;
}

void TForm1::w2_fill()
{
	TPoint cur;
	GetCursorPos(&cur);
	cur = PaintBox1->ScreenToClient(cur);
	w2_clr();

	for(int i = 0; i < pattern_n; i++)
	{
		int x, y, tmp;
		y = pat_ptr[i].y; x = pat_ptr[i].x;
		switch(rotate)
		{
			case 1: tmp = x; x = -y; y = tmp; break;
			case 2: x = -x; y = -y; break;
			case 3: tmp = x; x = y; y = -tmp; break;
		}
		if(mirror) x = -x;
		w2[BORDER + cur.y/CELL_SIZE + y][BORDER + cur.x/CELL_SIZE + x] = 1;
	}

	if(!CheckBox3->Checked)	(Form1->*paint)();
}

void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(RadioGroup1->ItemIndex == 5) //Select
	{
		sel_start.y = Y/CELL_SIZE; sel_start.x = X/CELL_SIZE;
		w2_clr();
		w2[BORDER + sel_start.y][BORDER + sel_start.x] = 1;
		(Form1->*paint)();
		click = true;
		return;
	}

	for(int i = 0; i < GroupBox4->ControlCount; i++)
	{
		if (GroupBox4->Controls[i]->InheritsFrom(__classid(TSpeedButton)))
		{
			TSpeedButton *button = static_cast<TSpeedButton *>(GroupBox4->Controls[i]);
			if(button->Down)
			{
				int color = 0;
				if(Shift.Contains(ssLeft))
				{
					switch(RadioGroup1->ItemIndex)
					{
						case 0: color = GREEN; break; case 1: color = RED; break; case 2: color = YELLOW; break;
						case 3: color = PURPLE; break; case 4: color = GREEN + rand()%3; break;	case 5: color = AGREEN + rand()%3; break;
					}
				}
				else if(Shift.Contains(ssRight))
				{
					switch(RadioGroup2->ItemIndex)
					{
						case 0: color = AGREEN; break; case 1: color = ARED; break; case 2: color = AYELLOW; break;
						case 3: color = APURPLE; break; case 4: color= AGREEN + rand()%3; break; case 5: color = EMPTY;
					}
				}
				w2_clr(); world_fill(color); (Form1->*paint)();
				click = true;
				return;
			}
		}
	}

	PaintBox1MouseMove(Sender, Shift, X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	Label37->Caption = AnsiString("Y=") + Y/CELL_SIZE;
	Label38->Caption = AnsiString("X=") + X/CELL_SIZE;

	if(RadioGroup1->ItemIndex == 5)
	{
		if(click)
		{
			sel_end.y = Y/CELL_SIZE; sel_end.x = X/CELL_SIZE;
			int sel_top = std::min(sel_start.y, sel_end.y);
			int sel_left = std::min(sel_start.x, sel_end.x);
			int sel_height = std::abs(sel_start.y - sel_end.y);
			int sel_width = std::abs(sel_start.x - sel_end.x);
			w2_clr();
			for(int i = 0; i <= sel_height; i++)
			{
				w2[BORDER + sel_top + i][BORDER + sel_left] = 1;
				w2[BORDER + sel_top + i][BORDER + sel_left + sel_width] = 1;
			}
			for(int i = 0; i < sel_width; i++)
			{
				w2[BORDER + sel_top][BORDER + sel_left + i] = 1;
				w2[BORDER + sel_top + sel_height][BORDER + sel_left + i] = 1;
			}
			(Form1->*paint)();
		}
		return;
	}

	// Идет установка паттерна (OnMouseDown)
	if(click) return;

	// Выбран паттерн
	if(SpeedButton6->Down)
	{
		pat_ptr = pat_selected;
		pattern_n = pat_selected_n;
		w2_fill();
		return;
	}

	for(int i = 0; i < GroupBox4->ControlCount; i++)
	{
		if (GroupBox4->Controls[i]->InheritsFrom(__classid(TSpeedButton)))
		{
				TSpeedButton *button = static_cast<TSpeedButton *>(GroupBox4->Controls[i]);
				if(button->Down)
				{
					if(button->Tag < 40) pat_ptr = pat_builtin[button->Tag];
					else if(button->Tag >= 60) pat_ptr = pat_loaded[button->Tag - 60];
					pattern_n = pat_n[button->Tag];
					w2_fill();
					return;
				}
		}
	}

	// Рисование по-клеткам
	int color;
	if(Shift.Contains(ssLeft))
	{
		switch(RadioGroup1->ItemIndex)
		{
			case 0: color = GREEN; break; case 1: color = RED; break; case 2: color = YELLOW; break;
			case 3: color = PURPLE; break; case 4: color = GREEN + rand()%3; break;	case 5: color = AGREEN + rand()%3; break;
		}
		int y = BORDER + Y/CELL_SIZE, x = BORDER + X/CELL_SIZE;

		if(world[y][x] != EMPTY) NewGen2_Delete(y, x);
		world[y][x] = color;
		if(world[y][x] != EMPTY) NewGen2_SendBack(y, x);

		sum = sums[GREEN] + sums[RED] + sums[YELLOW] + sums[PURPLE]; asum = sums[AGREEN] + sums[ARED] + sums[AYELLOW] + sums[APURPLE];
		(Form1->*paint)();
	}
	else if(Shift.Contains(ssRight))
	{
		switch(RadioGroup2->ItemIndex)
		{
			case 0: color = AGREEN; break; case 1: color = ARED; break; case 2: color = AYELLOW; break;
			case 3: color = APURPLE; break; case 4: color= AGREEN + rand()%3; break; case 5: color = EMPTY;
		}
		int y = BORDER + Y/CELL_SIZE, x = BORDER + X/CELL_SIZE;

		if(world[y][x] != EMPTY) NewGen2_Delete(y, x);
		world[y][x] = color;
		if(world[y][x] != EMPTY) NewGen2_SendBack(y, x);

		sum = sums[GREEN] + sums[RED] + sums[YELLOW] + sums[PURPLE]; asum = sums[AGREEN] + sums[ARED] + sums[AYELLOW] + sums[APURPLE];
		(Form1->*paint)();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(RadioGroup1->ItemIndex == 5)
	{
		int sel_top = std::min(sel_start.y, sel_end.y);
		int sel_left = std::min(sel_start.x, sel_end.x);
		int sel_height = std::abs(sel_start.y - sel_end.y);
		int sel_width = std::abs(sel_start.x - sel_end.x);
		pat_selected_n = 0;
		for(int y = BORDER + sel_top + 1; y < BORDER + sel_top + sel_height; y++)
			for(int x = BORDER + sel_left + 1; x < BORDER + sel_left + sel_width; x++)
				if(world[y][x] != EMPTY)
				{
					pat_selected[pat_selected_n].x = x - BORDER - sel_left;
					pat_selected[pat_selected_n++].y = y - BORDER - sel_top;
				}
		w2_clr();
		(Form1->*paint)();
	}

	click = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == 'r' || Key == 'R' )
	{
		switch(rotate)
		{
			case 0: rotate = 1; break;
			case 1: rotate = 2; break;
			case 2: rotate = 3; break;
			case 3: rotate = 0; break;
		}
	} else if(Key == 'm' || Key == 'M')
	{
		mirror = !mirror;
	} else if(Key == 'p' || Key == 'P')
	{
		for(int i = 0; i < GroupBox4->ControlCount; i++)
		{
			if (GroupBox4->Controls[i]->InheritsFrom(__classid(TSpeedButton)))
			{
				TSpeedButton *button = static_cast<TSpeedButton *>(GroupBox4->Controls[i]);
				if(button->Down)
				{
					button->OnMouseDown(button, mbRight, TShiftState(0), 0, 0);
					if(button->Tag < 40) pat_ptr =  pat_builtin[button->Tag];
					else if(button->Tag >= 60) pat_ptr = pat_loaded[button->Tag - 60];
					pattern_n = button->Tag;
					break;
				}
			}
		}
	} else if(Key == 'c' || Key == 'C')
		Button3Click(NULL);
	w2_fill();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ HELP, ABOUT +++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
	WideString help_str = "\
		Conway's Game of Life variation: Cells!\n\
		Preliminary help\n\n\
		The main difference from the original B3/S23 rule is that when all three colors (arranged in two concurrent sets):\n\
		1. Orange/Red/Yellow and\n\
		2. Cyan/Black/Green\n\
		are met in the Moore's neighborhood of the empty cell: the Magenta (for Set 1) or Purple (for Set 2) cell is born.\n\
		Otherwise all four colors of one set acts as plain black cells in the original Conway's game of life. The color of the newborn, previously empty cell is determined by the plain superiority of the neighborhood's cells colors.\n\n\
		The Magenta/Purple cells are also act like the normal active cells except for the one new rule:\n\
		- Variant 1 (When when gr1/gr2 DryLife checkbox is unchecked): if there are 6 or 7 Magenta/Purple cells respectivaly in the Moore's neighborhood of the cell - the next turn it become one of three color of her Set, determined by the random. This is Conway's B3/S23 variation of the game.\n\n\
		- Variant 2 (When when gr1/gr2 DryLife checkbox is checked): if there are 7 living cells in the Moore's neighborhood and none are Magenta/Purple - the next turn it become one of three color of her Set, determined by the random. This is DryLife B37/S23 variation of the game.\n\n\
		This new rules leads to almost eternal, living population, starting from the very small populations (of course, random-driven mechanics), and not growing very fast, for the other side.\n\n\
		Also notice that Set 1 and Set 2 are just concurrenting for the area and explodees when it meets each other in the one cell neighborhood.\n\n\
		\n\
		Visual effects are just neat-looking graphics effects on the standart cells representation. Nothing special except for the finded by-chance (lucky logic error in the blur algorithm) cool colorings (try all of them, Alt modes also).\n\
		User interface:\n\
		- Draw cell-by-cell mode just at the game area by the left/right mouse button. The color of the cell is determined by the right-menu.\n\
		- Right-click on the fast in-build pattern buttons to cycle between the patterns.\n\
		- Right-click on the \"Load...\" pattern buttons to load pattern from .cells file (can be founded at https://www.conwaylife.com/).\n\
		- Right-menu can be moved if dragged by the upper side in the fullscreeen mode.\n\
		- Press r/R/m/M/p/P keys when putting a pattern at the game area to Rotate/Mirror\n\
		- Press n/N/p/P keys when putting a pattern at the game area to choose the Next/Previous build-in pattern.\n\
		- Press c/C keys to Clear\n\
		- Use your imagination! :)\
	";
	Application->MessageBox(help_str.c_bstr(), L"Help", MB_OK);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ TRACKBARS ++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
	r = TrackBar2->Position + 1;
	Label5->Caption = AnsiString(TrackBar2->Max - TrackBar2->Position + 1) + "->";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
	gen_ms = 1000/TrackBar3->Position;
	Timer1->Interval = gen_ms;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	CheckBox2->Caption = AnsiString("Effect ") + TrackBar1->Position;
	(Form1->*paint)();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar4Change(TObject *Sender)
{
	gen_k = TrackBar4->Position;
	Label36->Caption = AnsiString("k=") + gen_k;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ DRAGGING IN FULLSCREEN +++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TPoint drag_p, obj_p;
bool drag = false;
void __fastcall TForm1::GroupBox2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(Form1->WindowState == wsMaximized)
	{
		GetCursorPos(&drag_p); obj_p.x = GroupBox5->Left; obj_p.y = GroupBox5->Top;
		drag = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GroupBox2MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(drag)
	{
		TPoint cur_p; GetCursorPos(&cur_p);
		GroupBox5->Left = obj_p.x + (cur_p.x - drag_p.x);
		GroupBox5->Top = obj_p.y + (cur_p.y - drag_p.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GroupBox2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	drag = false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ SAVING BMP ++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Button9Click(TObject *Sender)
{
	AnsiString fileName, dateStr;
	dateStr = DateToStr(Date());
	fileName = dateStr;
	fileName += ' ';
	AnsiString timeStr = TimeToStr(Time());
	if(timeStr.Length() == 7) timeStr = AnsiString("0") + timeStr;
	fileName += timeStr;
	fileName[3] = '_'; fileName[6] = '_';
	fileName[14] = '_'; fileName[17] = '_';
	fileName += ".bmp";
	fileName = AnsiString("Cells") + " " + fileName;

	WideString w(bmp_dir);	SetCurrentDirectory(w.c_bstr());
	bmp->SaveToFile(fileName);
	WideString w2(fileName); Application->MessageBox(w2.c_bstr(), L"Сохранено", MB_OK);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ CHECKBOXES ++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
	paint_fn_recalc();
	(Form1->*paint)();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Button == mbRight)
	{
		if( ((TSpeedButton *)Sender)->Tag % 10 == 9)
			((TSpeedButton *)Sender)->Tag = (((TSpeedButton *)Sender)->Tag / 10)*10;
		else
			((TSpeedButton *)Sender)->Tag = (((TSpeedButton *)Sender)->Tag / 10)*10 + ((TSpeedButton *)Sender)->Tag % 10 + 1;

		((TSpeedButton *)Sender)->Caption = pat_names[((TSpeedButton *)Sender)->Tag];
		((TSpeedButton *)Sender)->Down = true;
	}
}
//---------------------------------------------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ LOAD/SAVE PATTERNS ++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool __fastcall TForm1::LoadPattern(TSpeedButton *button)
{
	static AnsiString fileName;
	static bool first_file = true;

	if(first_file)
	{
		TCHAR buffer[MAX_PATH]; GetCurrentDirectory(sizeof(buffer),buffer);
		AnsiString patterns_dir = AnsiString(buffer) + "\\PATTERNS";
		OpenDialog1->InitialDir = patterns_dir;
		first_file = false;
	} else
		OpenDialog1->InitialDir = ExtractFilePath(fileName);

	if(!OpenDialog1->Execute()) return false;
	fileName = OpenDialog1->FileName;

	FILE *in;
	if( (in = fopen(fileName.c_str(), "r")) == NULL )
	{
		Application->MessageBox(L"Cannot open input file.", L"Error", MB_OK);
		return false;
	}

	char str[2000], str2[100];
	int y_pos = 0, x_pos = 0, str_pos = 0, str2_pos = 0, num = 0, n = 0;

	fileName = ExtractFileName(fileName);
	if(ExtractFileExt(fileName) == ".cells") //Plaintext Encoding
	{
		while(!feof(in))
		{
			fgets(str, sizeof(str), in);
			if(str[0] == '!') continue;
			x_pos = 0;
			while(str[x_pos] == '.' || str[x_pos] == 'O')
			{
				if(str[x_pos] == '.') {x_pos++; continue;}
				if(n >= sizeof(pat_loaded[0])/sizeof(pat_loaded[0][0]))
				{
					pat_n[button->Tag] = 0;
					button->Caption = "Load...";
					WideString text = WideString("The loading pattern exceeds ") +
						WideString(sizeof(pat_loaded[0])/sizeof(pat_loaded[0][0])) + " living cells.\nThe pattern was not loaded.";
					Application->MessageBox(text.c_bstr(), L"Error", MB_OK);
					fclose(in);	return false;
				}
				pat_loaded[button->Tag - 60][n].y = y_pos; pat_loaded[button->Tag - 60][n++].x = x_pos++;
			}
			y_pos++;
		}
		fileName.SetLength(fileName.Length() - 6);  //Ged rid of file extension .cells
	} else if(ExtractFileExt(fileName) == ".rle") //Run Length Encoding
	{
		x_pos = y_pos = 0;
		while(!feof(in))
		{
			fgets(str, sizeof(str), in);
			if(str[0] == '#' || str[0] == 'x') continue;
			str_pos = 0;
			while(str[str_pos] != '\n' && str[str_pos] != '\0')
			{
				if(str[str_pos] >= '0' && str[str_pos] <= '9') str2[str2_pos++] = str[str_pos++];
				else if(str[str_pos] == '!') goto RLE_EXIT;
				else if(str[str_pos] == ' ') str_pos++;
				else if(str[str_pos] == '$')
				{
					str2[str2_pos] = '\0'; num = atoi(str2);
					if(num == 0) y_pos++;
					else y_pos += num;
					x_pos = 0; str2_pos = 0; str_pos++;
				}
				else if(str[str_pos] == 'b')
				{
					str2[str2_pos] = '\0'; num = atoi(str2);
					if(num == 0) x_pos++;
					else x_pos += num;
					str2_pos = 0; str_pos++;
				} else if(str[str_pos] == 'o')
				{
					str2[str2_pos] = '\0'; num = atoi(str2);
					do {
						if(n >= sizeof(pat_loaded[0])/sizeof(pat_loaded[0][0]))
						{
							pat_n[button->Tag] = 0;
							button->Caption = "Load...";
							WideString text = WideString("The loading pattern exceeds ") +
								WideString(sizeof(pat_loaded[0])/sizeof(pat_loaded[0][0])) + " living cells.\nThe pattern was not loaded.";
							Application->MessageBox(text.c_bstr(), L"Error", MB_OK);
							fclose(in);	return false;
						}
						pat_loaded[button->Tag - 60][n].y = y_pos; pat_loaded[button->Tag - 60][n++].x = x_pos++;
					} while (--num > 0);
					str2_pos = 0; str_pos++;
				} else
				{
					pat_n[button->Tag] = 0;
					button->Caption = "Load...";
					WideString text = WideString("The loading file is invalid. The pattern was not loaded.");
					Application->MessageBox(text.c_bstr(), L"Error", MB_OK);
					fclose(in);	return false;
				}
			}
		}
		RLE_EXIT:
		fileName.SetLength(fileName.Length() - 4);  //Ged rid of file extension .rle
	} else	//Unknown Encoding
	{
		button->Caption = "Load...";
		Application->MessageBox(L"Unknown file format.", L"Error", MB_OK);
		fclose(in);	return false;
	}

	pat_n[button->Tag] = n;
	fclose(in);

	//!!!To fill built-in patterns in debug mode
	//static volatile	MyPoint TOLOAD[300] = {};
	//for(int i = 0; i < n; i++)	{TOLOAD[i].y = pat[button->Tag][i].y; TOLOAD[i].x = pat[button->Tag][i].x;}

	if(n == 0)
	{
		button->Caption = "Load...";
		Application->MessageBox(L"The loaded pattern is empty.", L"Error", MB_OK);
		return false;
	} else
	{
		button->Caption = fileName;
		return true;
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SpeedButton7MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Button == mbRight)
		((TSpeedButton *)Sender)->Down = LoadPattern((TSpeedButton *)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	w2_clr();
	(Form1->*paint)();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
	w2_clr();
	(Form1->*paint)();
	if(pat_n[((TSpeedButton *)Sender)->Tag] == 0)
		((TSpeedButton *)Sender)->Down = LoadPattern((TSpeedButton *)Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton6MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Button == mbRight)
	{
		static AnsiString fileName;
		static bool first_file = true;

		if(first_file)
		{
			TCHAR buffer[MAX_PATH]; GetCurrentDirectory(sizeof(buffer),buffer);
			AnsiString patterns_dir = AnsiString(buffer) + "\\PATTERNS";
			SaveDialog1->InitialDir = patterns_dir;
			first_file = false;
		} else
			SaveDialog1->InitialDir = ExtractFilePath(fileName);

		if(!SaveDialog1->Execute()) return;
		fileName = SaveDialog1->FileName + ".cells";

		FILE *out;
		if( (out = fopen(fileName.c_str(), "w")) == NULL )
		{
			Application->MessageBox(L"Cannot open output file.", L"Error", MB_OK);
			return;
		}
		fputs("!This file was generated by Cells! v0.9b", out);
		pat_ptr = pat_selected;
		pattern_n = pat_selected_n;
		for(int y = BORDER; y < HEIGHT_MAX + BORDER; y++)
			for(int x = BORDER; x < WIDTH_MAX + BORDER; x++)
				w2[y][x] = 0;
		for(int i = 0; i < pattern_n; i++)
		{
			int x, y, tmp;
			y = pat_ptr[i].y; x = pat_ptr[i].x;
			switch(rotate)
			{
				case 1: tmp = x; x = -y; y = tmp; break;
				case 2: x = -x; y = -y; break;
				case 3: tmp = x; x = y; y = -tmp; break;
			}
			if(mirror) x = -x;
			w2[BORDER + y][BORDER + x] = 1;
		}
		int blanks;
		for(int y = BORDER; y < HEIGHT_MAX + BORDER; y++)
		{
			fputs("\n", out); blanks = 0;
			for(int x = BORDER; x < WIDTH_MAX + BORDER; x++)
			{
				if(w2[y][x] == 1)
				{
					while(blanks) {fputc('.', out); blanks--;}
					fputc('O', out);
				} else blanks++;
			}
		}
		w2_clr();
		fclose(out);
	}

}
//---------------------------------------------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ AUTO PATTERN ++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
	Button3Click(NULL);

	switch(SpeedButton5->Tag)
	{
		case 40:
		{
			int size;
			switch(CELL_SIZE)
			{
				case 1:
				case 2:
				case 3:
					size = 75;
				break;
				case 4: size = 50; break;
				case 8: size = 30; break;
				case 16: size = 20; break;
			}

			for (int y = BORDER; y < BORDER + size; y++)
				for(int x = BORDER; x < BORDER + size; x++)
					if(! (rand() % 5)) world[y][x] = GREEN + rand()%3;

			for (int y = HEIGHT + BORDER - size; y < HEIGHT + BORDER; y++)
				for(int x = BORDER; x < BORDER + size; x++)
					if(! (rand() % 5)) world[y][x] = AGREEN + rand()%3;

			for (int y = BORDER; y < BORDER + size; y++)
				for(int x = WIDTH + BORDER - size; x < WIDTH + BORDER; x++)
					if(! (rand() % 5)) world[y][x] = AGREEN + rand()%3;

			for (int y = HEIGHT + BORDER - size; y < HEIGHT + BORDER; y++)
				for(int x = WIDTH + BORDER - size; x < WIDTH + BORDER; x++)
					if(! (rand() % 5)) world[y][x] =  GREEN + rand()%3;
		}
		break;

		case 41:
		{
			int size, size2;
			switch(CELL_SIZE)
			{
				case 1:
				case 2:
				case 3:
					size = 75; size2 = 50;
				break;
				case 4: size = 50; size2 = 35; break;
				case 8: size = 30; size2 = 20; break;
				case 16: size = 15; size2 = 10; break;
			}

			for (int y = BORDER; y < BORDER + size; y++)
				for(int x = BORDER; x < BORDER + size; x++)
					if(! (rand() % 5)) world[y][x] = GREEN + rand()%3;

			for (int y = HEIGHT + BORDER - size; y < HEIGHT + BORDER; y++)
				for(int x = BORDER; x < BORDER + size; x++)
					if(! (rand() % 5)) world[y][x] = GREEN + rand()%3;

			for (int y = BORDER; y < BORDER + size; y++)
				for(int x = WIDTH + BORDER - size; x < WIDTH + BORDER; x++)
					if(! (rand() % 5)) world[y][x] = GREEN + rand()%3;

			for (int y = HEIGHT + BORDER - size; y < HEIGHT + BORDER; y++)
				for(int x = WIDTH + BORDER - size; x < WIDTH + BORDER; x++)
					if(! (rand() % 5)) world[y][x] =  GREEN + rand()%3;

			for (int y = (HEIGHT>>1) + BORDER - size2; y < (HEIGHT>>1) + BORDER + size2; y++)
				for(int x = (WIDTH>>1) + BORDER - size2; x < (WIDTH>>1) + BORDER +size2; x++)
					if(! (rand() % 5)) world[y][x] =  AGREEN + rand()%3;
		}
		break;

		case 42:
		{
			for (int y = BORDER; y < BORDER + HEIGHT; y++)
				for(int x = BORDER; x < BORDER + WIDTH; x++)
					if(y%3 && x%3) world[y][x] = GREEN;
					else world[y][x] = EMPTY;
		}
		break;
	}

	NewGen2_RecalcAll();
	(Form1->*paint)();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(Button == mbRight)
	{
		SpeedButton5->Tag++;
		if(SpeedButton5->Tag > 42) SpeedButton5->Tag = 40;
		SpeedButton5->Caption = AnsiString("Auto Pattern ") + (SpeedButton5->Tag % 10 + 1);
	}
}
//---------------------------------------------------------------------------

