//make a array for each number
// import value from the dip switch
// put dip value in array brackekts and set output equal to it

#include "stm32f4xx.h"

int main(void)
{
    RCC->AHB1ENR =  7;                 /* enable GPIOA, GPIOB and GPIOC clock */

		GPIOC->PUPDR =  0x00055555;        /* set pin to input mode 		PC 0 - 9 */
		GPIOC->MODER =  0x00500000;				 /* set pin to output mode 		PC 10 - 11 */
    GPIOA->MODER =  0x00055500;        /* set pin to output mode 		PA 4 - 9 */
		GPIOB->MODER =  0x00005555;        /* set pin to output mode 		PB 0 - 7 */
		
		while(1) 
		{
			unsigned int selector = (GPIOC->IDR  & 0x03);
			int A = ((GPIOC->IDR >> 2) & 0x0F);
			int B = ((GPIOC->IDR >> 6) & 0x0F);
			
			int C0 = (((A & 0x1)+(B & 0x1)) & 0x2);
			int C1 = ((((A & 0x2)+(B & 0x2) + C0)) & 0x4);
			int C2 = ((((A & 0x4)+(B & 0x4) + C1)) & 0x8);
			int C3 = ((((A & 0x8)+(B & 0x8) + C2)) & 0x10);
			int Y = (C2 >> 3);
			int X = (C3 >> 4);
			int V = X ^ Y;

			int i;
			unsigned int lookup[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
			
			switch(selector)
			{
				case 0:																																									// A & B
								GPIOA->ODR = (((A & B) << 4) & 0x03F0);	
								if((A & B) == 0) GPIOC->ODR |= 0x400; else GPIOC->ODR &= 0xBFF;	// z flag
								GPIOC->ODR &= 0x7FF; 																				//V flag shut off
								i = ((A & B) & 0x0F);
								GPIOB->ODR = lookup[i];
								break;
				case 1:																																									// A | B
								GPIOA->ODR = (((A | B) << 4) & 0x03F0); 
								if((A | B) == 0) GPIOC->ODR |= 0x400; else GPIOC->ODR &= 0xBFF; // z flag
								GPIOC->ODR &= 0x7FF;																			 //V flag shut off
								i = ((A | B) & 0x0F);
								GPIOB->ODR = lookup[i];
								break;
				case 2:																																									// A + B
								GPIOA->ODR = (((A + B) << 4) & 0x03F0);
								if((A + B) == 0) GPIOC->ODR |= 0x400; else GPIOC->ODR &= 0xBFF; // z flag
								if(V == 1) GPIOC->ODR |= 0x800; else GPIOC->ODR &= 0x7FF;       // V flag
								i = ((A + B) & 0x0F);
								GPIOB->ODR = lookup[i];
								break;
				case 3:																																									// A - B
								if(A < B)
								{
									GPIOA->ODR = ((((~(A + ~B)) << 4) & 0x03F0) | 0x0200); 
									if( (~(A + ~B))	== 0) GPIOC->ODR |= 0x400; else GPIOC->ODR &= 0xBFF; // z flag
									if(V == 1) GPIOC->ODR |= 0x800; else GPIOC->ODR &= 0x7FF;						 // V flag
									i = ((~(A + ~B)) & 0x0F);
									GPIOB->ODR = lookup[i];
								}else
								{
									GPIOA->ODR = (((A - B) << 4) & 0x03F0); 
									if((A - B) == 0) GPIOC->ODR |= 0x400; else GPIOC->ODR &= 0xBFF; // z flag
									if(V == 1) GPIOC->ODR |= 0x800; else GPIOC->ODR &= 0x7FF;				// V flag
									i = ((A - B) & 0x0F);
									GPIOB->ODR = lookup[i];
								}
								break;
			}
    }	
}
