#pragma once
#include <AzCore/RTTI/RTTI.h>

namespace BookProject
{
  class MyInterface
  {
  public:
    AZ_RTTI(MyInterface, "{EFBB8670-5CDC-4FEC-B5C6-52040ED515E8}");
    virtual ~MyInterface() = default;

    virtual int GetMyInteger() = 0;
  };
}