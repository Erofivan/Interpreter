#ifndef _ITMOSCRIPT_LIB_REAL_NUMBER_HPP_
#define _ITMOSCRIPT_LIB_REAL_NUMBER_HPP_

#include <cmath>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>

class RealNumber {
public:
    RealNumber() : num_("0"), den_("1"), negative_(false) {}
    RealNumber(long long x);
    RealNumber(const std::string &s);

    template <typename T>
    T convert_to() const {
        if constexpr(std::is_same_v<T, std::string>) {
            std::string s;
            if (negative_ && num_ != "0") s.push_back('-');
            std::string q, r;
            DivmodBig(num_, den_, q, r);
            if (q.empty()) q = "0";
            s += q;
            if (r != "0") {
                s.push_back('.');
                std::string dcopy = den_;
                while (true) {
                    std::string tmpq, tmpr;
                    DivmodBig(dcopy, "2", tmpq, tmpr);
                    if (tmpr == "0") dcopy = tmpq;
                    else break;
                }
                while (true) {
                    std::string tmpq, tmpr;
                    DivmodBig(dcopy, "5", tmpq, tmpr);
                    if (tmpr == "0") dcopy = tmpq;
                    else break;
                }
                bool isFinite = (dcopy == "1");
                std::unordered_map<std::string, size_t> remPos;
                std::vector<char> digits;
                const size_t MAX_IRR_DIGITS = 15;
                bool isPeriodic = false;
                size_t cycleStart = 0;
                size_t pos = 0;
                std::string rem = r;
                while (rem != "0") {
                    if (!isFinite) {
                        auto it = remPos.find(rem);
                        if (it != remPos.end()) {
                            isPeriodic = true;
                            cycleStart = it->second;
                            break;
                        }
                        remPos[rem] = pos++;
                    }
                    if (!isFinite && !isPeriodic && digits.size() >= MAX_IRR_DIGITS) {
                        break;
                    }
                    rem.push_back('0');
                    std::string dq, dr;
                    DivmodBig(rem, den_, dq, dr);
                    digits.push_back(dq.empty() ? '0' : dq.front());
                    rem = dr;
                }
                if (rem == "0") {
                    for (char c : digits) s.push_back(c);
                } else if (isPeriodic) {
                    for (size_t i = 0; i < cycleStart; ++i) s.push_back(digits[i]);
                    s.push_back('(');
                    for (size_t i = cycleStart; i < digits.size(); ++i) s.push_back(digits[i]);
                    s.push_back(')');
                } else {
                    for (char c : digits) s.push_back(c);
                }
            }
            return s;
        } else if constexpr(std::is_integral_v<T>) {
            std::string q, r;
            DivmodBig(num_, den_, q, r);
            if (q.empty()) q = "0";
            long long val = std::stoll(q);
            return static_cast<T>(negative_ ? -val : val);
        } else {
            static_assert(!sizeof(T), "unsupported convert_to");
        }
    }

    RealNumber& operator+=(const RealNumber &o);
    RealNumber& operator-=(const RealNumber &o);
    RealNumber& operator*=(const RealNumber &o);
    RealNumber& operator/=(const RealNumber &o);
    RealNumber& operator%=(const RealNumber &o);
    RealNumber& operator^=(const RealNumber &o);

    RealNumber operator-() const;

    RealNumber& operator++();
    RealNumber operator++(int);
    RealNumber& operator--();
    RealNumber operator--(int);

    bool operator==(const RealNumber &o) const;
    bool operator!=(const RealNumber &o) const;
    bool operator<(const RealNumber &o) const;
    bool operator>(const RealNumber &o) const;
    bool operator<=(const RealNumber &o) const;
    bool operator>=(const RealNumber &o) const;

    std::string toString() const;

    RealNumber abs() const;
    RealNumber ceil() const;
    RealNumber floor() const;
    RealNumber round() const;
    RealNumber sqrt() const;

    explicit operator long long() const;

private:
    friend RealNumber operator+(RealNumber a, const RealNumber &b);
    friend RealNumber operator-(RealNumber a, const RealNumber &b);
    friend RealNumber operator*(RealNumber a, const RealNumber &b);
    friend RealNumber operator/(RealNumber a, const RealNumber &b);
    friend RealNumber operator^(RealNumber base, const RealNumber &exponent);
    friend RealNumber operator%(const RealNumber &a, const RealNumber &b);
    friend std::ostream& operator<<(std::ostream& os, const RealNumber& v);

    static std::string Normalize(const std::string &s);
    static bool LessThanBig(const std::string &a, const std::string &b);
    static std::string AddBig(const std::string &a, const std::string &b);
    static std::string SubBig(const std::string &a, const std::string &b);
    static std::string MulBig(const std::string &a, const std::string &b);
    static void DivmodBig(const std::string &a, const std::string &b,
                          std::string &q, std::string &r);
    static std::string GcdBig(std::string a, std::string b);
    void Reduce();

    std::string num_;
    std::string den_;
    bool negative_;
};

#endif