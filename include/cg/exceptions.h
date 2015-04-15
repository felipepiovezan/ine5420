#ifndef CG_EXCEPTIONS_H_
#define CG_EXCEPTIONS_H_

#include <exception>

class CGException : public std::runtime_error {
 public:
  CGException(const std::string& message) : runtime_error(message) {}
};

#endif
