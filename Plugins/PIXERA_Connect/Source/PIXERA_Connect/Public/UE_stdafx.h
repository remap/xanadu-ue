#pragma once
#include "CoreMinimal.h"

#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <string>
#include <memory>
#include <functional>
#include <chrono>
#include <thread>
#include <future>
#include <unordered_map>
#include <unordered_set>
#include <regex>
using std::string;
using std::unique_ptr;
using std::map;
using std::set;
using std::vector;
using std::list;
using std::deque;
using std::pair;
using std::thread;
using std::unordered_map;
using std::unordered_set;

#define IFNR(exp,returnVal) if(!(exp)){return returnVal;}
#define GETAS(oper,type) dynamic_cast<type>(oper)