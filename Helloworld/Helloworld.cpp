#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

char Master_Key[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                  0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1,
                  0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
                  0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1 };
char KEY_PC_1[56] = { 57, 49, 41, 33, 25, 17, 9,
               1, 58, 50, 42, 34, 26, 18,
               10, 2, 59, 51, 43, 35, 27,
               19, 11, 3, 60, 52, 44, 36,
               63, 55, 47, 39, 31, 23, 15,
               7, 62, 54, 46, 38, 30, 22,
               14, 6, 61, 53, 45, 37, 29,
               21, 13, 5, 28, 20, 12, 4 };
char KEY_PC_2[48] = { 14, 17, 11, 24, 1, 5, 3, 28,
               15, 6, 21, 10, 23, 19, 12, 4,
               26, 8, 16, 7, 27, 20, 13, 2,
               41, 52, 31, 37, 47, 55, 30, 40,
               51, 45, 33, 48, 44, 49, 39, 56,
               34, 53, 46, 42, 50, 36, 29, 32 };

int num_exc = 0; /*실행횟수*/
char Key[16][48] = { 0 };
char h[56] = { 0 };
char t0[56] = { 0 };

void shift_last(int x, int y)
{
    switch (h[x])
    {
    case 0:
        h[x + y] = 0;

    case 1:
        h[x + y] = 1;
    }

}

void keyzen()
{
    int i;

    printf("\n%d \n", num_exc); ///확인중

    /*Permuted_choice_1 // 최초실행시만 사용*/
    if (num_exc == 1) {
        for (i = 0; i <= 55; i++) {
            t0[i] = Master_Key[KEY_PC_1[i] - 1];
        }
    }

    else {
        for (i = 0; i <= 55; i++) {
            t0[i] = h[i];
        }
    }

    /*확인중*/
    for (i = 0; i <= 55; i++) {
        printf("%d ", t0[i]);
        if (i == 27) printf("//");
    }
    printf("\n");

    /*shift연산 // 1,2,9,16번째 실행은 1번 쉬프트*/
    if (num_exc == 1 || num_exc == 2 || num_exc == 9 || num_exc == 16) {
        for (i = 0; i <= 26; i++) {
            h[i] = t0[i + 1];
            shift_last(0, 27);
        }
        for (i = 28; i <= 54; i++) {
            h[i] = t0[i + 1];
            shift_last(28, 27);
        }
    }

    else {
        for (i = 0; i <= 25; i++) {
            h[i] = t0[i + 2];
            shift_last(0, 26);
            shift_last(1, 26);
        }
        for (i = 28; i <= 53; i++) {
            h[i] = t0[i + 2];
            shift_last(28, 26);
            shift_last(29, 26);
        }
    }

    /*확인중*/
    for (i = 0; i <= 55; i++) {
        printf("%d ", h[i]);
        if (i == 27) printf("//");
    }

    /*Permuted_choice_2*/
    for (i = 0; i <= 47; i++) {
        Key[num_exc][i] = h[KEY_PC_2[i] - 1];
        /// printf("%d ", Key[num_exc][i]);
    }
    printf("\n");
}

void printvector()
{

    int i;
    unsigned char tmp[8];

    for (int j = 1; j <= 16; j++)
    {
        memset(tmp, 0, sizeof(char) * 8);
        for (i = 0; i < 48; i++)
        {
            tmp[i >> 3] ^= (Key[j][i] & 1) << (7 - (i % 8));
        }

        printf(" Round Key %d : ", j);

        for (i = 0; i < (48 >> 3); i++)
        {
            printf(" %.2X ", tmp[i]);
        }
        printf("\n");

    }
}

int main()
{
    int i;

    for (i = 0; i <= 15; i++) {
        num_exc++;
        keyzen();
    }

    printf("\n");
    printf("\n");
    printf("\n");

    printvector();
}