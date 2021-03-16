/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 10:38:10 by matrus            #+#    #+#             */
/*   Updated: 2020/11/28 10:38:12 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include "../includes/vector.hpp"
#include <vector>
#include <string>
#include <stdexcept>

template <class T>
void	checkIfVectorsAreEqual(ft::vector<T> & f, std::vector<T> & s) {
	EXPECT_EQ(f.size(), s.size());
	EXPECT_EQ(f.empty(), s.empty());
	EXPECT_GE(f.capacity(), f.size());
	EXPECT_GE(s.capacity(), s.size());

	typename  ft::vector<T>::iterator itF = f.begin();
	typename  ft::vector<T>::iterator itFe = f.end();
	typename std::vector<T>::iterator itS = s.begin();
	typename std::vector<T>::iterator itSe = s.end();

	for (; itS != itSe; ) {
		EXPECT_EQ(*itS++, *itF++);
	}
	EXPECT_EQ(itF, itFe);
}

class VectorConstructorTest : public ::testing::Test {
protected:
	virtual void SetUp() { }
};

TEST_F(VectorConstructorTest, defaultConstructor) {
	ft::vector<int> f;
	std::vector<int> s;
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorConstructorTest, valueConstructor1) {
	ft::vector<int> f(60);
	std::vector<int> s(60);
	checkIfVectorsAreEqual(f, s);
	ft::vector<std::string> f1(60);
	std::vector<std::string> s1(60);
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(VectorConstructorTest, valueConstructor2) {
	ft::vector<int> f(60,5);
	std::vector<int> s(60, 5);
	checkIfVectorsAreEqual(f, s);
	ft::vector<std::string> f1(60, "Hello World!");
	std::vector<std::string> s1(60, "Hello World!");
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(VectorConstructorTest, rangeConstructor) {
	std::vector<int> sample;
	sample.push_back(54);
	sample.push_back(42);
	sample.push_back(21);
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorConstructorTest, copyConstructor) {
	ft::vector<std::string> f1(60, "Hello World!");
	std::vector<std::string> s1(60, "Hello World!");
	ft::vector<std::string> f2(f1);
	std::vector<std::string> s2(s1);
	checkIfVectorsAreEqual(f2, s2);
	ft::vector<std::string> f3 = f2;
	std::vector<std::string> s3 = s2;
	checkIfVectorsAreEqual(f3, s3);
}

template <typename itFt, typename itFtEnd, typename itStd, typename itStdEnd>
void checkVectorsAreEqualIt(itFt itF, itFtEnd itFe, itStd itS, itStdEnd itSe) {
	for (; itS != itSe; ) {
		EXPECT_EQ(*itS++, *itF++);
	}
	EXPECT_EQ(itF, itFe);
};

template <typename ftIter, typename stdIter, typename ftIterTmp, typename stdIterTmp>
void	vectorIteratorTest(ftIter & fIt, ftIter & fIte, ftIterTmp & ftmpIt,
						 stdIter & sIt, stdIter & sIte, stdIterTmp & stmpIt)
{
	ftmpIt = fIt;
	stmpIt = sIt;
	EXPECT_EQ(ftmpIt, fIt) << "Assignation or operator== fails.";
	EXPECT_EQ(stmpIt, sIt);
	EXPECT_GE(fIt, ftmpIt) << "operator>= fails.";
	EXPECT_GE(sIt, stmpIt);
	EXPECT_LE(ftmpIt, fIt) << "operator<= fails.";
	EXPECT_LE(stmpIt, sIt);

	ASSERT_EQ(*fIt, *sIt) << "Dereference fails.";

	++fIt;
	++sIt;
	EXPECT_EQ(*fIt, *sIt) << "++operator fails.";

	EXPECT_NE(fIt, ftmpIt) << "operator!= fails.";
	EXPECT_NE(sIt, stmpIt);
	EXPECT_GT(fIt, ftmpIt) << "operator> fails.";
	EXPECT_GT(sIt, stmpIt);
	EXPECT_GE(fIt, ftmpIt) << "operator>= fails.";
	EXPECT_GE(sIt, stmpIt);
	EXPECT_LT(ftmpIt, fIt) << "operator< fails.";
	EXPECT_LT(stmpIt, sIt);
	EXPECT_LE(ftmpIt, fIt) << "operator<= fails.";
	EXPECT_LE(stmpIt, sIt);

	--fIt;
	--sIt;
	EXPECT_EQ(*fIt, *sIt) << "--operator fails.";

	EXPECT_EQ(fIt[3], sIt[3]) << "operator[] fails.";
	EXPECT_EQ(*(fIt + 3), *(sIt + 3)) << "operator+ fails.";
	EXPECT_EQ(sIt[3], *(sIt + 3)) << "operator+ or operator[] fails.";
	EXPECT_EQ(fIt[3], *(fIt + 3)) << "operator+ or operator[] fails.";

	ftmpIt = fIt++;
	stmpIt = sIt++;
	EXPECT_EQ(*fIt, *sIt) << "operator++ fails.";
	EXPECT_EQ(*stmpIt, *ftmpIt) << "operator++ fails.";

	ftmpIt = fIt--;
	stmpIt = sIt--;
	EXPECT_EQ(*fIt, *sIt) << "operator-- fails.";
	EXPECT_EQ(*stmpIt, *ftmpIt) << "operator-- fails.";

	fIt += 4;
	sIt += 4;
	EXPECT_EQ(*fIt, *sIt) << "operator+= fails.";

	EXPECT_EQ(fIt[-3], sIt[-3]) << "operator[] fails.";
	EXPECT_EQ(*(fIt - 3), *(sIt - 3)) << "operator- fails.";
	EXPECT_EQ(sIt[-3], *(sIt - 3)) << "operator- or operator[] fails.";
	EXPECT_EQ(fIt[-3], *(fIt - 3)) << "operator- or operator[] fails.";

	fIt -= 4;
	sIt -= 4;
	EXPECT_EQ(*fIt, *sIt) << "operator-= fails.";

	checkVectorsAreEqualIt(fIt, fIte, sIt, sIte);
}

class VectorIteratorTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		sample.push_back(54);
		sample.push_back(42);
		sample.push_back(21);
		sample.push_back(12);
		sample.push_back(99);
		sample.push_back(66);

	}
	std::vector<int> sample;
};

TEST_F(VectorIteratorTest, IteratorInputInputTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::iterator itf =		f.begin();
	ft::vector<int>::iterator itfe =	f.end();
	ft::vector<int>::iterator tmpf;

	std::vector<int>::iterator its =	s.begin();
	std::vector<int>::iterator itse =	s.end();
	std::vector<int>::iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(VectorIteratorTest, IteratorInputConstInputTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::iterator itf =		f.begin();
	ft::vector<int>::iterator itfe =	f.end();
	ft::vector<int>::const_iterator tmpf;

	std::vector<int>::iterator its =	s.begin();
	std::vector<int>::iterator itse =	s.end();
	std::vector<int>::const_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(VectorIteratorTest, IteratorConstInputConstInputTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::const_iterator itf =		f.begin();
	ft::vector<int>::const_iterator itfe =	f.end();
	ft::vector<int>::const_iterator tmpf;

	std::vector<int>::const_iterator its =	s.begin();
	std::vector<int>::const_iterator itse =	s.end();
	std::vector<int>::const_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

/* THIS TEST NORMALLY SHOULD NOT COMPILE */
/*
TEST_F(VectorIteratorTest, IteratorConstInputInputTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::const_iterator itf =		f.begin();
	ft::vector<int>::const_iterator itfe =	f.end();
	ft::vector<int>::iterator tmpf;

	std::vector<int>::const_iterator its =	s.begin();
	std::vector<int>::const_iterator itse =	s.end();
	std::vector<int>::iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}*/

