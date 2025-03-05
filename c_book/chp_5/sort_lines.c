#include <stdio.h>
#include <string.h>

#define MAXLINES  5000 // max # of lines to be sorted

char *lineptr[MAXLINES]; // pointers to text lines

int my_readlines(char *lineptr[], int nlines);

void my_writelines(char *lineptr[], int nlines);

void my_qsort(char *lineptr[], int left, int right);

/* sort input lines*/

int main() {
    int nlines;

    if ((nlines = my_readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort(lineptr, 0, nlines - 1);
        my_writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 // max length of a single input line

int my_getline(char[], int);

/* my_getline:  get line into s, return length */
int my_getline(char s[], int lim) {
    int c, i;

    i = 0;
    // DOES -- prefix/postfix matter here?
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

char *my_alloc(int);


/* readlines: read input lines */
int my_readlines(char *lineptr[], int maxlines) {
    int len, nlines;

    char *p;
    char *line[MAXLEN]; /* list where each element is a char* */

    nlines = 0;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = my_alloc(len)) == NULL) {
            // too many lines or we can't allocate
            return 1;
        } else {
            line[len - 1] = '\0'; /* delete new line*/
            // copy to dest in ptr array
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    // total # of lines read
    return nlines;
}

// write lines: dump to output
void my_writelines(char *lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}


void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[j];
    v[j] = v[i];
    v[j] = temp;
}

void my_qsort(char *v[], int left, int right) {
    int i, last;

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    my_qsort(v, left, last - 1);
    my_qsort(v, last + 1, right);
}





