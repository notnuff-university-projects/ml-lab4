#ifndef FUZZYCONTROLLER_H
#define FUZZYCONTROLLER_H

#include <QObject>
#include <vector>
#include <map>

class FuzzyController : public QObject
{
    Q_OBJECT

public:
    explicit FuzzyController(QObject *parent = nullptr);

    // Вхідні змінні
    enum class TemperatureState { COLD, COMFORTABLE, HOT };
    enum class DesiredTemperature { LOW, MEDIUM, HIGH };
    enum class TemperatureDifference { NEGATIVE, ZERO, POSITIVE };
    enum class HeatPower { OFF, LOW, MEDIUM, HIGH };

    // Методи для встановлення вхідних значень
    void setCurrentTemperature(double temp);
    void setDesiredTemperature(double temp);

    // Метод для отримання результату
    double getHeatPower() const;

private:
    // Поточні значення
    double currentTemp;
    double desiredTemp;

    // Функції приналежності
    double membershipCold(double x) const;
    double membershipComfortable(double x) const;
    double membershipHot(double x) const;
    double membershipLowDesired(double x) const;
    double membershipMediumDesired(double x) const;
    double membershipHighDesired(double x) const;

    // Методи для обчислення нечіткої логіки
    TemperatureState fuzzifyCurrentTemperature() const;
    DesiredTemperature fuzzifyDesiredTemperature() const;
    TemperatureDifference calculateTemperatureDifference() const;
    HeatPower applyRules(TemperatureState current, DesiredTemperature desired) const;
    double defuzzify(HeatPower power) const;
};

#endif // FUZZYCONTROLLER_H 