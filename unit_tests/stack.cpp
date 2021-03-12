/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 10:38:08 by matrus            #+#    #+#             */
/*   Updated: 2020/11/28 10:38:12 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include "stack.hpp"
#include <stack>
#include <string>

class StackFullTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			svec.push_back(std::to_string(i));
			fvec.push_back(std::to_string(i));
		}
	}

	std::vector<std::string> svec;
	ft::vector<std::string> fvec;

};

TEST_F(StackFullTest, testFunctional) {
	std::stack<std::string> s;
	ft::stack<std::string> f;

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

	std::stack<std::string, std::vector<std::string>> s2(svec);
	ft::stack<std::string, ft::vector<std::string>>  f2(fvec);
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

TEST_F(StackFullTest, testOperators) {
	std::stack<std::string, std::vector<std::string> > s1, s2;
	ft::stack<std::string, ft::vector<std::string> > f1, f2;

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
