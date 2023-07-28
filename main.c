#include "main_suppl_func.h"

int cont;

int solve()
{
    cont = 0;

    list inp;
    init(&inp);

    get_info info;
    init_info(&info);

    char ch;
    while ((ch = getchar()) != '\n')
    {
        append(&inp, ch);
    }
    append(&inp, '\0');

    char_stack s;
    Big_stack val;

    init_Big_stack(&val);
    init_char_stack(&s);

    Big_N result, temp, op1, op2;
    init_num(&temp);
    init_num(&result);

    char operan, c;
    int unary_neg = 0;

    /*Get next token.*/
    get_token(&info, &inp);

    if (info.token == 'q')
    {
        printf("Thank You ! \n");
        exit(1);
    }

    if (info.token == '\0')
    {
        printf("0 \n");
        return 0;
    }

    /*If syntax error present in expression.*/
    handle_tokens(&info, &inp, &val);
    if (cont)
        return 0;

    while (info.token != '\0')
    {
        /*current token*/
        c = info.token;

        /*If token is digit.*/
        if (isdigit(c))
        {
            insertInEnd(&temp, c - '0');
            /*if next token is not digit i.e.
             * number is finished*/
            if (!isdigit(info.next_token))
            {
                /*if unary operator was present before number*/
                if (info.unary_neg)
                {
                    negation(&temp);
                    info.unary_neg = 0;
                }
                /*push into value stack and reinitialize*/
                push_Big_N(&val, temp);
                init_num(&temp);
            }
        }

        /*if token is opening bracket*/
        else if (c == '(')
        {
            push_char(&s, '(');
            /*to solve unary negative after (*/
            if (!isOperator(info.token = info.prev_token))
            {
                printf("Syntax error.\n");
                error(info.token, '(');
            }
        }
        /*if token is closing bracket*/
        else if (c == ')')
        {
            while (!isEmpty_char(s) && peek_char(s) != '(')
            {
                /*pop 2 operands(big numbers) from value stack*/
                op2 = pop_Big_N(&val);
                op1 = pop_Big_N(&val);
                /*pop operator from character stack*/
                operan = pop_char(&s);

                /*evaluate expression and push result in value stack*/
                push_Big_N(&val, eval(&op1, &op2, operan));
            }
            /*if '(', remove it*/
            if (peek_char(s) == '(')
                pop_char(&s);
            else
            {
                printf("Syntax Error.\n");
                printf("TYPE: closing brackets are not matched with opening bracket.\n");
                return 0;
            }
        }
        /*if token is operrator or anything else*/
        else
        {
            /*if token is operator*/
            if (isOperator(c))
            {
                if (isEmpty_char(s))
                    push_char(&s, c);
                else
                {
                    /*evaluate expression using two operands from value stack and operator from char stack,
                     * considering precedence and associativity*/
                    while (!isEmpty_char(s) && precedence(peek_char(s)) >= precedence(c) && !info.r_ass)
                    {
                        op2 = pop_Big_N(&val);
                        op1 = pop_Big_N(&val);
                        operan = pop_char(&s);

                        push_Big_N(&val, eval(&op1, &op2, operan));
                    }
                    push_char(&s, c);
                    info.r_ass = 0;
                }
            }
            /*error: other operators of symbols are used*/
            else
            {
                printf("Syntax Error.\n");
                printf("Type: Wrong operator or symbol '%c'\n", c);
                return 0;
            }
        }
        /*get next token*/
        get_token(&info, &inp);
        /*to handle errors and unary sign*/
        handle_tokens(&info, &inp, &val);
        /*if error: return from current expression*/
        if (cont)
            return 0;
    }

    /*evaluate all remaining operations till both stacks become empty*/
    while (!isEmpty_char(s))
    {
        op2 = pop_Big_N(&val);
        op1 = pop_Big_N(&val);
        operan = pop_char(&s);

        if (operan == '(')
        {
            printf("Syntax Error.\nTYPE: Opening brackets are not matched with closing bracket.\n");
            return 0;
        }

        push_Big_N(&val, eval(&op1, &op2, operan));
    }
    /*change output base if it is requirement*/
    // result = changeBase(pop_Big_N(&val), info.out_base);

    result = pop_Big_N(&val);

    /*display result*/
    display(result);

    // printf("\nLength of result is: %d\n", result.size);
    return 0;
}

int main()
{
    solve();
}