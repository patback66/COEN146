/*
* Matthew Koken <mkoken@scu.edu>
* PRNG using 3-shift method (XOR)
*
*
*/

//<byte><byte>
//unsigned chars
//%c -- 0 - 255
#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include "time.h"

/*
Mersenne Twister?
u, d, l: additional Mersenne Twister tempering bit shifts/masks
(w, n, m, r) = (64, 312, 156, 31)
*/

//static unsigned char oneByte = 1;
time_t t;

/*
* 3-shift method
* Use a seed unsigned char, perform shift and xor operations on it to
* generate the next random unsigned char.
* http://www.arklyffe.com/main/2010/08/29/xorshift-pseudorandom-number-generator/
* This algorithm is a PRNG -> given the same seed it will always produce the same pattern
* Since this is not suitable for a RNG, we need to change the to avoid repeating patterns;
* The seed will be changed at random intervals to aid with the randomness. The PRNG on its
* own provides a very nice entropy approaching 7.999, but the repeating pattern
* prevents this from being used on its own. Because of the randomness of the seed,
* THERE IS POTENTIAL FOR VERY POOR ENTROPY PERFORMANCE. Given that speed and efficiency
* is typically a major factor, an algorithm that could use fast hardware features is preferable.
* Since bit shifting and comparison operations are typically quite fast in modern CPUS and also
* in smaller, lower powered processors, this is a preferable implementation to fit the
* 8 bit limitations.
*/
static unsigned char oneByte = 1;
unsigned char xor3() {
      //use odd portions of the byte
      oneByte ^= (oneByte << 7); //xor with the LSB
      oneByte ^= (oneByte >> 5); //more xor
      oneByte ^= (oneByte << 3); //even more xor
    return oneByte;
}

int main(int argc, char* argv[]){
  //seed the included random generator
  srand((unsigned) time(&t));
  unsigned char gen;
  oneByte = rand();
  for(int i = 0; i < 65536; i++) { //gen 2^16 numbers
      //patterns are bad, reset the seed at random intervals
      if(random()%1000 == 1)
        oneByte = random();
      //get a random byte
      gen = xor3();
      //print the random byte
      printf("%c", gen);
  }

  return 0;
}
