#include<QApplication>
#include<QPainter>
#include<QWidget>



/* total memory of chip8 : */
unsigned char memory[4096];

/*registers of chip8 : */
unsigned char V[16]; /*r16*/

/*program counter of chip8 : */
unsigned short pc;

/*index register of chip8 : */
unsigned short I; /*ri;*/

/*stack of chip8 : */
unsigned short stack[16];

/*stack-pointer of chip8 : */
unsigned char sp;

/*delay-timer register of chip8 : */
unsigned char delay_timer; /*rd_t*/

/*sound-timer register of chip8 :*/
unsigned char sound_timer; /*rs_t*/

/*pixel state of screen of chip8 :*/
unsigned char gfx[64][32];

class QPaint2: public QWidget
{
	public:
	void paintEvent(QPaintEvent *event)
	{
		int i,j;
		for(i=0;i<64;++i)
		{
			for(j=0;j<32;++j)
			{
				/*checks gfx if a pixel has to be drawn or not */
				if(gfx[i][j] == 1)
				{
					QPainter Inst_p2(this);
					Inst_p2.drawRect((i*4),(j*4),4,4); /*x , y*/
				}
			}
		}
	}
};


/* This is not the final main-function. This modul just draws a 4*64 x 4*32 window on the screen.  *
* Later, this window will represent the screen of the chip-8 emulator.                             *
* Yet, no signal-handling is implemented. Pixel-drawing is now implemented:                       */  
int main(int argc, char** argv)
{
	QApplication Window1(argc, argv);

	QPaint2 Inst_but;
	Inst_but.paintEvent(NULL);;
	Inst_but.setGeometry(500,500,(4*64),(4*32));
	Inst_but.show();

return(Window1.exec());
}
