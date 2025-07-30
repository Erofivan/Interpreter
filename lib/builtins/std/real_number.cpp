#include "real_number.hpp"

RealNumber::RealNumber(long long x) {
    if (x < 0) {
        negative_ = true;
        x = -x;
    } else {
        negative_ = false;
    }
    num_ = std::to_string(x);
    den_ = "1";
}

RealNumber::RealNumber(const std::string &s) {
    std::string str = s;
    negative_ = false;
    if (!str.empty() && str[0] == '-') {
        negative_ = true;
        str.erase(str.begin());
    }
    size_t epos = str.find_first_of("eE");
    int expo = 0;
    if (epos != std::string::npos) {
        expo = std::stoi(str.substr(epos + 1));
        str = str.substr(0, epos);
    }
    size_t dot = str.find('.');
    if (dot == std::string::npos) {
        num_ = Normalize(str);
        den_ = "1";
    } else {
        std::string intpart = str.substr(0, dot);
        std::string frac = str.substr(dot + 1);
        num_ = Normalize(intpart + frac);
        den_ = "1" + std::string(frac.size(), '0');
    }
    if (num_.empty()) num_ = "0";
    if (expo > 0) {
        num_ += std::string(expo, '0');
    } else if (expo < 0) {
        den_ += std::string(-expo, '0');
    }
    if (den_.empty()) den_ = "1";
    num_ = Normalize(num_);
    den_ = Normalize(den_);
    Reduce();
}

RealNumber& RealNumber::operator+=(const RealNumber &o) {
    std::string a = num_, b = den_, c = o.num_, d = o.den_;
    bool sa = negative_, sb = o.negative_;
    std::string ad = MulBig(a, d);
    std::string bc = MulBig(c, b);
    if (sa == sb) {
        num_ = AddBig(ad, bc);
        negative_ = sa;
    } else {
        if (ad == bc) {
            num_ = "0";
            negative_ = false;
            den_ = "1";
            return *this;
        }
        if (LessThanBig(bc, ad)) {
            num_ = SubBig(ad, bc);
            negative_ = sa;
        } else {
            num_ = SubBig(bc, ad);
            negative_ = sb;
        }
    }
    den_ = MulBig(b, d);
    num_ = Normalize(num_);
    den_ = Normalize(den_);
    Reduce();
    return *this;
}

RealNumber& RealNumber::operator-=(const RealNumber &o) {
    RealNumber tmp = o;
    tmp.negative_ = !o.negative_;
    return *this += tmp;
}

RealNumber& RealNumber::operator*=(const RealNumber &o) {
    num_ = MulBig(num_, o.num_);
    den_ = MulBig(den_, o.den_);
    negative_ = (negative_ != o.negative_);
    num_ = Normalize(num_);
    den_ = Normalize(den_);
    Reduce();
    return *this;
}

RealNumber& RealNumber::operator/=(const RealNumber &o) {
    if (o.num_ == "0") throw std::runtime_error("division by zero");
    RealNumber inv = o;
    std::swap(inv.num_, inv.den_);
    *this *= inv;
    negative_ = (negative_ != o.negative_);
    return *this;
}

RealNumber& RealNumber::operator%=(const RealNumber &o) {
    *this = *this % o;
    return *this;
}

