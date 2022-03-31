
#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {

		public:
			typedef					Container					container_type;
			typedef		typename	container_type::value_type	value_type;
			typedef		typename	container_type::size_type	size_type;

		protected:
			container_type	c;	

		public:
			explicit stack (const container_type& container = container_type())
				: c(container) { }
			stack(const stack &source) { *this = source; }
			~stack() { }
			
			stack	&operator= (const stack &source) { this->c = source.c; }

			bool				empty() const { return c.empty(); }
			size_type			size() const { return c.size(); }
			void				push(const value_type &value) { return c.push_back(value); }
			void				pop() { return c.pop_back(); }

			value_type&			top() { return c.back(); }
			const value_type&	top() const { return c.back(); }

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
