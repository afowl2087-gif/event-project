#pragma once 
#include <vector>
#include <stdexcept>

template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void add(const T& value) {
        values.push_back(value);
    }

    T smallest() const {
        if (values.empty())
            throw std::logic_error("any values");
        T min = values[0];
        for (const T& v : values)
            if (v < min) 
            min = v;
        return min;
    }

    T largest() const {
        if (values.empty())
            throw std::logic_error("any values");
        T max = values[0];
        for (const T& v : values)
            if (v > max)
             max = v;
        return max;
    }

    double average() const {
        if (values.empty())
            throw std::logic_error("any values");
        double sum = 0;
        for (const T& v : values)
            sum += v;
        return sum / values.size();
    }
};

