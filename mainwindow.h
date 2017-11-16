#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QCamera;
class QLineEdit;
class QVideoWidget;
class QCameraImageCapture;
class QVideoFrame;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QCamera *camera;

    QLineEdit *output;
    QVideoWidget *viewer;
    QCameraImageCapture *imageCapture;
private slots:
    void decode(int id, QImage image);
    void check();
};

#endif // MAINWINDOW_H
