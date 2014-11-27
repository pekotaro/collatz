#include <stdio.h>
#include <time.h>

typedef struct {
    int n;
    int steps;
} result_t;

result_t collutz_roop(int first_n, int last_n){
    int n, steps;
    result_t result = {0, 0};
    
    for(n = first_n; n <= last_n; n++){
        steps = collutz((unsigned long)n);
        if(steps > result.steps){
            result.n = n;
            result.steps = steps;
        }
    }
    
    return result;
}

int collutz(unsigned long n){
    int steps;
    for(steps = 0; n != 1; steps++){
        n = (n % 2 == 0) ? n / 2 : (n * 3) + 1;
    }
    return steps;
}

void main(void) {
    result_t result;
    const int first_n = 2, last_n = 1000000;
    clock_t start_time, end_time;
    
    printf("コラッツの問題を計算します。（%d～%d）\r\n", first_n, last_n);
    start_time = clock();
    result = collutz_roop(first_n, last_n);
    end_time = clock();
    printf("結果：ステップ数が多くなる初期値は\"%d\"で%dステップかかります。\r\n", result.n, result.steps);
    printf("%d[ms]でした。\r\n", end_time - start_time);
}
