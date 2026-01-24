// #include <stdio.h>
#include <iostream>

int K=3;
int n=2;
int a[10];
int used[10];

void permutation(int c){
  if(c>n){
    for(int i = 1; i <= n; i++){
      printf("%d ", a[i]);
    }
    printf("\n");
    return;
  }
  for(int num=1; num <= K; num++){
    if(used[num]) continue;
    a[c] = num;
    used[num] = 1;
    permutation(c+1);
    used[num] = 0;
  }
}

void repeat_permutation(int c){
  if(c>n){
    for(int i = 1; i <= n; i++){
      printf("%d ", a[i]);
    }
    printf("\n");
    return;
  }
  for(int num=1; num <= K; num++){
    a[c] = num;
    repeat_permutation(c+1);
  }
}


void combination(int start, int c){
  if(c>n){
    for(int i = 1; i <= n; i++){
      printf("%d ", a[i]);
    }
    printf("\n");
    return;
  }
  for(int num=start; num <= K; num++){
    a[c] = num;
    combination(num+1, c+1);
  }
}

void repeat_combination(int start, int c){
  if(c>n){
    for(int i = 1; i <= n; i++){
      printf("%d ", a[i]);
    }
    printf("\n");
    return;
  }
  for(int num=start; num <= K; num++){
    a[c] = num;
    repeat_combination(num, c+1);
  }
}

int main(){

  printf("permutation\n");
  permutation(1);
  printf("repeat_permutation\n");
  repeat_permutation(1);
  printf("combination\n");
  combination(1, 1);
  printf("repeat_combination\n");
  repeat_combination(1, 1);

  return 0;
}
