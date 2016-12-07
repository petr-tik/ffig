#include <memory>
#include <string>
#include "Int_c.h"
#include "Int.h"


// thread_local won't work on Apple clang:
// http://stackoverflow.com/questions/28094794/why-does-apple-clang-disallow-c11-thread-local-when-official-clang-supports/29929949#29929949
static thread_local std::string Int_error_;

void Int_clear_error()
{
  Int_error_.clear();
}

const char* Int_error()
{
  return Int_error_.c_str();
}

namespace {
using Int_ptr = const std::shared_ptr<const Int>*;
} // end anonymous namespace

void Int_dispose(const void* myInt)
{
  delete reinterpret_cast<Int_ptr>(myInt);
}

int Int_Int_create(int value, const void** rv)
{
  try
  {
    auto p = std::make_unique<const Int>(value);
    *rv = new std::shared_ptr<const Int>(p.release());
  }
  catch(const std::exception& e)
  {
    Int_error_ = e.what();
    return Int_RC_FAIL;
  }
  return Int_RC_SUCCESS;
}
  
int Int_value(const void* myInt, int* rv)
{
  try
  {
    *rv = (*reinterpret_cast<Int_ptr>(myInt))->value();
    
  }
  catch(const std::exception& e)
  {
    Int_error_ = e.what();
    return Int_RC_FAIL;
  }
  return Int_RC_SUCCESS;
}
 
