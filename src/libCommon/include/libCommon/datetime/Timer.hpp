#pragma once

#include <ctime>
#include <vector>
#include "libCommon/Defs.hpp"

namespace util
{
// Eine einfache Klasse zum Messen der Prozessor-Zeit.
class Timer
{
  public:
    // Normaler Konstruktor.
    Timer();

    // Copy-Konstruktor, die neue Instanz hat denselben Zustand wie copy.
    Timer(const Timer &copy);

    // Beginnt die Zeitmessung.
    void Start();

    // Beendet die Zeitmessung.
    void Stop();

    // Gibt die clocks zurück, die zwischen dem Aufruf von Start() und Stop() vergangen sind.
    clock_t Elapsed() const;

  private:
    clock_t start;
    clock_t end;
};

// Eine einfache Klasse zum Messen von Rundenzeiten.
class RoundTimer
{
  public:
    // Normaler Konstruktor.
    RoundTimer();

    // Copy Konstruktor, die neue Instanz hat denselben Zustand wie copy.
    RoundTimer(const RoundTimer &copy);

    // Startet die Zeitmessung.
    void Start();

    // Erstellt eine Rundenzeit.
    void Round();

    // Gibt die Zahl der gestoppten Runden zurück.
    size_t RoundCount() const;

    // Gibt an, wie viele clocks zwischen dem Aufruf von Start() und dem letzten Aufruf von Round() vergangen
    // sind.
    clock_t Elapsed() const;

    // Gibt an, wie viele clocks eine bestimmten Runde gedauert hat.
    clock_t Elapsed(size_t Round) const;

    // Gibt die durchschnittlichen clocks pro Runde zurück.
    clock_t Average() const;

  private:
    clock_t start;
    std::vector<clock_t> rounds;
};
} // namespace util
