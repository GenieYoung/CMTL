#ifndef __common_attributes_h__
#define __common_attributes_h__

#include <cassert>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <map>

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
			this->clear();
			for (auto it = other._values.begin(); it != other._values.end(); ++it)
			{
				_values[it->first] = it->second->clone();
			}
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
			if (it != _values.end())
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
			const Attribute<T>* attr = dynamic_cast<const Attribute<T>*>(it->second);
			assert(attr != nullptr && "attribute with specific type not found"); 
			return attr->get();
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
			{
				Attribute<T>* attr = new Attribute<T>;
				_values[name] = attr;
				return attr->set();
			}
			Attribute<T>* attr = dynamic_cast<Attribute<T>*>(_values[name]);
			assert(attr != nullptr && "attribute with specific type not found");
			return attr->set();
		}

		/**
		 * @brief remove value with specific name
		 */
		void remove(const std::string& name)
		{
			auto it = _values.find(name);
			if (it != _values.end())
			{
				delete it->second;
				it->second = nullptr;
				_values.erase(it);
			}
		}

		/**
		 * @brief clear all the values
		 */
		void clear()
		{
			while (!_values.empty())
			{
				auto it = _values.begin();
				delete it->second;
				it->second = nullptr;
				_values.erase(it);
			}
		}

	private:
		/* pure virtual class used for representing different types */
		class Value
		{
			public:
				virtual ~Value() 
				{
				};

				virtual std::string type() const = 0;

				virtual Value* clone() const = 0;
		};

		/* class used for representing different types */
		template<typename T>
		class Attribute : public Value
		{
			public:
				const T& get() const 
				{ 
					return _value; 
				}

				T& set() 
				{
					return _value; 
				}

				virtual std::string type() const
				{
					return typeid(T).name();
				}

				virtual Value* clone() const
				{
					Attribute<T>* copy = new Attribute<T>;
					copy->_value = _value;
					return copy;
				}

			private:
				T _value;
		};
		
	private:
		std::map<std::string, Value*> _values;
};

}   // namespace CMTL

#endif	// __common_attributes_h__