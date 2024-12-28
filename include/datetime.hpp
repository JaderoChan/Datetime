// The "Datetime" library, in c++.
//
// Web: https://github.com/JaderoChan/Datetime
// You can contact me by email: c_dl_cn@outlook.com

// MIT License
//
// Copyright (c) 2024 頔珞JaderoChan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <cstdlib>  // atoi()
#include <ctime>    // time_t, tm, time(), localtime_s(), strftime(), mktime(), gmtime_s()
#include <string>   // string, to_string(), atoi()
#include <cassert>  // assert()

/// @brief Datetime namespace.
namespace dt
{

// Just for the intellisense better show "tip about namespace". :)

}

// Type alias.
namespace dt
{

using uchar     = unsigned char;
using uint      = unsigned int;

}

// Enum and constants.
namespace dt
{

enum LocalFlag : uint
{
    LF_NUM,
    LF_NUM_PADDING,
    LF_EN,
    LF_EN_SHORT,
    LF_CN,
    LF_JP,
    LF_KR
};

constexpr uint MINUTE_SECONDS   = 60;
constexpr uint HOUR_SECONDS     = 60 * MINUTE_SECONDS;
constexpr uint DAY_SECONDS      = 24 * HOUR_SECONDS;

constexpr const char* MONTH_STR_EN[] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

constexpr const char* MONTH_STR_EN_SHORT[] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
};

constexpr const char* MONTH_STR_CN[] = {
    "\xE4\xB8\x80\xE6\x9C\x88",
    "\xE4\xBA\x8C\xE6\x9C\x88",
    "\xE4\xB8\x89\xE6\x9C\x88",
    "\xE5\x9B\x9B\xE6\x9C\x88",
    "\xE4\xBA\x94\xE6\x9C\x88",
    "\xE5\x85\xAD\xE6\x9C\x88",
    "\xE4\xB8\x83\xE6\x9C\x88",
    "\xE5\x85\xAB\xE6\x9C\x88",
    "\xE4\xB9\x9D\xE6\x9C\x88",
    "\xE5\x8D\x81\xE6\x9C\x88",
    "\xE5\x8D\x81\xE4\xB8\x80\xE6\x9C\x88",
    "\xE5\x8D\x81\xE4\xBA\x8C\xE6\x9C\x88"
};

constexpr const char* MONTH_STR_JP[] = {
    "\xE3\x81\x84\xE3\x81\xA1\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\xAB\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x95\xE3\x82\x93\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x97\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x94\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x82\x8D\xE3\x81\x8F\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x97\xE3\x81\xA1\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\xAF\xE3\x81\xA1\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x8F\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x98\xE3\x82\x85\xE3\x81\x86\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x98\xE3\x82\x85\xE3\x81\x86\xE3\x81\x84\xE3\x81\xA1\xE3\x81\x8C\xE3\x81\xA4",
    "\xE3\x81\x98\xE3\x82\x85\xE3\x81\x86\xE3\x81\xAB\xE3\x81\x8C\xE3\x81\xA4"
};

constexpr const char* MONTH_STR_KR[] = {
    "\xEC\x9D\xBC\xEC\x9B\x94",
    "\xEC\x9D\xB4\xEC\x9B\x94",
    "\xEC\x82\xBC\xEC\x9B\x94",
    "\xEC\x82\xAC\xEC\x9B\x94",
    "\xEC\x98\xA4\xEC\x9B\x94",
    "\xEC\x9C\xA0\xEC\x9B\x94",
    "\xEC\xB9\xA0\xEC\x9B\x94",
    "\xED\x8C\x94\xEC\x9B\x94",
    "\xEA\xB5\xAC\xEC\x9B\x94",
    "\xEC\x8B\x9C\xEC\x9B\x94",
    "\xEC\x8B\xAD\xEC\x9D\xBC\xEC\x9B\x94",
    "\xEC\x8B\xAD\xEC\x9D\xB4\xEC\x9B\x94"
};

