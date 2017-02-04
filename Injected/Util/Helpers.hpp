#pragma once
#include <sstream>
#include <vector>
#include <string>

template<typename I>
auto tohex(I i)
{
	std::ostringstream stream;
	stream << std::hex << i;
	std::string result(stream.str());
	return result;
}

template<typename Cont, typename Pred>
std::vector<typename Cont::value_type> find_all(Cont& c, Pred p)
{
	std::vector<typename Cont::value_type> res;
	for (auto* x : c)
		if (p(x)) res.push_back(x);
	return res;
}

template<typename Cont, typename Pred>
typename Cont::value_type min_by(Cont& c, Pred p)
{   
	if (c.size() == 0)
		return nullptr;
	return *std::min_element(c.begin(), c.end(), p);
}

template<typename Cont, typename Pred>
typename Cont::value_type max_by(Cont c, Pred p)
{
	if (c.size() == 0)
		return nullptr;
	return *std::min_element(c.begin(), c.end(), p);
}

inline const char * const BoolToString(bool b)
{
	return b ? "true" : "false";
}

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}