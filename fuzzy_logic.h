#ifndef FUZZY_LOGIC_H
#define FUZZY_LOGIC_H

#include <QObject>
#include <QVector>

class FuzzyLogic : public QObject {
    Q_OBJECT

public:
    explicit FuzzyLogic(QObject *parent = nullptr);

    // Функції приналежності для температури
    double temperatureLow(double value) const;
    double temperatureNormal(double value) const;
    double temperatureHigh(double value) const;

    // Функції приналежності для вологості
    double humidityLow(double value) const;
    double humidityNormal(double value) const;
    double humidityHigh(double value) const;

    // Функції приналежності для потужності обігрівача
    double heaterPowerLow(double value) const;
    double heaterPowerMedium(double value) const;
    double heaterPowerHigh(double value) const;

    // Розрахунок рекомендованої потужності
    double calculateHeaterPower(double temperature, double humidity) const;

private:
    // Діапазони значень
    static constexpr double TEMP_MIN = 10.0;
    static constexpr double TEMP_MAX = 30.0;
    static constexpr double HUM_MIN = 20.0;
    static constexpr double HUM_MAX = 80.0;
    static constexpr double POWER_MIN = 0.0;
    static constexpr double POWER_MAX = 100.0;
};

#endif // FUZZY_LOGIC_H 