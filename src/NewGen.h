#ifndef __NEWGEN_H
#define __NEWGEN_H

void __fastcall TForm1::NewGen2_RecalcAll()
{
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
		for(int x = BORDER; x < WIDTH + BORDER; x++)
			all[y][x] = nb[y][x] = 0;

	sums[GREEN] = sums[RED] = sums[YELLOW] = sums[PURPLE] = sums[AGREEN] = sums[ARED] = sums[AYELLOW] = sums[APURPLE] = 0;
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
		for(int x = BORDER; x < WIDTH + BORDER; x++)
			if(world[y][x] != EMPTY) NewGen2_SendBack(y, x);
	sum = sums[GREEN] + sums[RED] + sums[YELLOW] + sums[PURPLE]; asum = sums[AGREEN] + sums[ARED] + sums[AYELLOW] + sums[APURPLE];
}

void __fastcall TForm1::NewGen2_Delete(int y, int x)
{
	unsigned char *all__ = &all[y-1][x-1];
	unsigned int *nb__ = &nb[y-1][x-1];
	unsigned char world_ = world[y][x];
	unsigned int world_color = 1<<(world_<<2);
	nb__[0] -= world_color; nb__[1] -= world_color; nb__[2] -= world_color; nb__[WIDTH_MAX + 2*BORDER] -= world_color;
	sums[world_]--;

	if(world_ < AGREEN)			{ all__[0]--; all__[1]--; all__[2]--; all__[WIDTH_MAX + 2*BORDER]--; }
	else 						{ all__[0] -= 0x10; all__[1] -= 0x10; all__[2] -= 0x10; all__[WIDTH_MAX + 2*BORDER] -= 0x10; }
}

void __fastcall __forceinline TForm1::NewGen2_SendBack(int y, int x)
{
	unsigned char *all__ = &all[y-1][x-1];
	unsigned int *nb__ = &nb[y-1][x-1];
	unsigned char world_ = world[y][x];
	unsigned int world_color = 1<<(world_<<2);
	nb__[0] += world_color; nb__[1] += world_color; nb__[2] += world_color; nb__[WIDTH_MAX + 2*BORDER] += world_color;
	sums[world_]++;

	if(world_ < AGREEN)			{ all__[0]++; all__[1]++; all__[2]++; all__[WIDTH_MAX + 2*BORDER]++; }
	else 						{ all__[0] += 0x10; all__[1] += 0x10; all__[2] += 0x10; all__[WIDTH_MAX + 2*BORDER] += 0x10; }
}

void __fastcall __forceinline TForm1::NewGen2_SendForward(int y, int x)
{
	unsigned char *all__ = &all[y+1][x+1];
	unsigned int *nb__ = &nb[y+1][x+1];
	unsigned char world_ = world[y][x];
	unsigned int world_color = 1<<(world_<<2);
	nb__[-(WIDTH_MAX + 2*BORDER)] += world_color; nb__[-2] += world_color; nb__[-1] += world_color; nb__[0] += world_color;

	if(world_ < AGREEN)		 	{ all__[-(WIDTH_MAX + 2*BORDER)]++; all__[-2]++; all__[-1]++; all__[0]++; }
	else 						{ all__[-(WIDTH_MAX + 2*BORDER)] += 0x10; all__[-2] += 0x10; all__[-1] += 0x10; all__[0] += 0x10; }
}

#define GREEN_MASK		(0x0000000F)
#define RED_MASK        (0x000000F0)
#define YELLOW_MASK     (0x00000F00)
#define PURPLE_MASK   	(0x0000F000)
#define AGREEN_MASK		(0x000F0000)
#define ARED_MASK		(0x00F00000)
#define AYELLOW_MASK	(0x0F000000)
#define APURPLE_MASK	(0xF0000000)

