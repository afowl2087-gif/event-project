#ifndef STATISTICS_HPP
#define STATISTICS_HPP
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
            throw std::logic_error("Aucune valeur");
        T min = values[0];
        for (const T& v : values)
            if (v < min) 
            min = v;
        return min;
    }

    T largest() const {
        if (values.empty())
            throw std::logic_error("Aucune valeur");
        T max = values[0];
        for (const T& v : values)
            if (v > max)
             max = v;
        return max;
    }

    double average() const {
        if (values.empty())
            throw std::logic_error("Aucune valeur");
        double sum = 0;
        for (const T& v : values)
            sum += v;
        return sum / values.size();
    }
};

#endif