/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 10:38:06 by matrus            #+#    #+#             */
/*   Updated: 2020/11/28 10:38:12 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include "map.hpp"
#include <map>
#include <string>
#include <stdexcept>

#ifndef FT_CONTAINERS_DEBUG
template < class G, class U >
std::ostream & operator<<(std::ostream & o, std::pair<G, U> p) {
	o << "_" << p.first;
	return o;
}
#endif

template< class T >
void printContainer(T & l) {
	for (typename T::iterator it = l.begin(); it != l.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

template < class T, class U>
bool operator==(std::pair<T, U> p1, std::pair<T, U> p2) {
	return (p1.first == p2.first && p1.second == p2.second);
}

template <class T, class U>
void	checkIfMapsAreEqual(ft::map<T, U> & f, std::map<T, U> & s, int i = 0) {
	EXPECT_EQ(f.size(), s.size()) << "i = " << i;
	EXPECT_EQ(f.empty(), s.empty()) << "i = " << i;

	typename  ft::map<T, U>::iterator itf = f.begin();
	typename  ft::map<T, U>::iterator itfe = f.end();
	typename std::map<T, U>::iterator its = s.begin();
	typename std::map<T, U>::iterator itse = s.end();

	for (; its != itse; ) {
		EXPECT_EQ(*its++, *itf++)  << "i = " << i;
	}
	EXPECT_EQ(itf, itfe)  << "i = " << i;
}

template <typename itFt, typename itFtEnd, typename itStd, typename itStdEnd>
void checkMapsAreEqualIt(itFt itF, itFtEnd itFe, itStd itS, itStdEnd itSe) {
	for (; itS != itSe; ) {
		EXPECT_EQ(*itS++, *itF++);
	}
	EXPECT_EQ(itF, itFe);
}

template <typename ftIter, typename stdIter, typename ftIterTmp, typename stdIterTmp>
void	mapIteratorTest(ftIter & fIt, ftIter & fIte, ftIterTmp & ftmpIt,
						stdIter & sIt, stdIter & sIte, stdIterTmp & stmpIt)
{
	ftmpIt = fIt;
	stmpIt = sIt;
	EXPECT_EQ(ftmpIt, fIt) << "Assignation or operator== fails.";
	EXPECT_EQ(stmpIt, sIt);

	ASSERT_EQ(*fIt, *sIt) << "Dereference fails.";

	++fIt;
	++sIt;
	EXPECT_EQ(*fIt, *sIt) << "++operator fails.";

	EXPECT_NE(fIt, ftmpIt) << "operator!= fails.";
	EXPECT_NE(sIt, stmpIt);

	--fIt;
	--sIt;
	EXPECT_EQ(*fIt, *sIt) << "--operator fails.";

	ftmpIt = fIt++;
	stmpIt = sIt++;
	EXPECT_EQ(*fIt, *sIt) << "operator++ fails.";
	EXPECT_EQ(*stmpIt, *ftmpIt) << "operator++ fails.";

	checkMapsAreEqualIt(fIt, fIte, sIt, sIte);
}

class MapInsertSimpleTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			s.insert(std::make_pair(std::to_string(i), i));
			f.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> s;
	ft::map<std::string, int> f;

	std::map<std::string, int>::iterator it;
};

TEST_F(MapInsertSimpleTest, case1) {
	EXPECT_EQ(s.size(), f.size());
	EXPECT_EQ(s.empty(), f.empty());
}

TEST_F(MapInsertSimpleTest, case2) {
	s.insert(std::make_pair("a", 43));
	f.insert(std::make_pair("a", 43));

	EXPECT_EQ(s.size(), f.size());
	EXPECT_EQ(s.empty(), f.empty());
}

TEST_F(MapInsertSimpleTest, case3) {
	 size_t ssize = s.size();
	 size_t fsize = f.size();

	s.insert(std::make_pair(std::string("1"), 43));
	f.insert(std::make_pair(std::string("1"), 43));

	EXPECT_EQ(s.size(), ssize);
	EXPECT_EQ(f.size(), fsize);
	EXPECT_EQ(s.size(), f.size());
	EXPECT_EQ(s.empty(), f.empty());
}

TEST_F(MapInsertSimpleTest, case4) {
	std::map<std::string, int> s1;
	std::map<std::string, int> f1;
	EXPECT_EQ(s1.size(), f1.size());
	EXPECT_EQ(s1.empty(), f1.empty());
}

class MapIteratorTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 11; ++i) {
			s.insert(std::make_pair(std::to_string(i), i));
			f.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> s;
	 ft::map<std::string, int> f;
};

TEST_F(MapIteratorTest, IteratorInputInputTest) {
	ft::map<std::string, int>::iterator itf =	f.begin();
	ft::map<std::string, int>::iterator itfe =	f.end();
	ft::map<std::string, int>::iterator tmpf;

	std::map<std::string,int>::iterator its =	s.begin();
	std::map<std::string,int>::iterator itse =	s.end();
	std::map<std::string,int>::iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
//	printContainer(f);
//	std::cout << std::endl;
//	printContainer(s);
//	f._dPrintStrangeTree();
}

TEST_F(MapIteratorTest, IteratorInputConstInputTest) {
	ft::map<std::string, int>::iterator itf =	f.begin();
	ft::map<std::string, int>::iterator itfe =	f.end();
	ft::map<std::string, int>::const_iterator tmpf;

	std::map<std::string,int>::iterator its =	s.begin();
	std::map<std::string,int>::iterator itse =	s.end();
	std::map<std::string,int>::const_iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(MapIteratorTest, IteratorConstInputConstInputTest) {
	ft::map<std::string, int>::const_iterator itf =		f.begin();
	ft::map<std::string, int>::const_iterator itfe =	f.end();
	ft::map<std::string, int>::const_iterator tmpf;

	std::map<std::string,int>::const_iterator its =	s.begin();
	std::map<std::string,int>::const_iterator itse =	s.end();
	std::map<std::string,int>::const_iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

/*// THIS TEST NORMALLY SHOULD NOT COMPILE
TEST_F(MapIteratorTest, IteratorConstInputInputTest) {
	ft::map<std::string, int>::const_iterator itf =		f.begin();
	ft::map<std::string, int>::const_iterator itfe =	f.end();
	ft::map<std::string, int>::iterator tmpf;

	std::map<std::string,int>::const_iterator its =	s.begin();
	std::map<std::string,int>::const_iterator itse =	s.end();
	std::map<std::string,int>::iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}*/

