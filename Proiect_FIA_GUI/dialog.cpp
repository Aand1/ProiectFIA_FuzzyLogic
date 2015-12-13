#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

   // QWidget::showMaximized();

    // get info about serial ports
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        portAvailable = info.portName();
    }

    // init serial port
    serial = new QSerialPort(this);

    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setPortName("ttyACM0");
    serial->open(QSerialPort::ReadOnly);
    if(serial->isOpen())
    {
        qDebug() << "serial is open" << " on port: " << serial->portName();
    }
    else
    {
        qDebug() << "serial is NOT open";
    }

    connect(serial,SIGNAL(readyRead()), this, SLOT(handlerRxSerial()));

    // init graph

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(2);
    ui->customPlot->axisRect()->setupFullAxesBox();

    ui->customPlot->yAxis->setRange(0.1, 0.9);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::handlerRxSerial()
{
    serialDataList = serialBuffer.split("\n");

    if(serialDataList.length() < 2) // if I need 1 value (for 2 values --> serialDataList.lenght() < 3 )
    {
        serialData = serial->readAll();     // keep reading

        serialBuffer += QString::fromStdString(serialData.toStdString());
    }
    else        // data is good for processing
    {
        qDebug() << serialDataList[0];

        QString buffer = serialDataList[0];

        ui->textEdit->append(buffer);

        y = buffer.toDouble();

        x = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

        ui->customPlot->graph(0)->addData(x, y);

        // make key axis range scroll with the data (at a constant range size of 8):
        ui->customPlot->xAxis->setRange(x+0.25, 8, Qt::AlignRight);
        ui->customPlot->replot();

        serialBuffer = "";
    }



    ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());

}
