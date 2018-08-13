#include "json.hpp"

#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

json::json_mapper::json_mapper() : json::parser()
{
}

void json::json_mapper::map(const json::node &node, i_json_mappable *mappable)
{
    
}