TEST_F(MapIteratorTest, IteratorReverseReverseTest) {
	ft::map<std::string, int>::reverse_iterator itf =		f.rbegin();
	ft::map<std::string, int>::reverse_iterator itfe =	f.rend();
	ft::map<std::string, int>::reverse_iterator tmpf;

	std::map<std::string,int>::reverse_iterator its =	s.rbegin();
	std::map<std::string,int>::reverse_iterator itse =	s.rend();
	std::map<std::string,int>::reverse_iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(MapIteratorTest, IteratorReverseConstReverseTest) {
	ft::map<std::string, int>::reverse_iterator itf =		f.rbegin();
	ft::map<std::string, int>::reverse_iterator itfe =	f.rend();
	ft::map<std::string, int>::const_reverse_iterator tmpf;

	std::map<std::string,int>::reverse_iterator its =	s.rbegin();
	std::map<std::string,int>::reverse_iterator itse =	s.rend();
	std::map<std::string,int>::const_reverse_iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(MapIteratorTest, IteratorConstReverseConstReverseTest) {
	ft::map<std::string, int>::const_reverse_iterator itf =		f.rbegin();
	ft::map<std::string, int>::const_reverse_iterator itfe =	f.rend();
	ft::map<std::string, int>::const_reverse_iterator tmpf;

	std::map<std::string,int>::const_reverse_iterator its =	s.rbegin();
	std::map<std::string,int>::const_reverse_iterator itse =	s.rend();
	std::map<std::string,int>::const_reverse_iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

/*// THIS TEST NORMALLY SHOULD NOT COMPILE
TEST_F(MapIteratorTest, IteratorConstReverseReverseTest) {
	ft::map<std::string, int>::const_reverse_iterator itf =		f.rbegin();
	ft::map<std::string, int>::const_reverse_iterator itfe =	f.rend();
	ft::map<std::string, int>::reverse_iterator tmpf;

	std::map<std::string,int>::const_reverse_iterator its =	s.rbegin();
	std::map<std::string,int>::const_reverse_iterator itse =	s.rend();
	std::map<std::string,int>::reverse_iterator tmps;

	mapIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}*/

class MapBoundAccessTest : public testing::Test {
protected:
	virtual void SetUp() {

	}
};

TEST_F(MapBoundAccessTest, beginsEmpty) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	ft::map<std::string, int>::iterator itf =	f.begin();
	ft::map<std::string, int>::iterator itfe =	f.end();

	std::map<std::string,int>::iterator its =	s.begin();
	std::map<std::string,int>::iterator itse =	s.end();

	EXPECT_EQ(its, itse);
	EXPECT_EQ(itf, itfe);

	ft::map<std::string, int>::reverse_iterator ritf =	f.rbegin();
	ft::map<std::string, int>::reverse_iterator ritfe =	f.rend();

	std::map<std::string,int>::reverse_iterator rits =	s.rbegin();
	std::map<std::string,int>::reverse_iterator ritse =	s.rend();

	EXPECT_EQ(rits, ritse);
	EXPECT_EQ(ritf, ritfe);
}

TEST_F(MapBoundAccessTest, beginsOneForvard) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;
	ft::map<std::string, int>::iterator itf;
	ft::map<std::string, int>::iterator itfe;
	std::map<std::string,int>::iterator its;
	std::map<std::string,int>::iterator itse;

	f.insert(std::make_pair("a", 123));
	s.insert(std::make_pair("a", 123));

	itf =	f.begin();	its =	s.begin();
	itfe =	f.end();	itse =	s.end();
	EXPECT_EQ(++its, itse);
	EXPECT_EQ(++itf, itfe);

	itf =	f.begin();	its =	s.begin();
	itfe =	f.end();	itse =	s.end();
	EXPECT_EQ(its, --itse);
	EXPECT_EQ(itf, --itfe);
}

TEST_F(MapBoundAccessTest, beginsOneReverse) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;
	ft::map<std::string, int>::reverse_iterator itf;
	ft::map<std::string, int>::reverse_iterator itfe;
	std::map<std::string,int>::reverse_iterator its;
	std::map<std::string,int>::reverse_iterator itse;

	f.insert(std::make_pair("a", 123));
	s.insert(std::make_pair("a", 123));

	itf =	f.rbegin();	its =	s.rbegin();
	itfe =	f.rend();	itse =	s.rend();
	EXPECT_EQ(++its, itse);
	EXPECT_EQ(++itf, itfe);

	itf =	f.rbegin();	its =	s.rbegin();
	itfe =	f.rend();	itse =	s.rend();
	EXPECT_EQ(its, --itse);
	EXPECT_EQ(itf, --itfe);
}

