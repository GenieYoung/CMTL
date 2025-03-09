#ifndef __common_attributes_h__
#define __common_attributes_h__

#include <cassert>
#include <string>
#include <map>
#include <any>

/**
 * @brief Computational Mathematics Tool Library
 */
namespace CMTL{

/**
 * @brief structure used to store values with different types and names
 */
class Attributes
{
	public:
		Attributes()
		{
		};

		Attributes(const Attributes& other)
		{
			*this = other;
		}

		~Attributes()
		{
			this->clear();
		}

		Attributes& operator=(const Attributes& other)
		{
			_values = other._values;
			return *this;
		}

		/**
		 * @brief check whether the value with specific name exist
		 * @param name value name
		 * @return true if exist, otherwise false
		 */
		bool contain(const std::string& name) const
		{
			auto it = _values.find(name);
			if (it != _values.end() && it->second.has_value())
				return true;
			return false;
		}

		/**
		 * @brief get the value with specific name and type
		 * @tparam T value type
		 * @param name value name
		 * @result value with specific name and type
		 */
		template<typename T>
		const T& get(const std::string& name) const
		{
			auto it = _values.find(name);
			assert(it != _values.end() && "attribute with specific name not found");
			assert(it->second.has_value() && "attribute has no value");
			assert(it->second.type() == typeid(T) && "attribute with specific type not found");
			return *std::any_cast<T>(&it->second);
		}

		/**
		 * @brief set the value with specific name and type, if not found, construct it
		 * @tparam T value type
		 * @param name value name
		 * @result the writable value that need to be set
		 */
		template<typename T>
		T& set(const std::string& name)
		{
			auto it = _values.find(name);
			if(it == _values.end())
				return _values[name].emplace<T>();	
			if(!it->second.has_value())
				return it->second.emplace<T>();
			if(it->second.type() == typeid(T))
				return *std::any_cast<T>(&it->second);
			assert(false && "attribute with specific type not found");
		}

		/**
		 * @brief remove value with specific name
		 */
		void remove(const std::string& name)
		{
			auto it = _values.find(name);
			if (it != _values.end())
				_values.erase(it);
		}

		/**
		 * @brief clear all the values
		 */
		void clear()
		{
			_values.clear();
		}
		
	private:
		std::map<std::string, std::any> _values;
};

}   // namespace CMTL

#endif	// __common_attributes_h__