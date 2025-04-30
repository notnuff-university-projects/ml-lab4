#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    controller = new FuzzyController(this);

    // Створення центрального віджета
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Створення слайдерів та міток
    currentTempSlider = new QSlider(Qt::Horizontal);
    currentTempSlider->setRange(0, 40);
    currentTempSlider->setValue(20);

    desiredTempSlider = new QSlider(Qt::Horizontal);
    desiredTempSlider->setRange(15, 30);
    desiredTempSlider->setValue(22);

    currentTempLabel = new QLabel("Поточна температура: 20°C");
    desiredTempLabel = new QLabel("Бажана температура: 22°C");
    heatPowerLabel = new QLabel("Потужність нагріву: 0%");

    // Розміщення елементів
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    QHBoxLayout *currentTempLayout = new QHBoxLayout();
    currentTempLayout->addWidget(new QLabel("Поточна температура:"));
    currentTempLayout->addWidget(currentTempSlider);
    currentTempLayout->addWidget(currentTempLabel);
    
    QHBoxLayout *desiredTempLayout = new QHBoxLayout();
    desiredTempLayout->addWidget(new QLabel("Бажана температура:"));
    desiredTempLayout->addWidget(desiredTempSlider);
    desiredTempLayout->addWidget(desiredTempLabel);
    
    mainLayout->addLayout(currentTempLayout);
    mainLayout->addLayout(desiredTempLayout);
    mainLayout->addWidget(heatPowerLabel);

    // Підключення сигналів
    connect(currentTempSlider, &QSlider::valueChanged, this, [this](int value) {
        controller->setCurrentTemperature(value);
        currentTempLabel->setText(QString("Поточна температура: %1°C").arg(value));
        updateHeatPower();
    });

    connect(desiredTempSlider, &QSlider::valueChanged, this, [this](int value) {
        controller->setDesiredTemperature(value);
        desiredTempLabel->setText(QString("Бажана температура: %1°C").arg(value));
        updateHeatPower();
    });

    // Встановлення початкових значень
    updateHeatPower();
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateHeatPower()
{
    double power = controller->getHeatPower();
    heatPowerLabel->setText(QString("Потужність нагріву: %1%").arg(power, 0, 'f', 1));
} 