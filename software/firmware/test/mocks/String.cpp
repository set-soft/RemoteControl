#include "String.h"
#include <string.h>

String::String(const char *cstr){
	this->cstr = cstr;
}

bool String::equals(const String &s2) const{
	return strcmp(this->cstr, s2.c_str()) == 0;
}
