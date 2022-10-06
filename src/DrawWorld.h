#ifndef __DRAWWORLD_H
#define __DRAWWORLD_H

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ DRAW WORLD 1 ++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const TRGBTriple draw_tbl[9] = { {0,128,255}, {0,0,255}, {0,255,255}, {132,0,132}, {255,255,128}, {0,0,0}, {0,255,0}, {255,0,128}, {255,255,255} };
const TRGBTriple draw_grey = {128, 128, 128};
void TForm1::draw_world()
{
	TRGBTriple  *a;
	TRGBTriple  col;
	int pos_y = 0, pos_x = 0;
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
	{
		for(int yy = 0; yy < CELL_SIZE; yy++)
		{
			a = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[pos_y++]); pos_x = 0;
			for(int x = BORDER; x < WIDTH + BORDER; x++)
			{
				if(w2[y][x] == 1) col = draw_grey;
				else col = draw_tbl[world[y][x]];
				for(int xx = 0; xx < CELL_SIZE; xx++, pos_x++)
					a[pos_x] = col;
			}
		}
	}
	PaintBox1->Canvas->Draw(0, 0, bmp);
	frames++;
}

void TForm1::draw_world_grid()
{
	TRGBTriple  *a;
	TRGBTriple  col;
	int pos_y = 0, pos_x = 0;
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
	{
		a = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[pos_y++]);
		for(int x = 0; x < WIDTH*CELL_SIZE; x++)
			{a[x].rgbtRed = 0; a[x].rgbtGreen = 0; a[x].rgbtBlue = 0;}
		for(int yy = 1; yy < CELL_SIZE; yy++)
		{
			a = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[pos_y++]); pos_x = 0;
			for(int x = BORDER; x < WIDTH + BORDER; x++)
			{
				a[pos_x].rgbtRed = 0; a[pos_x].rgbtGreen = 0; a[pos_x].rgbtBlue = 0; pos_x++;

				if(w2[y][x] == 1) col = draw_grey;
				else col = draw_tbl[world[y][x]];
				for(int xx = 1; xx < CELL_SIZE; xx++, pos_x++)
					a[pos_x] = col;
			}
		}
	}
	PaintBox1->Canvas->Draw(0, 0, bmp);
	frames++;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ DRAW WORLD 2 ++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//8 бит на цвет
const unsigned int draw2_tbl[9] = {0xFF20000, 0xFF00000, 0xFF3FC00, 0x8400084, 0x803FCFF, 0, 0x3FC00, 0x80000FF, 0xFF3FCFF};
unsigned int a[HEIGHT_MAX][WIDTH_MAX] = {0};
void TForm1::draw2_world()
{
	int pos_y = 0, pos_x = 0, col;
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
		for(int yy = 0; yy < CELL_SIZE; yy++, pos_x = 0, pos_y++)
			for(int x = BORDER; x < WIDTH + BORDER; x++)
			{
				col = draw2_tbl[world[y][x]];
				for(int xx = 0; xx < CELL_SIZE; xx++, pos_x++)
					a[pos_y][pos_x] = col;
			}

	TRGBTriple  *b, *b2;
	int height_count = HEIGHT*CELL_SIZE - 1, width_count = WIDTH*CELL_SIZE - 1;

	b = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[0]);
	b2 = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[height_count]);
	for(int x = 0; x <= width_count ; x++)
		b[x].rgbtRed = b[x].rgbtGreen = b[x].rgbtBlue = b2[x].rgbtRed = b2[x].rgbtGreen = b2[x].rgbtBlue = 0;

	for(int y = 1; y < height_count; y++)
	{
		b = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[y]);
		b[0].rgbtRed = b[0].rgbtGreen = b[0].rgbtBlue = b[width_count].rgbtRed = b[width_count].rgbtGreen = b[width_count].rgbtBlue = 0;

		unsigned int last1, last2, last3;
		last2 =	0x2FDBF6FD; //255*3 и во все цвета
		last3 =	a[y-1][1] + a[y][1] + a[y+1][1];
		for(int x = 1; x < width_count; x++)
		{
			last1 = last2; last2 = last3;
			last3 = a[y-1][x+1] + a[y][x+1] + a[y+1][x+1];
			switch (TrackBar1->Position)
			{
				case 1:
					b[x].rgbtRed =		( (last1>>20) + (last2>>20) + (last3>>20) );
					b[x].rgbtGreen =	( ((last1>>10)&1023) + ((last2>>10)&1023) + ((last3>>10)&1023) );
					b[x].rgbtBlue =		( (last1 & 1023) + (last2 & 1023) + (last3 & 1023) );
				break;
				case 2:
					b[x].rgbtRed =		( (last1>>20) + (last2>>20) + (last3>>20) )>>1;
					b[x].rgbtGreen =	( ((last1>>10)&1023) + ((last2>>10)&1023) + ((last3>>10)&1023) )>>1;
					b[x].rgbtBlue =		( (last1 & 1023) + (last2 & 1023) + (last3 & 1023) )>>1;
				break;
				case 4:
					b[x].rgbtRed =		( (last1>>20) + (last2>>20) + (last3>>20) )>>2;
					b[x].rgbtGreen =	( ((last1>>10)&1023) + ((last2>>10)&1023) + ((last3>>10)&1023) )>>2;
					b[x].rgbtBlue =		( (last1 & 1023) + (last2 & 1023) + (last3 & 1023) )>>2;
				break;
				case 8:
					b[x].rgbtRed =		( (last1>>20) + (last2>>20) + (last3>>20) )>>3;
					b[x].rgbtGreen =	( ((last1>>10)&1023) + ((last2>>10)&1023) + ((last3>>10)&1023) )>>3;
					b[x].rgbtBlue =		( (last1 & 1023) + (last2 & 1023) + (last3 & 1023) )>>3;
				break;
				default:
					b[x].rgbtRed =		( (last1>>20) + (last2>>20) + (last3>>20) ) / TrackBar1->Position;
					b[x].rgbtGreen =	( ((last1>>10)&1023) + ((last2>>10)&1023) + ((last3>>10)&1023) ) / TrackBar1->Position;
					b[x].rgbtBlue =		( (last1 & 1023) + (last2 & 1023) + (last3 & 1023) ) / TrackBar1->Position;
				break;
			}
		}
	}
	PaintBox1->Canvas->Draw(0, 0, bmp);
	frames++;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++ DRAW WORLD 3 ++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//6 бит на цвет