class MapInsertTest : public testing::Test {
protected:
	virtual void SetUp() {
		itf =	f.begin();
		itfe =	f.end();

		its =	s.begin();
		itse =	s.end();
	}
	std::pair<ft::map<std::string,int>::iterator, bool> pf;
	std::pair<std::map<std::string,int>::iterator, bool> ps;

	ft::map<std::string, int> f;
	std::map<std::string,int> s;

	ft::map<std::string, int>::iterator itf;
	std::map<std::string,int>::iterator its;
	ft::map<std::string, int>::iterator itfe;
	std::map<std::string,int>::iterator itse;
};

TEST_F(MapInsertTest, insertValCaseSingle) {
	pf = f.insert(std::make_pair("a", 1));
	ps = s.insert(std::make_pair("a", 1));

	EXPECT_EQ(pf.second, ps.second);

	checkMapsAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, insertValCaseOverride) {
	pf = f.insert(std::make_pair("a", 1));
	pf = f.insert(std::make_pair("a", 42));
	ps = s.insert(std::make_pair("a", 1));
	ps = s.insert(std::make_pair("a", 42));

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, f.begin());
	EXPECT_EQ(ps.first, s.begin());
	EXPECT_EQ(ps.first->second, 1);
	EXPECT_EQ(pf.first->second, 1);

	checkMapsAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, insertValCaseDouble1) {
	pf = f.insert(std::make_pair("a", 1));
	ps = s.insert(std::make_pair("a", 1));

	pf = f.insert(std::make_pair("b", 1));
	ps = s.insert(std::make_pair("b", 1));

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, --f.end());
	EXPECT_EQ(ps.first, --s.end());

	checkMapsAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, insertValCaseDouble2) {
	pf = f.insert(std::make_pair("b", 1));
	ps = s.insert(std::make_pair("b", 1));

	pf = f.insert(std::make_pair("a", 1));
	ps = s.insert(std::make_pair("a", 1));

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, f.begin());
	EXPECT_EQ(ps.first, s.begin());

	checkMapsAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, insertValCaseTriple1) {
	pf = f.insert(std::make_pair("b", 1));
	ps = s.insert(std::make_pair("b", 1));

	pf = f.insert(std::make_pair("a", 1));
	ps = s.insert(std::make_pair("a", 1));

	pf = f.insert(std::make_pair("c", 1));
	ps = s.insert(std::make_pair("c", 1));

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, --f.end());
	EXPECT_EQ(ps.first, --s.end());

	checkMapsAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, insertValCaseTriple2) {
	pf = f.insert(std::make_pair("b", 1));
	ps = s.insert(std::make_pair("b", 1));

	pf = f.insert(std::make_pair("c", 1));
	ps = s.insert(std::make_pair("c", 1));

	pf = f.insert(std::make_pair("a", 1));
	ps = s.insert(std::make_pair("a", 1));

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, f.begin());
	EXPECT_EQ(ps.first, s.begin());

	checkMapsAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, ultimative) {
	srand(1);
	int gen_key, gen_val;
	const int keys_limit = 500;

	for (int i = 0; i < keys_limit * 2; ++i) {
		gen_key = rand() % keys_limit;
		gen_val = rand();
		ps = s.insert(std::make_pair(std::to_string(gen_key), gen_val));
		pf = f.insert(std::make_pair(std::to_string(gen_key), gen_val));

		EXPECT_EQ(pf.second, ps.second);

		checkMapsAreEqualIt(pf.first, f.end(), ps.first, s.end());
		checkIfMapsAreEqual(f, s);
	}
}

TEST_F(MapInsertTest, insertPosVal1) {
	itf = f.insert(f.begin(), std::make_pair("123", 123));
	its = s.insert(s.begin(), std::make_pair("123", 123));

	checkMapsAreEqualIt(itf, f.end(), its, s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, insertPosVal2) {
	const int times = 100;

	for (int i = 0; i < times; ++i) {
		its = s.insert(s.begin(), std::make_pair(std::to_string(i + 10), i));
		itf = f.insert(f.begin(), std::make_pair(std::to_string(i + 10), i));

		checkMapsAreEqualIt(itf, f.end(), its, s.end());
		checkIfMapsAreEqual(f, s);
	}
}

TEST_F(MapInsertTest, insertRangeSameMap) {
	const int times = 100;

	for (int i = 0; i < times; ++i) {
		its = s.insert(s.begin(), std::make_pair(std::to_string(i + 10), i));
		itf = f.insert(f.begin(), std::make_pair(std::to_string(i + 10), i));
	}

	s.insert(s.begin(), s.end());
	f.insert(f.begin(), f.end());

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapInsertTest, insertAnotherRange) {
	const int times = 100;
	std::map<std::string, int> sample;

	for (int i = 0; i < times; ++i) {
		sample.insert(std::make_pair(std::to_string(i + 10), i));
	}

	its = sample.begin();
	std::advance(its, 30);

	s.insert(its, sample.end());
	f.insert(its, sample.end());

	checkIfMapsAreEqual(f, s);
}

class MapConstructionRange : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			sample.insert(std::make_pair(std::to_string(i + 142), i - 121));
		}
	}
	std::pair<ft::map<std::string,int>::iterator, bool> pf;
	std::pair<std::map<std::string,int>::iterator, bool> ps;

	ft::map<std::string, int>::iterator itf;
	std::map<std::string,int>::iterator its;
	ft::map<std::string, int>::iterator itfe;
	std::map<std::string,int>::iterator itse;

	std::map<std::string, int> sample;
};

