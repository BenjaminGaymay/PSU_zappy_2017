/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/
#pragma once

#include <iostream>
#include <vector>

namespace Graphical {
	typedef struct {
		int x;
		int y;
	} Pos;

	static std::vector<std::string> explode(const std::string &str, char separator)
	{
		std::string tmp;
		std::vector<std::string> splited;

		for (auto &c: str) {
			if (c != separator)
				tmp += c;
			else if (c == separator && !tmp.empty()) {
				splited.push_back(tmp);
				tmp.clear();
			}
		}
		if (!tmp.empty())
			splited.push_back(tmp);
		return splited;
	}
}