constexpr const char* WEEK_STR_EN[] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

constexpr const char* WEEK_STR_EN_SHORT[] = {
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat"
};

constexpr const char* WEEK_STR_CN[] = {
    "\xE6\x98\x9F\xE6\x9C\x9F\xE6\x97\xA5",
    "\xE6\x98\x9F\xE6\x9C\x9F\xE4\xB8\x80",
    "\xE6\x98\x9F\xE6\x9C\x9F\xE4\xBA\x8C",
    "\xE6\x98\x9F\xE6\x9C\x9F\xE4\xB8\x89",
    "\xE6\x98\x9F\xE6\x9C\x9F\xE5\x9B\x9B",
    "\xE6\x98\x9F\xE6\x9C\x9F\xE4\xBA\x94",
    "\xE6\x98\x9F\xE6\x9C\x9F\xE5\x85\xAD"
};

constexpr const char* WEEK_STR_JP[] = {
    "\xE6\x97\xA5\xE6\x9B\x9C\xE6\x97\xA5",
    "\xE6\x9C\x88\xE6\x9B\x9C\xE6\x97\xA5",
    "\xE7\x81\xAB\xE6\x9B\x9C\xE6\x97\xA5",
    "\xE6\xB0\xB4\xE6\x9B\x9C\xE6\x97\xA5",
    "\xE6\x9C\xA8\xE6\x9B\x9C\xE6\x97\xA5",
    "\xE9\x87\x91\xE6\x9B\x9C\xE6\x97\xA5",
    "\xE5\x9C\x9F\xE6\x9B\x9C\xE6\x97\xA5"
};

constexpr const char* WEEK_STR_KR[] = {
    "\xEC\x9D\xBC\xEC\x9A\x94\xEC\x9D\xBC",
    "\xEC\x9B\x94\xEC\x9A\x94\xEC\x9D\xBC",
    "\xED\x99\x94\xEC\x9A\x94\xEC\x9D\xBC",
    "\xEC\x88\x98\xEC\x9A\x94\xEC\x9D\xBC",
    "\xEB\xAA\xA9\xEC\x9A\x94\xEC\x9D\xBC",
    "\xEA\xB8\x88\xEC\x9A\x94\xEC\x9D\xBC",
    "\xED\x86\xA0\xEC\x9A\x94\xEC\x9D\xBC"
};

} // namespace dt

