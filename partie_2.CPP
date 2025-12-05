#ifndef PARTIE_2_H_INCLUDED
#define PARTIE_2_H_INCLUDED
 using namespace std;
#include <vector>// for dynamic tables
#include <iostream>//input and output values
#include <cmath> // help to  perform mathematics operation
#include<iomanip>//help for setprecisssion format

template<typename T> //do not need the data type
class BinaryTree {
private:
    int _depth;
    vector<vector<T>> _tree;

public:
    //constructeur
    explicit BinaryTree(int depth = 0) : _depth(depth) {
        //explicit restrict some binary conversion automatically
        setDepth(depth); //ON utilise setDepth pour initianiliser proprement
       }
    
    //modifie la profondeur et reconstruit l'arbre
    void setDepth(int depth) {
      if (depth < 0){
         cout<<"profondeur negative."\n;
         return;
      }
      _depth = depth;
      _tree.clear(); // vide l'arbre existant
      for (int n = 0; n <= depth; ++n) {
        _tree.push_back(vector<T>(n + 1)); // ajoute un niveau avec n+1 éléments
    }
}
    //definir la valeur d'un noeud au niveau n, position i (i de 0 à n)
    void setNode(int n, int i, const T& value) {
        // Vérifie que le niveau 'n' et la position 'i' sont valides
        if (n < 0 || n > _depth || i < 0 || i > n){
            cout<<"setNode :indices invalides (" << n <<","<< i <<")\n";
            return;
        }
          _tree[n][i] = value; // Place la valeur 'value' dans le noeud correspondant
        }
        
    //accede à un noeud
    T getNode(int n, int i) const {
    // Vérifie que le niveau et la position sont valides
       if (n < 0 || n > _depth || i < 0 || i > n) {
        cout << "Indices invalides !" << endl;
        return T(); // retourne une valeur par défaut du type T
    }
    // Retourne la valeur du noeud
      return _tree[n][i];
}
    // affichage centré
    void display() const {
        if(_depth < 0 ) return;
            for (int n = 0; n <= _depth; ++n) { //parcour chaque niveau de l'arbre de 0 jusqu'à _depth
               for (int s = 0; s < (_depth - n); ++s) cout << "   "; //centré l'arbre visuellement
                 for (int i = 0; i <= n; ++i) { // parcour chaque noeud du niveau n
                   cout << fixed << setprecision(4) << _tree[n][i]; //fixed et setprecision (4) sont là pour formater les nombres flottants
                      if (i < n) cout << "   ";
        }
        cout << '\n'; //passe à la ligne suivante aprés chaque niveau
    }
}

    int depth() const {
      return _depth;
      }





#endif // PARTIE_2_H_INCLUDED