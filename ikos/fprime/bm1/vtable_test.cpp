class Base {
  public:
    virtual int compute(int x) { return x; }
    virtual ~Base() {}
};

class Derived : public Base {
  public:
    int compute(int x) override { return x * 2; }
};

int main() {
  Derived d;
  return d.compute(1);
}