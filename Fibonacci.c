void main(){
int Fib[20];

Fib[0]=0;
Fib[1]=1;
for (int i =2; i<20; i++){
    Fib[i]=Fib[i-2]+Fib[i-1];
 }
register int a = Fib[19];
}
