#include <stdio.h>
#include <stdlib.h>

struct BigInteger {
    struct Node * head;
    int length;
};

struct Node {
    int data;
    struct Node * next;
};

struct BigInteger initialize(char * s) {
    struct BigInteger BigInt;
    BigInt.length = 0;
    BigInt.head = NULL;
    for (int i=0; s[i] != '\0'; i++) {
        struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = s[i] - '0';
        temp->next = BigInt.head;
        BigInt.head = temp;
        BigInt.length++;
    }
    return BigInt;
}

void displayHelper(struct Node * head) {
    if (head == NULL) {
        return;
    } else {
        displayHelper(head->next);
        printf("%d", head->data);
    }
}

void display(struct BigInteger a) {
    displayHelper(a.head);
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger add;
    struct Node * last1 = a.head;
    struct Node * last2 = b.head;
    struct Node *temp1;
    int carry = 0;
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if (last1->data + last2->data > 9)
    {
        temp->data = (last1->data + last2->data) % 10;
        carry = 1;
    }
    else
    {
        temp->data = last1->data + last2->data;
        carry = 0;
    }
    last1 = last1->next;
    last2 = last2->next;
    add.head = temp;
    while (last1 != NULL && last2 != NULL)
    {
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        temp->next = temp1;
        temp = temp1;
        if (last1->data + last2->data + carry > 9)
        {
            temp->data = (last1->data + last2->data + carry) % 10;
            carry = 1;
        }
        else
        {
            temp->data = last1->data + last2->data + carry;
            carry = 0;
        }
        last1 = last1->next;
        last2 = last2->next;
    }
    while (last1 != NULL)
    {
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        if ((last1->data + carry) > 9)
        {
            temp1->data = (last1->data + carry) % 10;
            carry = 1;
        }
        else
        {
            temp1->data = (last1->data + carry);
            carry = 0;
        }
        temp->next = temp1;
        temp = temp1;
        last1 = last1->next;
    }
    while (last2 != NULL)
    {
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        if ((last2->data + carry) > 9)
        {
            temp1->data = (last2->data + carry) % 10;
            carry = 1;
        }
        else
        {
            temp1->data = (last2->data + carry);
            carry = 0;
        }
        temp->next = temp1;
        temp = temp1;
        last2 = last2->next;
    }
    if (carry == 1)
    {
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        temp1->data = carry;
        temp->next = temp1;
        temp = temp1;
    }
    temp->next = NULL;
    return add;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    struct Node * last1 = a.head;
    struct Node * last2 = b.head;
    struct BigInteger sub;
    struct Node *temp, *temp1;
    int borrow = 0;
    if (last1->data >= last2->data)
    {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = last1->data - last2->data;
        borrow = 0;
    }
    else
    {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = (10 + last1->data) - last2->data;
        borrow = 1;
    }
    last1 = last1->next;
    last2 = last2->next;
    sub.head = temp;
    while (last1 != NULL && last2 != NULL)
    {
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        temp->next = temp1;
        temp = temp1;
        if (last1->data > last2->data && borrow == 1)
        {
            temp1->data = last1->data - 1 - last2->data;
            borrow = 0;
        }
        else if (last1->data >= last2->data && borrow == 0)
        {
            temp1->data = last1->data - last2->data;
            borrow = 0;
        }
        else if (last1->data < last2->data && borrow == 0)
        {
            temp1->data = 10 + last1->data - last2->data;
            borrow = 1;
        }
        else
        {
            temp->data = last1->data - 1 + 10 - last2->data;
            borrow = 1;
        }
        last1 = last1->next;
        last2 = last2->next;
    }
    while (last1 != NULL)
    {
        if (borrow == 1)
        {
            temp1 = (struct Node *)malloc(sizeof(struct Node));
            temp1->data = last1->data - 1;
        }
        else
        {
            temp1 = (struct Node *)malloc(sizeof(struct Node));
            temp1->data = last1->data;
        }
        temp->next = temp1;
        temp = temp1;
        last1 = last1->next;
    }
    temp->next = NULL;
    return sub;
}

void appendAtFirst(struct Node **mul)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = 0;
    temp->next = *mul;
    *mul = temp;
}

struct Node *mulTwoNumOneDigit(struct Node *num1, struct Node *last2)
{
    int carry = 0;
    struct Node * last1 = num1;
    struct Node *temp, *temp1;
    struct Node * mul;
    temp = (struct Node *)malloc(sizeof(struct Node));
    if (last1->data * last2->data > 9)
    {
        temp->data = (last1->data * last2->data) % 10;
        carry = ((last1->data * last2->data) - ((last1->data * last2->data) % 10)) / 10;
    }
    else
    {
        temp->data = last1->data * last2->data;
        carry = 0;
    }
    mul = temp;
    last1 = last1->next;
    while (last1 != NULL)
    {
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        if (last1->data * last2->data > 9)
        {
            temp1->data = (last1->data * last2->data + carry) % 10;
            carry = ((last1->data * last2->data + carry) - (last1->data * last2->data + carry) % 10) / 10;
        }
        else
        {
            if ((last1->data * last2->data + carry) > 9)
            {
                temp1->data = (last1->data * last2->data + carry) % 10;
                carry = 1;
            }
            else
            {
                temp1->data = last1->data * last2->data + carry;
                carry = 0;
            }
        }
        temp->next = temp1;
        temp = temp1;
        last1 = last1->next;
    }
    if (carry > 0)
    {
        temp1 = (struct Node *)malloc(sizeof(struct Node));
        temp1->data = carry;
        temp->next = temp1;
        temp = temp1;
    }
    temp->next = NULL;
    return mul;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    int i = 1;
    struct BigInteger multiply, temp, mul, final;
    struct Node * last1 = a.head;
    struct Node * last2 = b.head;
    temp.head = mulTwoNumOneDigit(last1, last2);
    final = temp;
    last2 = last2->next;
    while (last2 != NULL)
    {
        multiply.head = mulTwoNumOneDigit(last1, last2);
        for (int j = 1; j <= i; j++)
        {
            appendAtFirst(&(multiply.head));
        }
        i++;
        final = add(final, multiply);
        last2 = last2->next;
    }
    return final;
}


struct Node* create_node(int data)
{
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    if (new == NULL) 
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new->data = data;
    new->next = NULL;
    return new;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    struct Node *dividend = a.head;
    struct Node * divisor = b.head;
    struct Node * quotient = NULL;
    struct Node * currentQuotientNode = NULL;
    struct Node * remainder = NULL;
    struct Node* currentRemainderNode = NULL;

    if (divisor->data == 0) {
        printf("Division by zero is not allowed.\n");
        exit(1);
    }

    while (dividend != NULL) {
        int currentDividend = dividend->data;
        if (remainder != NULL) {
            struct Node* temp = create_node(currentDividend);
            temp->next = remainder;
            remainder = temp;
        } else {
            remainder = create_node(currentDividend);
        }

        int currentQuotient = 0;

        while (currentDividend >= divisor->data) {
            currentDividend -= divisor->data;
            currentQuotient++;
        }

        if (currentQuotient > 0) {
            if (quotient == NULL) {
                quotient = create_node(currentQuotient);
                currentQuotientNode = quotient;
            } else {
                currentQuotientNode->next = create_node(currentQuotient);
                currentQuotientNode = currentQuotientNode->next;
            }
        }

        dividend = dividend->next;
    }
    res.head = quotient;
    return res;
}