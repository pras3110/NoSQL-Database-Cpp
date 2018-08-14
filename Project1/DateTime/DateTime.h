#pragma once
/////////////////////////////////////////////////////////////////////
// DbCore.h - Implements NoSql database prototype                  //
// ver 1.0                                                         //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018   //
// Source : Jim Fawcett                                            //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * The DateTime class represents clock time, and supports:
 * - creating default instances and instances from specific time points
 * - return times as formatted strings
 * - building time points and durations from years, months, days, hours, ...
 * - performing addition and subtraction of times
 * - comparing times
 * - extracting counts of years, months, days, hours, minutes, and seconds
 *
 * Required Files:
 * ---------------
 *   DateTime.h, DateTime.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.1 : 6 Feb 2017

    Added <= operator to compare Datetime
*/

#include <chrono>
#include <ctime>
#include <string>

class DateTime
{
public:
  using SysClock = std::chrono::system_clock;
  using TimePoint = std::chrono::system_clock::time_point;
  using Duration = std::chrono::system_clock::duration;

  DateTime();
  DateTime(std::string dtStr);
  DateTime(const TimePoint& tp);
  operator std::string();

  std::string now();
  TimePoint timepoint();
  size_t ticks();
  std::string time();
  static TimePoint makeTime(
    size_t yrs, size_t mon, size_t day, 
    size_t hrs = 0, size_t min = 0, size_t sec = 0
  );
  static Duration makeDuration(
    size_t hrs, size_t min, size_t sec = 0, size_t millisec = 0
  );

  DateTime operator+=(const Duration& dt);
  DateTime operator+(const Duration& dt);
  DateTime operator-=(const Duration& dt);
  DateTime operator-(const Duration& dt);
  bool operator<(const DateTime& dt);
  bool operator>(const DateTime& dt);
  bool operator<=(const DateTime& dt);

  size_t year();
  size_t month();
  size_t day();
  size_t hour();
  size_t minute();
  size_t second();
private:
  char* ctime(const std::time_t* pTime);
  std::tm* localtime(const time_t* pTime);
  TimePoint tp_;
};