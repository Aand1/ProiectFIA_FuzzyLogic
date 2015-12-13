#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void handlerRxSerial();

private:
    Ui::Dialog *ui;

    QSerialPort* serial;

    QString portAvailable;

    QByteArray serialData;

    QString serialBuffer;

    QStringList serialDataList;     // to split data

    //graph variables
    double x, y;

};

#endif // DIALOG_H
