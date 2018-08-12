#include "json.hpp"

json::json_mapper::json_mapper() : json::parser()
{
}

void json::json_mapper::map(const std::string &, i_json_mappable *)
{
}