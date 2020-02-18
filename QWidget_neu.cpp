#include "QWidget_neu.h"



Thread1::Thread1(void)
{
	initialize1();
	clear_memory();
	clear_stack();
	clear_gfx();
	clear_key();
	clear_register();
	load_fontset();
}

Thread1::~Thread1(void)
{
}

void Thread1::clear_memory(void)
{
	int i=0;
	for(i=0;i<4096;++i)
	{
		memory[i] = 0;
	}
}

void Thread1::clear_stack(void)
{
	int i=0;
	for(i=0;i<16;++i)
	{
		stack[i] = 0;
	}
}

void Thread1::clear_gfx(void)
{
	int i=0, j=0;
	for(i=0;i<32;++i)
	{
		for(j=0;j<64;++j)
		{
			gfx[j][i] = 0;
		}
	}
}

void Thread1::clear_key(void)
{
	int i=0;
	for(i=0;i<16;++i)
	{
		key[i] = 0;
	}
}

void Thread1::clear_register(void)
{
	int i=0;
	for(i=0;i<16;++i)
	{
		V[i] = 0;
	}
}

void Thread1::initialize1(void)
{
	opcode = 0;
	I = 0;
	sp = 0;
	delay_timer = 0;
	sound_timer = 0;
	pc = 0x200;
}

void Thread1::load_fontset(void)
{
	unsigned char chip8_fontset[80] =
	{ 
	  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	  0x20, 0x60, 0x20, 0x20, 0x70, // 1
	  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
	int i=0;
	for(i=0;i<80;++i)
	{
		memory[(0x50+i)] = chip8_fontset[i];
	}
}

void Thread1::load_program(char* source)
{
	FILE * re_open;
	unsigned short opcode;
	int re_char, i=0, counter_memory=0;
	const char mode1 = 'r';

	re_open = fopen(source, &mode1);
	if(re_open==NULL)
	{
		printf("error: Not possible to open file\n");
	}
	else
	{
		while(1)
		{
				re_char = fgetc(re_open);
				if(re_char==EOF)
				{
					break;
				}
				memory[0x200+counter_memory] = re_char;
				++counter_memory;
				if((0x200+counter_memory)>(4096-1))
				{
					printf("loading program: memory size exceeded\n");
					break;
				}
		}
		fclose(re_open);
	}
}

unsigned short Thread1::opcode_memory(void)
{
	unsigned short opcode;
	opcode = memory[(pc+1)];
	opcode = opcode<<8;
	opcode = opcode + memory[pc];

return(opcode);
}

/* function  void fu_op(unsigned short op1)  selects the 1th nibble (counted from most significant nibble)   * 
*  of the variable  unsigned short op1  and checks its value. The same is done with the other nibbles of the * 
*  variable. The opcode can be identified by doing this :     						    */                                        
void Thread1::fu_op(unsigned short op1)
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
					if(sp>=1)
					{
						stack[sp] = 0x0; 
						--sp; /*decrement stack pointer*/
						pc = stack[sp];
					}
					else
					{
						printf("stack pointer exceeds minimum\n");
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

		pc = op2 - 2; 	
	}
	
	
	if(op1_1==0x2)
	{
		unsigned short subr_addr;
		stack[sp] = pc;
		++sp; /*increment stack pointer*/
		
		if(sp<=0xf)
		{
			subr_addr = op1 & 0xfff;
			pc = subr_addr - 2; 
		}
		else
		{
			printf("stack pointer exceeds maximum\n");
		}
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
		op2 = op1 & 0x00ff;

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
			if(V[op1_2]>=V[op1_3])
			{
				V[0xf] = 1;
				V[op1_2] = V[op1_2] - V[op1_3];
			}
			else
			{
				V[0xf] = 0;
				V[op1_2] = V[op1_2] - V[op1_3];
			}
		}
		else if(op1_4==0x6)
		{
			V[15] = V[op1_2] & 0x01;
			V[op1_2] = V[op1_2]>>1;
		}
		else if(op1_4==0x7)
		{
			if(V[op1_3]>=V[op1_2])
			{
				V[0xf] = 1;
				V[op1_2] = V[op1_3] - V[op1_2];
			}
			else
			{
				V[0xf] = 0;
				V[op1_2] = V[op1_3] - V[op1_2];
			}
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
		unsigned char** gfx2;
		int i,j;
		unsigned char and1, and2, exor, vx_value, vy_value;

		V[0xf] = 0;
		vx_value = V[op1_2];
		vy_value = V[op1_3];
		for(j=0;j<op1_4;++j)
		{
			for(i=0;i<8;++i)
			{
				and1 = memory[(I+j)] & (0x01<<(7-i));
				and2 = and1>>(7-i);
				exor = gfx[((vx_value+i)%64)][((vy_value+j)%32)] ^ and2;
				if( exor==0x1 )
				{
					gfx[((vx_value+i)%64)][((vy_value+j)%32)] = 1;
				}
				if( exor==0x0 )
				{
					if(gfx[((vx_value+i)%64)][((vy_value+j)%32)] == 1 )/* checks if screen flips from set to unset*/
					{
						V[0xf] = 1;
					} 
					gfx[((vx_value+i)%64)][((vy_value+j)%32)] = 0;	
				}
			}
		}
		emit fu_signal1();
	}
	
	
	
	
	if(op1_1==0xe)
	{
		/*missing: Print*/
	}
	
	
	if(op1_1==0xf)
	{
		if(op1_3==0x0)
		{
			if(op1_4==0x7)
			{
				V[op1_2] = delay_timer;
			}
			else if(op1_4==0xa)
			{
				/*missing: Print*/
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
				I = I + V[op1_2];
				if(I>0xfff)
				{
					V[0xf] = 1;
				}
				else
				{
					V[0xf] = 0;					
				}
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
				I = 0x50 + V[op1_2]*5;
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


void Thread1::update_timer(void)
{
	if(delay_timer>0)
	{
    		--delay_timer;
	}
  	if(sound_timer>0)
  	{
    		if(sound_timer == 1)
		{
		      printf("BEEP!\n");
		}
    		--sound_timer;
	}
	printf("update timer\n");
}

void Thread1::fu_connect(Thread2* Inst_t2)
{
	connect(Inst_t2, SIGNAL(fu_signal1(unsigned short)), this, SLOT(fu_slot1(unsigned short)) );
}

void Thread1::run(void)
{
	int k=0;
	while(1)
	{
		opcode = opcode_memory();
		fu_op(opcode);
		pc+=2;
		update_timer();
	}
}

void Thread1::fu_slot1(unsigned short opcode2_s)
{
	opcode = opcode2_s;
}

//-----------------------------------------------------------

QWidget_neu::QWidget_neu(void)
{
	window_scale = 4;
	connect( &Instt1, SIGNAL(fu_signal1(void)), this, SLOT(fu_slot1(void)) );
	Instt1.load_program(source);
	Instt1.start();
}

QWidget_neu::~QWidget_neu(void)
{
}

void QWidget_neu::paintEvent(QPaintEvent* event)
{
	QPainter painter1(this);
	for(i=0;i<32;++i)
	{
		for(j=0;j<64;++j)
		{
			if(gfx[j][i]==1)
			{
				painter1.drawRect((window_scale*j),(window_scale*i),(window_scale),(window_scale));
			}
		}
	}
}

void QWidget_neu::fu_slot1(void)
{
	update();
}






