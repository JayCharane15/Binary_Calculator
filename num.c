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

int main()
{
    Big_N a1, b1;

    char str1[500] = "13859287346598726349856298347659826349855";
    char str2[500]  = "960923745987203948750927340957092837904572093847057293048750983479";

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