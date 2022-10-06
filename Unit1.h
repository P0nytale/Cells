//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Diagnostics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button2;
	TTimer *Timer1;
	TButton *Button3;
	TLabel *Label1;
	TTimer *Timer2;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *CheckBox1;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label14;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *Label32;
	TLabel *Label33;
	TCheckBox *CheckBox2;
	TTrackBar *TrackBar1;
	TTrackBar *TrackBar2;
	TTrackBar *TrackBar3;
	TLabel *Label5;
	TCheckBox *CheckBox3;
	TButton *Button5;
	TButton *Button6;
	TPaintBox *PaintBox1;
	TCheckBox *CheckBox4;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TRadioGroup *RadioGroup1;
	TRadioGroup *RadioGroup2;
	TCheckBox *CheckBox5;
	TLabel *Label34;
	TLabel *Label35;
	TTrackBar *TrackBar4;
	TLabel *Label36;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton6;
	TGroupBox *GroupBox4;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8;
	TCheckBox *CheckBox6;
	TSpeedButton *SpeedButton9;
	TOpenDialog *OpenDialog1;
	TGroupBox *GroupBox5;
	TSpeedButton *SpeedButton10;
	TSpeedButton *SpeedButton11;
	TLabel *Label37;
	TLabel *Label38;
	TSpeedButton *SpeedButton12;
	TSpeedButton *SpeedButton13;
	TSpeedButton *SpeedButton14;
	TCheckBox *CheckBox7;
	TLabel *Label39;
	TSaveDialog *SaveDialog1;
	TLabel *Label40;
	TCheckBox *CheckBox8;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall TrackBar3Change(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall PaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall PaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall TrackBar4Change(TObject *Sender);
	void __fastcall GroupBox2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall GroupBox2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall GroupBox2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall PaintBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton7Click(TObject *Sender);
	void __fastcall SpeedButton6MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall SpeedButton1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall SpeedButton7MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall SpeedButton5MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

private:	// User declarations
	void init_world();
	void __fastcall NewGen2();
	void __fastcall NewGen2_RandVer();
	void __fastcall NewGen2_Delete(int y, int x);
	void __fastcall NewGen2_SendBack(int y, int x);
	void __fastcall NewGen2_SendForward(int y, int x);
	void __fastcall NewGen2_RecalcAll();

	void (TForm1::*paint)();
	void draw_world();
	void draw_world_grid();
	void draw2_world();
	void draw3_world();
	void paint_fn_recalc();

	void w2_fill();
	void w2_clr();
	void arad_recalc();
	void world_fill(unsigned char color);
	bool __fastcall LoadPattern(TSpeedButton *button);
	int WIDTH, HEIGHT, CELL_SIZE;

	Graphics::TBitmap *bmp;
	AnsiString bmp_dir;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
