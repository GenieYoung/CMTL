#ifndef CMTL_ATTRIBUTES_H
#define CMTL_ATTRIBUTES_H

#include <any>
#include <map>
#include <string>

/**
 * @brief Computational Mathematics Tool Library
 */
namespace CMTL {

/**
 * @brief structure used to store values with different types and names
 * @tparam K key type
 */
template <typename K = std::string>
class Attributes {
 public:
  typedef K key_type;

  Attributes() = default;

  /**
   * @brief check whether the value with specific name exist
   * @param name value name
   * @return true if exist, otherwise false
   */
  bool contains(const K& name) const {
    auto it = _values.find(name);
    return it != _values.end();
  }

  /**
   * @brief try to get the value with specific name and type, if not found,
   * return nullptr
   * @tparam T value type
   * @param name value name
   * @result the pointer to the value or nullptr if not found
   */
  template <typename T>
  T* try_get(const K& name) {
    auto it = _values.find(name);
    return it == _values.end() ? nullptr : std::any_cast<T>(&it->second);
  }

  /**
   * @brief try to get the value with specific name and type, if not found,
   * return nullptr
   * @tparam T value type
   * @param name value name
   * @result the pointer to the value or nullptr if not found
   */
  template <typename T>
  const T* try_get(const K& name) const {
    auto it = _values.find(name);
    return it == _values.end() ? nullptr : std::any_cast<T>(&it->second);
  }

  /**
   * @brief get the value with specific name and type, if not found, throw
   * std::bad_any_cast
   * @tparam T value type
   * @param name value name
   * @result value with specific name and type
   */
  template <typename T>
  T& get(const K& name) {
    if (T* value = try_get<T>(name)) return *value;
    throw std::bad_any_cast();
  }

  /**
   * @brief get the value with specific name and type, if not found, throw
   * std::bad_any_cast
   * @tparam T value type
   * @param name value name
   * @result value with specific name and type
   */
  template <typename T>
  const T& get(const K& name) const {
    if (const T* value = try_get<T>(name)) return *value;
    throw std::bad_any_cast();
  }

  /**
   * @brief set the value with specific name and type, if not found, construct
   * it, otherwise, return the reference of it
   * @tparam T value type
   * @param name value name
   * @result the writable value that need to be set
   * @note if found, the value type must be the same as the type of the value to
   * be set, otherwise throw std::bad_any_cast
   */
  template <typename T>
  [[nodiscard]] T& set(const K& name) {
    auto [it, inserted] = _values.try_emplace(name);
    if (inserted) return it->second.template emplace<T>();
    if (auto* value = std::any_cast<T>(&it->second)) return *value;
    throw std::bad_any_cast();
  }

  /**
   * @brief remove value with specific name
   */
  void remove(const K& name) { _values.erase(name); }

  /**
   * @brief clear all values
   */
  void clear() { _values.clear(); }

 private:
  std::map<K, std::any> _values;
};

}  // namespace CMTL

#endif  // CMTL_ATTRIBUTES_H
