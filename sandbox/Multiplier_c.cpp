#define Multiplier_RC_SUCCESS 0
#define Multiplier_RC_FAIL 1

#include "Multiplier.h"
#include <memory>
#include <string>

static thread_local std::string Multiplier_error_;

void Multiplier_clear_error()
{
  Multiplier_error_.clear();
}

const char* Multiplier_error()
{
  return Multiplier_error_.c_str();
}

namespace
{
  using Int_ptr = const std::shared_ptr<const Int>*;
  using Multiplier_ptr = const std::shared_ptr<const Multiplier>*;
} // end anonymous namespace

void Int_dispose(const void* myInt)
{
  delete reinterpret_cast<Int_ptr>(myInt);
}

int Int_create(int value, void** rv)
{
  try
  {
    auto p = std::make_unique<const Int>(value);
    *rv = new std::shared_ptr<const Int>(p.release());
  }
  catch (const std::exception& e)
  {
    Multiplier_error_ = e.what();
    return Multiplier_RC_FAIL;
  }
  return Multiplier_RC_SUCCESS;
}

int Int_value(void* myInt, double* rv)
{
  try
  {
    *rv = (*reinterpret_cast<Int_ptr>(myInt))->value();
  }
  catch (const std::exception& e)
  {
    Multiplier_error_ = e.what();
    return Multiplier_RC_FAIL;
  }
  return Multiplier_RC_SUCCESS;
}
    

void Multiplier_dispose(const void* myMultiplier)
{
  delete reinterpret_cast<Multiplier_ptr>(myMultiplier);
}

int Multiplier_create(int value, void** rv)
{
  try
  {
    auto p = std::make_unique<const Multiplier>(value);
    *rv = new std::shared_ptr<const Multiplier>(p.release());
  }
  catch (const std::exception& e)
  {
    Multiplier_error_ = e.what();
    return Multiplier_RC_FAIL;
  }
  return Multiplier_RC_SUCCESS;
}

int Multiplier_apply(void* myMultiplier, void* anInt, void** rvInt)
{
  try
  {
    Int i = *(*reinterpret_cast<Int_ptr>(anInt));
    Int rv = (*reinterpret_cast<Multiplier_ptr>(myMultiplier))->apply(i);

    auto p = std::make_unique<const Int>(rv);
    *rvInt = new std::shared_ptr<const Int>(p.release());
  }
  catch (const std::exception& e)
  {
    Multiplier_error_ = e.what();
    return Multiplier_RC_FAIL;
  }
  return Multiplier_RC_SUCCESS;
}
    
