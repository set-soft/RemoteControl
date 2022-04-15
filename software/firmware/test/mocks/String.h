#pragma once

class String{
public:
	String(const char *cstr = "");

	bool equals(const String &s) const;
	//bool equals(const char *cstr) const;

	friend bool operator == (const String &a, const String &b) { return a.equals(b); }
	//friend bool operator == (const String &a, const char   *b) { return a.equals(b); }
	//friend bool operator == (const char   *a, const String &b) { return b == a; }


	friend bool operator != (const String &a, const String &b) { return !(a == b); }
	//friend bool operator != (const String &a, const char   *b) { return !(a == b); }
	//friend bool operator != (const char   *a, const String &b) { return !(a == b); }

	const char* c_str() const { return cstr; }

private:
	const char* cstr;
};
