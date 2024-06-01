int hello(){
    int a;
    a = 1;
    int b;
    b = 2;
    return a + b;
}
int main(){
    int x1;
    x1 = 1;
    int x2;
    x2 = 2;
    int x3;
    x3 = 3;
    int x4;
    x4 = 4;
    int x5;
    x5 = 5;
    int x6;
    x6 = 6;
    int x7;
    x7 = 7;
    int x8;
    x8 = 8;
    int x9;
    x9 = 9;
    int x10;
    x10 = 10;
    int x11;
    x11 = 11;
    int x12;
    x12 = 12;
    int x13;
    x12 = 13;
    int x14;
    x14 = 14;
    int x15;
    x15 = 15;
    int x16;
    x16 = 16;
    int x17;
    x17 = 17;
    
    x17 = x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;
    x16 = x9 + x10 + x11 + x12 + x13 + x14 + x15;
    x16 = x16 * x17;
    x10 = x10 + x9;

    makeSum(x1,x2,x3,x4,x5,x6,x7);
    return 0;
    
}

int makeSum(int a, int b, int c, int d, int e, int f, int g){
    int sum;
    sum = a+ b+ c+ d + e +f + g;
    return sum;
}