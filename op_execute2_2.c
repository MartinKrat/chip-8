#include<stdio.h>
#include<stdlib.h>
#include"memory1h.h"

#ifdef Test
	#define Print printf("not yet implemented !\n");
#else
	#define Print /* not yet implemented */
#endif



/* function  void fu_op(unsigned short op1)  selects the 1th nibble (counted from most significant nibble)   * 
*  of the variable  unsigned short op1  and checks its value. The same is done with the other nibbles of the * 
*  variable. The opcode can be identified by doing this :     						    */
                                        
void fu_op(unsigned short op1)
{
	unsigned short op1_1=0x0, op1_2=0x0, op1_3=0x0, op1_4=0x0;

	op1_1 = op1>>12;
	op1_2 = op1 & 0x0f00;
	op1_2 = op1_2>>8;
	op1_3 = op1 & 0x00f0;
	op1_3 = op1_3>>4;
	op1_4 = op1 & 0x000f;
	
	if(op1_1==0x0)
	{
		if(op1_2==0x0)
		{
			if(op1_3==0xe)
			{
				if(op1_4==0x0)
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
				else if(op1_4==0xe)
				{
					Print
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
			printf("Call RCA 1802 program at address NNN (not implemented) \n");
		}
	}
	
	
	if(op1_1==0x1)
	{
		unsigned short op2;
		op2 = op1<<4;
		op2 = op2>>4;

		pc = op2;
	}
	
	
	if(op1_1==0x2)
	{
		Print
	}
	
	
	if(op1_1==0x3)
	{
		unsigned short op2;	
		op2 = op1 & 0x00ff;

		if(V[op1_2]==op2)
		{
			pc = pc + 2;
		}
	}
	
	
	if(op1_1==0x4)
	{
		unsigned short op2;
		op2 = op1 & 0x00ff;

		if(V[op1_2]!=op2)
		{
			pc = pc + 2;
		}
	}
	
	
	if(op1_1==0x5)
	{
		if(op1_4 == 0x0)
		{
			if(V[op1_2]==V[op1_3])
			{
				pc = pc + 2;
			}
		}
		else
		{
			printf("bad opcode\n");
		}
	}
	
	
	if(op1_1==0x6)
	{
		unsigned short op2;
		op2 = op1 & 0x00ff;

		V[op1_2] = op2;
	}
	
	
	if(op1_1==0x7)
	{
		unsigned short op2;
		op2 = op2 & 0x00ff;

		V[op1_2] = V[op1_2] + op2;
	}
	
	
	if(op1_1==0x8)
	{
		unsigned short carry1=0x0, carry2=0x0;

		if(op1_4==0x0)
		{
			V[op1_2] = V[op1_3];
		}
		else if(op1_4==0x1)
		{
			V[op1_2] = V[op1_2] | V[op1_3];
		}		
		else if(op1_4==0x2)
		{
			V[op1_2] = V[op1_2] & V[op1_3];
		}
		else if(op1_4==0x3)
		{
			V[op1_2] = V[op1_2] ^ V[op1_3];
		}
		else if(op1_4==0x4)
		{
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
		else if(op1_4==0x5)
		{
			Print
		}
		else if(op1_4==0x6)
		{
			V[15] = V[op1_2] & 0x01;
			V[op1_2] = V[op1_2]>>1;
		}
		else if(op1_4==0x7)
		{
			Print
		}
		else if(op1_4==0xe)
		{
			V[15] = V[op1_2]>>7;
			V[op1_2] = V[op1_2]<<1;
		}
		else
		{
			printf("bad opcode\n");
		}	
	}
	
	
	if(op1_1==0x9)
	{
		if(op1_4==0)
		{
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
	
	
	if(op1_1==0xa)
	{
		unsigned short op2;
		op2 = op1<<4;
		op2 = op2>>4;

		I = op2;
	}
	
	
	if(op1_1==0xb)
	{
		unsigned short op2;
		op2 = op1<<4;
		op2 = op2>>4;

		pc = op2 + V[0];
	}
	
	
	if(op1_1==0xc)
	{
		unsigned short op2;		
		op2 = op1 & 0x00ff;

		V[op1_2] = (rand()%256) & op2;
	}
	
	
	if(op1_1==0xd)
	{
		int i,j;

		V[0xf] = 0;

		for(j=0;j<op1_4;++j)
		{
			for(i=0;i<8;++i)
			{
				if( (memory[(I+j)] & (0x01<<(7-i))) != 0 )
				{
					/* pixel at location [op1_2+i][op1_3+j] in gfx that is 0, flips to 1 : */
					if( (gfx[op1_2+i][op1_3+j] ^ (memory[(I+j)]&(0x01<<(7-i)))) == 1 )
					{
						V[0xf] = 1;
						gfx[op1_2+i][op1_3+j] = 1;
					}
					/* pixel at location [op1_2+i][op1_3+j] in gfx that is 1, flips to 0 : */ 
					if( (gfx[op1_2+i][op1_3+j] ^ (memory[(I+j)]&(0x01<<(7-i)))) == 0 )
					{
						gfx[op1_2+i][op1_3+j] = 0;	
					}
				} 
			}
		}
	}
	
	
	if(op1_1==0xe)
	{
		Print
	}
	
	
	if(op1_1==0xf)
	{
		if(op1_3==0x0)
		{
			if(op1_4==0x7)
			{
				Print
			}
			else if(op1_4==0xa)
			{
				Print
			}
			else
			{
				printf("bad opcode\n");
			}
		}
		else if(op1_3==0x1)
		{
			if(op1_4==0x5)
			{
				delay_timer = V[op1_2];
			}
			else if(op1_4==0x8)
			{
				sound_timer = V[op1_2];
			}
			else if(op1_4==0xe)
			{
				Print
			}
			else
			{
				printf("bad opcode\n");
			}
		}
		else if(op1_3==0x2)
		{
			if(op1_4==0x9)
			{
				Print
			}
			else
			{
				printf("bad opcode\n");
			}		
		}
		else if(op1_3==0x3)
		{
			if(op1_4==0x3)
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
			if(op1_4==0x5)
			{
				unsigned char i;

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
			if(op1_4==0x5)
			{
				unsigned char i;

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
	
	
}

