#include "fuzzy_logic.h"
#include <cmath>
#include <algorithm>

FuzzyLogic::FuzzyLogic(QObject *parent) : QObject(parent) {}

// Функції приналежності для температури
double FuzzyLogic::temperatureLow(double value) const {
    if (value <= 15) return 1.0;
    if (value >= 20) return 0.0;
    return (20 - value) / 5.0;
}

double FuzzyLogic::temperatureNormal(double value) const {
    if (value <= 15 || value >= 25) return 0.0;
    if (value >= 17 && value <= 23) return 1.0;
    if (value < 17) return (value - 15) / 2.0;
    return (25 - value) / 2.0;
}

double FuzzyLogic::temperatureHigh(double value) const {
    if (value <= 20) return 0.0;
    if (value >= 25) return 1.0;
    return (value - 20) / 5.0;
}

// Функції приналежності для вологості
double FuzzyLogic::humidityLow(double value) const {
    if (value <= 30) return 1.0;
    if (value >= 40) return 0.0;
    return (40 - value) / 10.0;
}

double FuzzyLogic::humidityNormal(double value) const {
    if (value <= 30 || value >= 60) return 0.0;
    if (value >= 40 && value <= 50) return 1.0;
    if (value < 40) return (value - 30) / 10.0;
    return (60 - value) / 10.0;
}

double FuzzyLogic::humidityHigh(double value) const {
    if (value <= 50) return 0.0;
    if (value >= 60) return 1.0;
    return (value - 50) / 10.0;
}

// Функції приналежності для потужності обігрівача
double FuzzyLogic::heaterPowerLow(double value) const {
    if (value <= 30) return 1.0;
    if (value >= 50) return 0.0;
    return (50 - value) / 20.0;
}

double FuzzyLogic::heaterPowerMedium(double value) const {
    if (value <= 30 || value >= 70) return 0.0;
    if (value >= 40 && value <= 60) return 1.0;
    if (value < 40) return (value - 30) / 10.0;
    return (70 - value) / 10.0;
}

double FuzzyLogic::heaterPowerHigh(double value) const {
    if (value <= 60) return 0.0;
    if (value >= 80) return 1.0;
    return (value - 60) / 20.0;
}

double FuzzyLogic::calculateHeaterPower(double temperature, double humidity) const {
    // Розрахунок ступенів приналежності для вхідних змінних
    double tempLow = temperatureLow(temperature);
    double tempNormal = temperatureNormal(temperature);
    double tempHigh = temperatureHigh(temperature);
    
    double humLow = humidityLow(humidity);
    double humNormal = humidityNormal(humidity);
    double humHigh = humidityHigh(humidity);

    // Правила нечіткої логіки
    double rule1 = std::min(tempLow, humLow);    // Низька температура і низька вологість -> низька потужність
    double rule2 = std::min(tempNormal, humNormal); // Нормальна температура і нормальна вологість -> середня потужність
    double rule3 = std::max(tempHigh, humHigh);  // Висока температура або висока вологість -> висока потужність

    // Дефазифікація методом центру ваги
    double numerator = 0.0;
    double denominator = 0.0;

    // Для низької потужності (центр = 20)
    numerator += rule1 * 20;
    denominator += rule1;

    // Для середньої потужності (центр = 50)
    numerator += rule2 * 50;
    denominator += rule2;

    // Для високої потужності (центр = 80)
    numerator += rule3 * 80;
    denominator += rule3;

    if (denominator == 0.0) return 0.0;
    return numerator / denominator;
} 