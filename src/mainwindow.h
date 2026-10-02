#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vfs.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& vfsPath,const QString& startupScriptPath, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    std::unique_ptr<VFS> vfs;
    Ui::MainWindow *ui;
    QString vfsPath;
    QString startupScriptPath;
    void handleCommand();
    void executeCommand(const QString &command);
    void runStartupScript();
};
#endif // MAINWINDOW_H
