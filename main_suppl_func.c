#include "main_suppl_func.h"

void init_info(get_info *info)
{
    info->unary_neg = 0;
    info->r_ass = 0;
    info->prev_token = 0;
    /*To handle first unary negative sign*/
    info->token = '+';
    info->next_token = 0;
    return;
}

int precedence(char c)
{
    switch (c)
    {
    case '(':
        return 5;
    case '+':
        return 10;
    case '-':
        return 10;
    case '*':
        return 20;
    case '/':
        return 20;
    default:
        return 0;
    }
}

void error(char prev, char next)
{
    printf("Syntax Error\n");
    printf("TYPE: wrong operator '%c', after '%c'.\n", next, prev);
    cont = 1;
}

int isOperator(char c)
{
    switch (c)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 1;
    case '/':
        return 1;
    default:
        return 0;
    }
}

Big_N eval(Big_N *op1, Big_N *op2, char operan)
{
    switch (operan)
    {
    case ('+'):
        return add(op1, op2);
    case ('-'):
        return sub(op1, op2);
    case ('*'):
        return mult(op1, op2);
    case ('/'):
        return division(op1, op2);
    }

    Big_N zero;
    init_num(&zero);

    insertInEnd(&zero, 0);
    return zero;
}

int get_token(get_info *info, list *inp)
{
    info->prev_token = info->token;
    for (; touch(*inp) != '\0' && touch(*inp) == ' '; get_next(inp))
        ;
    info->token = get_next(inp);
    for (; touch(*inp) != '\0' && touch(*inp) == ' '; get_next(inp))
        ;
    info->next_token = touch(*inp);
    return 0;
}

void handle_tokens(get_info *info, list *inp, Big_stack *val)
{
    switch (info->token)
    {
        case '/':
            if (isOperator(info->prev_token))
                error(info->prev_token, info->token);
            break;
        case '*':
            if (isOperator(info->prev_token))
                error(info->prev_token, info->token);
            break;
        
        case '-':
            if (isOperator(info->prev_token) && isdigit(info->next_token))
            {
                info->unary_neg = 1;
                info->token = info->next_token;
                info->next_token = get_token(info, inp);
            }
            else if (isOperator(info->prev_token) && isOperator(info->next_token))
                error(info->prev_token, info->token);
            break;
        case '+':
            if (isOperator(info->prev_token) && isdigit(info->next_token))
            {
                info->token = info->next_token;
                info->next_token = get_token(info, inp);
            }
            else if (isOperator(info->prev_token) && isOperator(info->next_token))
                error(info->prev_token, info->token);
            break;
        case '\0':
            if (isOperator(info->prev_token))
            {
                printf("Syntax Error.\n");
                printf("TYPE: Unterminated operator '%c'\n", info->prev_token);
                cont = 1;
                return;
            }
            break;
        
    }
    return;
}