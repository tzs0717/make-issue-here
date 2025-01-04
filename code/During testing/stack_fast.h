/*
MIT License

Copyright (c)2024 make-cpp-new-stl-team.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef STACKFAST
#define STACKFAST
#include<memory>
#include<vector>
#include<algorithm>
#include<stdexcept>
namespace new_stl{
	template<typename T>
	class stack_fast{
	private:
		std::vector<T>v;
		size_t r;
	public:
		~stack_fast()=default;
		stack_fast(const stack_fast&)=default;
		stack_fast& operator=(const stack_fast&)=default;
		stack_fast(stack_fast&&)=default;
		stack_fast& operator=(stack_fast&&)=default;
		inline stack_fast(){
			r=0;
			v.reserve(512/sizeof(T));
		}
		inline stack_fast(const std::vector<T>& cl){
			r=cl.size();
			v=cl;
			v.reserve((v.size()+512)/sizeof(T));
		}
		inline void push(T in){
			v.push_back(in);
			r++;
		}
		inline void pop(){
			if(!r){
				throw std::out_of_range("stack is empty.");
			}
			r--;
			if(v.size()-r/sizeof(T)>8192){
				v.resize(r);
				v.shrink_to_fit();
				v.reserve(r+512/sizeof(T));
			}
		}
		inline size_t size()const{
			return r;
		}
		inline T top()const{
			if(!r){
				throw std::out_of_range("stack is empty.");
			}
			return v[r-1];
		}
		inline bool empty()const{
			return !r;
		}
	};
}
#endif
