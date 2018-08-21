# SDCC PSG AY38910 playFX Functions Library (object type)

Author: mvac7/303bcn

Architecture: MSX

Format: 8k ROM

Programming language: C and Z80 inline assembler (SDCC)

WEB: 

mail: mvac7303b@gmail.com




## 1. Introduction:

This project is an opensource.

Developed using Small Device C Compiler (SDCC).
  
Programs for test a Pseudo-Random Number Generator (PRNG).

- test_R - Displays screens with a list of 230 consecutive numbers provided by the R register of the Z80.

- test_PRNG - Displays screens with a list of 230 consecutive numbers provided by a PRNG routine.

- test_PRNG_GFX - Graphically displays a list of 32768 numbers provided by a PRNG routine, distributed in 256 horizontal columns with the repetitions of each value (0 to 255).


                           


## 2. Acknowledgments
  
Thanks for Info & help, to:

* Avelino Herrera > http://msx.atlantes.org/index_es.html
* Nerlaska > http://albertodehoyonebot.blogspot.com.es
* Fubu > http://www.gamerachan.org/fubu/
* Marq/Lieves!Tuore > http://www.kameli.net/lt/
* Sapphire/Z80ST > http://z80st.auic.es/
* Pentacour > http://pentacour.com/
* JamQue/TPM > http://www.thepetsmode.com/
* Andrear > http://andrear.altervista.org/home/msxsoftware.php
* Konamiman > https://www.konamiman.com
* MSX Assembly Page > http://map.grauw.nl/resources/msxbios.php
* Portar MSX Tech Doc > http://nocash.emubase.de/portar.htm
* MSX Resource Center > http://www.msx.org/
* Karoshi MSX Community > http://karoshi.auic.es/
* BlueMSX >> http://www.bluemsx.com/
* OpenMSX >> http://openmsx.sourceforge.net/
* Meisei  >> ?



## 3. Requirements:

* Small Device C Compiler (SDCC) v3.6 http://sdcc.sourceforge.net/
* Hex2bin v2.2 http://hex2bin.sourceforge.net/     



## 4. PRNG Function Code

```
char SEED;


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
```