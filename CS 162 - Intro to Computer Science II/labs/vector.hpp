#include <stdlib.h>
#include <stdexcept>
template <class T>
class vector{
	private:
		T *v;
		int s;
	public:
		vector(){
			s=0;
			v=NULL;
		}
		
		~vector(){
			delete [] v;
		}

		vector(vector<T> &other){
			s = other.s;
			v = new T[other.s];
			for(int i = 0; i < other.s; i++){
				v[i] = other.v[i];
			}
		}

		void operator=(vector<T> &other){
			s = other.s;
			if(v != NULL){
				delete v;
			}
			v = new T[other.s];
			for(int i = 0; i < other.s; i++){
				v[i] = other.v[i];
			}
		}
		
		T operator[](int i){
			return v[i];
		}

		T at(int i){
			if(i < 0 || i >= s)
				throw std::out_of_range("out of  my vector bounds");
			if(i >= 0 && i < s)
				return v[i];
		}

		int size(){
			return s;
		}

		void push_back(T ele){
			T *temp;
			temp = new T[++s];
			for(int i=0; i<s-1; i++)
				temp[i]=v[i];
			delete [] v;
			v=temp;
			v[s-1]=ele;
		}
};
