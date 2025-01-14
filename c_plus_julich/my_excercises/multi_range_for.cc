#include <iostream>
#include <iomanip>
#include <tuple>
#include <type_traits>
#include <deque>
#include <vector>
#include <list>
#include <functional>
#include <utility>
#include "print_tuple.cc"
using namespace std::rel_ops;
template <typename ... Itr>
class TruncatingIteratorBundle {
public:
    using value_type = std::tuple<typename Itr::value_type ...>;
    using internal_type = std::tuple<Itr ...>;
    using self_type = TruncatingIteratorBundle;
    TruncatingIteratorBundle() = default;
    TruncatingIteratorBundle(const self_type &) = default;
    TruncatingIteratorBundle(self_type &&) = default;
    TruncatingIteratorBundle &operator=(const self_type &) = default;
    TruncatingIteratorBundle &operator=(self_type &&) = default;
    bool operator==(const self_type &it) const { return loc==it.loc; }
    // Return true only if all iterators in the bundle compare unequal.
    // This is a hack with the consequence that there may be iterators
    // i and j such that i==j and i!=j are both false. But allowing this
    // helps make sure that range for loops over multiple containers
    // breaks at the first location where any of the iterators in the bundle
    // fails to compare unequal with the end point, i.e., at the end of 
    // the shortest container. Suggested in the class by Justin Finerty,
    // implemented by SM.
    bool operator!=(const self_type &it) const { 
        return all_unequal<0,sizeof ...(Itr)>::eval(loc,it.loc);
    }
    TruncatingIteratorBundle(Itr ... itr) : loc{itr ...} {}
    TruncatingIteratorBundle(std::tuple<Itr ...> oth) : loc{oth} {}
    ~TruncatingIteratorBundle()=default; 
    inline value_type operator*() const { return deref(); }
    inline TruncatingIteratorBundle & operator++() {
        advance_them<0,sizeof ...(Itr)>::eval(loc);
        return *this;
    }
    inline TruncatingIteratorBundle operator++(int) {
        TruncatingIteratorBundle it{*this};
        advance_them<0,sizeof ...(Itr)>::eval(loc);
        return it;
    }
private:
    inline value_type deref() const {
        value_type v;
        find_value<0, sizeof ...(Itr)>::eval(v,loc);
        return v;
    }
    template <unsigned I, unsigned J>
    struct find_value {
        static inline void eval(value_type &v, const internal_type &lc) {
            std::get<I>(v)=*(std::get<I>(lc));
            find_value<I+1,J>::eval(v,lc);
        }
    };
    template <unsigned I>
    struct find_value<I,I> {
        static inline void eval(value_type &v, const internal_type &lc) {}
    };
    template <unsigned I, unsigned J> struct advance_them { 
        static inline void eval(internal_type & lc) {
            std::get<I>(lc)++;
            advance_them<I+1,J>::eval(lc);
        }
    };
    template <unsigned I> struct advance_them<I,I> { static inline void eval(internal_type &lc) {} };
    template <unsigned I, unsigned J>
    struct all_unequal {
        static inline bool eval(const internal_type &it1, const internal_type & it2) {
            return std::get<I>(it1)!=std::get<I>(it2) and
                   all_unequal<I+1,J>::eval(it1,it2);
        }
    };
    template <unsigned I> struct all_unequal<I,I> { 
        static inline bool eval(const internal_type & it1, const internal_type & it2) { return true; }
    };

    internal_type loc;
};

template <typename ... Args>
class ContainerBundle {
public:
    using iterator = TruncatingIteratorBundle<typename Args::iterator ...>;
    using iter_coll = std::tuple<typename Args::iterator ...>;
    ContainerBundle(typename std::add_pointer<Args>::type ... args) : dat{(args) ...},
                                     bg{args->begin() ...}, nd{args->end() ...} {}
    ~ContainerBundle()=default;
    ContainerBundle(const ContainerBundle &)=delete;
    ContainerBundle(ContainerBundle &&)=default;
 
    inline iterator begin(){ return bg; }
    inline iterator end() const { return nd; }
private:
    std::tuple<typename std::add_pointer<Args>::type ...> dat;
    iterator bg,nd;
};

template <bool... b> struct static_all_of;

//implementation: recurse, if the first argument is true
template <bool... tail> 
struct static_all_of<true, tail...> : static_all_of<tail...> {};

//end recursion if first argument is false - 
template <bool... tail> 
struct static_all_of<false, tail...> : std::false_type {};

// - or if no more arguments
template <> struct static_all_of<> : std::true_type {};

template <typename ... Args>
ContainerBundle<typename std::remove_pointer<Args>::type ...> zip(Args ... args)
{
    static_assert(static_all_of<std::is_pointer<Args>::value ...>::value, 
                  "Each argument to zip must be a pointer to a container! Example: zip(&l,&d,&v) where l,d and v are containers.");
    return {args ...};
}

int main()
{
    std::vector<size_t> v{1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    std::list<double> l{0.2,0.4,0.6,0.8};
    std::deque<std::string> d{"Abc","DEF","GHI","JKL","MNO"};
    //ContainerBundle<std::list<double>,std::vector<size_t>> C{&l,&v};
    //v[3]=28;
    std::cout << "Iterating over ContainerBundle ...\n";
    for (auto el : zip(&l,&v,&d)) {
        std::cout << el <<"\n";
    }
    
    for (auto ch1: d) { std::cout << ch1 << "\n";}
}

