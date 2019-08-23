#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <thread>
#include <map>

#include "config.hpp"
#include "Test.hpp"
#include "Defs.hpp"

#include "TestList.hpp"

int main(int argc, char **argv)
{
    test::TestCollection tests;

    tests.push_back(test::TestRun(new test::SimpleTest("test integrity", &test::jsonTest::Integrity)));
    tests.push_back(test::TestRun(new test::SimpleTest("read expanded", &test::jsonTest::ExpandedRead)));
    tests.push_back(test::TestRun(new test::SimpleTest("read compact", &test::jsonTest::CompactRead)));
    tests.push_back(test::TestRun(new test::SimpleTest("write expanded", &test::jsonTest::ExpandedWrite)));
    tests.push_back(test::TestRun(new test::SimpleTest("write compact", &test::jsonTest::CompactWrite)));
    tests.push_back(test::TestRun(new test::SimpleTest("read and write", &test::jsonTest::ReadWrite)));
    tests.push_back(test::TestRun(new test::SimpleTest("write and read", &test::jsonTest::WriteRead)));
    tests.push_back(test::TestRun(new test::SimpleTest("string escaping", &test::jsonTest::StringEscaping)));
    tests.push_back(test::TestRun(new test::SimpleTest("number parsing", &test::jsonTest::NumberParsing)));
    tests.push_back(test::TestRun(new test::SimpleTest("basic color definitions", &test::colorTest::BasicColorValues)));
    tests.push_back(test::TestRun(new test::SimpleTest("Color conversions hsv <> rgb", &test::colorTest::HsvRgbConversions)));
    tests.push_back(test::TestRun(new test::SimpleTest("Color conversions color <> hex string", &test::colorTest::HexStringConversions)));
    tests.push_back(test::TestRun(new test::SimpleTest("function event test", &test::eventTest::FunctionEvents)));
    tests.push_back(test::TestRun(new test::SimpleTest("listener event test", &test::eventTest::ListenerEvents)));
    tests.push_back(test::TestRun(new test::SimpleTest("handler event test", &test::eventTest::HandlerEvents)));
    tests.push_back(test::TestRun(new test::SimpleTest("member handler event test", &test::eventTest::MemberHandlerEvents)));
    tests.push_back(test::TestRun(new test::SimpleTest("generalized event test", &test::eventTest::GeneralizedEventTest)));
    tests.push_back(test::TestRun(new test::SimpleTest("rectangle test", &test::geometryTest::TestRectangle)));
    tests.push_back(test::TestRun(new test::SimpleTest("rectangle move edge test", &test::geometryTest::TestRectangleMoves)));
    tests.push_back(test::TestRun(new test::SimpleTest("rectangle cut test", &test::geometryTest::TestRectangleCuts)));
    tests.push_back(test::TestRun(new test::SimpleTest("format", &test::stringTest::Format)));
    tests.push_back(test::TestRun(new test::SimpleTest("format2", &test::stringTest::Format2)));
    tests.push_back(test::TestRun(new test::SimpleTest("to upper", &test::stringTest::ToUpper)));
    tests.push_back(test::TestRun(new test::SimpleTest("to lower", &test::stringTest::ToLower)));
    tests.push_back(test::TestRun(new test::SimpleTest("split with space", &test::stringTest::SplitSpace)));
    tests.push_back(test::TestRun(new test::SimpleTest("split with custom char", &test::stringTest::SplitCustomChar)));
    tests.push_back(test::TestRun(new test::SimpleTest("split with multiple chars", &test::stringTest::SplitMultipleChars)));
    tests.push_back(test::TestRun(new test::SimpleTest("split with function", &test::stringTest::SplitFunction)));
    tests.push_back(test::TestRun(new test::SimpleTest("strip", &test::stringTest::Strip)));
    tests.push_back(test::TestRun(new test::SimpleTest("strip front", &test::stringTest::StripFront)));
    tests.push_back(test::TestRun(new test::SimpleTest("strip back", &test::stringTest::StripBack)));
    tests.push_back(test::TestRun(new test::SimpleTest("strip inplace", &test::stringTest::StripInplace)));
    tests.push_back(test::TestRun(new test::SimpleTest("strip front inplace", &test::stringTest::StripFrontInplace)));
    tests.push_back(test::TestRun(new test::SimpleTest("strip back inplace", &test::stringTest::StripBackInplace)));
    tests.push_back(test::TestRun(new test::SimpleTest("justification", &test::stringTest::Justification)));
    tests.push_back(test::TestRun(new test::SimpleTest("collect rope", &test::dataTest::collectionTest::TestCollectRope)));
    tests.push_back(test::TestRun(new test::SimpleTest("array", &test::dataTest::collectionTest::TestArray)));
    tests.push_back(test::TestRun(new test::SimpleTest("list", &test::dataTest::collectionTest::TestList)));
    tests.push_back(test::TestRun(new test::SimpleTest("cache", &test::dataTest::collectionTest::TestCache)));
    tests.push_back(test::TestRun(new test::SimpleTest("index mapper", &test::dataTest::collectionTest::TestIndexMapper)));
    tests.push_back(test::TestRun(new test::SimpleTest("hex4 to number", &test::mathTest::TestHex4ToNumber)));
    tests.push_back(test::TestRun(new test::SimpleTest("hex to number", &test::mathTest::TestHexToNumber)));
    tests.push_back(test::TestRun(new test::SimpleTest("is hex char", &test::mathTest::TestIsHexChar)));
    tests.push_back(test::TestRun(new test::SimpleTest("crop", &test::mathTest::TestCrop)));
    tests.push_back(test::TestRun(new test::SimpleTest("variadic max", &test::mathTest::TestMax)));

    return test::RunTests(tests, test::TestConfig::InitFromArgs(argc, argv));
}