TEST_F(MapConstructionRange, emptyRange) {
	ft::map<std::string, int> f(sample.begin(), sample.begin());
	std::map<std::string,int> s(sample.begin(), sample.begin());

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapConstructionRange, oneRange) {
	ft::map<std::string, int> f(sample.begin(), ++sample.begin());
	std::map<std::string,int> s(sample.begin(), ++sample.begin());

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapConstructionRange, oneHundredRange) {
	ft::map<std::string, int> f(sample.begin(), sample.end());
	std::map<std::string,int> s(sample.begin(), sample.end());

	checkIfMapsAreEqual(f, s);
}

class MapObserversTest : public testing::Test {
protected:
	virtual void SetUp() {
		s.insert(std::make_pair('x', 1001));
		s.insert(std::make_pair('y', 2002));
		s.insert(std::make_pair('z', 3003));
		f.insert(std::make_pair('x', 1001));
		f.insert(std::make_pair('y', 2002));
		f.insert(std::make_pair('z', 3003));

		its = s.begin();
		itf = f.begin();

	}

	std::map<char,int>::iterator its;
	ft::map<char, int>::iterator itf;
	std::map<char,int> s;
	ft::map<char, int> f;
	std::map<char,int> sfill;
	ft::map<char, int> ffill;
};

TEST_F(MapObserversTest, valueComp) {
	std::pair<char, int> shighest = *s.rbegin();
	std::pair<char, int> fhighest = *f.rbegin();

	do {
		sfill.insert(*its);
	} while ( s.value_comp()(*its++, shighest) );

	do {
		ffill.insert(*itf);
	} while ( f.value_comp()(*itf++, fhighest) );

	checkIfMapsAreEqual(ffill, sfill);
}

TEST_F(MapObserversTest, keyComp) {
	char shighest = s.rbegin()->first;
	char fhighest = f.rbegin()->first;

	std::map<char,int>::key_compare scomp = s.key_comp();
	ft::map<char,int>::key_compare fcomp = f.key_comp();

	do {
		sfill.insert(*its);
	} while ( scomp((*its++).first, shighest) );

	do {
		ffill.insert(*itf);
	} while ( scomp((*itf++).first, fhighest) );

	checkIfMapsAreEqual(ffill, sfill);
}

class MapFindTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s.insert(std::make_pair(std::to_string(i - 50), i + 50));
			f.insert(std::make_pair(std::to_string(i - 50), i + 50));
		}
	}
	
	std::map<std::string, int> s;
	ft::map<std::string, int> f;

	std::map<std::string,int>::iterator its;
	ft::map<std::string, int>::iterator itf;
	std::map<std::string,int>::iterator itse;
	ft::map<std::string, int>::iterator itfe;

	std::map<std::string,int>::const_iterator cits;
	ft::map<std::string, int>::const_iterator citf;
	std::map<std::string,int>::const_iterator citse;
	ft::map<std::string, int>::const_iterator citfe;
};

TEST_F(MapFindTest, notContain) {
	its = s.find("a");
	itf = f.find("a");

	EXPECT_EQ(its, s.end());
	EXPECT_EQ(itf, f.end());
}

TEST_F(MapFindTest, notContainEmpty) {
	std::map<std::string, int> sEmpty;
	ft::map<std::string, int> fEmpty;

	its = sEmpty.find("a");
	itf = fEmpty.find("a");

	EXPECT_EQ(its, sEmpty.end());
	EXPECT_EQ(itf, fEmpty.end());
	EXPECT_EQ(its, sEmpty.begin());
	EXPECT_EQ(itf, fEmpty.begin());
}

TEST_F(MapFindTest, findEach) {
	for (int i = -5; i < 105; ++i) {
		its = s.find(std::to_string(i - 50));
		itf = f.find(std::to_string(i - 50));

		checkMapsAreEqualIt(itf, f.end(), its, s.end());
	}
}

TEST_F(MapFindTest, findEachConst) {
	for (int i = -5; i < 105; ++i) {
		cits = s.find(std::to_string(i - 50));
		citf = f.find(std::to_string(i - 50));

		checkMapsAreEqualIt(citf, f.end(), cits, s.end());
	}
}

TEST_F(MapFindTest, count) {
	size_t cf;
	size_t cs;

	cf = f.count("1");
	cs = s.count("1");

	EXPECT_EQ(cs, cf);
	EXPECT_EQ(cs, 1);
	EXPECT_EQ(cf, 1);

	cf = f.count("a");
	cs = s.count("a");

	EXPECT_EQ(cs, cf);
	EXPECT_EQ(cs, 0);
	EXPECT_EQ(cf, 0);
}

class MapBoundTest : public testing::Test {
protected:
	virtual void SetUp() {
		step_iter = 0;
		for (int i = 0; i < 10; ++i) {
			s.insert(std::make_pair(std::to_string(step_iter), step_iter));
			f.insert(std::make_pair(std::to_string(step_iter), step_iter));
			step_iter += step / 2;
		}
	}

	const double step = 1.;
	double		 step_iter;

	std::map<std::string, double> s;
	ft::map<std::string, double> f;

	std::map<std::string, double>::iterator its;
	ft::map<std::string, double>::iterator itf;
	std::map<std::string, double>::iterator itse;
	ft::map<std::string, double>::iterator itfe;

	std::map<std::string, double>::const_iterator cits;
	ft::map<std::string, double>::const_iterator citf;
	std::map<std::string, double>::const_iterator citse;
	ft::map<std::string, double>::const_iterator citfe;
};

TEST_F(MapBoundTest, emptyLower) {
	std::map<std::string, double> sEmpty;
	ft::map<std::string, double> fEmpty;

	its = sEmpty.lower_bound("a");
	itf = fEmpty.lower_bound("a");

	EXPECT_EQ(its, sEmpty.end());
	EXPECT_EQ(itf, fEmpty.end());
	EXPECT_EQ(its, sEmpty.begin());
	EXPECT_EQ(itf, fEmpty.begin());
}

