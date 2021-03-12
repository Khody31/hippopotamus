#pragma once

class Singleton {
 protected:
  Singleton() {}
  Singleton(Singleton const&);
  void operator=(Singleton const&);
};