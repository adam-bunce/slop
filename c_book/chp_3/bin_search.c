#include "stdio.h"

int bin_search(int, const int s[], int n);

int bin_search(int v, const int s[], int n) {
    int l, r, m;

    l = 0;
    r = n - 1;

    while (l <= r) {
        m = (l + r) / 2; // should be floor division?
        if (v < s[m])  {
            // go left
            r = m - 1;
        } else if (v > s[m]) {
            // go right
            l = m + 1;
        } else {
            // found match
            return m;
        }
    }

   return -1;
}

#define SIZE 10
int main() {
    int nums[SIZE] = {1,2,3,4,5,6,7,8,9,10};
    int search_value = 3;
    int pos = bin_search(search_value, nums, SIZE);
    pos != -1 ? printf("index of %d is %d\n",search_value, pos) : printf("%d not in array\n", search_value);
}