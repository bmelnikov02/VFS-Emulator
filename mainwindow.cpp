#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->commandInput, &QLineEdit::returnPressed, this, &MainWindow::handleCommand);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleCommand()
{
    QString command = ui->commandInput->text();
    ui->commandInput->clear();
    QStringList parts = command.split(' ', Qt::SkipEmptyParts);
    if (parts.isEmpty())
    {
        return;
    }
    QString commandName = parts[0];
    QString commandArg = parts.mid(1).join(' ');
    if (commandName == "ls")
    {
        ui->outputText->appendPlainText("command: " + commandName);
        ui->outputText->appendPlainText("arg: " + commandArg);
    }
    else if (commandName == "cd")
    {
        ui->outputText->appendPlainText("command: " + commandName);
        ui->outputText->appendPlainText("arg: " + commandArg);
    }
    else if (commandName == "exit")
    {
        this->close();
    }
    else
    {
        ui->outputText->appendPlainText("Введена неправильная команда: " + commandName);
    }
}