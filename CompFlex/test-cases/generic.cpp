int fn1(int y,int x){
    int c; 
    c = y + x;
    if(y < x){
        y = y +1;
    }
    return c;
}

int main(){
    int a; 
    a = 1;
    int b;
    b= 2;
    fn1(a, b);
    int c;
    c = 3;
    int d;
    d = 4;
    fn1(d,c);
    
}