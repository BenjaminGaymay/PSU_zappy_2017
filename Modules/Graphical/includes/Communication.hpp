/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/
#pragma once

#include "macro.h"
#include "sockets.h"

namespace Graphical {
	class Communication {
	public:
		explicit Communication(const int &port)
		{
			_socket = create_socket(port, inet_addr("127.0.0.1"), CLIENT);
			if (_socket == FD_ERROR)
				throw std::logic_error("Create socket failed.");
		};

		~Communication()
		{
			if (isValidFd(_socket))
				close(_socket);
		};

		static bool isValidFd(const int &fd)
		{
			return (fcntl(fd, F_GETFD) != -1);
		}

	private:
		int _socket;
	};
}