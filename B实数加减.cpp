#include<iostream>
#include<stdio.h>
#include<mainwindow.h>
using namespace std;
struct Node
{
    int data;
    int carry;
    Node* next;
};
int subtractNum(Node*&, Node*&, Node*&, bool&, bool&, int&, int&);
//创建算数链表
void createAddend(Node*& h,bool& pn, int& zleng1, int& xleng1)
{
    h = new Node;
    Node* p = h;
    char a = cin.get();
    if (a >= '0' && a <= '9')
    {
        p->data = a - '0';
        a = cin.get();
        zleng1++;
    }
    bool c = true;
    while (a != '\n')
    {
        if (a == '.')
        {
            a = cin.get();
            c = false;
        }
        if (a >= '0' && a <= '9')
        {
            p->next = new Node;
            p = p->next;
            p->data = a - '0';
            a = cin.get();
            if (c)
            {
                zleng1++;
            }
            else
            {
                xleng1++;
            }
        }
        if (a == ',')
        {
            a = cin.get();
        }
        if (a == '-')
        {
            pn = false;
            a = cin.get();
            p->data = a - '0';
            zleng1++;
            a = cin.get();
        }
    }
    if (zleng1 == 0)
    {
        zleng1 = 1;
    }
    p->next = NULL;
}
//创建答案链表
void createAnswer(Node*& p3)
{
    p3->data = 0;
    p3->next = new Node;
}
//链表1、2反转
void convertList(Node*& h)
{
    Node* p = h->next;
    if (p != nullptr)
    {
        Node* q = p->next;
        p->next = h;
        Node* r = nullptr;
        while (q != nullptr && q->next != nullptr)
        {
            r = q->next;
            q->next = p;
            p = q;
            q = r;
        }
        if (q != nullptr)
        {
            q->next = p;
            h->next = nullptr;
            h = q;
        }
        else
        {
            h->next = nullptr;
            h = p;
        }
    }
}
//小数补0
void addZero(Node*& h1, Node*& h2, int& xleng1, int& xleng2, int& zleng1, int& zleng2)
{
    if (xleng1 == xleng2)
    {
        return;
    }
    else if (xleng1 > xleng2)
    {
        Node* p = h2;
        int zero = xleng1 - xleng2;
        for (int k = 0; k < zleng2 + xleng2 - 1; k++)
        {
            p = p->next;
        }
        for (int i = 0; i < zero; i++)
        {
            p->next = new Node;
            p = p->next;
            p->data = 0;
        }
        p->next = NULL;
    }
    else if (xleng1 < xleng2)
    {
        Node* p = h1;
        int zero = xleng2 - xleng1;
        for (int k = 0; k < zleng1 + xleng1 - 1; k++)
        {
            p = p->next;
        }
        for (int i = 0; i < zero; i++)
        {
            p->next = new Node;
            p = p->next;
            p->data = 0;
        }
        p->next = NULL;
    }

}
//加法
int addNum(Node*& h1, Node*& h2, Node*& h3, bool& pn1, bool& pn2, int& zleng1, int& zleng2)
{
    if (pn1 && pn2)
    {
    }
    else if (!pn1 && !pn2)
    {
        pn1 = true;
        pn2 = true;
        cout << '-';
    }
    else if (pn1 && !pn2)
    {
        pn2 = true;
        int c=subtractNum(h1, h2, h3, pn1, pn2, zleng1, zleng2);
        return c;
    }
    else
    {
        pn1 = true;
        int c=subtractNum(h2, h1, h3, pn1, pn2, zleng2, zleng1);
        return c;
    }
    convertList(h1);
    convertList(h2);
    Node* p1 = h1;
    Node* p2 = h2;
    Node* p3 = h3;
    p3->carry = 0;
    while (p1 != nullptr && p2 != nullptr)
    {
        createAnswer(p3);
        p3->data = p1->data + p2->data + p3->carry;
        if (p3->data > 9)
        {
            p3->next->carry = 1;
            p3->data = p3->data - 10;
        }
        else
        {
            p3->next->carry = 0;
        }
        p1 = p1->next;
        p2 = p2->next;
        if (p1 != nullptr || p2 != nullptr)
        {
            p3 = p3->next;
        }
    }
    while (p1 != nullptr && p2 == nullptr)
    {
        createAnswer(p3);
        p3->data = p1->data + p3->carry;
        if (p3->data > 9)
        {
            p3->next->carry = 1;
            p3->data = p3->data - 10;
        }
        else
        {
            p3->next->carry = 0;
        }
        p1 = p1->next;
        if (p1 != nullptr || p2 != nullptr)
        {
            p3 = p3->next;
        }
    }
    while (p2 != nullptr && p1 == nullptr)
    {
        createAnswer(p3);
        p3->data = p2->data + p3->carry;
        if (p3->data > 9)
        {
            p3->next->carry = 1;
            p3->data = p3->data - 10;
        }
        else
        {
            p3->next->carry = 0;
        }
        p2 = p2->next;
        if (p1 != nullptr || p2 != nullptr)
        {
            p3 = p3->next;
        }
    }
    if (p3->next->carry == 1)
    {
        p3 = p3->next;
        p3->data = 1;
        zleng1++;
        zleng2++;
    }
    p3->next = nullptr;
}
//比较被减数和减数大小(先化为正数）(传入时头指针指高位）1是被减数大，pn是1正
int compareNum2(Node* h1, Node* h2, int zleng1, int zleng2, bool pn1)
{
    bool a = true;
    if (pn1)
    {
        a = false;
    }
    Node* q1 = h1;
    Node* q2 = h2;
    //检查段数
    int i = 0;
    int k = 0;
    i = zleng1;
    k = zleng2;
    if (i > k)
    {
        if (a)
        {
            return -1;
        }
        else
            return 1;
    }
    else if (i < k)
    {
        if (a)
        {
            return 1;
        }
        else
            return -1;
    }
    else
    {
        //若段数相同，从高位开始比较
        if (q1->data - q2->data > 0)
        {
            if (a)
            {
                return -1;
            }
            else
                return 1;
        }
        if (q1->data - q2->data < 0)
        {
            if (a)
            {
                return 1;
            }
            else
                return -1;
        }
        while (q1->data == q2->data)
        {
            q1 = q1->next;
            q2 = q2->next;
            if (q1 == nullptr || q2 == nullptr)
            {
                return 0;
            }
            if (q1->data - q2->data > 0)
            {
                if (a)
                {
                    return -1;
                }
                else
                    return 1;
            }
            if (q1->data - q2->data < 0)
            {
                if (a)
                {
                    return 1;
                }
                return -1;
            }
        }
    }
}
//减法
int subtractNum(Node*& h1, Node*& h2, Node*& h3, bool& pn1, bool& pn2, int& zleng1, int& zleng2)
{
    int i = 0;
    if (pn1 && !pn2)
    {
        pn2 = true;
        addNum(h1, h2, h3, pn1, pn2, zleng1, zleng2);
        return 1;
    }
    else if (!pn1 && pn2)
    {
        pn1 = true;
        cout << '-';
        addNum(h1, h2, h3, pn1, pn2, zleng1, zleng2);
        return 1;
    }
    else
    {
        i = compareNum2(h1, h2, zleng1, zleng2, pn1);
        if (i == 0)
        {
            cout << '0' << endl;
            return 0;
        }
        else if (i > 0)
        {
            if (!pn1 && !pn2)
            {
                pn1 = true;
                pn2 = true;
                Node* temp = h2;
                h2 = h1;
                h1 = temp;
            }
        }
        else
        {
            cout << '-';
            if (!pn1 && !pn2)
            {
                pn1 = true;
                pn2 = true;
            }
            else
            {
                Node* temp = h2;
                h2 = h1;
                h1 = temp;
            }
        }
    }
    convertList(h1);
    convertList(h2);
    Node* p1 = h1;
    Node* p2 = h2;
    Node* p3 = h3;
    p3->carry = 0;
    while (p1 != nullptr && p2 != nullptr)
    {
        createAnswer(p3);
        p3->data = p1->data - p2->data + p3->carry;
        if (p3->data >= 0)
        {
            p3->next->carry = 0;
        }
        else
        {
            p3->data += 10;
            p3->next->carry = -1;
        }
        p1 = p1->next;
        p2 = p2->next;
        if (p1 != nullptr || p2 != nullptr)
        {
            p3 = p3->next;
        }
    }
    while (p1 != nullptr && p2 == nullptr)
    {
        createAnswer(p3);
        p3->data = p1->data + p3->carry;
        if (p3->data > 0)
        {
            p3->next->carry = 0;
        }
        else
        {
            p3->data += 10;
            p3->next->carry = -1;
        }
        p1 = p1->next;
        if (p1 != nullptr || p2 != nullptr)
        {
            p3 = p3->next;
        }
    }
    p3->next = nullptr;
    return 1;
}
//打印得数绝对值
void printAnswer(Node* h3, int& zleng1, int& zleng2, int& xleng1, int& xleng2)
{
    int max1 = zleng1 > zleng2 ? zleng1 : zleng2;
    int max2 = xleng1 > xleng2 ? xleng1 : xleng2;
    int m = 0;
    for (m = 0; h3->data == 0&&h3->next!=nullptr; m++)
    {
        h3 = h3->next;
    }
    max2 -= m;
    convertList(h3);
    Node* p = h3;
    int n = 0;
    while (p->data == 0&&n<max1-1)
    {
        p = p->next;
        n++;
    }
    max1 -= n;
    int remainder = max1 % 3;
    for (int i = 0; i < remainder; i++)
    {
        printf("%d", p->data);
        p = p->next;
    }
    if (remainder != max1&&remainder!=0)
    {
        printf(",");
    }
    for (int k = 0; k < max1 - remainder; k++)
    {
        printf("%d", p->data);
        p = p->next;
        if (k % 3 == 2 && k != max1 - remainder - 1)
        {
            printf(",");
        }
    }
    if (max2 != 0)
    {
        cout << '.';
    }
    for (int l = 0; l < max2; l++)
    {
        printf("%d",p->data);
        p = p->next;
    }
    cout << endl;

}
//删除指针
void deleteptr(Node*& h1)
{
    Node* p1 = h1;
    Node* p2 = nullptr;
    do
    {
        p2 = p1;
        p1 = p1->next;
        delete p2;
        p2 = nullptr;
    } while (p1 != nullptr);
}
void MainWindow::execute()
{
        Node* head1 = nullptr;
        Node* head2 = nullptr;
        Node* head3 = new Node;
        bool pn1 = true;
        bool pn2 = true;
        int zleng1 = 0;
        int xleng1 = 0;
        int zleng2 = 0;
        int xleng2 = 0;
        int c = 1;
        createAddend(head1, pn1, zleng1, xleng1);
        createAddend(head2, pn2, zleng2, xleng2);
        if (a == '+')
        {
            if (xleng1 != 0 || xleng2 != 0)
            {
                addZero(head1, head2, xleng1, xleng2, zleng1, zleng2);
            }
            c=addNum(head1, head2, head3, pn1, pn2, zleng1, zleng2);
        }
        else if (a == '-')
        {
            if (xleng1 != 0 || xleng2 != 0)
            {
                addZero(head1, head2, xleng1, xleng2, zleng1, zleng2);
            }
            c=subtractNum(head1, head2, head3, pn1, pn2, zleng1, zleng2);
        }
        if (c)
        {
            printAnswer(head3, zleng1, zleng2, xleng1, xleng2);
        }
        else
        {
            head3->next = nullptr;
        }
        deleteptr(head1);
        deleteptr(head2);
        deleteptr(head3);
        head3 = NULL;
}

