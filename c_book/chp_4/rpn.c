#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"


#define MAXOP 100
#define NUMBER '0'


void push(double);

double pop(void);

int mget_ch(void);

int mget_op(char[]);


void munget_ch(int);


int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = mget_op(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
}


#define MAXVAL 100 // max values on stack
int sp = 0; // next free stack position
double val[MAXVAL];


void push(double f) {
    if (sp < MAXVAL) {
        // printf("val[sp++] = f;");
        val[sp++] = f;
//        for (int i = 0; i < MAXVAL; i++)
//            printf(" %f", val[i]);
    } else {
        printf("error: stack full, can't push %g\n", f);
        exit(1);
    }
}

double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


int mget_op(char s[]) {
    int i, c;
    while ((s[0] = c = mget_ch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c; // not a number
    i = 0;
    if (c == '-' || isdigit(c)) // collect integer part along with '-'
        while (isdigit(s[++i] = c = mget_ch()));
    if (c == '.') // collect fraction part
        while (isdigit(s[++i] = c = mget_ch()));
    s[i] = '\0';
    if (c != EOF)
        munget_ch(c);
//    if (strcmp(s, "-") == 0)
//        return '-';
    return NUMBER;
}


#define BUF_SIZE 100

char buf[BUF_SIZE]; // buffer for unget_ch
int bufp = 0;       // next free position in buf

int mget_ch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void munget_ch(int c) {
    if (bufp >= BUF_SIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


