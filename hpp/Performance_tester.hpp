//
//  Performance_tester.hpp
//  network_simulation
//
//  Created by Filip Szafran on 17/11/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Performance_tester_hpp
#define Performance_tester_hpp

#include <chrono>
#include <string_view>


class test_performance
{
public:
    test_performance(const std::string_view& name);
    ~test_performance();
private:
    std::string_view function_name;
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float>duration;
};

#endif /* Performance_tester_hpp */

#ifndef test_perform
#define perform_test() test_performance test(__FUNCTION__)
#endif
