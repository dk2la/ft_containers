/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 10:38:07 by matrus            #+#    #+#             */
/*   Updated: 2020/11/28 10:38:12 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include "queue.hpp"
#include <queue>
#include <list>
#include <string>

class QueueFullTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			svec.push_back(std::to_string(i));
			fvec.push_back(std::to_string(i));
		}
	}

	std::list<std::string> svec;
	ft::list<std::string> fvec;

};

TEST_F(QueueFullTest, testFunctional) {
	std::queue<std::string> s;
	ft::queue<std::string> f;

	EXPECT_EQ(s.empty(), f.empty());
	EXPECT_EQ(s.size(), f.size());

	s.push("23");
	f.push("23");
	EXPECT_EQ(s.empty(), f.empty());
	EXPECT_EQ(s.size(), f.size());

	s.push("213");
	f.push("213");
	EXPECT_EQ(s.empty(), f.empty());
	EXPECT_EQ(s.size(), f.size());

	s.pop();
	f.pop();
	EXPECT_EQ(s.empty(), f.empty());
	EXPECT_EQ(s.size(), f.size());

	s.pop();
	f.pop();
	EXPECT_EQ(s.empty(), f.empty());
	EXPECT_EQ(s.size(), f.size());

	std::queue<std::string, std::list<std::string>> s2(svec);
	ft::queue<std::string, ft::list<std::string>>  f2(fvec);
	EXPECT_EQ(s2.empty(), f2.empty());
	EXPECT_EQ(s2.size(), f2.size());

	s2.push("23");
	f2.push("23");
	EXPECT_EQ(s2.empty(), f2.empty());
	EXPECT_EQ(s2.size(), f2.size());

	s2.push("213");
	f2.push("213");
	EXPECT_EQ(s2.empty(), f2.empty());
	EXPECT_EQ(s2.size(), f2.size());

	while (!s2.empty()) {
		s2.pop();
		f2.pop();
		EXPECT_EQ(s2.empty(), f2.empty());
		EXPECT_EQ(s2.size(), f2.size());
	}

}

TEST_F(QueueFullTest, testOperators) {
	std::queue<std::string, std::list<std::string> > s1, s2;
	ft::queue<std::string, ft::list<std::string> > f1, f2;

	s1.push("123");
	s1.push("321");
	s2.push("123");

	f1.push("123");
	f1.push("321");
	f2.push("123");

	EXPECT_EQ(s1, s1);
	EXPECT_EQ(f1, f1);

	EXPECT_NE(s1, s2);
	EXPECT_NE(f1, f2);

	EXPECT_LT(s2, s1);
	EXPECT_LT(f2, f1);

	EXPECT_LE(s2, s1);
	EXPECT_LE(f2, f1);

	EXPECT_GT(s1, s2);
	EXPECT_GT(f1, f2);

	EXPECT_GE(s1, s2);
	EXPECT_GE(f1, f2);
}