RealNumber& RealNumber::operator^=(const RealNumber &o) {
    if (o.den_ == "1") {
        long long exp = 0;
        if (o.num_.size() <= 18) {
            exp = std::stoll(o.num_);
            if (o.negative_) exp = -exp;
        } else {
            throw std::runtime_error("exponent too large");
        }
        if (exp == 0) {
            *this = RealNumber(1);
            return *this;
        }
        RealNumber base = *this;
        if (exp < 0) {
            base = RealNumber(1) / base;
            exp = -exp;
        }
        *this = RealNumber(1);
        while (exp > 0) {
            if (exp & 1) {
                *this = *this * base;
            }
            base = base * base;
            exp >>= 1;
        }
        return *this;
    } else {
        long double x = std::stold(this->convert_to<std::string>());
        long double y = std::stold(o.convert_to<std::string>());
        long double p = powl(x, y);
        if (std::isnan(p) || std::isinf(p)) {
            throw std::runtime_error("invalid power operation");
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(10) << p;
        std::string s = oss.str();
        while (!s.empty() && s.back() == '0') {
            s.pop_back();
        }
        if (!s.empty() && s.back() == '.') {
            s.pop_back();
        }
        *this = RealNumber(s);
        return *this;
    }
}

RealNumber RealNumber::operator-() const {
    RealNumber result = *this;
    result.negative_ = !result.negative_;
    return result;
}

RealNumber& RealNumber::operator++() {
    *this = *this + RealNumber("1");
    return *this;
}

RealNumber RealNumber::operator++(int) {
    RealNumber tmp = *this;
    ++(*this);
    return tmp;
}

RealNumber& RealNumber::operator--() {
    *this = *this - RealNumber("1");
    return *this;
}

RealNumber RealNumber::operator--(int) {
    RealNumber tmp = *this;
    --(*this);
    return tmp;
}

bool RealNumber::operator==(const RealNumber &o) const {
    return negative_ == o.negative_ && num_ == o.num_ && den_ == o.den_;
}

bool RealNumber::operator!=(const RealNumber &o) const {
    return !(*this == o);
}

bool RealNumber::operator<(const RealNumber &o) const {
    if (negative_ != o.negative_) return negative_;
    std::string ad = MulBig(num_, o.den_);
    std::string bc = MulBig(o.num_, den_);
    if (negative_) {
        return LessThanBig(bc, ad);
    } else {
        return LessThanBig(ad, bc);
    }
}

bool RealNumber::operator>(const RealNumber &o) const {
    return o < *this;
}

bool RealNumber::operator<=(const RealNumber &o) const {
    return !(*this > o);
}

bool RealNumber::operator>=(const RealNumber &o) const {
    return !(*this < o);
}

std::string RealNumber::toString() const {
    return convert_to<std::string>();
}

RealNumber operator+(RealNumber a, const RealNumber &b) {
    a += b;
    return a;
}

RealNumber operator-(RealNumber a, const RealNumber &b) {
    a -= b;
    return a;
}

RealNumber operator*(RealNumber a, const RealNumber &b) {
    a *= b;
    return a;
}

RealNumber operator/(RealNumber a, const RealNumber &b) {
    a /= b;
    return a;
}

RealNumber operator%(const RealNumber &a, const RealNumber &b) {
    if (b.num_ == "0") throw std::runtime_error("division by zero");
    std::string A = RealNumber::MulBig(a.num_, b.den_);
    std::string B = RealNumber::MulBig(b.num_, a.den_);
    std::string qStr, rStr;
    RealNumber::DivmodBig(A, B, qStr, rStr);
    if (qStr.empty()) qStr = "0";
    RealNumber q(qStr);
    q.negative_ = (a.negative_ != b.negative_) && (qStr != "0");
    RealNumber res = a - b * q;
    res.Reduce();
    return res;
}

RealNumber operator^(RealNumber base, const RealNumber &exponent) {
    base ^= exponent;
    return base;
}

RealNumber RealNumber::abs() const {
    RealNumber result = *this;
    result.negative_ = false;
    return result;
}

RealNumber RealNumber::ceil() const {
    RealNumber negated = *this;
    negated.negative_ = !negative_;
    return -(negated.floor());
}

RealNumber RealNumber::floor() const {
    std::string q, r;
    DivmodBig(num_, den_, q, r);
    if (!negative_) {
        return RealNumber(q);
    } else {
        if (r == "0") {
            RealNumber res(q);
            res.negative_ = true;
            return res;
        } else {
            RealNumber qPlusOne = RealNumber(q) + RealNumber(1);
            qPlusOne.negative_ = true;
            return qPlusOne;
        }
    }
}

RealNumber RealNumber::round() const {
    RealNumber absVal = this->abs();
    absVal += RealNumber("0.5");
    RealNumber floored = absVal.floor();
    if (negative_) floored.negative_ = true;
    return floored;
}

RealNumber RealNumber::sqrt() const {
    if (negative_) throw std::runtime_error("sqrt of negative number");
    long double x = std::stold(this->convert_to<std::string>());
    long double s = std::sqrt(x);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(10) << s;
    std::string s_str = oss.str();
    while (!s_str.empty() && s_str.back() == '0') s_str.pop_back();
    if (!s_str.empty() && s_str.back() == '.') s_str.pop_back();
    return RealNumber(s_str);
}

RealNumber::operator long long() const {
    try {
        return (*this).convert_to<long long>();
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("RealNumber to long long conversion error: ") + e.what());
    }
}