TEST_F(MapBoundTest, emptyUpper) {
	std::map<std::string, double> sEmpty;
	ft::map<std::string, double> fEmpty;

	its = sEmpty.upper_bound("a");
	itf = fEmpty.upper_bound("a");

	EXPECT_EQ(its, sEmpty.end());
	EXPECT_EQ(itf, fEmpty.end());
	EXPECT_EQ(its, sEmpty.begin());
	EXPECT_EQ(itf, fEmpty.begin());
}

TEST_F(MapBoundTest, singleUpper) {
	std::map<std::string, double> s1;
	ft::map<std::string, double> f1;

	s1.insert(std::make_pair("c", 123));
	f1.insert(std::make_pair("c", 123));

	its = s1.upper_bound("c");
	itf = f1.upper_bound("c");
	EXPECT_EQ(its, s1.end());
	EXPECT_EQ(itf, f1.end());

	its = s1.upper_bound("a");
	itf = f1.upper_bound("a");
	EXPECT_EQ(its, s1.begin());
	EXPECT_EQ(itf, f1.begin());

	its = s1.upper_bound("d");
	itf = f1.upper_bound("d");
	EXPECT_EQ(its, s1.end());
	EXPECT_EQ(itf, f1.end());
}

TEST_F(MapBoundTest, singleLower) {
	std::map<std::string, double> s1;
	ft::map<std::string, double> f1;

	s1.insert(std::make_pair("c", 123));
	f1.insert(std::make_pair("c", 123));

	its = s1.lower_bound("c");
	itf = f1.lower_bound("c");
	EXPECT_EQ(its, s1.begin());
	EXPECT_EQ(itf, f1.begin());

	its = s1.lower_bound("a");
	itf = f1.lower_bound("a");
	EXPECT_EQ(its, s1.begin());
	EXPECT_EQ(itf, f1.begin());

	its = s1.lower_bound("d");
	itf = f1.lower_bound("d");
	EXPECT_EQ(its, s1.end());
	EXPECT_EQ(itf, f1.end());
}

TEST_F(MapBoundTest, multitest) {
	step_iter = 0;
	for (double i = -step / 2; i < 10.5; i += step) {

		its = s.lower_bound(std::to_string(i));
		itf = f.lower_bound(std::to_string(i));
		checkMapsAreEqualIt(itf, f.end(), its, s.end());

		its = s.upper_bound(std::to_string(i));
		itf = f.upper_bound(std::to_string(i));
		checkMapsAreEqualIt(itf, f.end(), its, s.end());
	}
}

TEST_F(MapBoundTest, multitestConst) {
	step_iter = 0;
	for (double i = -step / 2; i < 10.5; i += step) {

		cits = s.lower_bound(std::to_string(i));
		citf = f.lower_bound(std::to_string(i));
		checkMapsAreEqualIt(citf, f.end(), cits, s.end());

		cits = s.upper_bound(std::to_string(i));
		citf = f.upper_bound(std::to_string(i));
		checkMapsAreEqualIt(citf, f.end(), cits, s.end());
	}
}

class MapEqualRangeTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 200; ++i) {
			iter = static_cast<double>(i);
			sample.insert(std::make_pair(std::to_string(iter), iter));
		}
	}

	typedef std::map<std::string, double>::const_iterator const_iterator_s;
	typedef std::map<std::string, double>::iterator iterator_s;

	typedef ft::map<std::string, double>::const_iterator const_iterator_f;
	typedef ft::map<std::string, double>::iterator iterator_f;

	double iter;

	std::map<std::string, double> sample;

	std::map<std::string, double> s;
	 ft::map<std::string, double> f;

	std::pair<const_iterator_s,const_iterator_s> cps;
				std::pair<iterator_s,iterator_s> ps;

	std::pair<const_iterator_f,const_iterator_f> cpf;
				std::pair<iterator_f,iterator_f> pf;
};

TEST_F(MapEqualRangeTest, empty) {
	std::map<std::string, double> sEmpty;
	 ft::map<std::string, double> fEmpty;

	ps = s.equal_range("a");
	pf = f.equal_range("a");

	EXPECT_EQ(ps.first, s.end());
	EXPECT_EQ(ps.second, s.end());
	EXPECT_EQ(pf.first, f.end());
	EXPECT_EQ(pf.second, f.end());
}

TEST_F(MapEqualRangeTest, emptyConst) {
	std::map<std::string, double> sEmpty;
	ft::map<std::string, double> fEmpty;

	cps = s.equal_range("a");
	cpf = f.equal_range("a");

	EXPECT_EQ(cps.first, s.end());
	EXPECT_EQ(cps.second, s.end());
	EXPECT_EQ(cpf.first, f.end());
	EXPECT_EQ(cpf.second, f.end());
}

TEST_F(MapEqualRangeTest, single) {
	std::map<std::string, double> s1;
	ft::map<std::string, double> f1;

	s1.insert(std::make_pair("c", 123));
	f1.insert(std::make_pair("c", 123));

	ps = s1.equal_range("c");
	pf = f1.equal_range("c");
	EXPECT_EQ(ps.first, s1.begin());
	EXPECT_EQ(ps.second, s1.end());
	EXPECT_EQ(pf.first, f1.begin());
	EXPECT_EQ(pf.second, f1.end());

	ps = s1.equal_range("a");
	pf = f1.equal_range("a");
	EXPECT_EQ(ps.first, s1.begin());
	EXPECT_EQ(ps.second, s1.begin());
	EXPECT_EQ(pf.first, f1.begin());
	EXPECT_EQ(pf.second, f1.begin());

	ps = s1.equal_range("d");
	pf = f1.equal_range("d");
	EXPECT_EQ(ps.first, s1.end());
	EXPECT_EQ(ps.second, s1.end());
	EXPECT_EQ(pf.first, f1.end());
	EXPECT_EQ(pf.second, f1.end());
}

