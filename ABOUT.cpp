//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ABOUT.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
	Panel1->Color = (TColor)RGB(239, 228, 176);
	bmp = new Graphics::TBitmap();
}
//---------------------------------------------------------------------


void __fastcall TAboutBox::Timer1Timer(TObject *Sender)
{
	static int state = 0;
	switch(state)
	{
		case 0: state = 1; bmp->LoadFromResourceName((int)HInstance, "Bitmap_1"); break;
		case 1: state = 2; bmp->LoadFromResourceName((int)HInstance, "Bitmap_2"); break;
		case 2: state = 0; bmp->LoadFromResourceName((int)HInstance, "Bitmap_3"); break;
	}
	Image1->Canvas->Draw(0,0,bmp);
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormDestroy(TObject *Sender)
{
	delete bmp;
}
//---------------------------------------------------------------------------

