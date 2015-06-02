#include "rxcpp/rx.hpp"

#include "rxcpp/rx-test.hpp"
#include "catch.hpp"

SCENARIO("reduce sample"){
    printf("//! [reduce sample]\n");
    auto values = rxcpp::observable<>::range(1, 7).
        reduce(
            std::make_pair(0, 1.0),
            [](std::pair<int, double> seed, int v){
                seed.first += 1;
                seed.second *= v;
                return seed;
            },
            [](std::pair<int, double> res){
                return std::pow(res.second, 1.0 / res.first);
            });
    values.
        subscribe(
            [](double v){printf("OnNext: %lf\n", v);},
            [](){printf("OnCompleted\n");});
    printf("//! [reduce sample]\n");
}

SCENARIO("reduce empty sample"){
    printf("//! [reduce empty sample]\n");
    auto values = rxcpp::observable<>::empty<int>().
        reduce(
            1,
            [](int seed, int){return seed;},
            [](int res){return res;});
    values.
        subscribe(
            [](int v){printf("OnNext: %d\n", v);},
            [](std::exception_ptr ep){
                try {std::rethrow_exception(ep);}
                catch (const std::exception& ex) {
                    printf("OnError: %s\n", ex.what());
                }
            },
            [](){printf("OnCompleted\n");});
    printf("//! [reduce empty sample]\n");
}
