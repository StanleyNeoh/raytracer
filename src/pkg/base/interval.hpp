#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
        double min, max;
        interval();
        interval(double _min, double _max);
        bool contains(double x) const;
        bool surrounds(double x) const;
        double clamp(double x) const;
};

#endif