TEST_F(VectorIteratorTest, IteratorReverseReverseTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::reverse_iterator itf =		f.rbegin();
	ft::vector<int>::reverse_iterator itfe =	f.rend();
	ft::vector<int>::reverse_iterator tmpf;

	std::vector<int>::reverse_iterator its =	s.rbegin();
	std::vector<int>::reverse_iterator itse =	s.rend();
	std::vector<int>::reverse_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(VectorIteratorTest, IteratorReverseConstReverseTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::reverse_iterator itf =		f.rbegin();
	ft::vector<int>::reverse_iterator itfe =	f.rend();
	ft::vector<int>::const_reverse_iterator tmpf;

	std::vector<int>::reverse_iterator its =	s.rbegin();
	std::vector<int>::reverse_iterator itse =	s.rend();
	std::vector<int>::const_reverse_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(VectorIteratorTest, IteratorConstReverseConstReverseTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::const_reverse_iterator itf =		f.rbegin();
	ft::vector<int>::const_reverse_iterator itfe =	f.rend();
	ft::vector<int>::const_reverse_iterator tmpf;

	std::vector<int>::const_reverse_iterator its =	s.rbegin();
	std::vector<int>::const_reverse_iterator itse =	s.rend();
	std::vector<int>::const_reverse_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

/* THIS TEST NORMALLY SHOULD NOT COMPILE */
/*TEST_F(VectorIteratorTest, IteratorConstReverseReverseTest) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	ft::vector<int>::const_reverse_iterator itf =		f.rbegin();
	ft::vector<int>::const_reverse_iterator itfe =	f.rend();
	ft::vector<int>::reverse_iterator tmpf;

	std::vector<int>::const_reverse_iterator its =	s.rbegin();
	std::vector<int>::const_reverse_iterator itse =	s.rend();
	std::vector<int>::reverse_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}*/

class VectorClearTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
};

TEST_F(VectorClearTest, capacityRemainsTheSame) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	size_t caps = s.capacity();
	size_t capf = f.capacity();

	s.clear();
	f.clear();

	EXPECT_EQ(capf, f.capacity()) << "capacity should remain the same after clear";
	EXPECT_EQ(caps, s.capacity());
	EXPECT_EQ(0, f.size());
	EXPECT_EQ(0, s.size());
}

class VectorAssignationTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		sample.push_back(54);
		sample.push_back(42);
		sample.push_back(21);
		sample.push_back(12);
		sample.push_back(99);
		sample.push_back(66);
	}
	std::vector<int> sample;
};

