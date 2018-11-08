#pragma once

#include "util/id_generator_base.hpp"
#include "util/has_name_base.hpp"

namespace logic
{
class development_rate
{
  private:
    long total_value;
    double growth;
    double science;
    double industry;
    double military;
    double project;

  public:
    long get_total_value() const;
    void set_total_value(long) const;

    double get_growth_rate() const;
    double get_science_rate() const;
    double get_industry_rate() const;
    double get_military_rate() const;
    double get_project_rate() const;

    void set_growth_rate(double) const;
    void set_science_rate(double) const;
    void set_industry_rate(double) const;
    void set_military_rate(double) const;
    void set_project_rate(double) const;

    long get_total_growth() const;
    long get_total_science() const;
    long get_total_industry() const;
    long get_total_military() const;
    long get_total_project() const;
};

class development
{
  private:
    long growth;
    long science;
    long industry;
    long military;
    long project;

  public:
    long get_growth() const;
    long get_science() const;
    long get_industry() const;
    long get_military() const;
    long get_project() const;

    development operator+(const development_rate &) const;
    development operator-(const development_rate &) const;
    development &operator+=(const development_rate &);
    development &operator-=(const development_rate &);
};

enum class planetary_body_type
{
    AsteroidBelt,
    Planet,
    Plantoid,
    GasGiant,
    Icy,
    Hot,
    Volcanic,
    Water,
    WellTempered,
};

class planetary_body : public has_name_base, public id_generator_base<planetary_body>
{
  private:
    development_rate development_rate;
    development total_development;
    planetary_body_type type;

  public:
    planetary_body();

    const development_rate &get_development_rate() const;
    const development &get_total_development() const;
    planetary_body_type get_type() const;
};

class planetary_system : public has_name_base, public id_generator_base<planetary_system>
{
  private:
    std::vector<planetary_body *> planets;

    public:
    planetary_system();
};
} // namespace logic