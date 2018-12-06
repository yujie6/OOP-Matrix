#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef> //using size_t, similar to unsigned int
#include <initializer_list>
#include <utility>
#include <vector>
#include <iterator>

using std::size_t; //use size_t of namespace std

namespace sjtu //create a namespace
{

	template <class T> //T is a placeholder
	class Matrix
	{
	private:
		// your private member variables here.
		size_t rowlen;
		size_t columnlen;
		std::vector<std::vector<T>> v;

	public:
		Matrix() = default;
		// myclass() = default >>> we have construct function
		// myclass() = delete  >>> we don't have
		Matrix(size_t n, size_t m, T _init = T())
		{
			std::vector<T> u;
			size_t i, j;
			for (i = 0; i < m; i++){
				u.push_back(_init);
			}
			for (j = 0; j < n; j++){
				v.push_back(u);
			}
			rowlen    = n;
			columnlen = m;
		}
		Matrix(size_t n, size_t m, std::vector<std::vector<T>> u)
		{
			rowlen    = n;
			columnlen = m;
			v = u;
		}

		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
		{
			std::vector<T> u;
			int i, j;
			for (i = 0; i < sz.second; i++){
				u.push_back(_init);
			}
			for (j = 0; j < sz.first; j++){
				v.push_back(u);
			}
			rowlen    = sz.first;
			columnlen = sz.second;
		}

		Matrix(const Matrix &o) //copy function
		{
			v         = o.v;
			rowlen    = o.rowlen;
			columnlen = o.columnlen;
		}