TEST_F(VectorAssignationTest, emptyAssign) {
	std::vector<int> s;
	std::vector<int> s1;
	ft::vector<int> f;
	ft::vector<int> f1;

	s = s1;
	f = f1;
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorAssignationTest, nonEmptyAssign) {
	std::vector<int> s(sample.begin(), sample.end());
	std::vector<int> s1;
	ft::vector<int> f(sample.begin(), sample.end());
	ft::vector<int> f1;

	s = s1;
	f = f1;
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorAssignationTest, nonEmptyAssignCapacityCheck) {
	std::vector<int> s(sample.begin(), sample.end());
	std::vector<int> s1;
	ft::vector<int> f(sample.begin(), sample.end());
	ft::vector<int> f1;

	s1.reserve(30);
	f1.reserve(30);

	s1 = s;
	f1 = f;
	EXPECT_EQ(s1.capacity(), 30);
	EXPECT_EQ(f1.capacity(), 30) << "Capacity should not be changed if you're assigning a smaller vector";
	checkIfVectorsAreEqual(f, s);
}

class VectorAccessTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
};

TEST_F(VectorAccessTest, operatorBrackets) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(f[i], s[i]) << "operator[] fails on " << i << " iteration";
	}
}

TEST_F(VectorAccessTest, at) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());
	int nouse = 0;

	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(f.at(i), s.at(i)) << "at() fails on " << i << " iteration";
	}
	EXPECT_THROW(nouse += s.at(10), std::out_of_range) << "at() does not throw std::out_of_range";
	EXPECT_THROW(nouse += f.at(10), std::out_of_range) << "at() does not throw std::out_of_range";
}

TEST_F(VectorAccessTest, frontBack) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	EXPECT_EQ(s.front(), f.front());
	EXPECT_EQ(s.back(), f.back());
}

class VectorReserveTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
};

TEST_F(VectorReserveTest, reserveEmpty) {
	std::vector<int> s;
	ft::vector<int> f;
	std::vector<int> s1(sample.begin(), sample.end());
	ft::vector<int> f1(sample.begin(), sample.end());

	s.reserve(10);
	f.reserve(10);
	EXPECT_GE(s.capacity(), 10);
	EXPECT_GE(f.capacity(), 10);
	s1.reserve(11);
	f1.reserve(11);
	EXPECT_GE(s1.capacity(), 11);
	EXPECT_GE(f1.capacity(), 11);
	checkIfVectorsAreEqual(f1, s1);
	f1.reserve(200000);
	s1.reserve(200000);
	EXPECT_GE(s1.capacity(), 200000);
	EXPECT_GE(f1.capacity(), 200000);
	checkIfVectorsAreEqual(f1, s1);
	EXPECT_THROW(f1.reserve(f1.max_size() + 1), std::length_error);
	EXPECT_THROW(s1.reserve(s1.max_size() + 1), std::length_error);
}

class VectorInsertIntTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
	ft::vector<int>::iterator itf;
	ft::vector<int>::iterator itfe;
	ft::vector<int>::iterator itfret;
	std::vector<int>::iterator its;
	std::vector<int>::iterator itse;
	std::vector<int>::iterator itsret;
};

TEST_F(VectorInsertIntTest, insertIntInPosition1) { // insert into begin with reallocation
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	itfret = f.insert(f.begin(), 42);
	itsret = s.insert(s.begin(), 42);

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorInsertIntTest, insertIntInPosition2) { // insert into begin without reallocation
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	s.reserve(30);

	itf = f.begin(); itfe = f.end();
	its = s.begin(); itse = s.end();

	itfret = f.insert(itf, 42);
	itsret = s.insert(its, 42);
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
}

TEST_F(VectorInsertIntTest, insertIntInPosition3) { // insert into mid with reallocation
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

//	itf = f.begin(); itfe = f.end();
//	its = s.begin(); itse = s.end();

	itfret = f.insert(++++f.begin(), 42);
	itsret = s.insert(++++s.begin(), 42);
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorInsertIntTest, insertIntInPosition4) { // insert into mid without reallocation
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	s.reserve(30);

	itf = ++f.begin(); itfe = f.end();
	its = ++s.begin(); itse = s.end();

	itfret = f.insert(++++f.begin(), 42);
	itsret = s.insert(++++s.begin(), 42);
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
	checkVectorsAreEqualIt(itf, f.end(), its, s.end()); // itf and its should remain valid
}

TEST_F(VectorInsertIntTest, insertIntInPosition5) { // insert into end with reallocation
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

//	itf = --f.end(); itfe = f.end();
//	its = --s.end(); itse = s.end();

	itfret = f.insert(f.end(), 42);
	itsret = s.insert(s.end(), 42);
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorInsertIntTest, insertIntInPosition6) { // insert into end without reallocation
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	s.reserve(30);

	itf = --f.end(); itfe = f.end();
	its = --s.end(); itse = s.end();

	itfret = f.insert(f.end(), 42);
	itsret = s.insert(s.end(), 42);
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
	checkVectorsAreEqualIt(itf, f.end(), its, s.end()); // itf and its should remain valid
}

