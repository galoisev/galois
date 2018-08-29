#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class Matrice{
public:
  int m,n;
  T **x;
  Matrice(int mm,int nn);  
  ~Matrice(){
    for(int i=0;i<m;i++)
      delete[]x[i];
    delete[]x;
  }
   Matrice(const Matrice<T>& mat):m(mat.m),n(mat.n){
     allocTab();
     for(int i=0;i<m;i++)
       for(int j=0;j<n;j++)
	 x[i][j] = mat.x[i][j];
   }   
   Matrice &operator=(const Matrice<T>& mat){
     if(this == &mat){
       return(*this);
     }
     else
     {
       if((m != mat.m)&&(n != mat.n)){
	 this->~Matrice();
	 m = mat.m;
	 n = mat.n;
	 allocTab();
       }
     }     
     for(int i=0;i<m;i++)
       for(int j=0;j<n;j++)
     return(*this);
   }
   
   
   Matrice operator+(const Matrice<T>mat){
     int m = mat.m;
     int n = mat.n;
     Matrice<T>temp(m,n);
     for(int i=0;i<m;i++){
       for(int j=0;j<n;j++){
	 temp.x[i][j] = x[i][j]+mat.x[i][j];
       }
     }       
     return temp;
   }

   
   
   T &operator()(int i,int j){
     assert((i>=0 && i<m) && (j>=0 && j<n));
     return x[i][j];
   }
   
   void setCoef(int i,int j,T val){
     assert((i>=0 && i<m) && (j>=0 && j<n));
     x[i][j] = val;
   }
   
   
   
   
   
   void allocTab(){
     x = new T*[m];
     for(int i=0;i<m;i++)
       x[i] = new T[n];
   }
   
   void affichage(){
     cout<<endl;
     for(int i=0;i<m;i++){
       for(int j=0;j<n;j++){
	 cout<<"\t"<<this->operator()(i,j)<<' ';
       }
       cout<<endl;
     }     
   }
  
};

template<class T>
Matrice<T>::Matrice(int mm,int nn):m(mm),n(nn){
  allocTab();
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      x[i][j]=0;
}




