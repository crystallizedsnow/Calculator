#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QDebug>
#include<string>
#include<QString>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
struct Node
{
    int data;
    int carry;
    Node* next;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    int addNum();
    int subtractNum();
    void printAnswer();
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_point_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_subtract_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_negative_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    QString expression1;
    QString sign;
    bool m;
    bool z1;
    bool z2;
    QString expression2;
    QString expression3;
    char a;
    int num;
     Node* h1;
     Node*h2;
     Node*h3;
     int zleng1;
     int zleng2;
     int xleng1;
     int xleng2;
     bool pn1;
     bool pn2;
     bool pn3;
};
#endif // MAINWINDOW_H
