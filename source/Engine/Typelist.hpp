#pragma once

#include <type_traits>
#include <utility>
#include <iostream>

namespace Caravan{

    template <typename... Ts>
    struct Typelist{
        static constexpr auto size = sizeof...(Ts);
    };

    template <typename T>
    struct Typelist<T>{
        using type = T;
    };

    ////////////////////////////////////////////////////////////////////////////////////

    namespace Impl{

        template <size_t I>
        struct Get{
            template <typename... Ts>
            static constexpr auto operator()(Typelist<Ts...>){
                return (Ts...[I]){};
            }
        };

        template <template <typename> typename... Us>
        struct Compose;

        template <template <typename> typename U, template <typename> typename... Us>
        struct Compose<U, Us...>{
            template <typename... Ts>
            static constexpr auto operator()(Typelist<Ts...>){
                return Compose<Us...>::operator()(Typelist<U<Ts>...>{});
            }
        };

        template <template <typename> typename U>
        struct Compose<U>{
            template <typename... Ts>
            static constexpr auto operator()(Typelist<Ts...>){
                return Typelist<U<Ts>...>{};
            }
        };

        template <template <typename> typename... Us>
        struct Decompose;

        template <template <typename> typename U, template <typename> typename... Us>
        struct Decompose<U, Us...>{
            template <typename... Ts>
            static constexpr auto operator()(Typelist<U<Ts>...>){
                return Decompose<Us...>::operator()(Typelist<Ts...>{});
            }
        };

        template <template <typename> typename U>
        struct Decompose<U>{
            template <typename... Ts>
            static constexpr auto operator()(Typelist<U<Ts>...>){
                return Typelist<Ts...>{};
            }
        };


        template <template <typename...> typename W>
        struct Bundle{
            template <typename... Ts>
            static constexpr auto operator()(Typelist<Ts...>){
                return W<Ts...>{};
            };
        };

        struct Unbundle{
            template <template <typename...> typename W, typename... Ts>
            static constexpr auto operator()(W<Ts...>){
                return Typelist<Ts...>{};
            };
        };

        struct Add{
            template <typename... T1s, typename... T2s>
            static constexpr auto operator()(Typelist<T1s...>, Typelist<T2s...>){
                return Typelist<T1s..., T2s...>{};
            };

            template <typename T, typename... T2s>
            static constexpr auto operator()(T, Typelist<T2s...>){
                return Typelist<T, T2s...>{};
            };
        };

        template <typename S>
        struct Remove{
            template <typename... Ts>
            constexpr auto operator()(Typelist<Ts...>);

            template <typename T, typename... Ts>
            constexpr auto operator()(Typelist<T, Ts...>){
                if constexpr (std::is_same<S, T>::value){
                    return this->operator()(Typelist<Ts...>{});
                } else {
                    return Add::operator()(T{},Remove<S>::operator()(Typelist<Ts...>{}));
                }
            };

            template <typename T>
            constexpr auto operator()(Typelist<T> tl){
                if constexpr (std::is_same<S, T>::value){
                    return Typelist<>{};
                } else {
                    return tl;
                }
            };

            constexpr auto operator()(Typelist<> tl){
                return tl;
            };
        };

        struct RemoveDuplicates{
            template <typename... Ts>
            constexpr auto operator()(Typelist<Ts...>);

            template <typename T, typename... Ts>
            constexpr auto operator()(Typelist<T, Ts...> tl){
                return Add::operator()(T{},RemoveDuplicates{}(Remove<T>{}(tl)));
            }

            template <typename T>
            constexpr auto operator()(Typelist<T> tl){
                return tl;
            }

            constexpr auto operator()(Typelist<> tl){
                return tl;
            }
        };

        template <size_t... Is>
        struct Select{
            template <typename... Ts>
            constexpr auto operator()(Typelist<Ts...>){
                return Typelist<Ts...[Is]...>{};
            }

            constexpr auto operator()(Typelist<> tl){
                return tl;
            }
        };

