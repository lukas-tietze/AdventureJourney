namespace test
{
namespace json_test
{
int integrity();
int expanded_read();
int compact_read();
int expanded_write();
int compact_write();
int read_write();
int write_read();
int string_escaping();
int number_parsing();
} // namespace json_test
namespace color_test
{
int basic_color_values();
}
namespace event_test
{
int function_events();
int listener_events();
int handler_events();
int member_handler_events();
} // namespace event_test
namespace geometry_test
{
int rectangle();
}
namespace string_test
{
int format();
int to_upper();
int to_lower();
int split_space();
int split_custom_char();
int split_multiple_chars();
int split_function();
int strip();
int strip_front();
int strip_back();
} // namespace string_test
namespace math_test
{
int test_hex4_to_number();
int test_hex_to_number();
int test_is_hex_char();
int test_crop();
} // namespace math_test
namespace data_test
{
namespace collection_test
{
int test_array();
int test_collect_rope();
int test_cache();
} // namespace collection_test
} // namespace data_test
} // namespace test