		template <class U>
		Matrix(const Matrix<U> &o)//transform class
		{
			size_t i, j;
			T tmp;
			std::vector<T> u1;
			std::vector<std::vector<T>> u0;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					tmp = (T)o(i, j);
					u1.push_back(tmp);
				}
				u0.push_back(u1);
				u1.clear();
			}
			v = u0;
		}

		Matrix &operator=(const Matrix &o)
		{
			v         = o.v;
			rowlen    = o.rowlen;
			columnlen = o.columnlen;
			return *this;
		}

		template <class U>
		Matrix &operator=(const Matrix<U> &o)
		{
			columnlen = o.columnLength();
			rowlen    = o.rowLength();
			size_t i, j;
			T tmp;
			std::vector<T> u1;
			std::vector<std::vector<T>> u0;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					tmp = (T)o(i ,j);
					u1.push_back(tmp);
				}
				u0.push_back(u1);
				u1.clear();
			}
			v = u0;
			return *this;
		}

		Matrix(Matrix &&o) noexcept //move constructor
		{

		}
	   /* try
	   	* throw
		* noexcept
	    * catch they're used for finding wrong things
	   */
		Matrix &operator=(Matrix &&o) noexcept
		{

		}

		~Matrix() { } //the destructor

		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
			int i, j;
			std::vector<T> u1;
			std::vector<std::vector<T>> u0;
			for (auto p = il.begin(); p != il.end(); p++){
				for (auto q = p->begin(); q != p->end(); q++){
					u1.push_back(*q);
				}
				u0.push_back(u1);
				u1.clear();
			}
			rowlen    = il.size();
			columnlen = (il.begin())->size();
			v = u0;
		}

	public:
		size_t rowLength() const { return rowlen;}

		size_t columnLength() const {return columnlen;}

		void resize(size_t _n, size_t _m, T _init = T())
		{
			rowlen    = _n;
			columnlen = _m;
			std::vector<T> u0;
			size_t i, j;
			v.clear();
			for (i = 0; i < _m; i++){
				u0.push_back(_init);
			}
			for (j = 0; j < _n; j++){
				v.push_back(u0);
			}
		}

		void resize(std::pair<size_t, size_t> sz, T _init = T())
		{
			rowlen    = sz.first;
			columnlen = sz.second;
			std::vector<T> u0;
			int i, j;
			v.clear();
			for (i = 0; i < sz.second; i++){
				u0.push_back(_init);
			}
			for (j = 0; j < sz.first; j++){
				v.push_back(u0);
			}
		}

		std::pair<size_t, size_t> size() const
		{
			std::pair<size_t, size_t> foo;
			foo = {rowlen, columnlen};
			return foo;
		};

		void clear()
		{
			v.clear();
			rowlen    = 0;
			columnlen = 0;
		}

	public:
		const T &operator()(size_t i, size_t j) const
		{
			return v[i][j];
		}

		T &operator()(size_t i, size_t j) //why???
		{
			return v[i][j];
		}

		Matrix<T> row(size_t i) const
		{
			size_t j;
			Matrix<T> M;
			std::vector<std::vector<T>> u0;
			std::vector<T> u;
			for (j = 0; j < columnlen; j++) u.push_back(v[i][j]);
			u0.push_back(u);
			M.v         = u0;
			M.rowlen    = 1;
			M.columnlen = i+1;
			return M;
		}

		Matrix<T> column(size_t i) const
		{
			size_t j;
			Matrix<T> M;
			std::vector<std::vector<T>> u0;
			std::vector<T> u;
			for (j = 0; j < rowlen; j++) {
				u.push_back(v[j][i]);
				u0.push_back(u);
				u.clear();
			}
			M.v     	  = u0;
			M.rowlen    = i+1;
			M.columnlen = 1;
			return M;
		}


	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const
		{
			bool flag = true;
			size_t i, j;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					if ((T)(i, j) != v[i][j]) {flag = false; break;}
				}
				if (!flag) break;
			}
			return flag;
		}

		template <class U>
		bool operator!=(const Matrix<U> &o) const
		{
			bool flag = true;
			int i, j;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					if (o(i, j) != v[i][j]) {flag = false; break;}
				}
				if (!flag) break;
			}
			return !flag;
		}
		//template <class U>
		Matrix operator-() const
		{
			int i, j;
			Matrix M = *this;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					M(i, j) = -M(i, j);
				}
			}
			return M;
		}

		template <class U>
		Matrix &operator+=(const Matrix<U> &o)
		{
			int i, j;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					v[i][j] = (T)(o(i, j) + v[i][j]);
				}
			}
			return *this;
		}

		template <class U>
		Matrix &operator-=(const Matrix<U> &o)
		{
			int i, j;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					v[i][j] = (T)(v[i][j] - o(i, j));
				}
			}
			return *this;
		}

		template <class U>
		Matrix &operator*=(const U &x)
		{
			int i, j;
			for (i = 0; i < rowlen; i++){
				for (j = 0; j < columnlen; j++){
					v[i][j] = (T)(x * v[i][j]);
				}
			}
			return *this;
		}

		Matrix tran() const //this is transition of matrix(a read-only function)
		{
			int i, j;
			std::vector<T> u;
			std::vector<std::vector<T>> u0;
			for (i = 0; i < columnlen; i++){
				for (j = 0; j < rowlen; j++){
					u.push_back(v[i][j]);
				}
				u0.push_back(u);
				u.clear();
			}
			Matrix<T> M = {columnlen, rowlen, u0};
			return M;
  		}

	public: // random-access iterator
		class iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag; // still don't know
			using value_type        = T;
			using pointer           = T *;
			using reference         = T &;
			using size_type         = size_t;
			using difference_type   = std::ptrdiff_t;

			iterator() = default;

			iterator(const iterator &) = default;

			iterator &operator=(const iterator &) = default;

		private:
			Matrix<T> * op;
			std::pair<size_t, size_t> pos;

		public:
			difference_type operator-(const iterator &o)
			{
				size_t row = (*op).rowLength();
				size_t col = (*op).columnLength();
				difference_type d;
				d = (pos.first-o.pos.first) * col + (pos.second - o.pos.second);
				return d;
			}

			iterator &operator+=(difference_type offset) //return reference to be left value
			{
				size_t row = (*op).rowLength(); size_t col = (*op).columnLength();
				if (pos.second + offset < col){
					pos = {pos.first, pos.second+offset};
				}
				else pos = {pos.first + (pos.second+offset)/col, (pos.second+offset)%col};
				return *this;
			}

			iterator operator+(difference_type offset) const
			{
				iterator ans = *this;
				size_t row = (*op).rowLength(); size_t col = (*op).columnLength();
				if (pos.second + offset < col){
					ans.pos = {pos.first, pos.second + offset};
				}
				else ans.pos = {pos.first + (pos.second+offset)/col, (pos.second+offset)%col};
				return ans;
			}

			iterator &operator-=(difference_type offset)
			{
				size_t row = (*op).rowLength(); size_t col = (*op).columnLength();
				if (pos.second - offset >= 0){
					pos = {pos.first, pos.second - offset};
				}
				else pos = {pos.first - (offset - pos.second)/col, (pos.second-offset)%col};
				return *this;
			}

			iterator operator-(difference_type offset) const
			{
				iterator ans = *this;
				size_t row = (*op).rowLength(); size_t col = (*op).columnLength();
				if (pos.second - offset >= 0){
					ans.pos = {pos.first, pos.second - offset};
				}
				else ans.pos = {pos.first -1- (offset - pos.second)/col, (pos.second-offset)%col};
				return ans;
			}

			iterator &operator++()//++t
			{
				size_t row = (*op).rowLength(); size_t col = (*op).columnLength();
				if (pos.second + 1 < col) pos = {pos.first, pos.second+1};
				else pos = {pos.first+1, 0};
				return *this;
			}

			iterator operator++(int)//t++
			{
				iterator now = *this;
				size_t col = (*op).columnLength();
				if (pos.second + 1 < col) pos = {pos.first, pos.second+1};
				else pos = {pos.first+1, 0};
				return now;
			}

			iterator &operator--()
			{
				size_t row = (*op).rowLength(); size_t col = (*op).columnLength();
				if (pos.second - 1 >= 0) pos = {pos.first, pos.second-1};
				else pos = {pos.first-1, col-1};
				return *this;
			}

			iterator operator--(int)
			{
				iterator now = *this;
				size_t col = (*op).columnLength();
				if (pos.second - 1 >= 0) pos = {pos.first, pos.second-1};
				else pos = {pos.first-1, col-1};
				return now;
			}

			reference operator*() const //ok
			{
				T tmp;
				Matrix M = *op;
				tmp = M(pos.first, pos.second);
				return tmp;
			}

			pointer operator->() const
			{
				T * ans;
				Matrix M = *op;
				*ans = M(pos.first, pos.second);
				return ans;
			}

			bool operator==(const iterator &o) const //ok
			{
				return(pos == o.pos);
			}

			bool operator!=(const iterator &o) const //ok
			{
				return(pos != o.pos);
			}
			friend iterator Matrix::begin();
			friend iterator Matrix::end();
		};

		iterator begin()
		{
			iterator a;
			Matrix M = *this;
			a.op = &M; //maybe there are some problems...
			a.pos = {0, 0};
			return a;
		}

		iterator end()
		{
			iterator b;
			b.pos = {rowlen-1, columnlen-1};
			return b;
		}

		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
		{

        }
	};

}