TEST_F(VectorInsertIntTest, insertIntRangeN1) {	// insert into begin with reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(f.begin(), 5, 42);
	s.insert(s.begin(), 5,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN2) {	// insert into begin without reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.begin(), 5, 42);
	s.insert(s.begin(), 5,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN3) {	// insert into begin with reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(f.begin(), 15, 42);
	s.insert(s.begin(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN4) {	// insert into begin without reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.begin(), 15, 42);
	s.insert(s.begin(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN5) {	// insert into mid with reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(++++f.begin(), 5, 42);
	s.insert(++++s.begin(), 5,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN6) {	// insert into mid without reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(++++f.begin(), 5, 42);
	s.insert(++++s.begin(), 5,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN7) {	// insert into mid n with reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(++++f.begin(), 15, 42);
	s.insert(++++s.begin(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN8) {	// insert into mid without reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(++++f.begin(), 15, 42);
	s.insert(++++s.begin(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN9) {	// insert into end with reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(f.end(), 5, 42);
	s.insert(s.end(), 5,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN10) {	// insert into end without reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.end(), 5, 42);
	s.insert(s.end(), 5,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN11) {	// insert into end with reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(f.end(), 15, 42);
	s.insert(s.end(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeN12) {	// insert into end without reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.end(), 15, 42);
	s.insert(s.end(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntRangeNMultiReallocation) {
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(f.end(), 15000, 42);
	s.insert(s.end(), 15000,42);

	checkIfVectorsAreEqual(f, s);
}

//TEST_F(VectorInsertIntTest, insertIntIterator1) {	// insert into begin with reallocation, less then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.insert(f.begin(), sample.begin(), ++++++sample.begin());
//	s.insert(s.begin(), sample.begin(), ++++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}
//
//TEST_F(VectorInsertIntTest, insertIntIterator2) {	// insert into begin without reallocation, less then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.reserve(30);
//	f.reserve(30);
//
//	f.insert(f.begin(), sample.begin(), ++++sample.begin());
//	s.insert(s.begin(), sample.begin(), ++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}
//
//TEST_F(VectorInsertIntTest, insertIntIterator3) {	// insert into begin with reallocation, greater then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.insert(f.begin(), sample.begin(), ++++sample.begin());
//	s.insert(s.begin(), sample.begin(), ++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}
//
//TEST_F(VectorInsertIntTest, insertIntIterator4) {	// insert into begin without reallocation, greater then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.reserve(30);
//	f.reserve(30);
//
//	f.insert(f.begin(), sample.begin(), ++++sample.begin());
//	s.insert(s.begin(), sample.begin(), ++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}

//TEST_F(VectorInsertIntTest, insertIntIterator5) {	// insert into mid with reallocation, less then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.insert(++++f.begin(), sample.begin(), ++++sample.begin());
//	s.insert(++++s.begin(), sample.begin(), ++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}
//
//TEST_F(VectorInsertIntTest, insertIntIterator6) {	// insert into mid without reallocation, less then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.reserve(30);
//	f.reserve(30);
//
//	f.insert(++++f.begin(), sample.begin(), ++++sample.begin());
//	s.insert(++++s.begin(), sample.begin(), ++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}
//
//TEST_F(VectorInsertIntTest, insertIntIterator7) {	// insert into mid n with reallocation, greater then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.insert(++++f.begin(), sample.begin(), ++++sample.begin());
//	s.insert(++++s.begin(), sample.begin(), ++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}
//
//TEST_F(VectorInsertIntTest, insertIntIterator8) {	// insert into mid without reallocation, greater then size
//	ft::vector<int> f(sample.begin(), sample.end());
//	std::vector<int> s(sample.begin(), sample.end());
//
//	f.reserve(30);
//	f.reserve(30);
//
//	f.insert(++++f.begin(), sample.begin(), ++++sample.begin());
//	s.insert(++++s.begin(), sample.begin(), ++++sample.begin());
//
//	checkIfVectorsAreEqual(f, s);
//}

TEST_F(VectorInsertIntTest, insertIntIterator9) {	// insert into end with reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntIterator10) {	// insert into end without reallocation, less then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntIterator11) {	// insert into end with reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntIterator12) {	// insert into end without reallocation, greater then size
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertIntTest, insertIntIteratorMultiReallocation) {
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());
	for (int i = 0; i < 15000; ++i) {
		sample.push_back(i * rand());
	}

	f.insert(f.end(), sample.begin(), sample.end());
	s.insert(s.end(), sample.begin(), sample.end());

	checkIfVectorsAreEqual(f, s);
}

class VectorInsertStrTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(std::to_string(i));
		}
	}
	std::vector<std::string> sample;
	ft::vector<std::string>::iterator itf;
	ft::vector<std::string>::iterator itfe;
	ft::vector<std::string>::iterator itfret;
	std::vector<std::string>::iterator its;
	std::vector<std::string>::iterator itse;
	std::vector<std::string>::iterator itsret;
};

TEST_F(VectorInsertStrTest, insertIntInPosition1) { // insert into begin with reallocation
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	itfret = f.insert(f.begin(), std::to_string(42));
	itsret = s.insert(s.begin(), std::to_string(42));

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorInsertStrTest, insertIntInPosition2) { // insert into begin without reallocation
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	f.reserve(30);
	s.reserve(30);

	itf = f.begin(); itfe = f.end();
	its = s.begin(); itse = s.end();

	itfret = f.insert(itf, std::to_string(42));
	itsret = s.insert(its, std::to_string(42));
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
}

TEST_F(VectorInsertStrTest, insertIntInPosition3) { // insert into mid with reallocation
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

//	itf = f.begin(); itfe = f.end();
//	its = s.begin(); itse = s.end();

	itfret = f.insert(++++f.begin(), std::to_string(42));
	itsret = s.insert(++++s.begin(), std::to_string(42));
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorInsertStrTest, insertIntInPosition4) { // insert into mid without reallocation
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	f.reserve(30);
	s.reserve(30);

	itf = ++f.begin(); itfe = f.end();
	its = ++s.begin(); itse = s.end();

	itfret = f.insert(++++f.begin(), std::to_string(42));
	itsret = s.insert(++++s.begin(), std::to_string(42));
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
	checkVectorsAreEqualIt(itf, f.end(), its, s.end()); // itf and its should remain valid
}

TEST_F(VectorInsertStrTest, insertIntInPosition5) { // insert into end with reallocation
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

//	itf = --f.end(); itfe = f.end();
//	its = --s.end(); itse = s.end();

	itfret = f.insert(f.end(), std::to_string(42));
	itsret = s.insert(s.end(), std::to_string(42));
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorInsertStrTest, insertIntInPosition6) { // insert into end without reallocation
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	f.reserve(30);
	s.reserve(30);

	itf = --f.end(); itfe = f.end();
	its = --s.end(); itse = s.end();

	itfret = f.insert(f.end(), std::to_string(42));
	itsret = s.insert(s.end(), std::to_string(42));
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
	checkVectorsAreEqualIt(itf, f.end(), its, s.end()); // itf and its should remain valid
}

TEST_F(VectorInsertStrTest, insertIntIterator9) {	// insert into end with reallocation, less then size
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertStrTest, insertIntIterator10) {	// insert into end without reallocation, less then size
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertStrTest, insertIntIterator11) {	// insert into end with reallocation, greater then size
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertStrTest, insertIntIterator12) {	// insert into end without reallocation, greater then size
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());

	f.reserve(30);
	f.reserve(30);

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorInsertStrTest, insertIntIteratorMultiReallocation) {
	ft::vector<std::string> f(sample.begin(), sample.end());
	std::vector<std::string> s(sample.begin(), sample.end());
	for (int i = 0; i < 15000; ++i) {
		sample.push_back(std::to_string(i * rand()));
	}

	f.insert(f.end(), sample.begin(), sample.end());
	s.insert(s.end(), sample.begin(), sample.end());

	checkIfVectorsAreEqual(f, s);
}

class VectorEraseTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
	ft::vector<int>::iterator itf;
	ft::vector<int>::iterator itfe;
	ft::vector<int>::iterator itfret;
	std::vector<int>::iterator its;
	std::vector<int>::iterator itse;
	std::vector<int>::iterator itsret;
};

TEST_F(VectorEraseTest, erasePos1) {		// erase from begin
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	size_t capf = f.capacity(); size_t caps = s.capacity();

	itfret = f.erase(f.begin());
	itsret = s.erase(s.begin());

	EXPECT_EQ(caps, s.capacity());
	EXPECT_EQ(capf, f.capacity());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorEraseTest, erasePos2) {		// erase from mid
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	size_t capf = f.capacity(); size_t caps = s.capacity();

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(----f.end());
	itsret = s.erase(----s.end());

	EXPECT_EQ(caps, s.capacity());
	EXPECT_EQ(capf, f.capacity());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorEraseTest, erasePos3) {		// erase from end
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	size_t capf = f.capacity(); size_t caps = s.capacity();

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(--f.end());
	itsret = s.erase(--s.end());

	EXPECT_EQ(caps, s.capacity());
	EXPECT_EQ(capf, f.capacity());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorEraseTest, eraseIterator2) { // erase from begin full
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	size_t capf = f.capacity(); size_t caps = s.capacity();

	itfret = f.erase(f.begin(), f.end());
	itsret = s.erase(s.begin(), s.end());

	EXPECT_EQ(caps, s.capacity());
	EXPECT_EQ(capf, f.capacity());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorEraseTest, eraseIterator4) { // erase from mid till end
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	size_t capf = f.capacity(); size_t caps = s.capacity();

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(++++++f.begin(), f.end());
	itsret = s.erase(++++++s.begin(), s.end());

	EXPECT_EQ(caps, s.capacity());
	EXPECT_EQ(capf, f.capacity());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(VectorEraseTest, eraseIterator5) { // erase end, noting should happen
	ft::vector<int> f(sample.begin(), sample.end());
	std::vector<int> s(sample.begin(), sample.end());

	size_t capf = f.capacity(); size_t caps = s.capacity();

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(f.end(), f.end());
	itsret = s.erase(s.end(), s.end());

	EXPECT_EQ(caps, s.capacity());
	EXPECT_EQ(capf, f.capacity());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

class VectorPushBackTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
	ft::vector<int>::iterator itf;
	ft::vector<int>::iterator itfe;
	ft::vector<int>::iterator itfret;
	std::vector<int>::iterator its;
	std::vector<int>::iterator itse;
	std::vector<int>::iterator itsret;
};

TEST_F(VectorPushBackTest, toEmpty) { // to empty with reallocation
	std::vector<int> es;
	ft::vector<int> ef;

	es.push_back(42);
	ef.push_back(42);

	checkIfVectorsAreEqual(ef, es);
}

TEST_F(VectorPushBackTest, toEmptyNoRealloc) { // to empty without reallocation
	std::vector<int> es;
	ft::vector<int> ef;

	es.reserve(10);
	ef.reserve(10);

	es.push_back(42);
	ef.push_back(42);

	checkIfVectorsAreEqual(ef, es);
}

TEST_F(VectorPushBackTest, withRealloc) { // to empty with reallocation
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	s.push_back(42);
	f.push_back(42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorPushBackTest, withoutRealloc) { // to empty without reallocation
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	s.reserve(15);
	f.reserve(15);

	s.push_back(42);
	f.push_back(42);

	checkIfVectorsAreEqual(f, s);
}

class VectorPopBackTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
	ft::vector<int>::iterator itf;
	ft::vector<int>::iterator itfe;
	ft::vector<int>::iterator itfret;
	std::vector<int>::iterator its;
	std::vector<int>::iterator itse;
	std::vector<int>::iterator itsret;
};

TEST_F(VectorPopBackTest, single) {
	std::vector<int> s(sample.begin(), ++sample.begin());
	 ft::vector<int> f(sample.begin(), ++sample.begin());

	s.pop_back();
	f.pop_back();

	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(f.size(), 0);
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorPopBackTest, simple) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	s.pop_back();
	f.pop_back();

	EXPECT_EQ(s.size(), 9);
	EXPECT_EQ(f.size(), 9);
	checkIfVectorsAreEqual(f, s);
}

class VectorResizeTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
	ft::vector<int>::iterator itf;
	ft::vector<int>::iterator itfe;
	ft::vector<int>::iterator itfret;
	std::vector<int>::iterator its;
	std::vector<int>::iterator itse;
	std::vector<int>::iterator itsret;
};

TEST_F(VectorResizeTest, toUp) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	for (int i = 0; i < 5; ++i) {
		s.resize(static_cast<size_t>(12 * i));
		f.resize(static_cast<size_t>(12 * i));
		EXPECT_EQ(s.size(), 12 * i);
		EXPECT_EQ(f.size(), 12 * i);
		checkIfVectorsAreEqual(f, s);
	}
}

TEST_F(VectorResizeTest, toDown) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	for (int i = 10; i > 0; --i) {
		s.resize(static_cast<size_t>(i));
		f.resize(static_cast<size_t>(i));
		EXPECT_EQ(s.size(), i);
		EXPECT_EQ(f.size(), i);
		checkIfVectorsAreEqual(f, s);
	}
}

TEST_F(VectorResizeTest, toMixed) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	s.resize(5);
	f.resize(5);
	EXPECT_EQ(s.size(), 5);
	EXPECT_EQ(f.size(), 5);
	checkIfVectorsAreEqual(f, s);

	s.resize(20);
	f.resize(20);
	EXPECT_EQ(s.size(), 20);
	EXPECT_EQ(f.size(), 20);
	checkIfVectorsAreEqual(f, s);

	s.resize(15);
	f.resize(15);
	EXPECT_EQ(s.size(), 15);
	EXPECT_EQ(f.size(), 15);
	checkIfVectorsAreEqual(f, s);
}

class VectorAssignTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
	ft::vector<int>::iterator itf;
	ft::vector<int>::iterator itfe;
	ft::vector<int>::iterator itfret;
	std::vector<int>::iterator its;
	std::vector<int>::iterator itse;
	std::vector<int>::iterator itsret;
};

TEST_F(VectorAssignTest, toEmpty) {
	std::vector<int> s(sample.begin(), sample.end());
	 ft::vector<int> f(sample.begin(), sample.end());

	std::vector<int> s1;
	 ft::vector<int> f1;

	s1.assign(s.begin(), s.end());
	f1.assign(f.begin(), f.end());
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(VectorAssignTest, toNotEmpty) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	std::vector<int> s1(s);
	ft::vector<int> f1(f);

	s1.assign(++++s.begin(), --s.end());
	f1.assign(++++f.begin(), --f.end());
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(VectorAssignTest, capacityCheck) { // capacity check
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	std::vector<int> s1;
	ft::vector<int> f1;

	s1.reserve(30);
	f1.reserve(30);

	s1.assign(++++s.begin(), --s.end());
	f1.assign(++++f.begin(), --f.end());

	EXPECT_EQ(s1.capacity(), 30);
	EXPECT_EQ(f1.capacity(), 30);
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(VectorAssignTest, toEmptyN) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	std::vector<int> s1;
	ft::vector<int> f1;

	s1.assign(42, 42);
	f1.assign(42, 42);
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(VectorAssignTest, toNotEmptyN) {
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	std::vector<int> s1(s);
	ft::vector<int> f1(f);

	s1.assign(42, 42);
	f1.assign(42, 42);
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(VectorAssignTest, capacityCheckN) { // capacity check
	std::vector<int> s(sample.begin(), sample.end());
	ft::vector<int> f(sample.begin(), sample.end());

	std::vector<int> s1;
	ft::vector<int> f1;

	s1.reserve(50);
	f1.reserve(50);

	s1.assign(42, 42);
	f1.assign(42, 42);

	EXPECT_EQ(s1.capacity(), 50);
	EXPECT_EQ(f1.capacity(), 50);
	checkIfVectorsAreEqual(f1, s1);
}

class VectorSwapTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s1.push_back(std::to_string(i));
			f1.push_back(std::to_string(i));
		}
	}

	std::vector<std::string> s2, s1;
	ft::vector<std::string>  f2, f1;
};

TEST_F(VectorSwapTest, integrityFullEmpty) {
	s1.swap(s2);
	f1.swap(f2);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
}

TEST_F(VectorSwapTest, integrityEmptyFull) {
	s2.swap(s1);
	f2.swap(f1);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
}

TEST_F(VectorSwapTest, integrityFullFull) {
	s2.push_back("std::to_string(i)");
	f2.push_back("std::to_string(i)");

	s2.swap(s1);
	f2.swap(f1);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
}

TEST_F(VectorSwapTest, iteratorValidity) {
	std::vector<std::string>::iterator its = ++s1.begin();
	ft::vector<std::string>::iterator itf = ++f1.begin();

	s2.push_back("std::to_string(i)");
	f2.push_back("std::to_string(i)");

	s2.swap(s1);
	f2.swap(f1);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
	checkVectorsAreEqualIt(itf, f2.end(), its, s2.end());
}

class VectorComprasionTest : public ::testing::Test {
protected:
	virtual void SetUp() {

	}
	std::vector<std::string> s1, s2;
	ft::vector<std::string> f1, f2;
};

TEST_F(VectorComprasionTest, equalSimple) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");
	s1.push_back("d"); f1.push_back("d");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("c"); f2.push_back("c");
	s2.push_back("d"); f2.push_back("d");

	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
}

TEST_F(VectorComprasionTest, equalSingleElem) {
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("a"); f2.push_back("a");

	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
}

TEST_F(VectorComprasionTest, equalEmpty) {
	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
}

TEST_F(VectorComprasionTest, lessSizeLess) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("c"); f2.push_back("c");
	s2.push_back("d"); f2.push_back("d");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(VectorComprasionTest, lessOneElem) {
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("d"); f2.push_back("d");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(VectorComprasionTest, lessCase1) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("cc"); f2.push_back("cc");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(VectorComprasionTest, lessCase2) {
	s1.push_back("a1"); f1.push_back("a1");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");

	s2.push_back("a9"); f2.push_back("a9");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("c"); f2.push_back("c");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(VectorComprasionTest, justCase1) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(VectorComprasionTest, justCase2) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");

	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
}

TEST_F(VectorComprasionTest, justCase3) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("z"); f2.push_back("z");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(VectorComprasionTest, justCase4) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(VectorComprasionTest, justCase5) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
	EXPECT_EQ(false, s1 > s2);
	EXPECT_EQ(false, f1 > f2);
	EXPECT_EQ(false, s1 >= s2);
	EXPECT_EQ(false, f1 >= f2);
	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(true, s1 <= s2);
	EXPECT_EQ(true, f1 <= f2);
}

