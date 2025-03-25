#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "jeu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString static relativeFileName( QString fileName );

    void dessinerPlateau( );

protected slots:
    void mousePressEvent(QMouseEvent *event);


private slots:
    void on_btnForfait_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *label;
    Jeu m_jeu;
};

#endif // MAINWINDOW_H
