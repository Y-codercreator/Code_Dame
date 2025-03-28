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

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_premier_click = true;
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(QRect(0,0,700,600));
    ui->graphicsView->setScene(scene);

    QString fileName = relativeFileName("/images/grille_dame.jpg");
    QImage image(fileName);
    QGraphicsPixmapItem *pixmap1 =  ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
    pixmap1->setOffset(0, -40);

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label-> setText("coordonnées");

    m_jeu.init(false);
    dessinerPlateau();
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

    int x2, y2;

    x2 = ( (x - 106) / ECART_CASE );
    y2 = ( (y - 116) / ECART_CASE );

    std::cout << x2 << ";" << y2 << std::endl;

    if ( m_premier_click )
    {
        m_premier_click = false;
        m_x2 = x2;
        m_y2 = y2;
    }
    else
    {
        m_premier_click = true;
        bool coup_valide = m_jeu.deplacement( m_x2, m_y2, x2, y2);

        if ( coup_valide )
            dessinerPlateau();
        else
            std::cout << "erreur" << std::endl;
    }
}

QString MainWindow::relativeFileName( QString fileName )
{
    return QString( APPLICATION_DIR ).append(fileName);
}

void MainWindow::dessinerPlateau( )
{
    ui->graphicsView->scene()->clear();

    QString fileName = relativeFileName("/images/grille_dame.jpg");
    QImage image(fileName);
    QGraphicsPixmapItem *pixmap1 =  ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
    pixmap1->setOffset(0, -40);

    QString fileName1 = relativeFileName("/images/pion_noir.png");
    QImage image1(fileName1);
    QString fileName2 = relativeFileName("/images/pion_blanc.png");
    QImage image2(fileName2);

    for ( int i = 0; i != 10; i++)
    {
        for ( int j = 0; j != 10; j++)
        {
            if ( m_jeu.get_case_grille(i,j) == NOIR )
            {
                QGraphicsPixmapItem *pixmap2 = ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image1));
                pixmap2->setOffset(  53 + i * ECART_CASE, 23 + j * ECART_CASE);
            }
            if ( m_jeu.get_case_grille(i,j) == BLANC)
            {
                QGraphicsPixmapItem *pixmap3 = ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image2));
                pixmap3->setOffset(  53 + i * ECART_CASE, 23 + j * ECART_CASE);
            }

        }

    }
}


void MainWindow::on_btnForfait_clicked()
{
    //m_jeu.fin_partie();
    QMessageBox msgBoxForfait;
    msgBoxForfait.setText("vous avez perdus");
    int ret = msgBoxForfait.exec();
}

void MainWindow::on_btnEgalite_clicked()
{
    //m_jeu.fin_partie();
    QMessageBox msgBoxEgalite;
    msgBoxEgalite.setText("vous êtes à égalité");
    int ret = msgBoxEgalite.exec();
}

void MainWindow::on_btnRestart_clicked()
{
    QMessageBox msgBoxRestart;
    msgBoxRestart.setText("La partie va redémarrer");
    int ret = msgBoxRestart.exec();

    dessinerPlateau();
}
