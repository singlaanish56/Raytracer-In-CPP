#pragma once

class interval{
    public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max): min(min), max(max){}

    double size() const{
        return max - min;
    }

    bool contains(const double r){
        return (min<=r && r<=max);
    }

    bool surrounds(const double r){
        return (min < r && r< max);
    }

    double clamp(double x) const{
        if(x<min) return min;
        if(x>max) return max;

        return x;
    }

    static const interval empty, universe;
};


const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
