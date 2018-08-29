#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <assert.h>
#include <stdio.h>


using namespace std;


typedef double R;


class R2{
  friend ostream& operator<<(ostream& f,const R2& v){
    f << v.x << ' ' << v.y;
    return f;
  }
  friend istream& operator>>(istream& f,R2& v){
    f >> v.x >> v.y;
    return f;
  }
public:
  R x,y;
  R2(){}
  R2(R xx,R yy):x(xx),y(yy){}
};


class etiquette{
  friend ostream& operator<<(ostream& f,const etiquette& e){
    f << e.r ;
    return f;
  }
  friend istream& operator>>(istream& f,etiquette& e){
    f >> e.r;
    return f;
  }
public:
  int r,ref;
  etiquette(){}
  etiquette(int rr,int rref):r(rr),ref(rref){}
};


class Vertex:public R2,public etiquette{
  friend ostream& operator<<(ostream& f,const Vertex& ve){
    f << ve.r << ' ' << ve.x << ',' << ve.y << ',' << ve.ref;
    return f;
  }
  friend istream& operator>>(istream& f,Vertex& ve){
    f >> ve.r >> ve.x >> ve.y >> ve.ref;
    return f;
  }
public:
  Vertex(){}
  Vertex(etiquette e,R2 v):etiquette(e),R2(v){}  
};





class Mesh{
public:
  int ns,nt;
  const char*filename;
  Vertex vertices;
  
  Mesh(const char*nomfichier):filename(nomfichier){
    fstream f(filename);
    if(!f){
      cerr<<"\tErreur a l''ouverture du fichier !"<<endl;
      exit(1);
    }
    f >> ns >> nt;
    cout<<"\t***********************"<<endl;
    cout<<"\t Nbre de sommet:"<<ns<<endl;
    cout<<"\t Nbre de triangle:"<<nt<<endl;
    cout<<"\t***********************"<<endl;

   
    for(int i=0;i<ns;i++){ 
      f >> vertices.r >> vertices.x >> vertices.y >> vertices.ref;
      cout << vertices.r <<','<< vertices.x <<','<< vertices.y << ',' << vertices.ref << endl;
    }


  


  
    f.close();
  }

};
