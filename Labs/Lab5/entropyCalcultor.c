/*
* Matthew Koken <mkoken@scu.edu>
* Entropy Calculator, using calculation method
* provided by http://blogs.cisco.com/security/on_information_entropy
*/
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "errno.h"
#include "math.h"

double log2( double n )  {
    return log(n) / log(2);
}

int main(int argc, char* argv[]){
  unsigned char buf[4194304];
  unsigned int fa[256]={0};
  double prob, entropy = 0;
  int i, k, m, count;
  char str[255];
  /* read a brick of data */
  while ((i = fread(buf, 1, sizeof(buf),stdin))){//fread(fd, buf, sizeof (buf)))) { //read until EOF
      if (i == -1)
      {
          //didn't get a read, break
          break;
      }
      int k;
      for (k = 0; k < i; k++)
      {
          /**
            *  For each brick of data we siphon from the file, record
            *  the number of instances of each observed value into
            *  the frequency array.
            */
            fa[buf[k]]++; //increment frequency given byte in buffer
            count++; //increment the count
      }
  }
  for (k = 0; k < 256; k++)
  {
    /** ignore empty slots */
    if (fa[k])
    {
       /** convert frequency array entry -> probability distribution*/
       prob = (double)fa[k] / (double)count;
       /** the famous Shannon Entropy formula */
       entropy += prob * log2(1/prob);
    }
  }
  printf("Entropy: %f\n", entropy);
}
