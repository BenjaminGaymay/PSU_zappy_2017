# coding: utf-8
"""
Inventory class
"""

class Inventory:
    """
    Inventory class

    Returns:
        Inventory
    """

    def __init__(self):
        self.bag = {
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane':0,
            'phiras': 0,
            'thystame': 0,
            'food': 0,
            'player': 0
        }
        self.empty = True

    def is_empty(self):
        """
        Returns wheter the bag is empty or not

        Returns:
            bool: empty bag
        """

        return self.empty


    def fill(self, data):
        """
        Fill inventory with data

        Args:
            data (string): Data sent by the server
        """
        print(data)
        data = data.replace('[', '')    \
                   .replace(']', '')    \
                   .replace(', ', ',')  \
                   .replace(' ,', ',')  \
                   .strip()             \
                   .split(',')
        print(data)
        for elem in data:
            tmp = elem.split(' ')
            try:
                self.bag[tmp[0]] = int(tmp[1])
            except ValueError as err:
                print(err)
                return False
        self.empty = False
        return True
