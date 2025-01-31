
// #include <Eigen/Dense>
// #include <array>
// #include <atomic>
// #include <iostream>
#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>

using namespace std;

const int N  = 5;
using data_t = Eigen::TensorFixedSize<float, Eigen::Sizes<N>>;

template <typename T, template <typename> class crtpType>
struct crtp {
    T&       underlying() { return static_cast<T&>(*this); }
    T const& underlying() const { return static_cast<T const&>(*this); }
};

// private:
//     crtp() {}
//     friend crtpType<T>;
// };

struct Interface {
    virtual float& operator()(std::initializer_list<int> list) = 0;

    Interface* interface() { return this; }
};

template <typename Derived>
class Parent: public Interface {
public:
    Derived&       child() { return static_cast<Derived&>(*this); }
    Derived const& child() const { return static_cast<Derived const&>(*this); }

    inline float& operator()(std::initializer_list<int> list) {
        return child()(list);
    }

    // virtual Parent* parent() = 0;
    // virtual float& operator()(int i1);
    // template <typename Ts>
    // float& operator()(Ts...);
    // virtual float& operator()(int i1, int i2, int i3);
    // virtual float& operator()(int i1, int i2, int i3, int i4);
    // virtual float& operator()(int i1, int i2, int i3, int i4, int i5);

    // auto& parent = static_cast<Derived&>(*this);
};

// template <typename Derived>
// struct ParentProxy : Parent {
//     Derived& self() { return static_cast<Derived&>(*this); }

//     float& operator()(int i) {
//         return self().p(i);
//     }
// };

class Child1 : public Parent<Child1> {

    data_t iarr;

public:
    // template <typename... Args>
    inline float& operator()(std::initializer_list<int> list) {
        return iarr(list);
    }
};

class Child2 : public Parent<Child2> {

    data_t iarr;

public:
    // template <typename... Args>
    inline float& operator()(std::initializer_list<int> list) {
        return iarr(list);
    }
};

int main() {

    Child1 c1;
    Child2 c2;
    auto&  p1 = *c1.interface();
    auto&  p1 = *c2.interface();

    // auto c2 = Child2();
    // volatile int n = 0;

    // float arr[N];

    // buffers.push_back(&c2);

    for (volatile int i(0); i < N; i++) {
        // for (int j = 0; j < 3; j++) {
        // arr[i]    = i;
        p1(i) = i;
        // p1(i)    = 100 * i;
        // (*buffers[1])(i, j) = 100 * i + 10 * j;
        // }
    }

    int sum = 0;
    for (int i(0); i < N; i++) {
        // sum += arr[i];
        sum += p1(i);
        // cout << p1(i) << " ";
    }

    cout << sum << "\n";

    // cout << "\nChild2\n";
    // for (int i(0); i < N; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cout << (*buffers[1])(i, j) << " ";
    //     }
    //     cout << "\n";
    // }

    // for( auto& buffer : buffers ) {
    //     if(buffer.dimens)

    // }

    // cout
    //     << "Child 1\n";
    // for (int i(0); i < parent1.dimension(0); i++)
    //     cout << parent1(i) << " ";
    // cout << "\n";

    // cout << "Child 2\n";
    // for (int i(0); i < parent2.dimension(0); i++) {
    //     for (int j(0); j < parent2.dimension(1); j++)
    //         cout << parent2(i, j) << " ";
    //     cout << "\n";
    // }

    return sum;
}
