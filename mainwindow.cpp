#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , fuzzyLogic(new FuzzyLogic(this))
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Температура
    QHBoxLayout *tempLayout = new QHBoxLayout();
    QLabel *tempLabel = new QLabel("Температура (°C):", this);
    tempInput = new QLineEdit(this);
    tempLayout->addWidget(tempLabel);
    tempLayout->addWidget(tempInput);
    mainLayout->addLayout(tempLayout);

    // Вологість
    QHBoxLayout *humLayout = new QHBoxLayout();
    QLabel *humLabel = new QLabel("Вологість (%):", this);
    humInput = new QLineEdit(this);
    humLayout->addWidget(humLabel);
    humLayout->addWidget(humInput);
    mainLayout->addLayout(humLayout);

    // Кнопка розрахунку
    QPushButton *calculateButton = new QPushButton("Розрахувати потужність", this);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculatePower);
    mainLayout->addWidget(calculateButton);

    // Результат
    resultLabel = new QLabel("Рекомендована потужність: --%", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(resultLabel);

    setWindowTitle("Керування обігрівачем з нечіткою логікою");
    resize(400, 200);
}

MainWindow::~MainWindow() {}

void MainWindow::calculatePower() {
    bool tempOk, humOk;
    double temperature = tempInput->text().toDouble(&tempOk);
    double humidity = humInput->text().toDouble(&humOk);

    if (!tempOk || !humOk) {
        QMessageBox::warning(this, "Помилка", "Будь ласка, введіть коректні числові значення.");
        return;
    }

    double power = fuzzyLogic->calculateHeaterPower(temperature, humidity);
    resultLabel->setText(QString("Рекомендована потужність: %1%").arg(power, 0, 'f', 1));
} 