#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MEMO_LENGTH (memo_size / 2)
#define MAX_MEMO_INDEX (MEMO_LENGTH - 1)

typedef struct {
    int n;
    unsigned short steps;
} result_t;

//メモ一つ分。メモリ節約のため、uchar２つ(2バイト)で表現する。
typedef struct {
    unsigned char high, low;
} memo_t;

//メモ領域の大きさ 2～1000,000の時はこれくらいにしておくのが最も早くなる。なぜかはわからない。
unsigned long memo_size = 2 * 1024 * 1024;

static memo_t* glob_memo; //メモ領域のポインタ

/*****************************************************
 * メモ領域を確保する。
 *****************************************************/
memo_t* allocMemo(){
    long size;
    memo_t* ptr_memo = NULL;
    
    //メモ領域確保
    while(1){
        ptr_memo = (memo_t*)calloc(memo_size / sizeof(memo_t), sizeof(memo_t));
        if(ptr_memo != NULL || memo_size < 0) break;
        memo_size = memo_size - (256 * 1024);
    }
    if(ptr_memo == NULL){
            printf("メモリ取得失敗");
            exit(1);
    }
    return ptr_memo;
}

/*****************************************************
 * メモから値を取得する。
 *****************************************************/
unsigned short getMemo(const unsigned int n){
    if(n > MAX_MEMO_INDEX) return 0;
    return (int)((int)(glob_memo[n].high << 8) + (int)glob_memo[n].low);
}

/*****************************************************
 * メモに値を登録する。
 *****************************************************/
void registerMemo(const unsigned int n, const unsigned short steps){
    if(n > MAX_MEMO_INDEX) return;
    glob_memo[n].high = (unsigned char)(steps >> 8);
    glob_memo[n].low = (unsigned char)(steps &  0xFF);
}


/*****************************************************
 * コラッツの計算を行う再帰関数
 *****************************************************/
int collatz(const unsigned long long n){
    unsigned long long next_n;
    unsigned short memo, steps_to_1;
    
    if(n == 1) return 0;
    
    memo = getMemo(n);
    if(memo > 0) return memo;
    
    next_n = (n % 2 == 0) ? n / 2 : (n * 3) + 1;
    
    steps_to_1 = collatz(next_n) + 1;
    registerMemo(n, steps_to_1);
    
    return steps_to_1;
}

/******************************************************
 * メイン・ループ
 ******************************************************/
result_t collatz_roop(int first_n, int last_n){
    int n;
    unsigned short steps;
    result_t result = {0, 0};
    
    glob_memo = allocMemo();
    
    //計算ループ
    for(n = first_n; n <= last_n; n++){
        steps = collatz((unsigned long long)n);
        if(steps > result.steps){
            result.n = n;
            result.steps = steps;
        }
    }
    free(glob_memo);
    return result;
}

/*****************************************************
 * 実行開始、終了処理。
 *****************************************************/
void main(void) {
    result_t result;
    const int first_n = 2, last_n = 1000000;
    clock_t start_time, end_time;
    
    start_time = clock();
    printf("コラッツの問題を計算します。（%d～%d）\r\n", first_n, last_n);
    
    //実行
    result = collatz_roop(first_n, last_n);
    
    end_time = clock();
    printf("結果：ステップ数が多くなる初期値は\"%d\"で%dステップかかります。\r\n", result.n, result.steps);
    printf("time=%.3f[s]   memo size=%lu[byte]\r\n", (double)(end_time - start_time) / CLOCKS_PER_SEC, memo_size);
    
    return;
}