//
namespace sjtu
{
	template <class T, class U> //here is calculating between 2 different class
	auto operator*(const Matrix<T> &mat, const U &x)->Matrix<decltype(T() * U())>
	{
		int i, j;
		std::vector<decltype(T() * U())> u1;
		std::vector<std::vector<decltype(T() * U())>> u0;
		for (i = 0; i < mat.rowLength(); i++){
			for (j = 0; j < mat.columnLength(); j++){
				u1.push_back(x * mat(i, j));
			}
			u0.push_back(u1);
			u1.clear();
		}
		Matrix<decltype(T() * U())> ans = {mat.rowLength(), mat.columnLength(), u0};
		return ans;
	}

	template <class T, class U>
	auto operator*(const U &x, const Matrix<T> &mat)->Matrix<decltype(T() * U())>
	{
		int i, j;
		std::vector<decltype(T() * U())> u1;
		std::vector<std::vector<decltype(T() * U())>> u0;
		for (i = 0; i < mat.rowLength(); i++){
			for (j = 0; j < mat.columnLength(); j++){
				u1.push_back(x * mat(i, j));
			}
			u0.push_back(u1);
			u1.clear();
		}
		Matrix<decltype(T() * U())> ans = {mat.rowLength(), mat.columnLength(), u0};
		return ans;
	}

	template <class U, class V>
	auto operator*(const Matrix<U> &a, const Matrix<V> &b)->Matrix<decltype(U() * V())>
	{
		int i, j, k;
		std::vector<decltype(V() * U())> u1;
		std::vector<std::vector<decltype(U() * V())>> u0;
		for (i = 0; i < a.rowLength(); i++){
			for (j = 0; j < b.columnLength(); j++){
				decltype(U() * V()) tmp = 0;
				for (k = 0; k < a.columnLength(); k++){
					tmp += a(i, k) * b(k, j);
				}
				u1.push_back(tmp);
			}
			u0.push_back(u1);
			u1.clear();
		}
		Matrix<decltype(U() * V())> ans = {a.rowLength(), b.columnLength(), u0};
		return ans;
	}

	template <class U, class V>
	auto operator+(const Matrix<U> &a, const Matrix<V> &b)->Matrix<decltype(U()+V())>
	{
		int i, j;
		std::vector<decltype(V() + U())> u1;
		std::vector<std::vector<decltype(U() + V())>> u0;
		for (i = 0; i < a.rowLength(); i++){
			for (j = 0; j < a.columnLength(); j++){
				u1.push_back(a(i, j) + b(i, j));
			}
			u0.push_back(u1);
			u1.clear();
		}
		Matrix<decltype(U() + V())> ans = {a.rowLength(), a.columnLength(), u0};
		return ans;
	}

	template <class U, class V>
	auto operator-(const Matrix<U> &a, const Matrix<V> &b)->Matrix<decltype(U() - V())>
	{
		int i, j;
		std::vector<decltype(U() - V())> u1;
		std::vector<std::vector<decltype(U() - V())>> u0;
		for (i = 0; i < a.rowLength(); i++){
			for (j = 0; j < a.columnLength(); j++){
				u1.push_back(a(i, j) - b(i, j));
			}
			u0.push_back(u1);
			u1.clear();
		}
		Matrix<decltype(U() - V())> ans = {a.rowLength(), a.columnLength(), u0};
		return ans;
	}

}

#endif //SJTU_MATRIX_HPP
