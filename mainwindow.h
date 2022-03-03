#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_a_clicked();

    QString open_file();

    QString creat_file();

    void read_output();
    void my_process();

    int check_files(QString a, QString b,QString dest);

    void start_process(QString type,QString a, QString b,QString dest);

    void on_button_b_clicked();

    void on_button_dest_clicked();

    void on_button_start_clicked();

    void on_actionComprimir_triggered();

    void on_actionDescomprimir_triggered();

    void on_set_type_valueChanged(int value);

    void on_actionSobre_triggered();

private:
    Ui::MainWindow *ui;
    QProcess * myProcess;
};
#endif // MAINWINDOW_H
