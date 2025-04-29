#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "fuzzy_logic.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculatePower();

private:
    QLineEdit *tempInput;
    QLineEdit *humInput;
    QLabel *resultLabel;
    FuzzyLogic *fuzzyLogic;
};

#endif // MAINWINDOW_H 