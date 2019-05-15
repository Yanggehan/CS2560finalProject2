#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MathFuncsLib.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
QString line;
QString item_0;
QString item_1;
QString item_2;
QString item_3;
QString item_4;
QString item_5;
QString item_6;
QString item_7;
QString item_8;
QString item_9;
int flag = 0,flag1 = 0; //flag加号标志，flag1等于号标志
int flag3 = 0;//减号标志
 int flag4 = 0;//乘号标志
int flag5 = 0;//除号标志
int flag6 = 0;//余数标志
 QString temp1,temp2;
 double sum = 0;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_7_clicked()
{

      item_1 = ui->pushButton_7->text();
        line += item_1;
       ui->label->setText(line);
}

void MainWindow::on_pushButton_2_clicked()
{
     item_8 = ui->pushButton_2->text();
       line += item_8;
      ui->label->setText(line);
}

void MainWindow::on_pushButton_3_clicked()
{
     item_9 = ui->pushButton_3->text();
       line += item_9;
      ui->label->setText(line);
}

void MainWindow::on_pushButton_clicked()
{
    item_7 = ui->pushButton->text();
      line += item_7;
     ui->label->setText(line);
}

void MainWindow::on_pushButton_4_clicked()
{
    item_4 = ui->pushButton_4->text();
      line += item_4;
     ui->label->setText(line);
}

void MainWindow::on_pushButton_5_clicked()
{
    item_5 = ui->pushButton_5->text();
      line += item_5;
     ui->label->setText(line);
}

void MainWindow::on_pushButton_6_clicked()
{
    item_6 = ui->pushButton_6->text();
      line += item_6;
     ui->label->setText(line);
}

void MainWindow::on_pushButton_8_clicked()
{
    item_2 = ui->pushButton_8->text();
      line += item_2;
     ui->label->setText(line);
}

void MainWindow::on_pushButton_9_clicked()
{
    item_3 = ui->pushButton_9->text();
      line += item_3;
     ui->label->setText(line);
}

void MainWindow::on_pushButton_10_clicked()
{
    item_0 = ui->pushButton_10->text();
      line += item_0;
     ui->label->setText(line);
}

void MainWindow::on_pushButton_14_clicked()
{
    flag = 1;
    temp1 = ui->label->text(); //获取前面输入的字符，并临时保存起来
     line.clear(); //清空字符数组
     ui->label->setText(line);//显示清空状态
}

void MainWindow::on_pushButton_13_clicked()
{
    flag3 = 1;
    temp1 = ui->label->text(); //获取前面输入的字符，并临时保存起来
     line.clear(); //清空字符数组
     ui->label->setText(line);//显示清空状态
}

void MainWindow::on_pushButton_12_clicked()
{
    flag4 = 1;
    temp1 = ui->label->text(); //获取前面输入的字符，并临时保存起来
     line.clear(); //清空字符数组
     ui->label->setText(line);//显示清空状态
}

void MainWindow::on_pushButton_11_clicked()
{
    flag5 = 1;
    temp1 = ui->label->text(); //获取前面输入的字符，并临时保存起来
     line.clear(); //清空字符数组
     ui->label->setText(line);//显示清空状态
}
void MainWindow::on_pushButton_15_clicked()
{
    flag6 = 1;
    temp1 = ui->label->text(); //获取前面输入的字符，并临时保存起来
     line.clear(); //清空字符数组
     ui->label->setText(line);//显示清空状态
}

void MainWindow::on_pushButton_16_clicked()
{
    flag1 = 1; //按一次等于号就改变状态
         if(flag == 1) //加法
       {
           temp2 = ui->label->text();
        line.clear(); //清空字符串
           sum = temp1.toDouble() + temp2.toDouble(); //将字符转换成浮点型
         ui->label->setText(QString::number(sum)); //将浮点型转换成字符
          flag = 0; //重新让标志位置零，等待下一次的加法进行
       }

     else if(flag3 == 1) //减法
      {
           temp2 = ui->label->text();
           line.clear(); //清空字符串
          ui->label->setText(line);
          sum = temp1.toDouble() - temp2.toDouble(); //将字符转换成浮点型

         if(sum == 0) //等于0
          {
               ui->label->setText("0");
            }
         ui->label->setText(QString::number(sum)); //将浮点型转换成字符
                // qDebug()<<sum;
           flag3 = 0; //重新让标志位置零，等待下一次的减法进行
      }

      else if(flag4 == 1) //除法
      {
          temp2 = ui->label->text();
         line.clear(); //清空字符串
         sum = temp1.toDouble() / temp2.toDouble(); //将字符转换成浮点型
        if(temp2 == "0") //分母等于0
          {
             ui->label->setText("0");
        }
         ui->label->setText(QString::number(sum)); //将浮点型转换成字符
          flag4 = 0; //重新让标志位置零,等待下一次的除法进行
      }

    else if(flag5 == 1) //乘法
      {
          temp2 = ui->label->text();
          line.clear(); //清空字符串
         sum = temp1.toDouble() * temp2.toDouble(); //将字符转换成浮点型
             ui->label->setText(QString::number(sum)); //将浮点型转换成字符
            flag5 = 0; //重新让标志位置零，等待下一次的乘法进行
         }
         else if(flag6 == 1) //余数
           {
               temp2 = ui->label->text();
               line.clear(); //清空字符串
              sum = temp1.toInt() % temp2.toInt(); //将字符转换成浮点型
                  ui->label->setText(QString::number(sum)); //将浮点型转换成字符
                 flag5 = 0; //重新让标志位置零，等待下一次的乘法进行
              }
}


