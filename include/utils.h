#pragma once

#include "types.h"
#include <random>
#include <string>

#include "type_name.h"

#include <vector>

#include <deque>
#include <list>

#include <map>
#include <unordered_map>

#include <set>
#include <unordered_set>

// ####################################################################
// globally available rng and random device

static std::random_device random_device;
static std::mt19937_64 rng(random_device());

// ####################################################################

// converts a (potentially looong) number to a better-readable uptick-separated string representation
// Example: 1000000 -> "1'000'000"
std::string size_to_string(size_t size)
{
    std::string s = std::to_string(size);
    auto len = s.length();
    auto pos = 3;

    while (len > 3)
    {
        s.insert(s.begin() + s.size() - pos, '\'');
        len -= 3;
        pos += 4;
    }

    return s;
}

// ####################################################################
// pretty typename printing

#define TYPE_NAME_HELPER(TYPE)                         \
    template <typename T>                              \
    [[nodiscard]] std::string TypeName(const TYPE<T>&) \
    {                                                  \
        return #TYPE "<" + TypeName<T>() + ">";        \
    }

#define TYPE_NAME_HELPER_2(TYPE)                                       \
    template <typename T, typename R>                                  \
    [[nodiscard]] std::string TypeName(const TYPE<T, R>&)              \
    {                                                                  \
        return #TYPE "<" + TypeName<T>() + ", " + TypeName<R>() + ">"; \
    }

TYPE_NAME_HELPER(std::vector)
TYPE_NAME_HELPER(std::list)
TYPE_NAME_HELPER(std::deque)
TYPE_NAME_HELPER(std::set)
TYPE_NAME_HELPER(std::unordered_set)
TYPE_NAME_HELPER_2(std::map)
TYPE_NAME_HELPER_2(std::unordered_map)

// ####################################################################
// constexpr functions to check whether a type is any kind of map or set, a vector, a list or a deque

template <typename T>
struct is_map_impl : std::false_type
{
};

template <typename... Is>
struct is_map_impl<std::map<Is...>> : std::true_type
{
};
template <typename... Is>
struct is_map_impl<std::unordered_map<Is...>> : std::true_type
{
};

template <typename T>
constexpr bool is_map = is_map_impl<std::remove_reference_t<T>>::value;

template <typename T>
struct is_set_impl : std::false_type
{
};

template <typename... Is>
struct is_set_impl<std::set<Is...>> : std::true_type
{
};
template <typename... Is>
struct is_set_impl<std::unordered_set<Is...>> : std::true_type
{
};

template <typename T>
constexpr bool is_set = is_set_impl<std::remove_reference_t<T>>::value;

template <typename T>
struct is_unordered_impl : std::false_type
{
};

template <typename... Is>
struct is_unordered_impl<std::unordered_map<Is...>> : std::true_type
{
};
template <typename... Is>
struct is_unordered_impl<std::unordered_set<Is...>> : std::true_type
{
};

template <typename T>
constexpr bool is_unordered = is_unordered_impl<std::remove_reference_t<T>>::value;

template <typename T>
struct is_vector_impl : std::false_type
{
};

template <typename... Is>
struct is_vector_impl<std::vector<Is...>> : std::true_type
{
};

template <typename T>
constexpr bool is_vector = is_vector_impl<std::remove_reference_t<T>>::value;

template <typename T>
struct is_list_impl : std::false_type
{
};

template <typename... Is>
struct is_list_impl<std::list<Is...>> : std::true_type
{
};

template <typename T>
constexpr bool is_list = is_list_impl<std::remove_reference_t<T>>::value;

template <typename T>
struct is_deque_impl : std::false_type
{
};

template <typename... Is>
struct is_deque_impl<std::deque<Is...>> : std::true_type
{
};

template <typename T>
constexpr bool is_deque = is_deque_impl<std::remove_reference_t<T>>::value;