TEST_F(MapEqualRangeTest, singleConst) {
	std::map<std::string, double> s1;
	ft::map<std::string, double> f1;

	s1.insert(std::make_pair("c", 123));
	f1.insert(std::make_pair("c", 123));

	cps = s1.equal_range("c");
	cpf = f1.equal_range("c");
	EXPECT_EQ(cps.first, s1.begin());
	EXPECT_EQ(cps.second, s1.end());
	EXPECT_EQ(cpf.first, f1.begin());
	EXPECT_EQ(cpf.second, f1.end());

	cps = s1.equal_range("a");
	cpf = f1.equal_range("a");
	EXPECT_EQ(cps.first, s1.begin());
	EXPECT_EQ(cps.second, s1.begin());
	EXPECT_EQ(cpf.first, f1.begin());
	EXPECT_EQ(cpf.second, f1.begin());

	cps = s1.equal_range("d");
	cpf = f1.equal_range("d");
	EXPECT_EQ(cps.first, s1.end());
	EXPECT_EQ(cps.second, s1.end());
	EXPECT_EQ(cpf.first, f1.end());
	EXPECT_EQ(cpf.second, f1.end());
}

TEST_F(MapEqualRangeTest, multitest) {
	for (int i = -5; i < 205; ++i) {
		iter = static_cast<double>(i) * 0.5;

		ps = s.equal_range(std::to_string(iter));
		pf = f.equal_range(std::to_string(iter));
		checkMapsAreEqualIt(pf.first, pf.second, ps.first, ps.second);
	}
}

TEST_F(MapEqualRangeTest, multitestConst) {
	for (int i = -5; i < 205; ++i) {
		iter = static_cast<double>(i) * 0.5;

		cps = s.equal_range(std::to_string(iter));
		cpf = f.equal_range(std::to_string(iter));
		checkMapsAreEqualIt(cpf.first, cpf.second, cps.first, cps.second);
	}
}

class MapEraseSimpleTest : public testing::Test {
protected:
	virtual void SetUp() {
			s.insert(std::make_pair("a", 1));
			s.insert(std::make_pair("b", 1));
			s.insert(std::make_pair("c", 1));
			f.insert(std::make_pair("a", 1));
			f.insert(std::make_pair("b", 1));
			f.insert(std::make_pair("c", 1));
	}

	std::map<std::string, int> s;
	ft::map<std::string, int>  f;

};

void	MapEraseSimpleTestFunc(ft::map<std::string, int> & f, std::map<std::string, int> & s,
							   std::string s1, std::string s2, std::string s3) {
	size_t retf;
	size_t rets;

	rets = s.erase(s1 + s2 + s3);
	retf = f.erase(s1 + s2 + s3);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(*s.begin(), *f.begin());
	EXPECT_EQ(*--s.end(), *--f.end());
	checkIfMapsAreEqual(f, s);

	rets = s.erase(s1);
	retf = f.erase(s1);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(*s.begin(), *f.begin());
	EXPECT_EQ(*--s.end(), *--f.end());
	checkIfMapsAreEqual(f, s);

	rets = s.erase(s2);
	retf = f.erase(s2);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(*s.begin(), *f.begin());
	EXPECT_EQ(*--s.end(), *--f.end());
	checkIfMapsAreEqual(f, s);

	rets = s.erase(s3);
	retf = f.erase(s3);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(s.begin(), s.end());
	EXPECT_EQ(f.begin(), f.end());
	checkIfMapsAreEqual(f, s);

	rets = s.erase(s1);
	retf = f.erase(s1);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(s.begin(), s.end());
	EXPECT_EQ(f.begin(), f.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapEraseSimpleTest, abc) {
	MapEraseSimpleTestFunc(f, s, "a", "b", "c");
}

TEST_F(MapEraseSimpleTest, acb) {
	MapEraseSimpleTestFunc(f, s, "a", "c", "b");
}

TEST_F(MapEraseSimpleTest, bac) {
	MapEraseSimpleTestFunc(f, s, "b", "a", "c");
}

TEST_F(MapEraseSimpleTest, bca) {
	MapEraseSimpleTestFunc(f, s, "b", "c", "a");
}

TEST_F(MapEraseSimpleTest, cab) {
	MapEraseSimpleTestFunc(f, s, "c", "a", "b");
}

TEST_F(MapEraseSimpleTest, cba) {
	MapEraseSimpleTestFunc(f, s, "c", "b", "a");
}

class MapEraseNoContainTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (char i = 'b'; i < 'z' ; ++i) {
			ss << i << i;
			s.insert(std::make_pair(ss.str(), i));
			f.insert(std::make_pair(ss.str(), i));
			ss.str("");
		}
	}

	std::stringstream ss;

	std::map<std::string, int> s;
	ft::map<std::string, int>  f;

	size_t retf;
	size_t rets;
};

TEST_F(MapEraseNoContainTest, eraseSimpleTest) {
	for (char i = 'a'; i <= 'z' ; ++i) {
		ss << i << i << i;
		rets = s.erase(ss.str());
		retf = f.erase(ss.str());
		EXPECT_EQ(retf, rets);
		EXPECT_EQ(*s.begin(), *f.begin());
		EXPECT_EQ(*--s.end(), *--f.end());
		checkIfMapsAreEqual(f, s);
		ss.str("");
	}

	for (char i = 'a'; i <= 'z' ; ++i) {
		ss << i;
		rets = s.erase(ss.str());
		retf = f.erase(ss.str());
		EXPECT_EQ(retf, rets);
		EXPECT_EQ(*s.begin(), *f.begin());
		EXPECT_EQ(*--s.end(), *--f.end());
		checkIfMapsAreEqual(f, s);
		ss.str("");
	}
}

class MapEraseByIteratorTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (char i = 'b'; i < 'z' ; ++i) {
			ss << i << i;
			s.insert(std::make_pair(ss.str(), i));
			f.insert(std::make_pair(ss.str(), i));
			ss.str("");
		}
	}

	std::stringstream ss;

	std::map<std::string, int>::iterator its;
	ft::map<std::string,  int>::iterator itf;
	std::map<std::string, int>::iterator itse;
	ft::map<std::string,  int>::iterator itfe;

	std::map<std::string, int> s;
	ft::map<std::string, int>  f;
};

TEST_F(MapEraseByIteratorTest, eraseAllByBegin) {

	its = s.begin();
	itse = s.end();
	itf = f.begin();
	itfe = f.end();

	for (; s.begin() != itse; ) {
		s.erase(s.begin());
		f.erase(f.begin());
		checkIfMapsAreEqual(f, s);
	}
	EXPECT_EQ(f.begin(), itfe);
}

TEST_F(MapEraseByIteratorTest, eraseAllByEnd) {

	its = s.begin();
	itse = s.end();
	itf = f.begin();
	itfe = f.end();

	while (s.size() != 0) {
		s.erase(--s.end());
		f.erase(--f.end());
		checkIfMapsAreEqual(f, s);
	}
	EXPECT_EQ(f.size(), 0);
}

TEST_F(MapEraseByIteratorTest, iteratorValidity) {
	its = s.begin();
	itf = f.begin();

	for (int i = 0; i < 10; ++i) {
		s.erase(++s.begin());
		f.erase(++f.begin());
		EXPECT_EQ(s.size(), f.size());
		checkMapsAreEqualIt(itf, f.end(), its, s.end());
	}
}

TEST_F(MapEraseByIteratorTest, iteratorValidity2) {
	ft::map<char, int> ftmap;
	ft::map<char,int>::iterator itf;
	std::map<char, int> stmap;
	std::map<char, int>::iterator its;

	ftmap.insert(std::make_pair('a', 123));		stmap.insert(std::make_pair('a', 123));
	ftmap.insert(std::make_pair('b', 123));		stmap.insert(std::make_pair('b', 123));
	ftmap.insert(std::make_pair('c', 123));		stmap.insert(std::make_pair('c', 123));
	ftmap.insert(std::make_pair('d', 123));		stmap.insert(std::make_pair('d', 123));
	ftmap.insert(std::make_pair('e', 123));		stmap.insert(std::make_pair('e', 123));
	ftmap.insert(std::make_pair('f', 123));		stmap.insert(std::make_pair('f', 123));
	ftmap.insert(std::make_pair('g', 123));		stmap.insert(std::make_pair('g', 123));
	ftmap.insert(std::make_pair('h', 123));		stmap.insert(std::make_pair('h', 123));
	ftmap.insert(std::make_pair('j', 123));		stmap.insert(std::make_pair('j', 123));
	ftmap.insert(std::make_pair('k', 123));		stmap.insert(std::make_pair('k', 123));

	itf = ftmap.find('c');	its = stmap.find('c');
	ftmap.erase('b');		stmap.erase('b');

	checkMapsAreEqualIt(itf, ftmap.end(), its, stmap.end());
}

class MapClearTest : public testing::Test {
protected:
	virtual void SetUp() {

	}
	std::map<std::string, int> s;
	ft::map<std::string, int>  f;
};

TEST_F(MapClearTest, emptyClear) {
	s.clear();
	f.clear();

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapClearTest, nonEmptyClear) {
	for (int i = 0; i < 100; ++i) {
		s.insert(std::make_pair(std::to_string(i), i));
		f.insert(std::make_pair(std::to_string(i), i));
	}

	s.clear();
	f.clear();
	checkIfMapsAreEqual(f, s);
}

class MapAssignationTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s.insert(std::make_pair(std::to_string(i), i));
			f.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> s;
	ft::map<std::string, int>  f;
	std::map<std::string, int> sEmpty;
	ft::map<std::string, int>  fEmpty;
	std::map<std::string, int> sTmp;
	ft::map<std::string, int>  fTmp;
};

TEST_F(MapAssignationTest, fromFullToEmpty) {
	sEmpty = s;
	fEmpty = f;
	checkIfMapsAreEqual(fEmpty, sEmpty);
	checkIfMapsAreEqual(f, s);

	sEmpty.insert(std::make_pair("sf", 23));
	fEmpty.insert(std::make_pair("sf", 23));
	checkIfMapsAreEqual(fEmpty, sEmpty);
}

TEST_F(MapAssignationTest, fromEmtpyToFull) {
	s = sEmpty;
	f = fEmpty;
	checkIfMapsAreEqual(fEmpty, sEmpty);
	checkIfMapsAreEqual(f, s);

	s.insert(std::make_pair("sf", 23));
	f.insert(std::make_pair("sf", 23));
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapAssignationTest, fromEmtpyToEmpty) {
	sTmp = sEmpty;
	fTmp = fEmpty;
	checkIfMapsAreEqual(fEmpty, sEmpty);
	checkIfMapsAreEqual(fTmp, sTmp);

	sTmp.insert(std::make_pair("sf", 23));
	fTmp.insert(std::make_pair("sf", 23));
	checkIfMapsAreEqual(fTmp, sTmp);
}

