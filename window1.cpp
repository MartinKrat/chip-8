#include<QApplication>
#include<QPushButton>
#include<QPainter>


/* This is not the final main-function. This modul just draws a 4*128 x 4*64 window on the screen. *
* Later, this window will represent the screen of the chip-8 emulator.                             *
* Yet, no signal-handling or pixel-drawing is implemented.                                        */  
int main(int argc, char** argv)
{
	QApplication Window1(argc, argv);

	QPushButton Window_push_button1;
	Window_push_button1.setGeometry(200,200,(4*128),(4*64));
	Window_push_button1.show();

return(Window1.exec());
}