std::ostream& operator<<(std::ostream& os, const RealNumber& v) {
    return os << v.toString();
}

std::string RealNumber::Normalize(const std::string &s) {
    size_t p = 0;
    while (p < s.size() && s[p] == '0') p++;
    if (p == s.size()) return "0";
    return s.substr(p);
}

bool RealNumber::LessThanBig(const std::string &a, const std::string &b) {
    if (a.size() != b.size())
        return a.size() < b.size();
    return a < b;
}

std::string RealNumber::AddBig(const std::string &a, const std::string &b) {
    std::string A = a, B = b;
    if (A.size() < B.size()) A.insert(A.begin(), B.size() - A.size(), '0');
    if (B.size() < A.size()) B.insert(B.begin(), A.size() - B.size(), '0');
    int carry = 0;
    std::string C(A.size(), '0');
    for (int i = A.size() - 1; i >= 0; --i) {
        int sum = (A[i] - '0') + (B[i] - '0') + carry;
        carry = sum / 10;
        C[i] = char('0' + (sum % 10));
    }
    if (carry) C.insert(C.begin(), char('0' + carry));
    return Normalize(C);
}

std::string RealNumber::SubBig(const std::string &a, const std::string &b) {
    std::string A = a, B = b;
    B.insert(B.begin(), A.size() - B.size(), '0');
    int borrow = 0;
    std::string C(A.size(), '0');
    for (int i = A.size() - 1; i >= 0; --i) {
        int diff = (A[i] - '0') - (B[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        C[i] = char('0' + diff);
    }
    return Normalize(C);
}

std::string RealNumber::MulBig(const std::string &a, const std::string &b) {
    int na = a.size(), nb = b.size();
    std::vector<int> prod(na + nb);
    for (int i = na - 1; i >= 0; --i) {
        for (int j = nb - 1; j >= 0; --j) {
            prod[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (int i = na + nb - 1; i > 0; --i) {
        int carry = prod[i] / 10;
        prod[i - 1] += carry;
        prod[i] %= 10;
    }
    std::string C;
    for (int x : prod) C.push_back(char('0' + x));
    return Normalize(C);
}

void RealNumber::DivmodBig(const std::string &a, const std::string &b,
                          std::string &q, std::string &r) {
    if (b == "0") throw std::runtime_error("division by zero");
    q.clear();
    r.clear();
    for (char c : a) {
        r.push_back(c);
        r = Normalize(r);
        int x = 0;
        while (r.size() > b.size() || (r.size() == b.size() && r >= b)) {
            r = SubBig(r, b);
            ++x;
        }
        q.push_back(char('0' + x));
    }
    q = Normalize(q);
    if (q.empty()) q = "0";
    if (r.empty()) r = "0";
}

std::string RealNumber::GcdBig(std::string a, std::string b) {
    while (b != "0") {
        std::string q, r;
        DivmodBig(a, b, q, r);
        a = std::move(b);
        b = std::move(r);
    }
    return a;
}

void RealNumber::Reduce() {
    if (den_ == "0") throw std::runtime_error("division by zero");
    std::string g = GcdBig(num_, den_);
    if (g != "1") {
        std::string q1, r1, q2, r2;
        DivmodBig(num_, g, q1, r1);
        DivmodBig(den_, g, q2, r2);
        num_ = q1;
        den_ = q2;
    }
    if (num_ == "0") {
        negative_ = false;
        den_ = "1";
    }
}