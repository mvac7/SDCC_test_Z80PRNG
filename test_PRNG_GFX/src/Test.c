/* =============================================================================
  Test Generador de Números Pseudoaleatorios GFX 8 bits
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
#include "../include/msxSystemVars.h"
#include "../include/msxBIOS.h"

#include "../include/VDP_TMS9918A.h"




#define  HALT __asm halt __endasm   //wait for the next interrupt



void test();

char INKEY();         

void WAIT(uint cicles);

void PSET(char x, char y);

char Random(char mask);
char getR();



// constants  ------------------------------------------------------------------

const char text01[] = "Test GFX PRNG 8b";
const char text02[] = "v1 (21/08/2018)";


// global variables ------------------------------------------------------------
char SEED;

char conta[255];


// Functions -------------------------------------------------------------------


//
void main(void)
{ 
  SEED=0;
  
  while(1) test();
}



/* =============================================================================
One character input (waiting)
============================================================================= */
char INKEY()
{
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



// TEST ###############################################################
void test()
{
  uint i;
  char value;
   
  for(i=0;i<256;i++) conta[i]=0;
  
  COLOR(LIGHT_GREEN,DARK_BLUE,LIGHT_BLUE);      
  SCREEN(2);
  
  //Fill color table for 3 tilesets areas
  FillVRAM(BASE11,6144,(WHITE*16)+DARK_BLUE); //(INK color * 16) + BG color

  for(i=0;i<32768;i++)
  {
    //HALT;
    value = Random(255);
    if (conta[value]<192) conta[value]++;
    
    PSET(value,192-conta[value]);  
  }

  INKEY();
}



void PSET(char x, char y)
{
  uint vaddr;
  char value;
  char bite;
  
  vaddr = ((y / 8) * 256) + ((x / 8) * 8); // + ((y) & 7);
  vaddr += (y & 7);
  
  value= VPEEK(vaddr);
  
  bite = 128 >> ((x) & 7);
  
  VPOKE(vaddr,value|bite);

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
