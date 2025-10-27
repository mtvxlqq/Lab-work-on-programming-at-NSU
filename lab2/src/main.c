#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef enum {
    ERROR_OK = 0,
    
    ERROR_READ_EOF_OR_FAIL,
    ERROR_READ_TOO_LONG,
    
    ERROR_VALIDATE_INVALID_FORMAT,
    ERROR_VALIDATE_OUT_OF_RANGE,
    ERROR_VALIDATE_IS_NEGATIVE,
    
    ERROR_VALIDATE_P_HAS_DUPLICATES

} ErrorCode;


void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverse_suffix(char *P, int start, int len){
    int end = len - 1;
    while (start < end) {
        swap(&P[start], &P[end]);
        start++;
        end--;
    }
}

int find_turning_point(char *P, int len){
    for (int i = len - 2; i >= 0; i--){
        if (P[i] < P[i + 1]){
            return i;
        }
    }
    return -1;
}


int find_min_suffix_el(char *P, int len, int index_turning_point){
    int turning_point_val = P[index_turning_point];
    int i = len - 1;
    while (turning_point_val > P[i]){
        i--;
    }
    return i;
}

int next_permutation(char *P) {
    int len_P = strlen(P);
    if (len_P <= 1) {
        return 0;
    }

    int k = find_turning_point(P, len_P);

    if (k == -1) {
        return 0;
    }

    int l = find_min_suffix_el(P, len_P, k);

    swap(&P[k], &P[l]);

    reverse_suffix(P, k + 1, len_P);

    return 1;
}

int duplicate_check(long P){
    int digit_counter[10] = {0};

    do {
        digit_counter[P % 10]++;
        P = P / 10;
    }
    while (P != 0);

    for (int i = 0; i < 10; i++){
        if (digit_counter[i] > 1){
            return 0;
        }
    }
    return 1;
}

ErrorCode validate_P(char *P_str){
    char *endptr;
    errno = 0;

    long P_l = strtol(P_str, &endptr, 10);

    if (errno != 0){
        return ERROR_VALIDATE_OUT_OF_RANGE;
    }
    if (*endptr != '\0'){
        return ERROR_VALIDATE_INVALID_FORMAT;
    }
    if (P_str == endptr){
        return ERROR_VALIDATE_INVALID_FORMAT;
    }
    if (P_l < 0) {
        return ERROR_VALIDATE_IS_NEGATIVE;
    }
    if (duplicate_check(P_l) == 0){
        return ERROR_VALIDATE_P_HAS_DUPLICATES;
    }
    return ERROR_OK;
}

ErrorCode validate_N(char *N_str, long long *N_val) {
    char *endptr;
    errno = 0;
    *N_val = strtoll(N_str, &endptr, 10);

    if (errno != 0) {
        return ERROR_VALIDATE_OUT_OF_RANGE;
    }
    if (*endptr != '\0') {
        return ERROR_VALIDATE_INVALID_FORMAT;
    }
    if (N_str == endptr) {
        return ERROR_VALIDATE_INVALID_FORMAT;
    }
    if (*N_val < 0) {
        return ERROR_VALIDATE_IS_NEGATIVE;
    }
    
    return ERROR_OK;
}


ErrorCode read_value(char *buffer, int max_size){
    if (fgets(buffer, max_size, stdin) == NULL){
        return ERROR_READ_EOF_OR_FAIL; 
    }
    
    char *newline_pos = strchr(buffer, '\n');

    if (newline_pos != NULL){
        *newline_pos = '\0';
        return ERROR_OK;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return ERROR_READ_TOO_LONG;
    }
}

int main(void) {
    char P[12] = {0};
    char N_str[22] = {0};
    long long N_val;
    
    if ((read_value(P, 12) != ERROR_OK) || (read_value(N_str, 22) != ERROR_OK)){
        printf("bad input\n");
        return 0;
    }
    
    if (validate_P(P) != ERROR_OK){
        printf("bad input\n");
        return 0;
    }

    if (validate_N(N_str, &N_val) != ERROR_OK) {
        printf("bad input\n");
        return 0;
    }

    for (long long i = 0; i < N_val; i++) {
        if (next_permutation(P) == 1) {
            printf("%s\n", P);
        } else {
            break;
        }
    }
    
    return 0;
}