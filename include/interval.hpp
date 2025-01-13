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
        return (r<=max && r>=min);
    }

    bool surrounds(const double r){
        return (min < r && r< max);
    }

    static const interval empty, universe;
};


const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