const unsigned int draw3_tbl[9] = {0x3F08000, 0x3F00000, 0x3F0FC00, 0x2100021, 0x200FC3F, 0, 0xFC00, 0x200003F, 0x3F0FC3F};
void TForm1::draw3_world()
{
	TRGBTriple  *b;
	int pos_y = 0, pos_x = 0;
	unsigned int last1, last2, last3, last, red, green, blue;
	union {TRGBTriple triple; uint32_t val;} rgbtriple_union;
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
	{
		for(int yy = 0; yy < CELL_SIZE; yy++)
		{
			b = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[pos_y++]); pos_x = 0;

			last2 =	0xBD2F4BD; //63*3 и во все цвета
			last3 =	draw3_tbl[world[y-1][BORDER]] + draw3_tbl[world[y][BORDER]] + draw3_tbl[world[y+1][BORDER]];
			for(int x = BORDER; x < WIDTH + BORDER; x++)
			{
				last1 = last2; last2 = last3;
				last3 = draw3_tbl[world[y-1][x+1]] + draw3_tbl[world[y][x+1]] + draw3_tbl[world[y+1][x+1]];
				last = last1 + last2 + last3;
				switch (TrackBar1->Position)
				{
					case 1:
						rgbtriple_union.val = ((last<<2)&0xFC) | (last&0xFC00) | ((last>>2)&0xFC0000);
					break;
					case 2:
						rgbtriple_union.val = ((last<<1)&0xFE) | ((last>>1)&0xFE00) | ((last>>3)&0xFE0000);
					break;
					case 4:
						rgbtriple_union.val = (last&0xFF) | ((last>>2)&0xFF00) | ((last>>4)&0xFF0000);
					break;
					case 8:
						rgbtriple_union.val = ((last>>1)&0xFF) | ((last>>3)&0xFF00) | ((last>>5)&0xFF0000);
					break;
					default:
						rgbtriple_union.triple.rgbtRed = ((last>>18)&4092)/TrackBar1->Position;
						rgbtriple_union.triple.rgbtGreen = ((last>>8)&4092)/TrackBar1->Position;
						rgbtriple_union.triple.rgbtBlue = ((last<<2)&4092) / TrackBar1->Position;
					break;
				}
				for(int xx = 0; xx < CELL_SIZE; xx++, pos_x++)
					b[pos_x] = rgbtriple_union.triple;
			}
		}
	}
	PaintBox1->Canvas->Draw(0, 0, bmp);
	frames++;
}


#endif  /*__DRAWWORLD_H*/
