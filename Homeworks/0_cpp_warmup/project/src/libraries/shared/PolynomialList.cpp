#include "PolynomialList.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <assert.h>
#include <algorithm>

using namespace std;

#define lowerBound 1.0e-10

PolynomialList::PolynomialList(const PolynomialList& other) {
    m_Polynomial = other.m_Polynomial;
}

PolynomialList::PolynomialList(const string& file) {
    ReadFromFile(file);
}

PolynomialList::PolynomialList(const double* cof, const int* deg, int n) {
    for (int i = 0; i < n; i++) {
        AddOneTerm(Term(deg[i], cof[i]));
    }
}

PolynomialList::PolynomialList(const vector<int>& deg, const vector<double>& cof) {
    assert(deg.size() == cof.size());

    for (size_t i = 0; i < deg.size(); i++) {
        AddOneTerm(Term(deg[i], cof[i]));
    }
}

// get coefficient of x^i
double PolynomialList::coff(int i) const {
    for (const Term& Term : m_Polynomial) {
        if (Term.deg < i) 
            break;
        if (Term.deg == i)
            return Term.cof;
    }
    return 0.0f; // you should return a correct value
}

// get reference of coefficient of x^i, if not exist then create it
double& PolynomialList::coff(int i) {
    return AddOneTerm(Term(i, 0)).cof;
}

// remove terms with zero or near zero cofficient
void PolynomialList::compress() {
    auto itr = m_Polynomial.begin();
    while (itr != m_Polynomial.end()) {
        if (fabs((*itr).cof) < lowerBound) {
            // erase will remove the term that itr points to and return a new itr points to the next term
            itr = m_Polynomial.erase(itr);
        } else {
            itr++;
        }
    }
}

PolynomialList PolynomialList::operator+(const PolynomialList& right) const {
    PolynomialList new_poly(*this);
    for (const Term& term : right.m_Polynomial) {
        new_poly.AddOneTerm(term);
    }
    new_poly.compress();
    return new_poly;
}

PolynomialList PolynomialList::operator-(const PolynomialList& right) const {
    PolynomialList new_poly(*this);
    for (const Term& term : right.m_Polynomial) {
        new_poly.AddOneTerm(Term(term.deg, -term.cof));
    }
    new_poly.compress();
    return new_poly;
}

PolynomialList PolynomialList::operator*(const PolynomialList& right) const {
    PolynomialList new_poly;
    for (const Term& term_left : m_Polynomial) {
        for (const Term& term_right : right.m_Polynomial) {
            new_poly.AddOneTerm(Term(term_left.deg + term_right.deg, term_left.cof * term_right.cof));
        }
    }
    new_poly.compress();
    return new_poly;
}

PolynomialList& PolynomialList::operator=(const PolynomialList& right) {
    m_Polynomial = right.m_Polynomial;
    return *this;
}

void PolynomialList::Print() const {
    auto itr = m_Polynomial.begin();
    while (itr != m_Polynomial.end()) {
        if (itr != m_Polynomial.begin()) {
            cout << ' ';
            if (itr->cof > 0) {
                cout << '+';
            }
        }

        cout << itr->cof << "x^" << itr->deg;
        itr++;
    }
    cout << endl;
}

bool PolynomialList::ReadFromFile(const string& file) {
    m_Polynomial.clear();

    ifstream f(file);
    assert(f.is_open());

    char trash;
    int num;
    f >> trash; // read P
    f >> num; // read first number(line counts)

    for (int i = 0; i < num; i++) {
        Term new_term;
        f >> new_term.deg >> new_term.cof;

        AddOneTerm(new_term);
    }

    f.close();
    return true;
}

PolynomialList::Term& PolynomialList::AddOneTerm(const Term& term) {
    auto itr = m_Polynomial.begin();
    while (itr != m_Polynomial.end()) {
        if (itr->deg < term.deg) {
            break;
        } else if (itr->deg == term.deg) {
            itr->cof += term.cof;
            return *itr;
        }
        itr++;
    }

    // insert will insert the term before the term that itr points to 
    m_Polynomial.insert(itr, term);
    return *(--itr);
}
