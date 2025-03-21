#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defines.h"

#include <QDialog>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QSettings>
#include <iostream>

#include <QFile>
#include <QGraphicsPixmapItem>
#include <QImage>

#include <QMouseEvent>
#include <QLabel>

#include <defines.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(QRect(0,0,700,600));
    ui->graphicsView->setScene(scene);

    QString fileName = relativeFileName("/images/grille_dame.jpg");
    QImage image(fileName);
    QGraphicsPixmapItem *pixmap1 =  ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
    pixmap1->setOffset(0, -40);

    QString fileName = relativeFileName("/images/pion_noir.png");
    QImage image1(fileName);
    QGraphicsPixmapItem *pixmap2 = ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image1));
    pixmap2->setOffset(116 + 2 * i * ECART_CASE, 23);


    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label-> setText("coordonnées");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    int x = event->x();
    int y = event->y();

    label->setText(QString("%1, %2").arg(x).arg(y));
}

QString MainWindow::relativeFileName( QString fileName )
{
    return QString( APPLICATION_DIR ).append(fileName);
}


