/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/
#pragma once

#include <stdexcept>
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

		bool closeFd(const int &fd)
		{
			if (isValidFd(fd))
				return close(fd), true;
			return false;
		}

		std::vector<std::string> readFd(int fd)
		{
			std::vector<std::string> array;
			static char buffer[4096];
			ssize_t size;
			char *tmp = nullptr;

			size = read(fd, buffer, 4096);
			if (size > 0) {
				buffer[size] = '\0';
				tmp = strtok(buffer, "\n");
				while (tmp) {
					array.push_back(tmp);
					tmp = strtok(nullptr, "\n");
				}
			} else
				closeFd(_socket);
			return array;
		}

		const int &getSocket() const { return _socket; };
	private:
		int _socket;
	};
}