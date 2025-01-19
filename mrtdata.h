#ifndef mrtdata_h
#define mrtdata_h

#include <bits/stdc++.h>

using std::make_pair;
using std::string;
using std::vector;
using std::unordered_map;
using std::pair;

extern const vector<string> mrt_names;
extern unordered_map<string, vector<pair<string,int>>> mrt_adjacency_list;
extern unordered_map<string, string> mrt_dictionary_formatter;
extern unordered_map<string, string> mrt_line_grabber;

void init_mrt_adjacency_list();
void init_mrt_dictionary_formatter();
void init_mrt_line_grabber();

#endif //mrtdata_h

