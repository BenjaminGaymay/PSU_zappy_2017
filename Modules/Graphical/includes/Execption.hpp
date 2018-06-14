/*
** EPITECH PROJECT, 2018
** student
** File description:
** 13/06/18
*/
#pragma once

#include <iostream>
#include <exception>

namespace Graphical {
	class NotFound : public std::exception {
	public:
		explicit NotFound(const std::string &msg) : _msg(msg) {};
		NotFound(const NotFound &obj) :_msg(obj.getMsg()){};
		~NotFound() override = default;
		const char *what() const noexcept override { return _msg.c_str(); };
		const std::string &getMsg() const { return _msg; };
	private:
		const std::string _msg;
	};
}