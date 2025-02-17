//==========================================================
// Author: Xin Qu
// DATE : 2019-12-10
//==========================================================
#ifndef DFTU_Yukawa_H
#define DFTU_Yukawa_H

#include <vector>

using namespace std;

//==========================================================
// CLASS :
// NAME : DFTU_Yukawa 
//==========================================================
namespace ModuleDFTU{
class DFTU_Yukawa
{
public:
    DFTU_Yukawa();                      // constructor 
    ~DFTU_Yukawa();                     // deconstructor

    void cal_slater_Fk(const int L, const int T); //L:angular momnet, T:atom type   
    void cal_yukawa_lambda(double** rho);
    void cal_slater_UJ(double** rho);

    double spherical_Bessel(const int k, const double r, const double lambda);
    double spherical_Hankel(const int k, const double r, const double lambda);

    //void cal_unscreened_slater_Fk(const int L, const int T); //L:angular momnet, T:atom type
    //void cal_slater_Vsc(const int T, const int L);

    bool Yukawa;         //1:use Yukawa potential; 0: do not use Yukawa potential 
    double lambda;       //the parameter in Yukawa potential
    int cal_type;        //1:dftu_tpye=1, dc=1; 2:dftu_type=1, dc=2; 3:dftu_tpye=2, dc=1; 4:dftu_tpye=2, dc=2; 
    int dc;              //dc (type of double_counting)
    double *U;           //U (Hubbard parameter U)
    double *J;           //J (Hund parameter J)
    int *orbital_corr;   //
    int omc;
    int dftu_type;
    int double_counting;

    //std::vector<std::vector<matrix>> Vsc; //Vsc[T][N](i,j)
    std::vector<std::vector<std::vector<std::vector<double>>>> Fk; //slater integral:Fk[T][L][N][k]
    std::vector<std::vector<std::vector<double>>> U_Yukawa;   //U_Yukawa[T][L][N]
    std::vector<std::vector<std::vector<double>>> J_Yukawa;   //J_Yukawa[T][L][N]

    double Nval;         //Total nmuber of valence electrons of the system 
    double Nc;           //Total nmuber of correlated electrons of the system 

};
}
#endif