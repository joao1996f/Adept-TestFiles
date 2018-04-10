// Fibonacci sequence using registers
void main(void) {
  register int a = 0;
  register int b = 1;
  register int c;

  for (register int i = 0; i < 18; i++) {
    c = a + b;
    a = b;
    b = c;
  }

}
