import pygtk
pygtk.require('2.0')
import gtk

import random

import singleton

class Dice():
    __metaclass__ = singleton.Singleton
    def __init__(self):
        self._total = 0

    def roll(self,dice_faces):
        self._total = random.randint(1, dice_faces)

    @property
    def result(self):
        return self._total

    def reset(self):
        self._total = 0
