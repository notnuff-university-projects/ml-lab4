#include "fuzzycontroller.h"
#include <cmath>
#include <algorithm>

FuzzyController::FuzzyController(QObject *parent)
    : QObject(parent), currentTemp(20.0), desiredTemp(22.0)
{
}

void FuzzyController::setCurrentTemperature(double temp)
{
    currentTemp = std::clamp(temp, 0.0, 40.0);
}

void FuzzyController::setDesiredTemperature(double temp)
{
    desiredTemp = std::clamp(temp, 15.0, 30.0);
}

// Функції приналежності для поточної температури
double FuzzyController::membershipCold(double x) const
{
    if (x <= 10) return 1.0;
    if (x >= 20) return 0.0;
    return (20 - x) / 10.0;
}

double FuzzyController::membershipComfortable(double x) const
{
    if (x <= 10 || x >= 30) return 0.0;
    if (x >= 15 && x <= 25) return 1.0;
    if (x < 15) return (x - 10) / 5.0;
    return (30 - x) / 5.0;
}

double FuzzyController::membershipHot(double x) const
{
    if (x <= 20) return 0.0;
    if (x >= 30) return 1.0;
    return (x - 20) / 10.0;
}

// Функції приналежності для бажаної температури
double FuzzyController::membershipLowDesired(double x) const
{
    if (x <= 15) return 1.0;
    if (x >= 20) return 0.0;
    return (20 - x) / 5.0;
}

double FuzzyController::membershipMediumDesired(double x) const
{
    if (x <= 15 || x >= 25) return 0.0;
    if (x >= 20 && x <= 22) return 1.0;
    if (x < 20) return (x - 15) / 5.0;
    return (25 - x) / 3.0;
}

double FuzzyController::membershipHighDesired(double x) const
{
    if (x <= 20) return 0.0;
    if (x >= 25) return 1.0;
    return (x - 20) / 5.0;
}

FuzzyController::TemperatureState FuzzyController::fuzzifyCurrentTemperature() const
{
    double cold = membershipCold(currentTemp);
    double comfortable = membershipComfortable(currentTemp);
    double hot = membershipHot(currentTemp);

    if (cold >= comfortable && cold >= hot) return TemperatureState::COLD;
    if (comfortable >= cold && comfortable >= hot) return TemperatureState::COMFORTABLE;
    return TemperatureState::HOT;
}

FuzzyController::DesiredTemperature FuzzyController::fuzzifyDesiredTemperature() const
{
    double low = membershipLowDesired(desiredTemp);
    double medium = membershipMediumDesired(desiredTemp);
    double high = membershipHighDesired(desiredTemp);

    if (low >= medium && low >= high) return DesiredTemperature::LOW;
    if (medium >= low && medium >= high) return DesiredTemperature::MEDIUM;
    return DesiredTemperature::HIGH;
}

FuzzyController::TemperatureDifference FuzzyController::calculateTemperatureDifference() const
{
    double diff = currentTemp - desiredTemp;
    if (diff < -2) return TemperatureDifference::NEGATIVE;
    if (diff > 2) return TemperatureDifference::POSITIVE;
    return TemperatureDifference::ZERO;
}

FuzzyController::HeatPower FuzzyController::applyRules(TemperatureState current, DesiredTemperature desired) const
{
    // Правила нечіткої логіки
    if (current == TemperatureState::HOT) return HeatPower::OFF;
    
    if (current == TemperatureState::COLD && desired == DesiredTemperature::HIGH)
        return HeatPower::HIGH;
    
    if (current == TemperatureState::COMFORTABLE && desired == DesiredTemperature::MEDIUM)
        return HeatPower::LOW;
    
    if (current == TemperatureState::COLD)
        return HeatPower::MEDIUM;
    
    return HeatPower::LOW;
}

double FuzzyController::getHeatPower() const
{
    TemperatureState currentState = fuzzifyCurrentTemperature();
    DesiredTemperature desiredState = fuzzifyDesiredTemperature();
    HeatPower power = applyRules(currentState, desiredState);
    
    // Дефазифікація
    switch (power) {
        case HeatPower::OFF: return 0.0;
        case HeatPower::LOW: return 25.0;
        case HeatPower::MEDIUM: return 50.0;
        case HeatPower::HIGH: return 100.0;
    }
    return 0.0;
} 