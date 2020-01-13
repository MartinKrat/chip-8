#include<stdio.h>
#include"memory1h.h"



/* sub-functions which are called by the function  void fu_op(unsigned short)  *
*  (In future implementations there will be only one function) :              */
void fu_0NNN(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_2=0x0, op1_3=0x0;

	op1_1 = op1 & 0x0f00;
	op1_1 = op1_1>>8;

	if(op1_1==0x0)
	{
		op1_2 = op1 & 0x00f0;
		op1_2 = op1_2>>4;

		if(op1_2==0xe)
		{
			op1_3 = op1 & 0x000f;

			if(op1_3==0x0)
			{
				unsigned char i, j;

				for(i=0;i<64;++i)
				{					
					for(j=0;j<32;++j)
					{
						gfx[i][j] = 0x0;
					}
				}
			}
			else if(op1_3==0xe)
			{
				/*not yet implemented !*/
			}
			else
			{
				printf("bad opcode\n");
			}
		}
		else
		{
			printf("bad opcode\n");
		}
	}
	else
	{
		printf("bad opcode: Call RCA 1802 program at address NNN (not implemented) \n");
	}
}


void fu_1NNN(unsigned short op1)
{
	op1 = op1<<4;
	op1 = op1>>4;

	pc = op1;
}


void fu_2NNN(unsigned short op1)
{
	/*not yet implemented*/
}


void fu_3XNN(unsigned short op1)
{
	unsigned short op1_1;

	op1_1 = op1 & 0x0f00;
	op1_1 = op1_1>>8;

	op1 = op1 & 0x00ff;

	if(V[op1_1]==op1)
	{
		pc = pc + 2;
	}
}


void fu_4XNN(unsigned short op1)
{
	unsigned short op1_1;

	op1_1 = op1 & 0x0f00;
	op1_1 = op1_1>>8;

	op1 = op1 & 0x00ff;

	if(V[op1_1]!=op1)
	{
		pc = pc + 2;
	}
}


void fu_5XNN(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_3=0x0;

	op1_1 = op1 & 0x0f00;
	op1_1 = op1_1>>8;

	op1_3 = op1 & 0x00f0;
	op1_3 = op1_3>>4;

	if(V[op1_1]==V[op1_3])
	{
		pc = pc + 2;
	}
}


void fu_6XNN(unsigned short op1)
{
	unsigned short op1_1;

	op1_1 = op1 & 0x0f00;
	op1_1 = op1_1>>8;

	op1 = op1 & 0x00ff;

	V[op1_1] = op1;
}


void fu_7XNN(unsigned short op1)
{
	unsigned short op1_1;

	op1_1 = op1 & 0x0f00;
	op1_1 = op1_1>>8;

	op1 = op1 & 0x00ff;

	V[op1_1] = V[op1_1] + op1;
}


void fu_8XYN(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_2=0x0, op1_3=0x0, carry1=0x0, carry2=0x0;
	
	op1_1 = op1 & 0x000f;

	if(op1_1==0x0)
	{
		op1_2 = op1 & 0x0f00;
		op1_2 = op1_2>>8;

		op1_3 = op1 & 0x00f0;
		op1_3 = op1_3>>4;

		V[op1_2] = V[op1_3];
	}
	else if(op1_1==0x1)
	{
		op1_2 = op1 & 0x0f00;
		op1_2 = op1_2>>8;

		op1_3 = op1 & 0x00f0;
		op1_3 = op1_3>>4;

		V[op1_2] = V[op1_2] | V[op1_3];
	}
	else if(op1_1==0x2)
	{
		op1_2 = op1 & 0x0f00;
		op1_2 = op1_2>>8;

		op1_3 = op1 & 0x00f0;
		op1_3 = op1_3>>4;

		V[op1_2] = V[op1_2] & V[op1_3];
	}
	else if(op1_1==0x3)
	{
		op1_2 = op1 & 0x0f00;
		op1_2 = op1_2>>8;

		op1_3 = op1 & 0x00f0;
		op1_3 = op1_3>>4;

		V[op1_2] = V[op1_2] ^ V[op1_3];
	}
	else if(op1_1==0x4)
	{
		op1_2 = op1 & 0x0f00;
		op1_2 = op1_2>>8;

		op1_3 = op1 & 0x00f0;
		op1_3 = op1_3>>4;

		carry1 = V[op1_2] + V[op1_3];
		carry2 = carry1>>8;
		if(carry2>0x0)
		{
			V[15] = 0x1;
			V[op1_2] = (unsigned char) carry1;
		}
		else
		{
			V[15] = 0x0;
			V[op1_2] = (unsigned char) carry1;
		}
	}
	else if(op1_1==0x5)
	{
	}
	else if(op1_1==0x6)
	{
		V[15] = V[op1_2] & 0x01;
		V[op1_2] = V[op1_2]>>1;
	}
	else if(op1_1==0x7)
	{
	}
	else if(op1_1==0xe)
	{
		V[15] = V[op1_2]>>7;
		V[op1_2] = V[op1_2]<<1;
	}
	else
	{
		printf("bad opcode\n");
	}
}


void fu_9XY0(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_2=0x0, op1_3=0x0;

	op1_1 = op1 & 0x000f;
	
	if(op1_1==0)
	{
		op1_2 = op1 & 0x0f00;
		op1_2 = op1_2>>8;

		op1_3 = op1 & 0x00f0;
		op1_3 = op1_3>>4;

		if(V[op1_2]!=V[op1_3])
		{
			pc = pc + 2;
		}
	}
	else
	{
		printf("bad opcode\n");
	}
}


