#ifndef QWIDGET_NEU_H
#define QWIDGET_NEU_H

/*declaration of all widgets, threads and major functions is done here: */

#include<QObject>
#include<QWidget>
#include<QThread>
#include<QPainter>
#include<QPaintEvent>
#include<stdio.h>
#include<unistd.h>
#include "memory1h.h"


	
class Thread1: public QThread
{
	Q_OBJECT

public:
	Thread1(void);
	~Thread1(void);
	
	void initialize1(void);
	void clear_memory(void);
	void clear_stack(void);
	void clear_gfx(void);
	void clear_key(void);
	void clear_register(void);
	void load_fontset(void);
	void load_program(char* source);
	unsigned short opcode_memory(void);
	void fu_op(unsigned short op1);
	void update_timer(void);	
	void fu_connect(Thread2* Inst_t2);	

	void run(void);
	
public slots:
	void fu_slot1(unsigned short opcode2_s);
signals:
	void fu_signal1(void);
};


class QWidget_neu: public QWidget
{
	Q_OBJECT

	Thread1 Instt1;
	unsigned short opcode;
	int i, j, window_scale;
	char* source = {""/*source of program-file has to be included here*/};
	
public:
	QWidget_neu(void);
	~QWidget_neu(void);
	
	void paintEvent(QPaintEvent* event);

public slots:
	void fu_slot1(void);
};



#endif
