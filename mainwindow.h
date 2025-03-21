#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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

protected slots:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QLabel *label;
};

#endif // MAINWINDOW_H
