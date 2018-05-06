//
//  Stopwatch.h
//  MeldingHeaps
//
//  Created by Никита on 10.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef Stopwatch_h
#define Stopwatch_h
#include <chrono>

using namespace std::chrono;

class Stopwatch {
public:
    void start();
    double circle();
private:
    high_resolution_clock::time_point _start_point; //= high_resolution_clock::now();
};

void Stopwatch::start() {
    _start_point = high_resolution_clock::now();
}

double Stopwatch::circle() {
    high_resolution_clock::time_point finish_point = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(finish_point - _start_point);
    _start_point = high_resolution_clock::now();
    return time_span.count();
}
#endif /* Stopwatch_h */
