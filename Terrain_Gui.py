import threading
import math

import pygtk
pygtk.require('2.0')
import gtk

import terrain_generator 
from terrain_viewer import TerrainView
from terrain_data_viewer import TerrainDataView
from terrain_controller import TerrainController
from terrain_viewer_controller import TerrainViewController
from dice_gui import DiceGui

class TerrainGui():
    def __init__(self):
        self.top = gtk.Fixed()
        
        self.content = gtk.Table(rows=5, columns=4)
        self.top.add(self.content)

        seperator = gtk.VSeparator()
        self.content.attach(seperator,1,2,0,4)

        seperator = gtk.VSeparator()
        self.content.attach(seperator,3,4,0,4)

        seperator = gtk.HSeparator()
        self.content.attach(seperator,2,3,1,2)

        self.terrain_view = TerrainView()
        self.content.attach(self.terrain_view.top,2,3,0,1)

        self.terrain_data = TerrainDataView()
        self.content.attach(self.terrain_data.top,4,5,0,2)

        self.terrain_controller = TerrainController(self.terrain_view, self.terrain_data)
        self.content.attach(self.terrain_controller.top,0,1,0,4)

        self.terrain_view_controller = TerrainViewController(self.terrain_view)
        self.content.attach(self.terrain_view_controller.top,2,3,2,4)

        self.dice = DiceGui()
        self.content.attach(self.dice.top,4,5,3,4)


    @property
    def top(self):
        return self.top
