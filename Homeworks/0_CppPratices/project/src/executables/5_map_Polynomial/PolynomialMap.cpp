#include "PolynomialMap.h"

#include <assert.h>
#include<fstream>
#include<iostream>
#define EPSILON 1.0E-10
using namespace std;

PolynomialMap::PolynomialMap(const std::string& file) {
	ReadFromFile(file);
}

PolynomialMap::PolynomialMap(const std::vector<int>& deg, const std::vector<double>& cof) {
	assert(deg.size() == cof.size());

	for (int i = 0; i != deg.size();++i) {
		m_Polynomial[deg[i]] += cof[i];
	}
}

PolynomialMap::PolynomialMap(const double* cof, const int* deg, int n) {
	for (int i = 0; i < n; i++)
		coff(deg[i]) = cof[i];
}

PolynomialMap::PolynomialMap(const PolynomialMap& other) {
	m_Polynomial = other.m_Polynomial;

}

double PolynomialMap::coff(int i) const{
	auto target = m_Polynomial.find(i);
	if (target == m_Polynomial.end())
		return 0.;

	return target->second;
}

double& PolynomialMap::coff(int i) {
	return m_Polynomial[i];
}

void PolynomialMap::compress() {
	auto itr = m_Polynomial.begin();
	while (itr!=m_Polynomial.end())
	{
		if (itr->second < EPSILON) {
			itr = m_Polynomial.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

PolynomialMap PolynomialMap::operator+(const PolynomialMap& right) const {
	PolynomialMap poly(right);
	for (const auto& term : m_Polynomial) {
		poly.m_Polynomial[term.first] += term.second;
	}
	poly.compress();
	return poly;
}

PolynomialMap PolynomialMap::operator-(const PolynomialMap& right) const {
	PolynomialMap poly(right);
	for (const auto& term : m_Polynomial)
		poly.coff(term.first) -= term.second;

	poly.compress();
	return poly;
}

PolynomialMap PolynomialMap::operator*(const PolynomialMap& right) const {
	PolynomialMap poly;
	for (const auto& term1 : m_Polynomial) {
		for (const auto& term2 : right.m_Polynomial) {
			int deg = term1.first + term2.first;
			double cof = term1.second * term2.second;
			poly.coff(deg) += cof;
		}
	}
	poly.compress();
	return poly;
}

PolynomialMap& PolynomialMap::operator=(const PolynomialMap& right) {
	m_Polynomial = right.m_Polynomial;
	return *this;
}


void PolynomialMap::Print() const {
	auto itr = m_Polynomial.begin();
	if (itr == m_Polynomial.end()) {
		cout << "0" << endl;
		return;
	}

	for (; itr != m_Polynomial.end(); itr++) {
		if (itr != m_Polynomial.begin()) {
			cout << " ";
			if (itr->second > 0)
				cout << "+";
		}

		cout << itr->second;

		if (itr->first > 0)
			cout << "x^" << itr->first;
	}
	cout << endl;
}

bool PolynomialMap::ReadFromFile(const string& file)
{
	m_Polynomial.clear();

	ifstream inp;
	inp.open(file.c_str());
	if (!inp.is_open()) {
		cout << "ERROR::PolynomialList::ReadFromFile:" << endl
			<< "\t" << "file [" << file << "] opens failed" << endl;
		return false;
	}

	char ch;
	int n;
	inp >> ch;
	inp >> n;
	for (int i = 0; i < n; i++) {
		int deg;
		double cof;
		inp >> deg;
		inp >> cof;
		coff(deg) = cof;
	}

	inp.close();

	return true;
}
