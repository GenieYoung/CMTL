#ifndef __common_attributes_h__
#define __common_attributes_h__

#include <cassert>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <map>

namespace CMTL{

/**
 * @brief struct used to store attributes
 */
class Attributes
{
	public:
		/**
		 * @brief constructor
		 */
		Attributes()
		{
		};

		/**
		 * @brief copy constructor
		 */
		Attributes(const Attributes& other)
		{
			*this = other;
		}

		/**
		 * @brief deconstructor
		 */
		~Attributes()
		{
			this->clear();
		}

		/**
		 * @brief assign operator
		 */
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
		 * @brief check whether the attribute with specific name and type exist
		 * @tparam T attribute type
		 * @param name attribute name
		 * @return true if exist, otherwise false
		 */
		template<typename T>
		bool contain(const std::string& name) const
		{
			auto it = _values.find(name);
			if (it != _values.end())
				return true;
			return false;
		}

		/**
		 * @brief get the attribute with specific name and type
		 * @tparam T attribute type
		 * @param name attribute name
		 * @result true if successfully get, otherwise false
		 */
		template<typename T>
		const T& get(const std::string& name) const
		{
			if (!this->contain<T>(name))
				std::abort();
			auto it = _values.find(name);
			const Attribute<T>* attr = dynamic_cast<const Attribute<T>*>(it->second);
			assert(attr != nullptr); 
			return attr->get();
		}

		template<typename T>
		T& set(const std::string& name)
		{
			if (!this->contain<T>(name))
				_values[name] = new Attribute<T>;
			Attribute<T>* attr = dynamic_cast<Attribute<T>*>(_values[name]);
			assert(attr != nullptr);
			return attr->set();
		}

		/**
		 * @brief remove attribute with specific name
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
		class Value
		{
			public:
				virtual ~Value() 
				{
				};

				virtual std::string type() const = 0;

				virtual Value* clone() const = 0;
		};

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