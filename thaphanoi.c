#include<stdio.h>
void move(int n, char A, char B, char C) {
if(n == 1) {
printf("Move 1 disk from %c to %c\n", A, B);
}else{
move(n-1, A, C, B);
move(1, A, B, C);
move(n-1, C, B, A);
}
}
int main() {
int n = 5;//so tang thap
move(n, 'A' ,'B', 'C');
}