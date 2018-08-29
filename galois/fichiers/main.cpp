#include "smef.h"
#include "Matrice.h"
#include <cmath>

using namespace std;


class vect{
  friend ostream& operator<<(ostream& f,const vect& v){
    f << v.x << ' ' << v.y;
    return f;
  }
  friend istream& operator>>(istream& f,vect& v){
    f >> v.x >> v.y;
    return f;
  }
public:
  R x,y;
  vect(){}
  vect(R xx,R yy):x(xx),y(yy){}
  vect(vect a,vect b):x(b.x-a.x),y(b.y-a.y){}
  vect perp(){return vect(-y,x);}
  R operator,(vect P){
    return(x*P.x+y*P.y);
  }
  R operator^(vect P){
    return(x*P.y-y*P.x);
  }
  vect operator/(R c)const{
    return vect(x/c,y/c);
  }
  vect operator*(R c)const{
    return vect(x*c,y*c);
  }

};


class etiq{
  friend ostream& operator<<(ostream& f,const etiq& e){
    f << e.r ;
    return f;
  }
  friend istream& operator>>(istream& f,etiq& e){
    f >> e.r;
    return f;
  }
public:
  int r,ref;
  etiq(){}
  etiq(int rr,int rref):r(rr),ref(rref){}
};


class vert:public vect,public etiq{
  friend ostream& operator<<(ostream& f,const vert& ve){
    f << ve.r << ' ' << ve.x << ',' << ve.y << ',' << ve.ref;
    return f;
  }
  friend istream& operator>>(istream& f,vert& ve){
    f >> ve.r >> ve.x >> ve.y >> ve.ref;
    return f;
  }
public:
  vert(){}
  vert(etiq e,vect v):etiq(e),vect(v){} 
};


// class bound:public etiq{
// public:
//   vert*vertices[2];
//   bound(){}
//   void set(vert* v0,int eti,int i0,int i1int rft){
//   }
//   R length(){
//     vect A = *vertices[0];
//     vect B = *vertices[1];
//     vect AB = vect(A,B);
//     return sqrt(AB.operator,(AB));
//   }
// };


class tria:public etiq{
public:
  int l,i0,i1,i2,rft;
  vert* vertices[3];
  R aire;
  tria(){}
  tria(int ll,int i00,int i11,int i22,int rftt,R S):l(ll),i0(i00),i1(i11),i2(i22),rft(rftt){}
  
  vert& operator[](int i){
    assert(i>=0 && i<3);
    return *vertices[i];//evaluation des pointeurs
  }
  
  void set(vert* v0,int eti,int i0,int i1,int i2,int rft){
    vertices[0]= v0+i0;
    vertices[1]= v0+i1;
    vertices[2]= v0+i2;    
    r=eti;
    ref=rft;    
    vert A = *vertices[0];
    vert B = *vertices[1];
    vert C = *vertices[2];
    vect AB = vect(A,B);
    vect AC = vect(A,C);
    aire=0.5*(AB^AC);
  }
  
  tria &operator=(const tria& t){
     for(int i=0;i<10;i++){
      l = t.l;
      i0= t.i0;
      i1= t.i1;
      i2= t.i2;
      rft= t.rft; 
      aire = t.aire;
    }
    return (*this);
  }
  
  
  //arete opposee au cote i
  vect Edge(int i)const{
    assert(i>=0 && i<3);
    return vect(*vertices[(i+1)%3],*vertices[(i+2)%3]);  
  }
  
//   la normale au sommet i
  vect normale(int i)const{
    assert(i>=0 && i<3);
    vect E = Edge(i);
    return E.perp()/(2*aire);    
  }
  
};



 Matrice<R> matElementaire(const tria& t){
   Matrice<R> Kel(3,3);
   double s(0.0);
   for(int i=0;i<3;i++){
     double axi,ayi;
     axi = t.normale(i).x;
     ayi = t.normale(i).y;
     for(int j=0;j<3;j++){
       double axj,ayj;
       axj = t.normale(j).x;
       ayj = t.normale(j).y;
       s += axi*axj+ayi*ayj;
       Kel.setCoef(i,j,s);
     }
     
   }
   return Kel;
 }

 
 
 
 
 
 
 
 

int main(){
  
  int niter=0;
  R delta = 1000.0;
  
  
  
  
  bool test;
  printf("\n\n");
  printf("\tTests sur la M.E.F 2D basee sur le modele celle issue de Matlab.\n\n");
  printf("\t ( Copyright, ENSX. Alls rights Reserved, April 2014. )\n\n");
//   ******************************************************************
  test=false;
  const char*filename = "maillage.amdba";
//   Mesh mesh(filename);
  test=true;
 
  //vect*v=new vect[mesh.ns];
  vect v;
  etiq e;
  vert ve;
  fstream ff(filename);
  int is,it,ib;
  ff>>is>>it>>ib;
  
  cout<<is<<','<<it<<','<<ib<<endl;
  
  vert* vt;
  vt = new vert[is];
  for(int i=0;i<is;i++){ 
    //ff >> ve.r >> ve.x >> ve.y >> ve.ref; 
    ff>>vt[i].r >> vt[i].x >> vt[i].y >> vt[i].ref;
    vt[i] = ve;
    cout << vt[i].r <<','<< vt[i].x <<','<< vt[i].y <<','<< vt[i].ref << endl;
  }
  
  

  
  return 0;

  
}
