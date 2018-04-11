#include <stdlib.h>

const unsigned int VERY_NICE = 69;

int MY_VAR;

int main(void) {
  for (size_t i = 0; i < VERY_NICE; i++) {
    MY_VAR = MY_VAR + (VERY_NICE >> i);
  }

  return MY_VAR;
}
