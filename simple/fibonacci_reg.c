// Fibonacci sequence using registers
int main(void) {
  register int a = 0;
  register int b = 1;
  register int c;

  for (register int i = 0; i < 18; i++) {
    c = a + b;
    a = b;
    b = c;
  }

  return c;
}
