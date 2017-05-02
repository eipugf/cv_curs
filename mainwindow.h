#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QLabel>
#include <QRunnable>

#include "classificator.h"
#include <memory>
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    unique_ptr<Classificator> classifier;
    QString path;

public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private slots:
    void on_computeBayesian_clicked();
    void TimerTick( void );
    void traine();
    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_classifyButton_clicked();

private:
    Ui::MainWindow *ui;

    QTimer timer;
};

#endif // MAINWINDOW_H
