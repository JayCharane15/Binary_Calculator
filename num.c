#include"num.h"

void init_num(Big_N *num)
{
    num->size = 0;
    num->head = num->tail = NULL;
    num->sign = 0;
}

void negation(Big_N *num) {
	if(num->sign)
		num->sign = 0;
	else
		num->sign = 1;
}

void rem_lead_zeros(Big_N* num)
{
    node* temp = num->head;
    node* follow;
    int count = 0;
    Big_N new;
    init_num(&new);

    while (temp && temp->data == 0) {
        follow = temp;
        temp = temp->next;
	/*free the leading zeros*/
        free(follow);
	
        count++;
    }
    if(temp == NULL) {
	    *num = new;
	    return;
    }
    temp->prev = NULL;
    num->head = temp;
    num->size -= count;
    return;
}


void destroy(Big_N* num)
{
    Big_N new;
    init_num(&new);
    *num = new;


    node* temp = num->head;
    node* follow;
    while(temp)
    {
        follow = temp;
        temp = temp->next;
        free(follow);
    }

    
}

void display(Big_N num)
{
    node* temp = num.head;
    if(num.size == 0)
    {
        printf("0\n");
        return;
    }
    if(num.sign)
    {
        printf("-");
    }
    while(temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void isnertInFront(Big_N* num, int val)
{
    if(val == '-' - '0')
    {
        num->sign = 1;
        return;
    }
    node* nn = malloc(sizeof(node));
    if(!nn)
    {
        printf("Malloc failed");
        return;
    }
    nn->prev = nn->next = NULL;
    nn->data = val;

    if(num->head == NULL)
    {
        num->head = num->tail = nn;
        num->size++;
        return;

    }

    node* temp = num->head;
    temp->prev = nn;
    num->head = nn;
    nn->next = temp;

    num->size++;
}

void insertInEnd(Big_N* num, int val )
{
    if(val == '-' - '0')
    {
        num->sign = 1;
        return;
    }
    node* nn = malloc(sizeof(node));
    if(!nn)
    {
        printf("Malloc failed");

        return;

    }

    nn->prev = nn->next = NULL;
    nn->data = val;

    if(num->tail == NULL)
    {
        num->head = num->tail = nn;
        num->size++;
        return;
    }
    else
    {
        num->tail->next = nn;
        nn->prev = num->tail;
        num->tail = nn;

    }

    num->size++;


}


int length(Big_N num) {
    return num.size;
}


// 1 if a > b,  0 if a == b ,  2 if b > a
int compare(Big_N a, Big_N b)
{
    rem_lead_zeros(&a);
    rem_lead_zeros(&b);

    Big_N a1 = a;
    Big_N b1 = b;

    int rev = 0;
    if(a1.sign != b1.sign) {
	    if(b1.sign)
		    return 1;
	    else
		    return 2;
    }
    else{
        if(a1.sign)
        {
            rev = 1;
        }
    }


    if(a1.size != b1.size)
    {
        if(!rev)
        {
            return (a1.size > b1.size) ? 1 : 2;
        }
        else{
            return (a1.size > b1.size) ? 2 : 1;

        }
    }

    while(a1.head != NULL && b1.head != NULL)
    {
        if(a1.head->data > b1.head->data)
        {
            if(!rev)
            {
                return 1;
            }
            else{
                return 2;
            }
        }
        else if(b1.head->data > a1.head->data)
        {
            if(!rev)
            {
                return 2;
            }
            else{
                return 1;
            }
        }
        a1.head = a1.head->next;
        b1.head = b1.head->next;
    }

    return 0;

}

Big_N sub(Big_N* a, Big_N* b);
Big_N add(Big_N *a, Big_N *b)
{
    rem_lead_zeros(a);
    rem_lead_zeros(b);

    Big_N a1 = *a;
    Big_N b1 = *b;

    int c = 0;
    int s ;

    Big_N addititon;
    init_num(&addititon);

    if(a1.sign != b1.sign)
    {
        if(a1.sign == 0) {
            negation(&b1);
            return sub(&a1, &b1);
        }
        else {
            negation(&a1);
            return sub(&b1, &a1);
        }
        
    }
    else
    {
        addititon.sign = a1.sign;
    }

    while(a1.tail != NULL || b1.tail != NULL)
    {
        if(a1.tail != NULL && b1.tail != NULL)
        {
            s = (a1.tail->data + b1.tail->data + c) % 10;
            c = (a1.tail->data + b1.tail->data + c) / 10;
            a1.tail = a1.tail->prev;
            b1.tail = b1.tail->prev;
            
        }
        else if(a1.tail != NULL && b1.tail == NULL)
        {
            s = (a1.tail->data + c) % 10;
            c = (a1.tail->data + c) / 10;
            a1.tail = a1.tail->prev;


        }
        else
        {
            s = (b1.tail->data + c) % 10;
            c = (b1.tail->data + c) / 10;
            b1.tail = b1.tail->prev;
        }
        isnertInFront(&addititon, s);

    }


    if(c != 0)
    {
        isnertInFront(&addititon, c);
    }

    return addititon;
    
    

}

Big_N sub(Big_N* a, Big_N* b)
{
    if(b->size == 1 && b->head->data == 0)
    {
        return *a;
    }
    rem_lead_zeros(a);
    rem_lead_zeros(b);

    Big_N a1 = *a;
    Big_N b1 = *b;

    Big_N substarction;
    init_num(&substarction);


    int c = 0;
    int s;
    int rev;


    if(a1.sign != b1.sign)
    {
        if(a1.sign == 0)
        {
            negation(&b1);
            return add(&a1, &b1);
        }
        else
        {
            negation(&a1);
            return add(&a1, &b1);
        }
    }
    else if(a1.sign && b1.sign)
    {
        // substarction.sign = 1;
        negation(&a1);
        negation(&b1);
        rev = 1;

    }

    int cmp = compare(a1, b1);
    if(cmp == 0)
    {
        return substarction;
    }

    if(cmp == 2)
    {
        Big_N temp = a1;
        a1 = b1;
        b1 = temp;
        negation(&substarction);
    }
    if(cmp == 1)
    {
        substarction.sign = 0;
    }

    while(a1.tail != NULL || b1.tail != NULL)
    {
        if(a1.tail != NULL && b1.tail != NULL)
        {
            if(a1.tail->data + c >= b1.tail->data)
            {
                s = (a1.tail->data + c - b1.tail->data);
                c = 0;
            }
            else
            {
                s = (a1.tail->data + c + 10 - b1.tail->data);
                c = -1;

            }
            a1.tail = a1.tail->prev;
            b1.tail = b1.tail->prev;
        }
        else if(a1.tail != NULL && b1.tail == NULL)
        {
            if (a1.tail->data >= 1) {
                s = ((a1.tail->data) + c);
                c = 0;
            }
            else {
                if (c != 0) {
                    s = ((a1.tail->data) + 10 + c);
                    c = -1;
                }
                else
                    s = a1.tail->data;
            }
            a1.tail = a1.tail->prev;
        }
        isnertInFront(&substarction, s);
        // display(substarction);
    }
    rem_lead_zeros(&substarction);

    return substarction;

    
}
Big_N  mult(Big_N* a, Big_N* b)
{
    rem_lead_zeros(a);
    rem_lead_zeros(b);



    Big_N multiplication;
    init_num(&multiplication);
    

    Big_N a1 = *a;
    Big_N b1 = *b;

    if(a1.size == 0 || b1.size == 0)
    {
        return multiplication;
    }
    if(a1.sign != b1.sign)
    {
        multiplication.sign = 1;
    }


    int k = 0;

    while(b1.tail != NULL)
    {
        
        a1 = *a;
        int c,s;
        c = s = 0;

        Big_N temp;
        init_num(&temp);

        while(a1.tail != NULL)
        {
            s = (a1.tail->data * b1.tail->data + c) % 10;
            c = (a1.tail->data * b1.tail->data + c) / 10;
            isnertInFront(&temp, s);
            a1.tail = a1.tail->prev;
        }
       
        if(c != 0)
        {
            isnertInFront(&temp, c);
        }


        for(int i = 0; i < k; i++)
        {
            insertInEnd(&temp, 0);

        }


        k++;
        multiplication = add(&multiplication, &temp);

        // display(multiplication);
        destroy(&temp);
        b1.tail = b1.tail->prev;
        
        
    }

    return multiplication;

}


void delete_from_end(Big_N* num)
{
    if(num->size == 1)
    {
        free(num->tail);
        Big_N new;
        init_num(&new);
        *num = new;
        return;
    }
    node* temp = num->tail;

    num->tail = temp->prev;

    free(temp);
}

Big_N division(Big_N* l, Big_N* m)
{
    rem_lead_zeros(l);
    rem_lead_zeros(m);

    Big_N a1 = *l;
    Big_N b1 = *m;

    Big_N one;
    init_num(&one);
    insertInEnd(&one, 1);

    int sign = 0;
    if(a1.sign != b1.sign)
    {
        sign = 1;
    }

    Big_N ex, mp, pr, a = a1, b = b1, b2, quotient, tmpfree;
    init_num(&ex);
    init_num(&mp);
    init_num(&pr);
    init_num(&quotient);
    Big_N zero;
    init_num(&zero);
    insertInEnd(&zero, 0);

    if(b1.size == 0)
    {
        printf("Zero division error detected\n");
        return ex;
       
    }

    if(a1.sign)
    {
        negation(&a1);
    }
    if(b1.sign)
    {
        negation(&b1);
    }

    int cmp = compare(a1, b1);

    if(cmp == 0)
    {
        // printf("Entered here");
        one.sign = sign;
        return one;
    }
    if(cmp == 2)
    {
        
        return quotient;
    }

    //  a/ b. Taking out n digits from a where n = b.size;
    for(int i = 0; i < b1.size && a1.head; i++)
    {
        insertInEnd(&ex, a1.head->data);
        a1.head = a1.head->next;

    }

    display(ex);

    // Find the multiplier such that second number is just greater;
    int i;
    for(i = 1; i < 10; i++)
    {
        // printf("%d\n", i);
        b2 = b;
        Big_N mp_temp;
        init_num(&mp_temp);

        insertInEnd(&mp_temp, i);
        pr = mult(&b2, &mp_temp);

        int cmp = compare(ex, pr);

        if(cmp == 2)
        {
            break;
        }

        

        


    }

    display(pr);
    printf("Checkpoint\n");

    int multiplier = i-1;

    Big_N mp2;
    init_num(&mp2);
    insertInEnd(&mp2, multiplier);
    if(multiplier == 0)
    {
        pr = zero;
        display(pr);
        
    }
    else
    {
        pr = mult(&mp2, &b1);
        display(pr);

    }

    ex = sub(&ex, &pr);
    display(ex);

    insertInEnd(&quotient, multiplier);
    rem_lead_zeros(&quotient);



    while(a1.head != NULL)
    {
        insertInEnd(&ex, a1.head->data);
        rem_lead_zeros(&ex);

        for(i = 1; i < 10; i++)
        {
            b2 = b;
            Big_N mp_temp;
            init_num(&mp_temp);

            insertInEnd(&mp_temp, i);
            pr = mult(&b2, &mp_temp);

            int cmp = compare(ex, pr);

            if(cmp == 2)
            {
                break;
            }

        }

        multiplier = i - 1;
        insertInEnd(&quotient, multiplier);
        rem_lead_zeros(&quotient);

        printf("Quotient till now is: ");
        display(quotient);

        Big_N mp_temp;
        init_num(&mp_temp);
        insertInEnd(&mp_temp, multiplier);
        if(multiplier == 0)
        {
            pr = zero;
            display(pr);

        }
        else
        {
            pr = mult(&b1, &mp_temp);

        }


        ex = sub(&ex, &pr);

        display(ex);


        a1.head = a1.head->next;

    }

    printf("Loop completed\n");
    quotient.sign = sign;
    rem_lead_zeros(&quotient);

    return quotient;









}


// int main()
// {
//     Big_N a1, b1;

//     char str1[500]  = "-1948723482611";
//     char str2[500] = "50243242";

//     init_num(&a1);
//     init_num(&b1);

//     for(int i = 0; str1[i] != '\0'; i++)
//     {
//         insertInEnd(&a1, str1[i] - '0');
//     }

//     // display(a1);
//     for(int i = 0; str2[i] != '\0'; i++)
//     {
//         insertInEnd(&b1, str2[i] - '0');
//     }

//     // Big_N c = add(&a1, &b1);
//     Big_N c;
//     init_num(&c);
    
//     c = division(&a1, &b1);

//     printf("\nFinal answer: ");
//     display(c);

//     return 0;
// }