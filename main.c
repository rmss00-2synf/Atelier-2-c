#include <stdio.h>
#include <stdlib.h>

typedef struct Poly
{
    int exp;
    float coef;
    struct Poly *suivant;
} Poly;

// 1

Poly *SaisieMonome(int e, float coeff)
{
    Poly *P;
    if (!coeff)
        return NULL;
    P = malloc(sizeof(Poly));
    P->coef = coeff;
    P->exp = e;
    P->suivant = NULL;
    return P;
}

// 2

int VeriExp(Poly *P, int e)
{
    for (; P && P->exp != e; P = P->suivant)
        ;
    if (P)
        return 1;
    return 0;
}

Poly *AjoutMonome(Poly *P, int e, float coeff)
{
    Poly *Nv;
    Nv = SaisieMonome(e, coeff);
    if (!Nv)
        return P;
    if (!P)
        return Nv;
    Poly *p, *q;
    if (!VeriExp(P, Nv->exp))
    {
        if (Nv->exp > P->exp)
        {
            Nv->suivant = P;
            return Nv;
        }
        for (q = P, p = P->suivant; p && p->exp > Nv->exp; q = p, p = p->suivant)
            ;
        if (p)
        {
            q->suivant = Nv;
            Nv->suivant = p;
            return P;
        }
        q->suivant = Nv;
        return P;
    }
    for (p = P; p->exp != Nv->exp; p = p->suivant)
        ;
    p->coef += Nv->coef;
    return P;
}

// 3

// Poly *MonomeParamettre(int e, float coeff)
// {
//     Poly *Nv;
//     Nv = malloc(sizeof(Poly));
//     Nv->coef = coeff;
//     Nv->exp = e;
//     return Nv;
// }

Poly *CopiePoly(Poly *P)
{
    Poly *copie = NULL;
    for (; P; P = P->suivant)
        copie = AjoutMonome(copie, P->exp, P->coef);
    return copie;
}

// 4

Poly *SommePoly(Poly *P1, Poly *P2)
{
    Poly *P = NULL;
    P = CopiePoly(P1);
    for (; P2; P2 = P2->suivant)
        P = AjoutMonome(P, P2->exp, P2->coef);
    return P;
}

// 5
Poly *DeriveMono(Poly *M)
{
    Poly *Nv;
    Nv = SaisieMonome(M->exp, M->coef);
    if (M->exp = 0)
        return NULL;
    Nv->coef *= Nv->exp;
    Nv->exp--;
    return Nv;
}
Poly *DerivePoly(Poly *P)
{
    Poly *Derive = NULL, *cp = NULL;
    for (; P; P = P->suivant)
    {
        cp = DeriveMono(P);
        if (cp)
            Derive = AjoutMonome(Derive, cp->exp, cp->coef);
    }
    return Derive;
}

// 6

void AffichePoly(Poly *P)
{
    for (; P; P = P->suivant)
    {
        if (P->exp)
            printf("(%.2fx^%d) +", P->coef, P->exp);
        else
            printf(" %.3f", P->coef);
    }
    puts("\n==================================================================");
}

int main(int argc, char const *argv[])
{
    Poly *P = NULL, *Q = NULL;
    P = AjoutMonome(P, 4, 5);
    P = AjoutMonome(P, 2, 2);
    P = AjoutMonome(P, 0, 3);
    AffichePoly(P);
    P = AjoutMonome(P, 3, 4);
    AffichePoly(P);
    // Q = DerivePoly(P);
    AffichePoly(DerivePoly(P));

    return 0;
}
