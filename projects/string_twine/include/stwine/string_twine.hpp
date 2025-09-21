#pragma once

#include <cassert>
#include <sstream>
#include <string>
#include <string_view>

namespace mcpp {

namespace detail {

template <typename... Fs> struct overloaded final : public Fs... {
  overloaded(Fs &&...fs) : Fs(fs)... {}
  using Fs::operator()...;
};
} // namespace detail

template <typename char_t> class basic_string_twine final {
  using string_view = std::basic_string_view<char_t>;
  std::optional<string_view> m_content;
  std::variant<std::monostate, const basic_string_twine *, string_view> m_left;
  std::variant<std::monostate, const basic_string_twine *, string_view> m_right;

  bool is_leaf() const { return m_content.has_value(); }

  void print(std::ostream &os) const {
    if (is_leaf()) {
      os << m_content.value();
      return;
    }
    assert(!holds_alternative<std::monostate>(m_left) ||
           !holds_alternative<std::monostate>(m_right));
    auto visitor = detail::overloaded(
        [](std::monostate) {}, [&](std::string_view sv) { os << sv; },
        [&](const basic_string_twine *st) { st->print(os); });
    std::visit(visitor, m_left);
    std::visit(visitor, m_right);
  }

  basic_string_twine() = default;

public:
  basic_string_twine(string_view s) : m_content(s) {}
  basic_string_twine(const std::string &s) : m_content(s) {}
  basic_string_twine(const char *s) : m_content(s) {}

  basic_string_twine concat(const basic_string_twine &suffix) const {
    basic_string_twine merged;
    if (is_leaf())
      merged.m_left = m_content.value();
    else
      merged.m_left = this;
    if (suffix.is_leaf())
      merged.m_right = suffix.m_content.value();
    else
      merged.m_right = &suffix;
    return merged;
  }

  std::basic_string<char_t> str() const {
    std::stringstream os;
    print(os);
    return os.str();
  }
};

template <typename char_t>
basic_string_twine<char_t> operator+(const basic_string_twine<char_t> &lhs,
                                     const basic_string_twine<char_t> &rhs) {
  return lhs.concat(rhs);
}

template <typename char_t>
basic_string_twine<char_t> operator+(const basic_string_twine<char_t> &lhs,
                                     std::basic_string_view<char_t> rhs) {
  return lhs.concat(rhs);
}

template <typename char_t>
basic_string_twine<char_t> operator+(const basic_string_twine<char_t> &lhs,
                                     const char_t *rhs) {
  return lhs.concat(rhs);
}

template <typename char_t>
basic_string_twine<char_t> operator+(std::basic_string_view<char> lhs,
                                     const basic_string_twine<char_t> &rhs) {
  return basic_string_twine<char_t>(lhs) + rhs;
}

template <typename char_t>
basic_string_twine<char_t> operator+(const char_t *lhs,
                                     const basic_string_twine<char_t> &rhs) {
  return basic_string_twine<char_t>(lhs) + rhs;
}

using string_twine = basic_string_twine<char>;

} // namespace mcpp
