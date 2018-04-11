int fibonacci(int a, int b, int max) {
  if (max == 0)
    return a + b;
  return fibonacci(b, a + b, max - 1);
}

int main(void) {
  return fibonacci(0, 1, 17);
}
