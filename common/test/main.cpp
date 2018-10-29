#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <thread>
#include <map>

#include "test.hpp"
#include "config.hpp"
#include "defs.hpp"

#include "test_list.hpp"

int main(int argc, char **argv)
{
    test::test_collection tests;

    tests.push_back(test::test_run(new test::simple_test("test integrity", &test::json_test::integrity)));
    tests.push_back(test::test_run(new test::simple_test("read expanded", &test::json_test::expanded_read)));
    tests.push_back(test::test_run(new test::simple_test("read compact", &test::json_test::compact_read)));
    tests.push_back(test::test_run(new test::simple_test("write expanded", &test::json_test::expanded_write)));
    tests.push_back(test::test_run(new test::simple_test("write compact", &test::json_test::compact_write)));
    tests.push_back(test::test_run(new test::simple_test("read and write", &test::json_test::read_write)));
    tests.push_back(test::test_run(new test::simple_test("write and read", &test::json_test::write_read)));
    tests.push_back(test::test_run(new test::simple_test("string escaping", &test::json_test::string_escaping)));
    tests.push_back(test::test_run(new test::simple_test("number parsing", &test::json_test::number_parsing)));
    tests.push_back(test::test_run(new test::simple_test("basic color definitions", &test::color_test::basic_color_values)));
    tests.push_back(test::test_run(new test::simple_test("function event test", &test::event_test::function_events)));
    tests.push_back(test::test_run(new test::simple_test("listener event test", &test::event_test::listener_events)));
    tests.push_back(test::test_run(new test::simple_test("handler event test", &test::event_test::handler_events)));
    tests.push_back(test::test_run(new test::simple_test("member handler event test", &test::event_test::member_handler_events)));
    tests.push_back(test::test_run(new test::simple_test("rectangle test", &test::geometry_test::rectangle)));
    tests.push_back(test::test_run(new test::simple_test("format", &test::string_test::format)));
    tests.push_back(test::test_run(new test::simple_test("to upper", &test::string_test::to_upper)));
    tests.push_back(test::test_run(new test::simple_test("to lower", &test::string_test::to_lower)));
    tests.push_back(test::test_run(new test::simple_test("split with space", &test::string_test::split_space)));
    tests.push_back(test::test_run(new test::simple_test("split with custom char", &test::string_test::split_custom_char)));
    tests.push_back(test::test_run(new test::simple_test("split with multiple chars", &test::string_test::split_multiple_chars)));
    tests.push_back(test::test_run(new test::simple_test("split with function", &test::string_test::split_function)));
    tests.push_back(test::test_run(new test::simple_test("strip", &test::string_test::strip)));
    tests.push_back(test::test_run(new test::simple_test("strip front", &test::string_test::strip_front)));
    tests.push_back(test::test_run(new test::simple_test("strip back", &test::string_test::strip_back)));
    tests.push_back(test::test_run(new test::simple_test("collect rope", &test::data_test::collection_test::test_collect_rope)));
    tests.push_back(test::test_run(new test::simple_test("array", &test::data_test::collection_test::test_array)));
    tests.push_back(test::test_run(new test::simple_test("cache", &test::data_test::collection_test::test_cache)));

    return test::run_tests(tests, test::test_config::init_from_args(argc, argv));
}