TEST_F(MapAssignationTest, fromFullToFull) {
	sEmpty.insert(std::make_pair("sf", 23));
	fEmpty.insert(std::make_pair("sf", 23));
	s = sEmpty;
	f = fEmpty;
	checkIfMapsAreEqual(fEmpty, sEmpty);
	checkIfMapsAreEqual(fTmp, sTmp);

	s.insert(std::make_pair("sf", 23));
	f.insert(std::make_pair("sf", 23));
	checkIfMapsAreEqual(f, s);
}

class MapCopyConstructionTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s.insert(std::make_pair(std::to_string(i), i));
			f.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> s;
	ft::map<std::string, int>  f;
	std::map<std::string, int> sEmpty;
	ft::map<std::string, int>  fEmpty;

};

TEST_F(MapCopyConstructionTest, fromFull) {
	std::map<std::string, int> s1 = s;
	ft::map<std::string, int>  f1 = f;
	
	checkIfMapsAreEqual(f1, s1);
	checkIfMapsAreEqual(f, s);

	s1.insert(std::make_pair("sf", 23));
	f1.insert(std::make_pair("sf", 23));
	checkIfMapsAreEqual(f1, s1);
}

TEST_F(MapCopyConstructionTest, fromEmtpy) {
	std::map<std::string, int> s1 = sEmpty;
	ft::map<std::string, int>  f1 = fEmpty;

	checkIfMapsAreEqual(f1, s1);
	checkIfMapsAreEqual(fEmpty, sEmpty);

	s1.insert(std::make_pair("sf", 23));
	f1.insert(std::make_pair("sf", 23));
	checkIfMapsAreEqual(f1, s1);
}

class MapSwapTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s1.insert(std::make_pair(std::to_string(i), i));
			f1.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> s2, s1;
	ft::map<std::string, int>  f2, f1;
};

TEST_F(MapSwapTest, integrityFullEmpty) {
	s1.swap(s2);
	f1.swap(f2);

	checkIfMapsAreEqual(f1, s1);
	checkIfMapsAreEqual(f2, s2);
}

TEST_F(MapSwapTest, integrityEmptyFull) {
	s2.swap(s1);
	f2.swap(f1);

	checkIfMapsAreEqual(f1, s1);
	checkIfMapsAreEqual(f2, s2);
}

TEST_F(MapSwapTest, integrityFullFull) {
	s2.insert(std::make_pair("std::to_string(i)", 123));
	f2.insert(std::make_pair("std::to_string(i)", 123));

	s2.swap(s1);
	f2.swap(f1);

	checkIfMapsAreEqual(f1, s1);
	checkIfMapsAreEqual(f2, s2);
}

TEST_F(MapSwapTest, iteratorValidity) {
	std::map<std::string, int>::iterator its = ++s1.begin();
	ft::map<std::string,  int>::iterator itf = ++f1.begin();

	s2.insert(std::make_pair("std::to_string(i)", 123));
	f2.insert(std::make_pair("std::to_string(i)", 123));

	s2.swap(s1);
	f2.swap(f1);

	checkIfMapsAreEqual(f1, s1);
	checkIfMapsAreEqual(f2, s2);
	checkMapsAreEqualIt(itf, f2.end(), its, s2.end());
}

class MapEraseRangeTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = -50; i < 50; ++i) {
			sRef.insert(std::make_pair(std::to_string(i), i));
			fRef.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> sRef, s;
	ft::map<std::string, int>  fRef, f;

	std::map<std::string, int>::iterator its, jts, itse, itsdel1, itsdel2, itscheck, itschecke;
	ft::map<std::string, int>::iterator itfdel1, itfdel2, itfcheck, itfchecke;

	size_t retf;
	size_t rets;
};

TEST_F(MapEraseRangeTest, eraseSimpleTest) {
	itse = sRef.end();
	int i = 0;
	int j = 0;

	for (its = sRef.begin(); its != itse; ++its) {
		j = i;
		for (jts = its; true; ++jts) {
			f = fRef;
			s = sRef;
			checkIfMapsAreEqual(f, s);
			itsdel1 = s.find(its->first);
			itfdel1 = f.find(its->first);
			itsdel2 = s.find(jts->first);
			itfdel2 = f.find(jts->first);
			s.erase(itsdel1, itsdel2);
			f.erase(itfdel1, itfdel2);

			EXPECT_EQ(f.size(), s.size()) << "from = " << i << " to = " << j;
			EXPECT_EQ(f.empty(), s.empty()) << "from = " << i << " to = " << j;
			itschecke = s.end();
			itfchecke = f.end();
			itfcheck = f.begin();
			for (itscheck = s.begin(); itscheck != itschecke; ) {
				EXPECT_EQ(*itscheck++, *itfcheck++) << "from = " << i << " to = " << j;
			}
			EXPECT_EQ(itfcheck, itfchecke) << "from = " << i << " to = " << j;
//			std::cout << "i " << i << " j " << j << std::endl;
			if (jts == itse)
				break;
			j++;
		}
		i++;
	}
}

class MapOperatorSqBracketsTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = -200; i < 200; i += 2) {
			s.insert(std::make_pair(std::to_string(i), i));
			f.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> s;
	ft::map<std::string, int>  f;
};

TEST_F(MapOperatorSqBracketsTest, fullTest) {
	for (int i = -200; i < 200; ++i) {
		s[std::to_string(i)] = i % 2;
		f[std::to_string(i)] = i % 2;
		checkIfMapsAreEqual(f, s);
//		std::cout << i << std::endl;
	}
}
