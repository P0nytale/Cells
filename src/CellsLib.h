#ifndef __CELLSLIB_H
#define __CELLSLIB_H

#define EMA1_K 1
#define EMA1_K_HBIT_MASK 0x0001

unsigned int EMA1(unsigned int in)
{
	static unsigned int valOld = 0;
	valOld += in;
	int ema = (valOld + EMA1_K_HBIT_MASK) >> EMA1_K;
	valOld -= ema;
	return ema;
}

#define EMA2_K 1
#define EMA2_K_HBIT_MASK 0x0001
unsigned int EMA2(unsigned int in)
{
	static unsigned int valOld = 0;
	valOld += in;
	int ema = (valOld + EMA2_K_HBIT_MASK) >> EMA2_K;
	valOld -= ema;
	return ema;
}

#define EMA3_K 2
#define EMA3_K_HBIT_MASK 0x0002
unsigned int EMA3(unsigned int in)
{
	static unsigned int valOld = 0;
	valOld += in;
	int ema = (valOld + EMA3_K_HBIT_MASK) >> EMA3_K;
	valOld -= ema;
	return ema;
}

#define EMA4_K 2
#define EMA4_K_HBIT_MASK 0x0002
unsigned int EMA4(unsigned int in)
{
	static unsigned int valOld = 0;
	valOld += in;
	int ema = (valOld + EMA4_K_HBIT_MASK) >> EMA4_K;
	valOld -= ema;
	return ema;
}

#endif /*__CELLSLIB_H*/

