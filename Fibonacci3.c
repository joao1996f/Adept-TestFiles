
int Fibonacci(int a, int b, int max){
    if (max == 0) return a + b;
    return Fibonacci(b, a+b, max-1);
}
void main(void){
    int Fib;
    Fib = Fibonacci(0, 1, 17);
}
