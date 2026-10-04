#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(const QString& vfsPath,const QString& startupScriptPath,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , vfsPath(vfsPath)
    , startupScriptPath(startupScriptPath)
{
    ui->setupUi(this);
    uptimeTimer.start();
    connect(ui->commandInput, &QLineEdit::returnPressed, this, &MainWindow::handleCommand);
    vfs = std::make_unique<VFS>(vfsPath);
    runStartupScript();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleCommand()
{
    QString command = ui->commandInput->text();
    ui->commandInput->clear();
    ui->outputText->appendPlainText("> " + command);
    executeCommand(command);
}

void MainWindow::executeCommand(const QString &command)
{
    QStringList parts = command.split(' ', Qt::SkipEmptyParts);
    if (parts.isEmpty())
    {
        return;
    }
    QString commandName = parts[0];
    QString commandArg = parts.mid(1).join(' ');
    if (commandName == "ls")
    {
        QStringList entries = vfs->listCurrentDirectory();
        for (const auto& entry : entries)
        {
            ui->outputText->appendPlainText(entry);
        }

    }
    else if (commandName == "cd")
    {
        if (!vfs->changeDirectory(commandArg))
        {
            ui->outputText->appendPlainText("Каталог не найден: " + commandArg);
        }
    }
    else if (commandName == "exit")
    {
        this->close();
    }
    else if (commandName == "conf-dump")
    {
        ui->outputText->appendPlainText("vfsPath=" + vfsPath);
        ui->outputText->appendPlainText("startupScriptPath=" + startupScriptPath);
    }
    else if (commandName == "tree")
    {
        ui->outputText->appendPlainText(vfs->tree());
    }
    else if (commandName == "uptime")
    {
        qint64 seconds = uptimeTimer.elapsed() / 1000;
        ui->outputText->appendPlainText("uptime: " + QString::number(seconds) + "s");
    }
    else if (commandName == "chmod")
    {
        if (parts.size() != 3)
        {
            ui->outputText->appendPlainText("Использование: chmod <permissions> <name>");
            return;
        }
        QString permissionsText = parts[1];
        QString name = parts[2];
        bool ok;
        int permissions = permissionsText.toInt(&ok, 8);
        if (!ok || permissions < 0 || permissions > 0777)
        {
            ui->outputText->appendPlainText("Некорректные права");
            return;
        }
        if (!vfs->changePermissions(name, permissions))
        {
            ui->outputText->appendPlainText("Объект не найден: " + name);
            return;
        }
        ui->outputText->appendPlainText("Права изменены: " + name + " -> " + permissionsText);
    }
    else if (commandName == "cp")
    {
        if (parts.size() != 3)
        {
            ui->outputText->appendPlainText("Использование: cp <source> <destination>");
            return;
        }
        QString sourceName = parts[1];
        QString destinationName = parts[2];
        if (!vfs->copyNode(sourceName,destinationName))
        {
            ui->outputText->appendPlainText("Не удалось выполнить копирование");
            return;
        }
        ui->outputText->appendPlainText("Скопировано: " + sourceName + " -> " + destinationName);
    }
    else
    {
        ui->outputText->appendPlainText("Введена неправильная команда: " + commandName);
    }
}

void MainWindow::runStartupScript()
{
    QFile file(startupScriptPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->outputText->appendPlainText("Не удалось открыть файл");
        return;
    }
    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        ui->outputText->appendPlainText("> " + line);
        executeCommand(line);
    }
}