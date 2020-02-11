#include<stdio.h>

/*Function key_opcode reads each character from the input.            *
 Moreover key_opcode checks if each opcode consists of 4 characters   *
and if each character is a number (1 to 9) or a letter (a,b,c,d,e,f). *
Then, key_opcode transforms this string to a real hex-number and      *
stores it in opcode2. After that key_opcode returns opcode2 .         */ 



unsigned short key_opcode(void)
{
	int counter=0, i, no_emit=0;
	unsigned short opcode2=0, opcode3=0;
	char key_str[4];
	char key;

	while(1)
	{
		key = getchar();
		if(key!=10)
		{
			if(counter<4)
			{
				key_str[counter] = key;
				++counter;
			}
			if(counter==4)
			{
				counter=0;
				for(i=0;i<4;++i)
				{
					if(key_str[i]>47)
					{
						if(key_str[i]<58)
						{
							opcode3 = (unsigned short) (key_str[i]-48);
							opcode3 = opcode3<<(12-i*4);
							opcode2 = opcode2 + opcode3;
							opcode3 = 0; 
						}
						else if((key_str[i]>64) && (key_str[i]<71))
						{
							opcode3 = (unsigned short) (key_str[i]-55);
							opcode3 = opcode3<<(12-i*4);
							opcode2 = opcode2 + opcode3;
							opcode3 = 0;
						}
						else if((key_str[i]>96) && (key_str[i]<103))
						{
							opcode3 = (unsigned short) (key_str[i]-87);
							opcode3 = opcode3<<(12-i*4);
							opcode2 = opcode2 + opcode3;
							opcode3 = 0;
						}
						else
						{
							opcode3 = 0;
							i = 4;
							no_emit = 1;
							printf("bad opcode \n");
						}
					}
					else
					{
						opcode3 = 0;
						i = 4;
						no_emit = 1;
						printf("bad opcode\n");
					}
				}
				if(no_emit==0)
				{
					return(opcode2);
				}
				opcode2 = 0; /*reset opcode2 to 0 */
				no_emit = 0; /*reset no_emit to 0 */
				key_str[counter] = key;
			}
		}
		if(key==10)
		{
			counter=0;
		}
	}
}
