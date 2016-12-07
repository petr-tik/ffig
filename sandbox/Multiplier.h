class Int
{
  int value_ = 0;

public:
  Int(int value) : value_(value)
  {
  }

  int value() const
  {
    return value_;
  }
};

class Multiplier
{
  Int i_;

public:
  Multiplier(Int value) : i_(value)
  {
  }

  Int apply(Int i) const
  {
    return i_.value() * i.value();
  }
};

