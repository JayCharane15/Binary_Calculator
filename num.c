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

    node* follow = temp;
    int count = 0;
    while(temp && temp->data == 0)
    {
        follow = temp;
        free(follow);
        count++;
        temp = temp->next;

    }

    if(temp == NULL)
    {
        Big_N new;
        init_num(&new);

        *num = new;
        return;
    }

    num->size -= count;
    temp->prev = NULL;
    num->head = temp;
}


void destroy(Big_N* num)
{
    node* temp = num->head;
    node* follow;
    while(temp)
    {
        follow = temp;
        free(follow);
        temp = temp->next;
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
    }

    rem_lead_zeros(&substarction);
    // if(rev)
    // {
    //     negation(&substarction);
    // }

    return substarction;

    
}


int main()
{
    Big_N a1, b1;

    char str1[500] = "12345678910";
    char str2[500]  = "-1234567891011";

    init_num(&a1);
    init_num(&b1);

    for(int i = 0; str1[i] != '\0'; i++)
    {
        insertInEnd(&a1, str1[i] - '0');
    }

    // display(a1);
    for(int i = 0; str2[i] != '\0'; i++)
    {
        insertInEnd(&b1, str2[i] - '0');
    }

    // Big_N c = add(&a1, &b1);
    Big_N c;
    init_num(&c);

    c = add(&a1, &b1);

    display(c);

    return 0;
}