# coding: utf-8
# author: Benoit Pingris
"""
 Hold connection with server
"""

import os
import socket
import macro

class Connect:
    """
     Connect class
    """

    def __init__(self, opt):
        self.opt = opt
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def connect_to_serv(self):
        """
        Connect to server

        Returns:
            bool: Either connected to server or not
        """

        try:
            self.socket.connect((self.opt.machine, self.opt.port))
        except (ConnectionError, socket.gaierror) as err:
            print(err)
            return False
        print('[+] Connected to {}:{}\n'.format(self.opt.machine, self.opt.port))
        return True

    def send_cmd(self, cmd):
        """
        Send command to server

        Args:
            cmd (str): command to be sent
        """
        self.socket.send(cmd.encode())

    def recv_response(self):
        """
        Get server's response
        """
        res = self.socket.recv(macro.BUFF_SIZE).decode().split('\n')
        res = list(filter(None, res))
        return res[0] if len(res) == 1 else res
