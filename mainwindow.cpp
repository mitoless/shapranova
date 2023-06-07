#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPixmap"
#include "3polka.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_GO_clicked()
{
    QPainterPath path;
    QPixmap pm(width(), height());
    QPainter painter;
    painter.begin(&pm);
    pm.fill(Qt::white);
    QPen pen;
    pen.setColor(0xBB518B);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(1);
    painter.setPen(pen);

    double xmin = -5, xmax = 5;
    double ymin = -5, ymax = 5;
    int xg, yg;
    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();
    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    double x0 = xgmin - kx * xmin;
    double y0 = ygmin - ky * ymax;

    painter.drawLine(0, pm.height()*0.5, pm.width(), pm.height()*0.5);
    painter.drawLine(pm.width()*0.5, 0, pm.width()*0.5, pm.height());

    // функция !!

    double zn = xmin;
    double rr;
    //double step = (xmax - xmin)/(xgmax - xgmin);
    double step = 0.1;
    QString s = ui->lineEdit_z->text();

    QPen pen2;
    pen2.setColor(0x321414);
    pen2.setWidth(1);
    painter.setPen(pen2);
    QString ss = s.replace("x", "(" + QString::number(zn) + ")");
    int z = calc(ss.toStdString(), rr);
    xg = x0 + kx * zn;
    yg = y0 + ky * rr;
    path.moveTo(xg, yg);

    while (zn <= xmax) {        
        QString s = ui->lineEdit_z->text();
        QString ss = s.replace("x", "(" + QString::number(zn) + ")");
        for (int i = 0; i<ss.length();i++){
            if (ss[i] == 'e') {
                ss = "0.000000";
            }
        }
        int z = calc(ss.toStdString(), rr);
        QString pr = QString::number(rr);

        rr = pr.toDouble();
        xg = x0 + kx * zn;
        yg = y0 + ky * rr;
        path.lineTo(xg, yg);
        zn = zn + step;
    }

    painter.drawPath(path);
    painter.end();
    ui->label_r->setPixmap(pm);

}
