#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include "fuzzycontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateHeatPower();

private:
    FuzzyController *controller;
    QSlider *currentTempSlider;
    QSlider *desiredTempSlider;
    QLabel *currentTempLabel;
    QLabel *desiredTempLabel;
    QLabel *heatPowerLabel;
};

#endif // MAINWINDOW_H 