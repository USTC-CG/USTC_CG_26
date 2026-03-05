#include "PolynomialMap.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <assert.h>
#include <algorithm>

using namespace std;

#define lowerBound 1.0e-10

PolynomialMap::PolynomialMap(const PolynomialMap& other) {
    m_Polynomial = other.m_Polynomial;
}

PolynomialMap::PolynomialMap(const string& file) {
    ReadFromFile(file);
}

PolynomialMap::PolynomialMap(const double* cof, const int* deg, int n) {
    for (int i = 0; i < n; i++) {
		coff(deg[i]) = cof[i];
	}
}

PolynomialMap::PolynomialMap(const vector<int>& deg, const vector<double>& cof) {
    assert(deg.size() == cof.size());

    for (size_t i = 0; i < deg.size(); i++) {
		coff(deg[i]) = cof[i];
    }
}

double PolynomialMap::coff(int i) const
{
    auto target = m_Polynomial.find(i);
	// if not found, target will be m_Polynomial.end()
    if (target == m_Polynomial.end())
        return 0.;

    return target->second;
}

// get reference of coefficient of x^i, if not exist then create it
double& PolynomialMap::coff(int i) {
    return m_Polynomial[i];
}

// remove terms with zero or near zero cofficient
void PolynomialMap::compress() {
	map<int, double> tempPoly = m_Polynomial;
	m_Polynomial.clear();
	for (const auto& term : tempPoly) {
		if (fabs(term.second) > lowerBound) {
			coff(term.first) = term.second;
		}
	}
}

PolynomialMap PolynomialMap::operator+(const PolynomialMap& right) const {
    PolynomialMap new_poly(right);
    for (const auto& term : m_Polynomial)
        new_poly.coff(term.first) += term.second;

    new_poly.compress();
    return new_poly;
}

PolynomialMap PolynomialMap::operator-(const PolynomialMap& right) const {
    PolynomialMap new_poly(right);
    for (const auto& term : m_Polynomial)
        new_poly.coff(term.first) -= term.second;

    new_poly.compress();
    return new_poly;
}

PolynomialMap PolynomialMap::operator*(const PolynomialMap& right) const {
    PolynomialMap new_poly;
	for (const auto& term_left : m_Polynomial) {
		for (const auto& term_right : right.m_Polynomial) {
			int deg = term_left.first + term_right.first;
			double coff = term_left.second * term_right.second;
			new_poly.coff(deg) += coff;
		}
	}
    return new_poly;
}

PolynomialMap& PolynomialMap::operator=(const PolynomialMap& right) {
    m_Polynomial = right.m_Polynomial;
    return *this;
}

void PolynomialMap::Print() const {
    auto itr = m_Polynomial.begin();
    while (itr != m_Polynomial.end()) {
        if (itr != m_Polynomial.begin()) {
            cout << ' ';
            if (itr->second > 0) {
                cout << '+';
            }
        }

        cout << itr->second << "x^" << itr->first;
        itr++;
    }
    cout << endl;
}

bool PolynomialMap::ReadFromFile(const string& file) {
    m_Polynomial.clear();

    ifstream f(file);
    assert(f.is_open());

    char trash;
    int num;
    f >> trash; // read P
    f >> num; // read first number(line counts)

    for (int i = 0; i < num; i++) {
		int deg;
		double cof;

		f >> deg >> cof;
		coff(deg) = cof;
    }

    f.close();
    return true;
}