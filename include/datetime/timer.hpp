#pragma once

#include <ctime>
#include <vector>
#include "defs.hpp"

namespace util
{
// Berechnet den Bias einer Wahrscheinlichtkeit p. Der Bias ist als |0.5-p|*2 definiert.
math_t calc_bias(math_t p);

// Eine einfache Klasse zum Messen der Prozessor-Zeit.
class timer
{
  public:
    // Normaler Konstruktor.
    timer();

    // Copy-Konstruktor, die neue Instanz hat denselben Zustand wie copy.
    timer(const timer &copy);

    // Beginnt die Zeitmessung.
    void start();

    // Beendet die Zeitmessung.
    void stop();

    // Gibt die clocks zurück, die zwischen dem Aufruf von start() und stop() vergangen sind.
    clock_t elapsed() const;

  private:
    clock_t m_start;
    clock_t m_end;
};

// Eine einfache Klasse zum Messen von Rundenzeiten.
class round_timer
{
  public:
    // Normaler Konstruktor.
    round_timer();

    // Copy Konstruktor, die neue Instanz hat denselben Zustand wie copy.
    round_timer(const round_timer &copy);

    // Startet die Zeitmessung.
    void start();

    // Erstellt eine Rundenzeit.
    void round();

    // Gibt die Zahl der gestoppten Runden zurück.
    size_t round_count() const;

    // Gibt an, wie viele clocks zwischen dem Aufruf von start() und dem letzten Aufruf von round() vergangen
    // sind.
    clock_t elapsed() const;

    // Gibt die durchschnittlichen clocks pro Runde zurück.
    clock_t average() const;

    // Gibt an, wie viele clocks eine bestimmten Runde gedauert hat.
    clock_t elapsed(size_t round) const;

  private:
    clock_t m_start;
    std::vector<clock_t> m_rounds;
};

// Rechnet clocks in Millitsekunden um.
double clocks_to_ms(double clocks);

// Rechnet clocks in Sekunden um.
double clocks_to_seconds(double clocks);
} // namespace util
