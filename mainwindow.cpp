#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::open_file()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    return fileName;
}

QString MainWindow::creat_file()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    return fileName;
}

int MainWindow::check_files(QString a, QString b, QString dest){
     QMessageBox msgBox;
    if(a.size() == 0 || QString::compare(a,"Nenhum arquivo selecionado") == 0){
        msgBox.setText("O primeiro arquivo não foi selecionado");
        msgBox.exec();
        ui->label_path_a->setText(this->open_file());
        return 1;
    }
    if(b.size() == 0 || QString::compare(b,"Nenhum arquivo selecionado") == 0){
        if(ui->set_type->value() == 0){
            msgBox.setText("O segundo arquivo não foi selecionado");
        } else {
           msgBox.setText("O arquivo delta não foi selecionado");
        }
        msgBox.exec();
        ui->label_path_b->setText(this->open_file());

        return 2;
    }
    if(dest.size() == 0 || QString::compare(dest,"Nenhum arquivo selecionado") == 0){
        msgBox.setText("O destino do arquivo não foi selecionado");
        msgBox.exec();
        ui->label_path_dest->setText(this->creat_file());
        return 3;
    }
    return 0;
}

void MainWindow::start_process(QString type,QString a, QString b,QString dest){
    ui->label_load->setText("Carregando..");

    MainWindow::myProcess = new QProcess();
    MainWindow::myProcess->setProgram("delta");

    QStringList arguments;
    arguments << type << a << b << dest;

    MainWindow::myProcess->setArguments(arguments);
    MainWindow::myProcess->start();

    connect(MainWindow::myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(read_output()));
    connect(MainWindow::myProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &MainWindow::my_process);
}

void MainWindow::on_button_a_clicked()
{
    ui->label_path_a->setText(this->open_file());
}

void MainWindow::on_button_b_clicked()
{
    ui->label_path_b->setText(this->open_file());
}


void MainWindow::on_button_dest_clicked()
{
    ui->label_path_dest->setText(this->creat_file());
}

void MainWindow::on_button_start_clicked()
{
    ui->console->setText("");
    QString a = ui->label_path_a->text();
    QString b = ui->label_path_b->text();
    QString dest = ui->label_path_dest->text();
    QString type = ui->set_type->value() == 0 ? "c" : "d";
    const int r_check = this->check_files(a,b,dest);

    if(r_check == 0){
        ui->button_start->setEnabled(false);
        ui->label_load->setText(QString::number(r_check));
        MainWindow::start_process(type,a,b,dest);
    }
}

void MainWindow::read_output(){
   ui->console->text();
   ui->console->setText(ui->console->text()+myProcess->readAllStandardOutput());
}

void MainWindow::my_process(){
    ui->label_load->setText("");
    ui->button_start->setEnabled(true);
}


void MainWindow::on_actionComprimir_triggered()
{
    ui->set_type->setValue(0);
}


void MainWindow::on_actionDescomprimir_triggered()
{
    ui->set_type->setValue(1);
}

void MainWindow::on_set_type_valueChanged(int value)
{
    if(value == 0){
       ui->label_b->setText("Escolha segundo arquivo");
    } else {
       ui->label_b->setText("Escolha delta arquivo");
    }
}


void MainWindow::on_actionSobre_triggered()
{
    about *about_w = new about();
    about_w->show();
}

