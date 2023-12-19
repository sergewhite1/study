#pragma once

#include <ostream>

class NullStream : public std::ostream
{
  public:
    NullStream() : std::ostream(nullptr) {}
    NullStream(const NullStream&) : std::ostream(nullptr) {}
    virtual ~NullStream() = default;
};

template <class T>
const NullStream &operator<<(NullStream &&os, const T &value)
{
  return os;
}

extern NullStream nullStream;
