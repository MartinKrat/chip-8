/* Declaration of variables used for chip-8 implementation.  *
*  Definition of these variables is done in another module. */
 


	/* total memory of chip8 : */
	extern unsigned char memory[4096];

	/*registers of chip8 : */
	extern unsigned char V[16]; /*r16*/

	/*program counter of chip8 : */
	extern unsigned short pc;

	/*index register of chip8 : */
	extern unsigned short I; /*ri;*/

	/*stack of chip8 : */
	extern unsigned short stack[16];

	/*stack-pointer of chip8 : */
	extern unsigned char sp;

	/*delay-timer register of chip8 : */
	extern unsigned char delay_timer; /*rd_t*/

	/*sound-timer register of chip8 :*/
	extern unsigned char sound_timer; /*rs_t*/

	/*pixel state of screen of chip8 :*/
	extern unsigned char gfx[64][32];