// Utility functions.
namespace dt
{

inline bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

inline bool isValidMonth(int month)
{
    return month >= 1 && month <= 12;
}

inline bool isLongMonth(int month)
{
    assert(isValidMonth(month));
    return (month <= 7 && month % 2 == 1) || (month >= 8 && month % 2 == 0);
}

inline bool isShortMonth(int month)
{
    assert(isValidMonth(month));
    return (month <= 7 && month % 2 == 0) || (month >= 8 && month % 2 == 1);
}

inline bool isValidDay(int day)
{
    return day >= 1 && day <= 31;
}

inline bool isValidDay(int day, int month)
{
    if (!isValidDay(day) || !isValidMonth(month))
        return false;

    if (month == 2 && day > 29)
        return false;

    if (isShortMonth(month) && day > 30)
        return false;

    return true;
}

inline bool isValidDay(int day, int month, int year)
{
    if (!isValidDay(day, month))
        return false;

    if (!isLeapYear(year) && month == 2 && day > 28)
        return false;

    return true;
}

inline bool isValidHour(int hour)
{
    return hour >= 0 && hour <= 23;
}

inline bool isValidMinute(int minute)
{
    return minute >= 0 && minute <= 59;
}

inline bool isValidSecond(int second)
{
    return second >= 0 && second <= 59;
}

inline bool isValidWeekday(int weekday)
{
    return weekday >= 1 && weekday <= 7;
}

inline bool isValidYearday(int yearday)
{
    return yearday >= 1 && yearday <= 366;
}

inline bool isValidYearday(int yearday, int year)
{
    return (isLeapYear(year) && yearday >= 1 && yearday <= 366) || (yearday >= 1 && yearday <= 365);
}

inline bool isValidUtcOffset(double utcOffset)
{
    return utcOffset >= -12.0 && utcOffset <= 14.0;
}

inline int daysOfYear(int year)
{
    return isLeapYear(year) ? 366 : 365;
}

inline std::time_t currentTime()
{
    std::time_t t;
    return std::time(&t);
}

inline double localUtcOffset()
{
    std::time_t localTime;
    std::time(&localTime);

    std::tm gmtTm;
    ::gmtime_s(&gmtTm, &localTime);

    std::time_t gmtTime = std::mktime(&gmtTm);

    return static_cast<double>(localTime - gmtTime) / HOUR_SECONDS;
}

inline std::string getMonthName(int month, LocalFlag localFlag)
{
    assert(isValidMonth(month));

    switch (localFlag) {
        case LF_EN:
            return MONTH_STR_EN[month - 1];
        case LF_EN_SHORT:
            return MONTH_STR_EN_SHORT[month - 1];
        case LF_CN:
            return MONTH_STR_CN[month - 1];
        case LF_JP:
            return MONTH_STR_JP[month - 1];
        case LF_KR:
            return MONTH_STR_KR[month - 1];
        case LF_NUM:
            return std::to_string(month);
        case LF_NUM_PADDING:
            // Fallthrough.
        default:
            return month < 10 ? '0' + std::to_string(month) : std::to_string(month);
    }
}

inline std::string getWeekName(int week, LocalFlag localFlag)
{
    assert(isValidWeekday(week));

    switch (localFlag) {
        case LF_EN:
            return WEEK_STR_EN[week - 1];
        case LF_EN_SHORT:
            return WEEK_STR_EN_SHORT[week - 1];
        case LF_CN:
            return WEEK_STR_CN[week - 1];
        case LF_JP:
            return WEEK_STR_JP[week - 1];
        case LF_KR:
            return WEEK_STR_KR[week - 1];
        case LF_NUM:
            // Fallthrough.
        case LF_NUM_PADDING:
            // Fallthrough.
        default:
            return std::to_string(week);
    }
}

inline std::string timeToString(std::time_t time,
                                char timeSeparator = ':', char dateSeparator = '-', char separator = ' ')
{
    std::tm lt;
    localtime_s(&lt, &time);

    int y = lt.tm_year + 1900;

    std::string hour = lt.tm_hour < 10 ? '0' + std::to_string(lt.tm_hour) : std::to_string(lt.tm_hour);
    std::string min = lt.tm_min < 10 ? '0' + std::to_string(lt.tm_min) : std::to_string(lt.tm_min);
    std::string sec = lt.tm_sec < 10 ? '0' + std::to_string(lt.tm_sec) : std::to_string(lt.tm_sec);
    std::string year = std::to_string(y);
    std::string mon = lt.tm_mon + 1 < 10 ? '0' + std::to_string(lt.tm_mon + 1) : std::to_string(lt.tm_mon + 1);
    std::string day = lt.tm_mday < 10 ? '0' + std::to_string(lt.tm_mday) : std::to_string(lt.tm_mday);

    if (y < 1)
        year = "0000" + year;
    else if (y < 10)
        year = "000" + year;
    else if (y < 100)
        year = "00" + year;
    else if (y < 1000)
        year = '0' + year;

    return year + dateSeparator + mon + dateSeparator + day + separator +
        hour + timeSeparator + min + timeSeparator + sec;
}

inline std::time_t stringToTime(const std::string& str)
{
    std::tm lt;
    lt.tm_year = std::atoi(str.substr(0, 4).c_str()) - 1900;
    lt.tm_mon = std::atoi(str.substr(5, 2).c_str()) - 1;
    lt.tm_mday = std::atoi(str.substr(8, 2).c_str());
    lt.tm_hour = std::atoi(str.substr(11, 2).c_str());
    lt.tm_min = std::atoi(str.substr(14, 2).c_str());
    lt.tm_sec = std::atoi(str.substr(17, 2).c_str());

    return std::mktime(&lt);
}

inline std::string currentTimeString(char timeSeparator = ':', char dateSeparator = '-', char separator = ' ')
{
    return timeToString(currentTime(), timeSeparator, dateSeparator, separator);
}

} // namespace dt

