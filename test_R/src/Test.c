/* =============================================================================
  Test Z80 R register
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

char getR();


// constants  ------------------------------------------------------------------
const char text01[] = "Test Z80 R register";
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
    PrintFNumber(getR(),' ',4);
  }
  
  LOCATE(0,23);
  PRINT(presskey);
  INKEY();  
}




char getR()
{
__asm

  ld   A,R  
  ld   L,A ;return L
   
__endasm;
}











/*void testPrintNumber()
{
  uint uintvalue=12345;
  char charValue=71;
  
  CLS();
   
  PRINT(">Test PrintNumber(2400):");
  PrintNumber(2400);

  PRINT("\n>Test PrintNumber(uint):");
  PrintNumber(uintvalue);

  PRINT("\n>Test PrintNumber(char):");
  PrintNumber(charValue);

  PRINT("\n>Test PrintNumber(0)   :");
  PrintNumber(0);
  
  PRINT("\n\n");
  
  PRINT(">Test PrintFNumber(2400,32,6):\n");
  PrintFNumber(2400,' ',6); //" 2400" Testing when the length parameter is above the maximum size (5) 

  PRINT("\n>Test PrintFNumber(uint,32,5):\n");
  PrintFNumber(uintvalue,' ',5); //"12345"
  
  PRINT("\n>Test PrintFNumber(uint,32,3):\n");
  PrintFNumber(uintvalue,' ',3); //"345"
  
  PRINT("\n>Test PrintFNumber(7,48,3):\n");
  PrintFNumber(7,48,3);  //"007"

  PRINT("\n>Test PrintFNumber(char,' ',4):\n");
  PrintFNumber(charValue,' ',4); //"  71"
  
  PRINT("\n>Test PrintFNumber(char,'0',4):\n");
  PrintFNumber(charValue,'0',4); //"0071"

  LOCATE(0,22);
  PRINT(presskey);
  INKEY();
}*/




