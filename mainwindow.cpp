#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m=true;
    h1 = new Node;
    h2=new Node;
    h3=new Node;
    zleng1=0;
    zleng2=0;
    xleng1=0;
    xleng2=0;
    z1=true;
    z2=true;
    pn1=true;
    pn2=true;
    pn3=true;
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
}
MainWindow::~MainWindow()
{
    delete ui;
}

//创建答案链表
void createAnswer(Node*& p3)
{
    p3->data = 0;
    p3->next = new Node;
}
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
int MainWindow::addNum()
{
    if (pn1 && pn2)
    {
    }
    else if (!pn1 && !pn2)
    {
        pn1 = true;
        pn2 = true;
        pn3= false;
    }
    else if (pn1 && !pn2)
    {
        pn2 = true;
        int c=subtractNum();
        return c;
    }
    else
    {
        pn1 = true;
        int temp1=zleng1;
        zleng1=zleng2;
        zleng2=temp1;
        temp1=xleng1;
        xleng1=xleng2;
        xleng2=temp1;
        Node*temp=h1;
        h1=h2;
        h2=temp;
        int c=subtractNum();
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
int MainWindow::subtractNum()
{
    int i = 0;
    if (pn1 && !pn2)
    {
        pn2 = true;
        addNum();
        return 1;
    }
    else if (!pn1 && pn2)
    {
        pn1 = true;
        pn3=false;
        addNum();
        return 1;
    }
    else
    {
        i = compareNum2(h1, h2, zleng1, zleng2, pn1);
        if (i == 0)
        {
            expression3='0';
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
            pn3=false;
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
        if (p1 != nullptr || p2 != nullptr)
        {
            p3 = p3->next;
        }
    }
    p3->next = nullptr;
    return 1;
}
//打印得数绝对值
void MainWindow::printAnswer()
{
    int max1 = zleng1 > zleng2 ? zleng1 : zleng2;
    int max2 = xleng1 > xleng2 ? xleng1 : xleng2;
    int m = 0;
    for (m = 0; h3->data == 0&&h3->next!=nullptr; m++)
    {
        h3 = h3->next;
    }
    if(pn3==false)
    {expression3+='-';}
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
        string d=to_string(p->data);
        expression3+= QString::fromStdString(d);
        p = p->next;
    }
    if (remainder != max1&&remainder!=0)
    {
         expression3+=',';
    }
    for (int k = 0; k < max1 - remainder; k++)
    {
        string d=to_string(p->data);
        expression3+= QString::fromStdString(d);
        p = p->next;
        if (k % 3 == 2 && k != max1 - remainder - 1)
        {
          expression3+=',';
        }
    }
    if (max2 != 0)
    {
         expression3+='.';
    }
    for (int l = 0; l < max2; l++)
    {
        string d=to_string(p->data);
        expression3+= QString::fromStdString(d);
        p = p->next;
    }
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

void MainWindow::on_pushButton_1_clicked()
{  if(m)
    {
    expression1+="1";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="1";
        ui->lineEdit_3->setText(expression2);
    }
}
void MainWindow::on_pushButton_2_clicked()
{

    if(m)
    {
    expression1+="2";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="2";
        ui->lineEdit_3->setText(expression2);
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    if(m)
    {
    expression1+="3";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="3";
        ui->lineEdit_3->setText(expression2);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(m)
    {
    expression1+="4";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="4";
        ui->lineEdit_3->setText(expression2);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(m)
    {
    expression1+="5";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="5";
        ui->lineEdit_3->setText(expression2);
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if(m)
    {
    expression1+="6";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="6";
        ui->lineEdit_3->setText(expression2);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if(m)
    {
    expression1+="7";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="7";
        ui->lineEdit_3->setText(expression2);
    }
}
void MainWindow::on_pushButton_8_clicked()
{
    if(m)
    {
    expression1+="8";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="8";
        ui->lineEdit_3->setText(expression2);
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(m)
    {
    expression1+="9";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="9";
        ui->lineEdit_3->setText(expression2);
    }
}
void MainWindow::on_pushButton_10_clicked()
{
    if(m)
    {
    expression1+="0";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+="0";
        ui->lineEdit_3->setText(expression2);
    }
}

void MainWindow::on_pushButton_point_clicked()
{
    if(m)
    {
    expression1+=".";
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2+=".";
        ui->lineEdit_3->setText(expression2);
    }
}

void MainWindow::on_pushButton_add_clicked()
{
    sign="+";
    a='+';
    ui->lineEdit_1->setText(sign);
    m=false;
}

void MainWindow::on_pushButton_subtract_clicked()
{
    sign="-";
    a='-';
    ui->lineEdit_1->setText(sign);
    m=false;
}
void MainWindow::on_pushButton_clear_clicked()
{
    expression1.clear();
    expression2.clear();
    expression3.clear();
    sign.clear();
     ui->lineEdit_2->setText(expression1);
     ui->lineEdit_3->setText(expression2);
     ui->lineEdit_1->setText(sign);
     ui->lineEdit_4->setText(expression3);
     m=true;
     h1 = new Node;
     h2=new Node;
     h3=new Node;
     zleng1=0;
     zleng2=0;
     xleng1=0;
     xleng2=0;
     z1=true;
     z2=true;
     pn1=true;
     pn2=true;
     pn3=true;

}

void MainWindow::on_pushButton_delete_clicked()
{
    if(m)
    {
    expression1.chop(1);
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
        expression2.chop(1);
        ui->lineEdit_3->setText(expression2);
    }

}

void MainWindow::on_pushButton_negative_clicked()
{
    if(m)
    {
    expression1="-";
    pn1=false;
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
    expression2="-";
    pn2=false;
    ui->lineEdit_3->setText(expression2);
    }
}

void MainWindow::on_pushButton_equal_clicked()
{
   string Expression1=expression1.toStdString();
   string Expression2=expression2.toStdString();
   if(pn1==false)
   {
   Expression1=Expression1.substr(1,Expression1.length());
   }
   if(pn2==false)
   {
   Expression2=Expression2.substr(1,Expression2.length());
   }

   Node*p1=h1;
   Node*p2=h2;

   p1->data = Expression1[0]-'0';
   zleng1++;
   for(int i = 1;i<Expression1.length()&&Expression1[i]!='.';i++)
   {
       p1->next=new Node;
       p1=p1->next;
        p1->data = Expression1[i] - '0';
        zleng1++;
   }
   for(int i = zleng1+1;i<Expression1.length()&&Expression1[i]!='.';i++)
   {
       p1->next=new Node;
       p1=p1->next;
        p1->data = Expression1[i] - '0';
        xleng1++;
   }
   p1->next=NULL;

   p2->data = Expression2[0]-'0';
   zleng2++;
   for(int i = 1;i<Expression2.length()&&Expression2[i]!='.';i++)
   {
       p2->next=new Node;
       p2=p2->next;
        p2->data = Expression2[i] - '0';
        zleng2++;
   }
   for(int i = zleng2+1;i<Expression2.length()&&Expression2[i]!='.';i++)
   {
       p2->next=new Node;
       p2=p2->next;
        p2->data = Expression2[i] - '0';
        xleng2++;
   }
   p2->next=NULL;

   int c = 1;
   if (a == '+')
   {
       if (xleng1 != 0 || xleng2 != 0)
       {
           addZero(h1, h2, xleng1, xleng2, zleng1, zleng2);
       }
       c=addNum();
   }
   else if (a == '-')
   {
       if (xleng1 != 0 || xleng2 != 0)
       {
           addZero(h1, h2, xleng1, xleng2, zleng1, zleng2);
       }
       c=subtractNum();
   }
   if (c)
   {
       printAnswer();
   }
   else
   {
       h3->next = nullptr;
   }
   deleteptr(h1);
   deleteptr(h2);
   deleteptr(h3);
   h3 = NULL;
   ui->lineEdit_4->setText(expression3);
}





void MainWindow::on_pushButton_12_clicked()
{
    if(m)
    {
    expression1="";
    pn1=true;
    ui->lineEdit_2->setText(expression1);
    }
    else
    {
    expression2="";
    pn2=true;
    ui->lineEdit_3->setText(expression2);
    }
}
