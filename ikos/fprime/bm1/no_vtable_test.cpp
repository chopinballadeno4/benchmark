// no_vtable_test.cpp - virtual 없음
class Base {
public:
    int compute(int x) { return x; }
};

int main() {
    Base b;
    return b.compute(1);
}