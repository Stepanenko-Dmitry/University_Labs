#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE 256

double stack[STACK_SIZE];
int sp = 0;

int is_digit(char c) { return c >= '0' && c <= '9'; }
int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
int is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

void push(double x) { stack[sp++] = x; }
double pop() { return stack[--sp]; }
double top() { return stack[sp - 1]; }

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double div_op(double a, double b) { return a / b; }
double power(double a, double b) { return pow(a, b); }

double apply(char op, double a, double b)
{
    switch(op)
    {
        case '+': return add(a, b);
        case '-': return sub(a, b);
        case '*': return mul(a, b);
        case '/': return div_op(a, b);
        case '^': return power(a, b);
        default: return 0;
    }
}

typedef struct { char items[256]; int top; } CharStack;
void init_stack(CharStack *s) { s->top = -1; }
void push_op(CharStack *s, char c) { if (s->top < 255) s->items[++s->top] = c; }
char pop_op(CharStack *s) { return s->top == -1 ? 0 : s->items[s->top--]; }
char peek_op(CharStack *s) { return s->top == -1 ? 0 : s->items[s->top]; }
int is_empty(CharStack *s) { return s->top == -1; }

int precedence(char op)
{
    switch(op)
    {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int is_right_associative(char op) { return op == '^'; }

void evaluate_rpn(const char *rpn)
{
    const char *p = rpn;
    sp = 0;

    while (*p)
    {
        while (is_space(*p)) p++;
        if (*p == '\0') break;

        if (is_digit(*p) || (*p == '-' && is_digit(*(p+1))))
        {
            push(strtod(p, (char**)&p));
        }
        else if (is_operator(*p))
        {
            double b = pop();
            double a = pop();
            push(apply(*p, a, b));
            p++;
        }
        else
        {
            p++;
        }
    }
}

char* infix_to_rpn(const char *expr)
{
    static char output[1024];
    CharStack ops;
    init_stack(&ops);
    int out_len = 0;
    const char *p = expr;
    int expect_operand = 1;

    while (*p)
    {
        while (is_space(*p)) p++;
        if (*p == '\0') break;

        if (is_digit(*p) || (*p == '.' && is_digit(*(p+1))))
        {
            while (is_digit(*p) || *p == '.')
                output[out_len++] = *p++;
            output[out_len++] = ' ';
            expect_operand = 0;
        }
        else if (*p == '(')
        {
            push_op(&ops, *p++);
            expect_operand = 1;
        }
        else if (*p == ')')
        {
            while (!is_empty(&ops) && peek_op(&ops) != '(')
                output[out_len++] = pop_op(&ops), output[out_len++] = ' ';
            if (!is_empty(&ops)) pop_op(&ops);
            p++;
            expect_operand = 0;
        }
        else if (*p == '-' && expect_operand)
        {
            output[out_len++] = '0';
            output[out_len++] = ' ';
            push_op(&ops, '-');
            p++;
            expect_operand = 1;
        }
        else if (*p == '+' && expect_operand)
        {
            p++;
        }
        else if (is_operator(*p))
        {
            while (!is_empty(&ops) && peek_op(&ops) != '(')
            {
                int top_prec = precedence(peek_op(&ops));
                int curr_prec = precedence(*p);

                if (top_prec > curr_prec ||
                    (top_prec == curr_prec && !is_right_associative(*p)))
                {
                    output[out_len++] = pop_op(&ops);
                    output[out_len++] = ' ';
                }
                else break;
            }
            push_op(&ops, *p++);
            expect_operand = 1;
        }
        else
        {
            p++;
        }
    }

    while (!is_empty(&ops))
    {
        output[out_len++] = pop_op(&ops);
        output[out_len++] = ' ';
    }
    output[out_len] = '\0';
    return output;
}

int main()
{
    char input[1024];

    if (!fgets(input, sizeof(input), stdin))
        return 1;

    input[strcspn(input, "\n")] = '\0';

    char *rpn = infix_to_rpn(input);
    evaluate_rpn(rpn);

    printf("%.6f\n", top());

    return 0;
}