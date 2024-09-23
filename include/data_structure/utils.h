//
// Created by Eden_ on 2024/9/23.
//

#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <type_traits>
#include <utility>

namespace utils
{
    /**
     * @brief Trait to check if the equality (==) operator is implemented for a type.
     *
     * This trait evaluates to `std::true_type` if the type `T` has an equality operator (`==`),
     * otherwise it evaluates to `std::false_type`.
     *
     * @tparam T The type to check.
     * @tparam D Void An optional void parameter, used for SFINAE (default: void).
     */
    template <typename T, typename D = void>
    struct has_equal : std::false_type {};

    /**
     * @brief Specialization of has_equal when the equality (==) operator exists.
     *
     * This template specialization will be selected if the type `T` supports `==` comparison.
     */
    template <typename T>
    struct has_equal<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

    /**
     * @brief Trait to check if all comparison operators are implemented for a type.
     *
     * This trait checks if a type `T` has the following comparison operators: `==`, `<`, `>`, `<=`, and `>=`.
     * If all these operators are implemented, it evaluates to `std::true_type`, otherwise it evaluates to `std::false_type`.
     *
     * @tparam T The type to check.
     * @tparam D Void An optional void parameter, used for SFINAE (default: void).
     */
    template <typename T, typename D = void>
    struct has_all_comparisons : std::false_type {};

    /**
     * @brief Specialization of has_all_comparisons when all comparison operators exist.
     *
     * This template specialization will be selected if the type `T` supports all the following
     * comparison operators: `==`, `<`, `>`, `<=`, and `>=`.
     */
    template <typename T>
    struct has_all_comparisons<T, std::void_t<
        decltype(std::declval<T>() == std::declval<T>()),
        decltype(std::declval<T>() < std::declval<T>()),
        decltype(std::declval<T>() > std::declval<T>()),
        decltype(std::declval<T>() <= std::declval<T>()),
        decltype(std::declval<T>() >= std::declval<T>())
    >> : std::true_type {};

    /**
     * @brief Trait to check if `std::hash` is implemented for a type.
     *
     * This trait evaluates to `std::true_type` if the type `T` has a specialization for `std::hash`,
     * otherwise it evaluates to `std::false_type`.
     *
     * @tparam T The type to check.
     * @tparam D Void An optional void parameter, used for SFINAE (default: void).
     */
    template <typename T, typename D = void>
    struct has_hash : std::false_type {};

    /**
     * @brief Specialization of has_hash when the hash function exists.
     *
     * This template specialization will be selected if `std::hash<T>` is implemented for the type `T`.
     */
    template <typename T>
    struct has_hash<T, std::void_t<decltype(std::declval<std::hash<T>>()(std::declval<T>()))>> : std::true_type {};
}

#endif //UTILS_H