void fu_ANNN(unsigned short op1)
{
	op1 = op1<<4;
	op1 = op1>>4;

	I = op1;
}


void fu_BNNN(unsigned short op1)
{
	op1 = op1<<4;
	op1 = op1>>4;

	pc = op1 + V[0];
}


void fu_CXNN(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_2=0x0;

	op1_1 =	op1 & 0x00ff;

	op1_2 = op1 & 0x0f00;
	op1_2 = op1_2>>8;
	V[op1_2] = (rand()%256) & op1_1;
}

void fu_DXYN(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_2=0x0, op1_3=0x0;
	int i=0,j=0;

	op1_1 = op1 & 0x000f;

	op1_2 = op1 & 0x0f00;
	op1_2 = op1_2>>8;

	op1_3 =	op1 & 0x00f0;
	op1_3 = op1_3>>4;

	V[0xf] = 0;

	for(j=0;j<op1_1;++j)
	{
		for(i=0;i<8;++i)
		{
			if( (memory[(I+j)] & (0x01<<(7-i))) != 0 )
			{
				/* pixel at location [op1_2+i][op1_3j] in gfx that is 0, flips to 1 : */
				if( (gfx[op1_2+i][op1_3+j] ^ (memory[(I+j)]&(0x01<<(7-i)))) == 1 )
				{
					V[0xf] = 1;
					gfx[op1_2+i][op1_3+j] = 1;
				}
				/* check: pixel at location [op1_2+i][op1_3j] in gfx that is 1, flips to 0 : */ 
				if( (gfx[op1_2+i][op1_3+j] ^ (memory[(I+j)]&(0x01<<(7-i)))) == 0 )
				{
					gfx[op1_2+i][op1_3+j] = 0;	
				}
			} 
		}
	}
}


void fu_EXNN(unsigned short op1)
{
	/*not yet implemented*/
}


void fu_FXNN(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_2=0x0, op1_3=0x0;

	op1_1 = op1 & 0x000f;

	op1_2 = op1 & 0x0f00;
	op1_2 = op1_2>>8;

	op1_3 =	op1 & 0x00f0;
	op1_3 = op1_3>>4;

	if(op1_3==0x0)
	{
		if(op1_1==0x7)
		{
			/*not yet implemented !*/
		}
		else if(op1_1==0xa)
		{
			/*not yet implemented !*/
		}
		else
		{
			printf("bad opcode\n");
		}
	}
	else if(op1_3==0x1)
	{
		if(op1_1==0x5)
		{
			delay_timer = V[op1_2];
		}
		else if(op1_1==0x8)
		{
			sound_timer = V[op1_2];
		}
		else if(op1_1==0xe)
		{
			/*not yet implemented !*/
		}
		else
		{
			printf("bad opcode\n");
		}
	}
	else if(op1_3==0x2)
	{
		if(op1_1==0x9)
		{
			/*not yet implemented !*/
		}
		else
		{
			printf("bad opcode\n");
		}		
	}
	else if(op1_3==0x3)
	{
		if(op1_1==0x3)
		{
			memory[I+2] = op1_2%10;
			memory[I+1] = op1_2%100;
			memory[I] = op1_2%1000;
		}
		else
		{
			printf("bad opcode\n");
		}
	}
	else if(op1_3==0x5)
	{
		if(op1_1==0x5)
		{
			unsigned char i=0;

			for(i=0;i<(op1_2+1);++i)
			{
				memory[(I+i)]= V[i]; 
			}
		}
		else
		{
			printf("bad opcode\n");
		}
	}
	else if(op1_3==0x6)
	{
		if(op1_1==0x5)
		{
			unsigned char i=0;

			for(i=0;i<(op1_2+1);++i)
			{
				V[i] = memory[(I+i)]; 
			}
		}
		else
		{
			printf("bad opcode\n");
		}
	}
	else
	{
		printf("bad opcode\n");
	}
}


/* function  void fu_op(unsigned short )  selects the 4th nibble (counted from least significant nibble)    * 
*  of the variable  unsigned short op1  and checks its value. Then the suitable function for that value is  *
*  called.												    *
*  (in future implementations there will be only one function):                                            */
void fu_op(unsigned short op1)
{
	unsigned short op2=0x0;

	op2 = op1>>12;
	
	if(op2==0x0)
	{
		fu_0NNN(op1);
	}
	if(op2==0x1)
	{
		fu_1NNN(op1);
	}
	if(op2==0x2)
	{
		fu_2NNN(op1);
	}
	if(op2==0x3)
	{
		fu_3XNN(op1);
	}
	if(op2==0x4)
	{
		fu_4XNN(op1);
	}
	if(op2==0x5)
	{
		fu_5XNN(op1);
	}
	if(op2==0x6)
	{
		fu_6XNN(op1);
	}
	if(op2==0x7)
	{
		fu_7XNN(op1);
	}
	if(op2==0x8)
	{
		fu_8XYN(op1);
	}
	if(op2==0x9)
	{
		fu_9XY0(op1);
	}
	if(op2==0xa)
	{
		fu_ANNN(op1);
	}
	if(op2==0xb)
	{
		fu_BNNN(op1);
	}
	if(op2==0xc)
	{
		fu_CXNN(op1);
	}
	if(op2==0xd)
	{
		fu_DXYN(op1);
	}
	if(op2==0xe)
	{
		fu_EXNN(op1);
	}
	if(op2==0xf)
	{
		fu_FXNN(op1);
	}
}

