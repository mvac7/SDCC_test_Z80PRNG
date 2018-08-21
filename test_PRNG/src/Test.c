/* =============================================================================
  Test Generador de Números Pseudoaleatorios 8 bits
  #PRNG
  
  Version: 1.0
  Date: 21/08/2018
  Author: mvac7/303bcn
  Architecture: MSX
  Format: 8k ROM
  Programming language: C
  WEB: 
  mail: mvac7303b@gmail.com
   
  Description:
  
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxsystemvars.h"
#include "../include/msxBIOS.h"

#include "../include/textmode.h"



#define  HALT __asm halt __endasm   //wait for the next interrupt


// Function Declarations -------------------------------------------------------
char PEEK(uint address);
void POKE(uint address, char value);

char INKEY();

void WAIT(uint cicles);

void test();

char Random(char mask);
char getR();


// constants  ------------------------------------------------------------------
const char text01[] = "Test PRNG 8bits";
const char text02[] = "v1.0 (21/08/2018)";

const char presskey[] = "Press a key to continue";


// global variable definition --------------------------------------------------
char SEED;




// Functions -------------------------------------------------------------------


//
void main(void)
{
  SEED=0;
  
  COLOR(LIGHT_GREEN,DARK_GREEN,DARK_GREEN);      

  WIDTH(40);
  SCREEN0();
  
  PRINT(text01);
  PRINT("\n");
  PRINT(text02);
  PRINT("\n");
  PRINT(presskey);
  INKEY();
  
  while(1) test();

}



char PEEK(uint address)
{
address;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
    
  ld   L,4(IX)
  ld   H,5(IX)
  ld   A,(HL)

  ld   L,A
  pop  IX
__endasm;
}



void POKE(uint address, char value)
{
address;value;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
    
  ld   L,4(IX)
  ld   H,5(IX)
  ld   A,6(IX)
  ld   (HL),A

  pop  IX  
__endasm;
}



/* =============================================================================
One character input (waiting)
============================================================================= */
char INKEY(){
__asm   
   call CHGET
   ld   L,A
__endasm;
}



// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
  return;
}



void test()
{
  uint i;
  
  CLS();
  
  for(i=0;i<230;i++)
  {
    //HALT;
    PrintFNumber(Random(255),' ',4);
  }
  
  LOCATE(0,23);
  PRINT(presskey);
  INKEY();  
}




char Random(char mask)
{
mask;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   C,4(ix)    ;get the Mask

  ld   A,(_SEED)  ;get the Seed
    			
  ld   B,A	
  ld   A,R  
  add	 A,B        ;add the value of R to the Seed
  
  ld   B,A
  ld   A,R
  rlca            ;rotation to the left
  sub	 A,B        ;and subtracts it from the value 
  
  ld   (_SEED),A  ;save as Seed 
  
  and  C          ;apply the Mask
  
  ld   L,A        ;return L
  
  pop  IX    
__endasm;
}



char getR()
{
__asm

  ld   A,R  
  ld   L,A ;return L
   
__endasm;
}










