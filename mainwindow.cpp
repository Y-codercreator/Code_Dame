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



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(QRect(0,0,700,600));
    ui->graphicsView->setScene(scene);

    QString fileName = relativeFileName("/images/dame.jpg");
    QImage image(fileName);
    QGraphicsPixmapItem *pixmap =  ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
    pixmap->setOffset(11,10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::relativeFileName( QString fileName )
{
return QString( APPLICATION_DIR ).append(fileName);
}
