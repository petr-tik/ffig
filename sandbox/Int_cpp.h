#include <exception>
#include <string>
#include "Int_c.h"

namespace CPP_API {


class Int
{
protected:
  const void* object_ = nullptr;
  Int() = default;

public:
  
  Int(int value)
  {
    int rc = Int_Int_create(value, &object_);
    if ( rc == Int_RC_SUCCESS ) return;
    throw exception();
  }
  Int(const Int&) = delete;
  Int& operator = (const Int&) = delete;
  Int(Int&& c)
  {
    object_ = c.object_;
    c.object_ = nullptr;
  }

  Int& operator = (Int&& c)
  {
    object_ = c.object_;
    c.object_ = nullptr;
    return *this;
  }
  
  class exception : public std::runtime_error
  {
  public:
    exception() : std::runtime_error(Int_error())
    {
      Int_clear_error();
    }
  };

  virtual ~Int()
  {
    Int_dispose(object_);
  }

  int value() const
  {
    int rv;
    int rc = Int_value(object_, &rv);
    
    if (rc == Int_RC_SUCCESS) return rv;
    throw exception();
  }

};

} // end namespace CPP_API
