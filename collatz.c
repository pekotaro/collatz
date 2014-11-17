#include <stdio.h>

typedef struct {
    int n;
    int steps;
} result_t;

void main(void) {
    result_t result = {0,0};
    int n, steps, max_steps = 0;
    
    printf("コラッツの問題を計算します。（2～100000）\r\n");

    for(n = 2; n <= 100000; n++){
        steps = collutz(n);
        if(steps > result.steps){
            result.n = n;
            result.steps = steps;
        }
    }    

    printf("結果：ステップ数が多くなる初期値は\"%d\"で%dステップかかります。\r\n", result.n, result.steps);
}

int collutz(int n){
    int steps;
    for(steps = 0; n != 1; steps++){
        n = (n % 2 == 0) ? n / 2 : (n * 3) + 1;
    }
    return steps;
}
