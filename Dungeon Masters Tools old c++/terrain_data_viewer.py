import math

import pygtk
pygtk.require('2.0')
import gtk

import terrain_generator

class TerrainDataView():
    def __init__(self):
        self.terrain = terrain_generator.Terrain([100,100], 6, 5, .4,4, 3, 1)

        self.top = gtk.Fixed()

        self.tabs = gtk.Notebook()
        self.top.add(self.tabs)

        self.tabs.append_page(create_traps_tab())

    def create_traps_tab(self):
        self.traps_tab = gtk.VBox(homogeneous=True)
        self.trap_boxes = []

        for trap in terrain.traps:
            self.trap_boxes.append(create_trap_box(trap))
            self.traps_tab.pack_start(self.trap_boxes[-1])

        return self.traps_tab

    def create_trap_box(self, trap):
        box = gtk.Fixed()

        box.trap_trigger = gtk.Label(trap.trigger)
        box.add(box.trap_trigger, 0, 0)

        box.trap_reset = gtk.Label(trap.reset)
        box.add(box.trap_reset, 0, 50)

        box.trap_find = gtk.Label(str(trap.findDC))
        box.add(box.trap_find, 30, 0)

        box.trap_disable = gtk.Label(str(trap.disable))
        box.add(box.trap_disable, 30, 50)

        box.trap_die = gtk.Label(str(trap.die) + " D ")
        box.add(box.trap_die, 60, 0)

        box.trap_dammage = gtk.Label(str(trap.dammage))
        box.add(box.trap_dammage, 60,50)

        return box

        

    @property
    def top(self):
        return self.top