        template <size_t I, size_t J>
        struct Slice{
            template <std::size_t... Is>
            static constexpr auto offset(std::index_sequence<Is...>){
                return std::integer_sequence<std::size_t, (I + Is)...>{};
            };

            static constexpr auto range = offset(std::make_index_sequence<(J > I ? J - I : 0)>{});

            template <size_t... Is, typename... Ts>
            static constexpr auto operator()(std::index_sequence<Is...>, Typelist<Ts...> tl){
                return Select<Is...>{}(tl);
            };
        };

        template <size_t... Is>
        struct Pop;

        template <>
        struct Pop<>{
            template <typename... Ts>
            static constexpr auto operator()(Typelist<Ts...> tl){
                return tl;
            };
        };

        template <size_t I, size_t... Is>
        struct Pop<I, Is...>{

            template <class T, size_t A, size_t B>
            using slice = decltype(Impl::Slice<A,B>{}(Impl::Slice<A,B>::range, T{}));

            template <typename... Ts>
            static constexpr auto operator()(Typelist<Ts...> tl){
                return Add::operator()(slice<Typelist<Ts...>, 0, I>{}, Pop<(Is-I-1  )...>::operator()(slice<Typelist<Ts...>, I+1, sizeof...(Ts)>{}));
            };
        };

        template <typename... Ts>
        constexpr void print(std::ostream& os, Typelist<Ts...>){
            (os << ...  << (std::string(typeid(Ts).name()) + ", ")) << '\n';
        };

        template <typename... Ts>
        constexpr void print(std::ostream& os, Ts...){
            (os << ...  << (std::string(typeid(Ts).name()) + ", ")) << '\n';
        };

        struct CompareEqual{
            template <typename... T1s, typename... T2s>
            constexpr bool compareEqual(Typelist<T1s...>, Typelist<T2s...>);

            template <typename T1, typename... T1s, typename T2, typename... T2s>
            constexpr bool compareEqual(Typelist<T1, T1s...> tl1, Typelist<T2, T2s...> tl2){
                return std::is_same_v<T1,T2> && compareEqual(Typelist<T1s...>{}, Typelist<T2s...>{});
            }

            template <typename... T1s>
            constexpr bool compareEqual(Typelist<T1s...> tl1, Typelist<> tl2){
                return false;
            }

            template <typename... T2s>
            constexpr bool compareEqual(Typelist<> tl1, Typelist<T2s...> tl2){
                return false;
            }

            constexpr bool compareEqual(Typelist<> tl1, Typelist<> tl2){
                return true;
            }
        };

    }

    ////////////////////////////////////////////////////////////////////////////////////

    template <class T, size_t I>
    using get = decltype(Impl::Get<I>{}(T{}));

    template <class T, template <typename> typename... Us>
    using compose = decltype(Impl::Compose<Us...>::operator()(T{}));

    template <class T, template <typename> typename... Us>
    using decompose = decltype(Impl::Decompose<Us...>::operator()(T{}));

    template <class T, template <typename...> typename W>
    using bundle = decltype(Impl::Bundle<W>::operator()(T{}));

    template <class T>
    using unbundle = decltype(Impl::Unbundle::operator()(T{}));

    template <class T1, class T2>
    using add = decltype(Impl::Add::operator()(T1{}, T2{}));

    template <class T, typename S>
    using remove = decltype(Impl::Remove<S>{}(T{}));

    template <class T>
    using removeDuplicates = decltype(Impl::RemoveDuplicates{}(T{}));

    template <class T, size_t... Is>
    using select = decltype(Impl::Select<Is...>{}(T{}));

    template <class T, size_t I, size_t J>
    using slice = decltype(Impl::Slice<I,J>{}(Impl::Slice<I,J>::range, T{}));

    template <class T, size_t... Is>
    using pop = decltype(Impl::Pop<Is...>::operator()(T{}));

    template <class T>
    constexpr void print(std::ostream& os = std::cout){
        Impl::print(os, T{});
    }

    template <class T1, class T2>
    constexpr bool compareEqual(){
        return (T1::size == T2::size) && Impl::CompareEqual{}.compareEqual(T1{}, T2{});
    }

};