void __fastcall TForm1::NewGen2()
{
	sums[GREEN] = sums[RED] = sums[YELLOW] = sums[PURPLE] = sums[AGREEN] = sums[ARED] = sums[AYELLOW] = sums[APURPLE] = 0;
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
	{
		for(int x = BORDER; x < WIDTH + BORDER; x++)
		{
			unsigned char &world_ = world[y][x];
			unsigned char &all_ = all[y][x];
			unsigned int &nb_ = nb[y][x];

			if(all_ == 0)
			{
				if(world_ != EMPTY) NewGen2_SendForward(y, x);
				world_ = EMPTY;
			}
			else if ( (all_ & 0xF0) == 0) //Set1
			{
				if(CheckBox7->Checked && all_ == 0x07 && (nb_ & PURPLE_MASK) == 0 && world_ == EMPTY)   //B37/S23 условно
				{   // Рождается, если есть есть 7 соседей и среди них ни одного фиолетового (правила DryLife)
					world_ = GREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(!CheckBox7->Checked && (nb_ & PURPLE_MASK) > 0x00006000)    //B378/S2378 условно
				{   // Рождается или меняется, если среди соседей 7 или 8 фиолетовых (фиолетовый распад)
					if(world_ != EMPTY) NewGen2_SendForward(y, x);
					world_ = GREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(world_ == EMPTY)
				{
					if(all_ == 0x03)
					{   // Рождаетсся, если ровно три соседа - тем цветом, которого два или три, а если такого нет - то фиолетовым
						if( (nb_ & GREEN_MASK) > 0x00000001) world_ = GREEN;
						else if ( (nb_ & RED_MASK) > 0x00000010) world_ = RED;
						else if ( (nb_ & YELLOW_MASK) > 0x00000100) world_ = YELLOW;
						else world_ = PURPLE;
						//Fast SendBack()
						unsigned char *all__ = &all[y-1][x-1];
						unsigned int *nb__ = &nb[y-1][x-1];
						unsigned int world_color = 1<<(world_<<2);
						nb__[0] += world_color;	nb__[1] += world_color;	nb__[2] += world_color;	nb__[WIDTH_MAX + 2*BORDER] += world_color;
						all__[0]++; all__[1]++; all__[2]++; all__[WIDTH_MAX + 2*BORDER]++;
						sums[world_]++;
					}
				} else
				{   // Сохраняется, если два или три соседа, иначе становится пустой
					NewGen2_SendForward(y, x);
					if(all_ < 0x02 || all_ > 0x03) world_ = EMPTY;
					else NewGen2_SendBack(y, x);
				}
				all_ = nb_ = 0;
			} else if( (all_ & 0x0F) == 0) //Set2
			{
				if(CheckBox8->Checked && all_ == 0x70 && (nb_ & APURPLE_MASK) == 0 && world_ == EMPTY)
				{
					world_ = AGREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(!CheckBox8->Checked && (nb_ & APURPLE_MASK) > 0x60000000)
				{
					if(world_ != EMPTY) NewGen2_SendForward(y, x);
					world_ = AGREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(world_ == EMPTY)
				{
					if(all_ == 0x30)
					{
						if( (nb_ & AGREEN_MASK)> 0x00010000) world_ = AGREEN;
						else if ( (nb_ & ARED_MASK) > 0x00100000) world_ = ARED;
						else if ( (nb_ & AYELLOW_MASK)> 0x01000000) world_ = AYELLOW;
						else world_ = APURPLE;
						//Fast SendBack()
						unsigned char *all__ = &all[y-1][x-1];
						unsigned int *nb__ = &nb[y-1][x-1];
						unsigned int world_color = 1<<(world_<<2);
						nb__[0] += world_color;	nb__[1] += world_color;	nb__[2] += world_color;	nb__[WIDTH_MAX + 2*BORDER] += world_color;
						all__[0] += 0x10; all__[1] += 0x10; all__[2] += 0x10; all__[WIDTH_MAX + 2*BORDER] += 0x10;
						sums[world_]++;
					}
				} else
				{
					NewGen2_SendForward(y, x);
					if(all_ < 0x20 || all_ > 0x30) world_ = EMPTY;
					else NewGen2_SendBack(y, x);
				}
				all_ = nb_ = 0;
			} else	//Collision
			{
				if(world_ != EMPTY) NewGen2_SendForward(y, x);
				if(CheckBox6->Checked)
				{
					int arad;
					switch( (all_ & 0x0F) + (all_ >> 4) )
					{
						case 2: coll1++; arad = arad1; break;
						case 3:	coll2++; arad = arad2; break;
						case 4:	coll3++; arad = arad3; break;
						case 5:
						case 6:
						case 7:
						case 8:	coll4++; arad = arad4; break;
						default:       //Just in-case
							//Application->MessageBox(L"NewGen2 Error: look at the collision section", L"Error", MB_OK);
							arad = 0;
						break;
					}
					for(int yy = std::max(y - arad, BORDER), h = y - yy; yy <= std::min(y + arad, BORDER + HEIGHT - 1); yy++)
					{
						for(int xx = std::max(x - arad + h, BORDER); xx <= std::min(x + arad - h, BORDER + WIDTH - 1); xx++)
						{
							if(yy < y || (yy == y && xx < x) )
							{
								if(world[yy][xx] != EMPTY) NewGen2_Delete(yy, xx);
								world[yy][xx] = EMPTY;

							} else
							{
								all[yy][xx] = nb[yy][xx] = 0;
								world[yy][xx] = EMPTY;
							}
						}
						if(yy < y) h--;
						else h++;
					}
				} else
				{
					all_ = nb_ = 0;
					world_ = EMPTY;
				}
			}
		}
	}
	sum = sums[GREEN] + sums[RED] + sums[YELLOW] + sums[PURPLE]; asum = sums[AGREEN] + sums[ARED] + sums[AYELLOW] + sums[APURPLE];
	gen++;
}

void __fastcall TForm1::NewGen2_RandVer()
{
	sums[GREEN] = sums[RED] = sums[YELLOW] = sums[PURPLE] = sums[AGREEN] = sums[ARED] = sums[AYELLOW] = sums[APURPLE] = 0;
	for (int y = BORDER; y < HEIGHT + BORDER; y++)
	{
		for(int x = BORDER; x < WIDTH + BORDER; x++)
		{
			unsigned char &world_ = world[y][x];
			unsigned char &all_ = all[y][x];
			unsigned int &nb_ = nb[y][x];

			if(all_ == 0)
			{
				if(world_ != EMPTY) NewGen2_SendForward(y, x);
				if(!(rand()%r) ) {world_ = ((x > (WIDTH>>1)+BORDER) ? GREEN : AGREEN) + rand()%3; NewGen2_SendBack(y, x);}
				else world_ = EMPTY;
			}
			else if ( (all_ & 0xF0) == 0) //Set1
			{
				if(CheckBox7->Checked && all_ == 0x07 && (nb_ & PURPLE_MASK) == 0 && world_ == EMPTY)   //B37/S23 условно
				{
					world_ = GREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(!CheckBox7->Checked && (nb_ & PURPLE_MASK) > 0x00006000)    //B378/S2378 условно
				{
					if(world_ != EMPTY) NewGen2_SendForward(y, x);
					world_ = GREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(world_ == EMPTY)
				{
					if(all_ == 0x03)
					{
						if( (nb_ & GREEN_MASK) > 0x00000001) world_ = GREEN;
						else if ( (nb_ & RED_MASK) > 0x00000010) world_ = RED;
						else if ( (nb_ & YELLOW_MASK) > 0x00000100) world_ = YELLOW;
						else world_ = PURPLE;
						//Fast SendBack()
						unsigned char *all__ = &all[y-1][x-1];
						unsigned int *nb__ = &nb[y-1][x-1];
						unsigned int world_color = 1<<(world_<<2);
						nb__[0] += world_color;	nb__[1] += world_color;	nb__[2] += world_color;	nb__[WIDTH_MAX + 2*BORDER] += world_color;
						all__[0]++; all__[1]++; all__[2]++; all__[WIDTH_MAX + 2*BORDER]++;
						sums[world_]++;
					}
				} else
				{
					NewGen2_SendForward(y, x);
					if(all_ < 0x02 || all_ > 0x03)
					{
						if(!(rand()%r) ) {world_ = ((x > (WIDTH>>1)+BORDER) ? GREEN : AGREEN) + rand()%3; NewGen2_SendBack(y, x);}
						else world_ = EMPTY;
					}
					else NewGen2_SendBack(y, x);
				}
				all_ = nb_ = 0;
			} else if( (all_ & 0x0F) == 0) //Set2
			{
				if(CheckBox8->Checked && all_ == 0x70 && (nb_ & APURPLE_MASK) == 0 && world_ == EMPTY)
				{
					world_ = AGREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(!CheckBox8->Checked && (nb_ & APURPLE_MASK) > 0x60000000)
				{
					if(world_ != EMPTY) NewGen2_SendForward(y, x);
					world_ = AGREEN + rand()%3;
					NewGen2_SendBack(y, x);
				}
				else if(world_ == EMPTY)
				{
					if(all_ == 0x30)
					{
						if( (nb_ & AGREEN_MASK)> 0x00010000) world_ = AGREEN;
						else if ( (nb_ & ARED_MASK) > 0x00100000) world_ = ARED;
						else if ( (nb_ & AYELLOW_MASK)> 0x01000000) world_ = AYELLOW;
						else world_ = APURPLE;
						//Fast SendBack()
						unsigned char *all__ = &all[y-1][x-1];
						unsigned int *nb__ = &nb[y-1][x-1];
						unsigned int world_color = 1<<(world_<<2);
						nb__[0] += world_color;	nb__[1] += world_color;	nb__[2] += world_color;	nb__[WIDTH_MAX + 2*BORDER] += world_color;
						all__[0] += 0x10; all__[1] += 0x10; all__[2] += 0x10; all__[WIDTH_MAX + 2*BORDER] += 0x10;
						sums[world_]++;
					}
				} else
				{
					NewGen2_SendForward(y, x);
					if(all_ < 0x20 || all_ > 0x30)
					{
						if(!(rand()%r) ) {world_ = ((x > (WIDTH>>1)+BORDER) ? GREEN : AGREEN) + rand()%3; NewGen2_SendBack(y, x);}
						else world_ = EMPTY;
					}
					else NewGen2_SendBack(y, x);
				}
				all_ = nb_ = 0;
			} else	//Collision
			{
				if(world_ != EMPTY) NewGen2_SendForward(y, x);
				if(CheckBox6->Checked)
				{
					int arad;
					switch( (all_ & 0x0F) + (all_ >> 4) )
					{
						case 2: coll1++; arad = arad1; break;
						case 3:	coll2++; arad = arad2; break;
						case 4:	coll3++; arad = arad3; break;
						case 5:
						case 6:
						case 7:
						case 8:	coll4++; arad = arad4; break;
						default:       //Just in-case
							//Application->MessageBox(L"NewGen2 Error: look at the collision section", L"Error", MB_OK);
							arad = 0;
						break;
					}
					for(int yy = std::max(y - arad, BORDER), h = y - yy; yy <= std::min(y + arad, BORDER + HEIGHT - 1); yy++)
					{
						for(int xx = std::max(x - arad + h, BORDER); xx <= std::min(x + arad - h, BORDER + WIDTH - 1); xx++)
						{
							if(yy < y || (yy == y && xx < x) )
							{
								if(world[yy][xx] != EMPTY) NewGen2_Delete(yy, xx);
								if(!(rand()%r) ) {world[yy][xx] = ((xx > (WIDTH>>1)+BORDER) ? GREEN : AGREEN) + rand()%3; NewGen2_SendBack(yy, xx);}
								else world[yy][xx] = EMPTY;

							} else if(yy == y && xx == x)
							{
								all[yy][xx] = nb[yy][xx] = 0;
								if(!(rand()%r) ) {world[yy][xx] = ((xx > (WIDTH>>1)+BORDER) ? GREEN : AGREEN) + rand()%3; NewGen2_SendBack(yy, xx);}
								else world[yy][xx] = EMPTY;
							}
							else
							{
								all[yy][xx] = nb[yy][xx] = 0;
								world[yy][xx] = EMPTY;
							}
						}
						if(yy < y) h--;
						else h++;
					}
				} else
				{
					all_ = nb_ = 0;
					if(!(rand()%r) ) {world_ = ((x > (WIDTH>>1)+BORDER) ? GREEN : AGREEN) + rand()%3; NewGen2_SendBack(y, x);}
					else world_ = EMPTY;
				}
			}
		}
	}
	sum = sums[GREEN] + sums[RED] + sums[YELLOW] + sums[PURPLE]; asum = sums[AGREEN] + sums[ARED] + sums[AYELLOW] + sums[APURPLE];
	gen++;
}

#endif  /*__NEWGEN_H*/

