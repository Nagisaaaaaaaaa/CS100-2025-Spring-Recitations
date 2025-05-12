#include <iostream>

// Inheritance: Public v.s. Private

class Animal {
public:
  virtual void speak() { std::cout << "Animal sound\n"; }
};

// "IS-A" relationship: a dog is an animal
class Dog : public Animal {
public:
  void speak() override { std::cout << "Bark!\n"; }
};

void makeSound(Animal *a) {
  a->speak();
}

//! About public inheritance:
//! 1. Allows implicit upcasting (e.g., std::shared_ptr<Derived> to std::shared_ptr<Base>).
//! 2. All public and protected members of Base remain public and protected in Derived.

class Timer {
public:
  void start() { std::cout << "Timer started\n"; }

  void stop() { std::cout << "Timer stopped\n"; }
};

class Stopwatch : private Timer { // Private inheritance
public:
  using Timer::start; // Exposing only specific methods
};

//! About private inheritance: "HAS-A" relationship
//! 1. No implicit upcasting: Cannot pass Derived* where Base* is expected.
//! 2. Members from Base become private in Derived (even if they were public).

int main() {

  Dog dog;
  makeSound(&dog); // OK! Outputs: Bark!

  Stopwatch sw;
  sw.start(); // OK
  // sw.stop();
  // Error! `stop` is now private in Stopwatch.
}
