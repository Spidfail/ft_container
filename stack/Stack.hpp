
#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/Vector.hpp"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {

		public:
			typedef					Container					container_type;
			typedef		typename	container_type::value_type	value_type;
			typedef		typename	container_type::size_type	size_type;

		private:
			container_type	_container;	

		public:
			explicit stack (const container_type& container = container_type())
				: _container(container) { }
			stack(const stack &source) { *this = source; }
			~stack() { }
			
			stack	&operator= (const stack &source) { this->_container = source._container; }

			bool				empty() const { return _container.empty(); }
			size_type			size() const { return _container.size(); }
			void				push(const value_type &value) { return _container.push_back(value); }
			void				pop() { return _container.pop_back(); }

			value_type&			top() { return _container.back(); }
			const value_type&	top() const { return _container.back(); }

			friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	};

	template <class T, class Container>
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._container == rhs._container;
		}

	template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._container != rhs._container;
		}

	template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._container < rhs._container;
		}

	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._container <= rhs._container;
		}

	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._container > rhs._container;
		}

	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._container >= rhs._container;
		}

}

#endif 
