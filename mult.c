#include <stdint.h>
void main (void){
    register int a = 2;
    register int b;
    for (register int i=1; i<20; i++){
         b= a*i;
    }
    

}
