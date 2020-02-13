#include<QtGui/QApplication>
#include "QWidget_neu.h"
#include "memory1h.h"



/* This modul just draws a 4*64 x 4*32 window on the screen.                                       *
* Later, this window will represent the screen of the chip-8 emulator.                             */

int main(int argc, char** argv)
{
	QApplication Window1(argc, argv);

	QWidget_neu Inst_w1;
	Inst_w1.setGeometry(200,200,(4*64),(4*32));
	Inst_w1.show();

return(Window1.exec());
}
