//
//  Performance_tester.cpp
//  network_simulation
//
//  Created by Filip Szafran on 17/11/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Performance_tester.hpp"
#include <iostream>
#include <iomanip>

test_performance::test_performance(const std::string_view& name)
:function_name(name)
{
    start = std::chrono::high_resolution_clock::now();
}

test_performance::~test_performance()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end-start;
    
    float ms = duration.count()*1000.f;
    std::cout<<std::setprecision(3);
    std::cout<<function_name<<" took: "<<ms<<"ms"<<std::endl;
}
