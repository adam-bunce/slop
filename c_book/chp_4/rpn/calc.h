#define NUMBER '0'

// from cwd
// gcc -o rpn_program main.c gettop.c getch.c stack.c

void push(double);

double pop(void);

int mget_op(char[]);

int mget_ch(void);

void munget_ch(int);
