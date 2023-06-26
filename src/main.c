/*

 Name: Sara Ayman Mohamed Abdullah
 Section: 1
 Bench Number: 39

 */


#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"



// Enable port B
// Define pin register mode/type for port B pin 3 &
// Define input register external pull up register
// Define input register data for port A pin 3


// -------------------------------- ADDRESSES Definitions ---------------------------------


#define GPIOB_BASE_ADD 0x40020400
#define MODER_OFFSET 0x00
#define MODER_ADD  *(unsigned long*) (GPIOB_BASE_ADD+MODER_OFFSET)

#define INPUT_TYPER_OFFSET 0x0C
#define INPUT_TYPER_ADD  *(unsigned long*)(GPIOB_BASE_ADD+INPUT_TYPER_OFFSET)
#define INPUT_DATAR_OFFSET 0x10
#define INPUT_DATAR_ADD *(unsigned long*)(GPIOB_BASE_ADD+INPUT_DATAR_OFFSET)

#define OUTPUT_TYPER_OFFSET 0x04
#define OUTPUT_TYPER_ADD (*(unsigned long*)(GPIOB_BASE_ADD+OUTPUT_TYPER_OFFSET))
#define OUTPUT_DATAR_OFFSET 0x14
#define OUTPUT_DATAR_ADD ( *(unsigned long*)(GPIOB_BASE_ADD+OUTPUT_DATAR_OFFSET) )


// Enable PORTB
#define RCC_PORTB_CLK *(unsigned long*)(0x40023800+0x30)
// Enable internal CLK
#define RCC_CONTROLR *(unsigned long*)(0x40023800+0x00)







// ---------------------------------------- main() -----------------------------------------


int main()
{


	RCC_PORTB_CLK |= (1 << 1);			// Enable PORTB CLK
    RCC_CONTROLR |= (1 << 0);			// Enable internal CLK
    MODER_ADD &= ~(0x03 << 2*3);		// Define Pin 3 as Input


    MODER_ADD |= (1 << 2*5);		// Define Pin 5 as Output
    MODER_ADD |= (1 << 2*6);		// Define Pin 6 as Output
    MODER_ADD |= (1 << 2*7);		// Define Pin 7 as Output


    INPUT_TYPER_ADD |= (1 << 6);			// Define Pull-up Resistance as Input type
    //INPUT_DATAR_ADD= ;					// Take the state of the push button

    OUTPUT_TYPER_ADD &= ~(0x07 << 5);		// Define Push-Pull as Output type
    //OUTPUT_DATAR_ADD= ;					// Define the state of the Leds

    unsigned int states = 1;					// The state of the 3 leds
    unsigned char prevValue= 1;					// Get the previous state of button


   // Scan the Button Infinitely
   while (1)
    {



	   // wait for 1s then check for the button's state
	  /* for(int i = 0; i < 1000000; i++){

	   }*/


	  // Check if Button is pressed & previous value was 1 (indicates falling edge)
	  if( (!(INPUT_DATAR_ADD&(1<<3))) && (prevValue==1) ){


		   // wait for 1s to overcome the debounce effect
		  for(int i = 0; i < 1000000; i++);


		  // Check if the button is still pressed
		  if(! (INPUT_DATAR_ADD&(1<<3)) ){

			   switch(states){


			   case 1:
				   OUTPUT_DATAR_ADD |= (1<<5);
				   states+=1;
				   break;
			   case 2:
				   OUTPUT_DATAR_ADD |= (1<<6);
				   states+=1;
				   break;
			   case 3:
				   OUTPUT_DATAR_ADD |= (0x03<<5);
				   states+=1;
				   break;
			   case 4:
				   OUTPUT_DATAR_ADD |= (1<<7);
				   states+=1;
				   break;
			   case 5:
				   OUTPUT_DATAR_ADD |= (1<<5);
				   OUTPUT_DATAR_ADD |= (1<<7);
				   states+=1;
				   break;
			   case 6:
				   OUTPUT_DATAR_ADD |= (1<<6);
				   OUTPUT_DATAR_ADD |= (1<<7);
				   states+=1;
				   break;
			   case 7:
				   OUTPUT_DATAR_ADD |= (1<<5);
				   OUTPUT_DATAR_ADD |= (0x03<<6);
				   states=1;
				   break;

			   }	// End of switch case


		  }	// End of second check on button / debounce effect



	  }		// End of first check on button







	  // Get the current state of the button
	  if(!(INPUT_DATAR_ADD&(1<<3))){

		   // wait for 1s to overcome the debounce effect
		   for(int i = 0; i < 1000000; i++);

		  	// Check if the button is still pressed
		   if(! (INPUT_DATAR_ADD&(1<<3)) ){

			   // Set the previous value to 0
			   prevValue = 0;

		   }
	   }


	  // If Push Button Not pressed
	  else if(INPUT_DATAR_ADD&(1<<3)){

			  // wait for 1s to overcome the debounce effect
			  for(int i = 0; i < 1000000; i++);

			  // Check if the button is still pressed
			  if(INPUT_DATAR_ADD&(1<<3)){

				  // Clear all LEDS
				  OUTPUT_DATAR_ADD &= ~(0x03<<5);
				  OUTPUT_DATAR_ADD &= ~(1<<7);

				  // Set the Previous value to 1
				  prevValue = 1;

			  }

		  }



    }		// End of while loop



   return 0;

}



//OUTPUT_DATAR_ADD &= ~(1<<5);
//OUTPUT_DATAR_ADD |= (1<<5);
