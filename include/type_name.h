#pragma once

#include <array>
#include <cstddef>
#include <tuple>

namespace impl
{
    // thanks to HolyBlackCat @ https://stackoverflow.com/a/59522794

    template <typename T>
    constexpr const auto& RawTypeName()
    {
#ifdef _MSC_VER
        return __FUNCSIG__;
#else
        return __PRETTY_FUNCTION__;
#endif
    }

    struct RawTypeNameFormat
    {
        std::size_t leading_junk = 0, trailing_junk = 0;
    };

    // Returns `false` on failure.
    inline constexpr bool GetRawTypeNameFormat(RawTypeNameFormat* format)
    {
        const auto& str = RawTypeName<int>();
        for (std::size_t i = 0;; i++)
        {
            if (str[i] == 'i' && str[i + 1] == 'n' && str[i + 2] == 't')
            {
                if (format)
                {
                    format->leading_junk = i;
                    format->trailing_junk = sizeof(str) - i - 3 - 1; // `3` is the length of "int", `1` is the space for the null terminator.
                }
                return true;
            }
        }
        return false;
    }

    inline static constexpr RawTypeNameFormat format =
        [] {
            static_assert(GetRawTypeNameFormat(nullptr), "Unable to figure out how to generate type names on this compiler.");
            RawTypeNameFormat format;
            GetRawTypeNameFormat(&format);
            return format;
        }();

    // Returns the type name in a `std::array<char, N>` (null-terminated).
    template <typename T>
    [[nodiscard]] constexpr auto CexprTypeName()
    {
        constexpr std::size_t len = sizeof(impl::RawTypeName<T>()) - impl::format.leading_junk - impl::format.trailing_junk;
        std::array<char, len> name{};
        for (std::size_t i = 0; i < len - 1; i++)
        {
            name[i] = impl::RawTypeName<T>()[i + impl::format.leading_junk];
        }
        return name;
    }

    template <typename T>
    [[nodiscard]] std::string GenerateTypeName(int template_args_to_print)
    {
        auto type = CexprTypeName<T>();
        auto name = std::string(type.data());
        if (name.find('<') != std::string::npos)
        {
            if (template_args_to_print >= 0)
            {
                auto pos = name.find('<') + 1;
                auto end_pos = name.find('>');
                for (int arg = 0; (arg < template_args_to_print) && (pos < end_pos); ++arg)
                {
                    unsigned level = 0;
                    while (pos < end_pos)
                    {
                        pos++;
                        if (name[pos] == ',' && level == 0)
                        {
                            break;
                        }
                        if (name[pos] == '<')
                            level++;
                        if (name[pos] == '>')
                            level--;
                    }
                }
                if (pos == end_pos)
                {
                    pos++;
                }
                name = name.substr(0, pos) + ">";
            }
            else
            {
                for (size_t i = name.size() - 1; i > 0; --i)
                {
                    if (name[i - 1] != ' ')
                    {
                        name = name.substr(0, i) + ">";
                        break;
                    }
                }
            }
        }

        static const std::array<std::tuple<std::string, std::string>, 12> beautify_map
        {
            std::tuple<std::string, std::string>{CexprTypeName<float>().data(), "f32"},
            std::tuple<std::string, std::string>{CexprTypeName<double>().data(), "f64"},
            std::tuple<std::string, std::string>{CexprTypeName<uint64_t>().data(), "u64"},
            std::tuple<std::string, std::string>{CexprTypeName<uint32_t>().data(), "u32"},
            std::tuple<std::string, std::string>{CexprTypeName<uint16_t>().data(), "u16"},
            std::tuple<std::string, std::string>{CexprTypeName<uint8_t>().data(), "u8"},
            std::tuple<std::string, std::string>{CexprTypeName<int64_t>().data(), "i64"},
            std::tuple<std::string, std::string>{CexprTypeName<int32_t>().data(), "i32"},
            std::tuple<std::string, std::string>{CexprTypeName<int16_t>().data(), "i16"},
            std::tuple<std::string, std::string>{CexprTypeName<int8_t>().data(), "i8"},
            {" *", "*"},
            {" &", "&"},
        };

        for (auto [x, y] : beautify_map)
        {
            size_t pos = name.find(x);
            while (pos != std::string::npos)
            {
                name.replace(pos, x.size(), y);
                pos = name.find(x, pos + y.size());
            }
        }

        return name;
    }
} // namespace impl

template <typename T>
[[nodiscard]] std::string TypeName(int template_args_to_print = -1)
{
    return impl::GenerateTypeName<T>(template_args_to_print);
}

template <typename T>
[[nodiscard]] std::string TypeName(const T&, int template_args_to_print = -1)
{
    return impl::GenerateTypeName<T>(template_args_to_print);
}
