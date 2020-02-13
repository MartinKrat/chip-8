#define MEMORY1H_H
#include "memory1h.h"



/*total memory of chip8 : */
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
/*keypad-memory of chip8 : */
unsigned char key[16];