// Classes.
namespace dt
{

class DateTime
{
public:
    DateTime() = default;

    DateTime(std::time_t time)
    {
        std::tm lt;
        ::localtime_s(&lt, &time);

        year_ = lt.tm_year + 1900;
        month_ = lt.tm_mon + 1;
        day_ = lt.tm_mday;
        hour_ = lt.tm_hour;
        min_ = lt.tm_min;
        sec_ = lt.tm_sec;
        weekday_ = lt.tm_wday + 1;
        yearday_ = lt.tm_yday + 1;
    }

    static DateTime fromCurrentTime() { return DateTime(currentTime()); }

    static DateTime fromString(const std::string& str) { return DateTime(stringToTime(str)); }

    std::string toString(char timeSeparator = ':', char dateSeparator = '-', char separator = ' ') const
    {
        std::string hour = hour_ < 10 ? '0' + std::to_string(hour_) : std::to_string(hour_);
        std::string min = min_ < 10 ? '0' + std::to_string(min_) : std::to_string(min_);
        std::string sec = sec_ < 10 ? '0' + std::to_string(sec_) : std::to_string(sec_);
        std::string year = std::to_string(year_);
        std::string mon = month_ < 10 ? '0' + std::to_string(month_) : std::to_string(month_);
        std::string day = day_ < 10 ? '0' + std::to_string(day_) : std::to_string(day_);

        if (year_ < 1)
            year = "0000" + year;
        else if (year_ < 10)
            year = "000" + year;
        else if (year_ < 100)
            year = "00" + year;
        else if (year_ < 1000)
            year = '0' + year;

        return year + dateSeparator + mon + dateSeparator + day + separator +
            hour + timeSeparator + min + timeSeparator + sec;
    }

    std::string weekName(LocalFlag localFlag) const { return getWeekName(weekday_, localFlag); }

    std::string monthName(LocalFlag localFlag) const { return getMonthName(month_, localFlag); }

    std::time_t time() const
    {
        std::tm lt;
        lt.tm_year = year_ - 1900;
        lt.tm_mon = month_ - 1;
        lt.tm_mday = day_;
        lt.tm_hour = hour_;
        lt.tm_min = min_;
        lt.tm_sec = sec_;

        return std::mktime(&lt);
    }

    int year() const { return year_; }

    uchar month() const { return month_; }

    uchar day() const { return day_; }

    uchar hour() const { return hour_; }

    uchar minute() const { return min_; }

    uchar second() const { return sec_; }

    uchar weekday() const { return weekday_; }

    uchar yearday() const { return yearday_; }

private:
    int year_;
    uchar month_;
    uchar day_;
    uchar hour_;
    uchar min_;
    uchar sec_;
    uchar weekday_;
    uchar yearday_;
};

struct TimeRange
{
    TimeRange() = default;

    TimeRange(std::time_t start, std::time_t end) : start(start), end(end) {}

    TimeRange(const std::string& start, const std::string& end) : start(stringToTime(start)), end(stringToTime(end)) {}

    bool isValid() const { return start != -1 && end != -1 && start <= end; }

    bool contains(std::time_t time) const { return start <= time && time <= end; }

    bool contains(const std::string& str) const { return contains(stringToTime(str)); }

    std::time_t start   = -1;
    std::time_t end     = -1;
};

constexpr TimeRange ALL_TIME = TimeRange();

} // namespace dt

#endif // !DATETIME_HPP
