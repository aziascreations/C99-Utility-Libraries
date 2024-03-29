#pragma once

#define assert(expression, name) \
if(expression) {printf("> \033[32mPASS\033[0m -> %s\n", name);} else {printf("> \033[31mFAIL\033[0m -> %s\n", name); return 1;}

#define assert_warn(expression, name) \
if(expression) {printf("> \033[33mWARN\033[0m -> %s\n", name);} else {printf("> \033[31mFAIL\033[0m -> %s\n", name); return 1;}
