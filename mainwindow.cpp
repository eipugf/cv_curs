#include "mainwindow.h"
#include <QFileDialog>
#include "ui_mainwindow.h"
#include "fileutils.h"
#include "classificator.h"
#include "convertutils.h"
#include "trainer.h"
#include <QTime>
#include <stdio.h>
#include <QtConcurrent/QtConcurrentMap>
#include <QtConcurrent/QtConcurrentRun>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->trainerProgress->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_computeBayesian_clicked()
{
    path = QFileDialog::getExistingDirectory(
                this,
                tr("Выберите директорию"),
                "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(path.isEmpty())
         return;
    ui->trainerProgress->setVisible(true);
    QObject::connect(&timer, SIGNAL(timeout()), SLOT(TimerTick()));
    timer.setInterval(100);
    timer.start();
    QtConcurrent::run(this, &MainWindow::traine);
    ui->computeBayesian->setEnabled(false);
}

void MainWindow::TimerTick()
{
    if( ui->trainerProgress->value() >= ui->trainerProgress->maximum())
        ui->trainerProgress->reset();
    ui->trainerProgress->setValue(ui->trainerProgress->value()+1);
}

void MainWindow::traine()
{
    QString timeForm = "hh:mm:ss";
    ui->textPanel->setText("");
    QString log = QTime::currentTime().toString(timeForm)+") Загружаю файлы...\n";
    ui->textPanel->setText(log);
    vector<vector<Matrix>> classes = FileUtils::dataLoad(path);
    log += QTime::currentTime().toString(timeForm)+") Вычисляю дескрипторы...\n";
    ui->textPanel->setText(log);
    auto descr = Trainer().computeDescriptors(classes);
    log += QTime::currentTime().toString(timeForm)+") Кластеризую...\n";
    ui->textPanel->setText(log);
    auto bagOfWords = Trainer().computeBagOfWords(descr, ui->countClasters->value());
    log += QTime::currentTime().toString(timeForm)+") Вычисляю вероятности...\n";
    ui->textPanel->setText(log);
    auto prob = Trainer().computeProbability(descr,bagOfWords);
    this->classifier = make_unique<Classificator>(bagOfWords,prob);
    log += QTime::currentTime().toString(timeForm)+") Обучение выполнено...";
    ui->textPanel->setText(log);
    ui->trainerProgress->setVisible(false);
    ui->computeBayesian->setEnabled(true);

}

void MainWindow::on_saveButton_clicked()
{
    if(classifier != NULL){
        QString path = QFileDialog::getSaveFileName(this,
                                            tr("Имя файла для записи"),"/home",".json");
        if(path.isEmpty())
            return;
        if(!path.endsWith(".json"))
            path += ".json";
        FileUtils::save(*classifier,path);
    }
}

void MainWindow::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                           tr("Имя файла для записи"),"/home","Data (*.json)");
    auto cl = FileUtils::load(path);
    this->classifier = make_unique<Classificator>(std::move(cl));
}

void MainWindow::on_classifyButton_clicked()
{
    if(classifier != NULL){
        QString path = QFileDialog::getOpenFileName(this,
                   tr("Имя файла для записи"),"/home","Image(*.png *.jpg)");
        if(path.isEmpty())
            return;
        auto solve = classifier->classify(FileUtils::loagImage(path));
        QString res = "Класс: "+QString::number(solve.classId)+"\nПорядок: "+
                QString::number(solve.exp)+"\nМантисса: "+
                QString::number((double)solve.mant);
        ui->textPanel->setText(res);
    }
}
