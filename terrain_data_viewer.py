import math

import pygtk
pygtk.require('2.0')
import gtk

from dice_math import fix_dice

import terrain_generator

class TerrainDataView():
    def __init__(self):
        self.terrain = terrain_generator.Terrain([100,100], 6, 5, .4,4, 3, 1)

        self.top = gtk.Fixed()

        self.tabs = gtk.Notebook()
        self.top.add(self.tabs)

        self.tabs.append_page(self.create_traps_tab(), gtk.Label("Traps"))
        self.tabs.append_page(self.create_treasure_tab(), gtk.Label("Treasure"))

    def update(self):
        while self.tabs.get_n_pages():
            self.tabs.remove_page(-1)
        self.tabs.append_page(self.create_traps_tab(), gtk.Label("Traps"))
        self.tabs.append_page(self.create_treasure_tab(), gtk.Label("Treasure"))
        self.top.show_all()

    def create_traps_tab(self):

        self.traps_tab_scroller = gtk.ScrolledWindow()
        self.traps_tab_scroller.set_policy(gtk.POLICY_AUTOMATIC,
                                         gtk.POLICY_ALWAYS)
        self.traps_tab_scroller.set_size_request(100,100)


        self.traps_tab = gtk.VBox(homogeneous=True)
        self.traps_tab_scroller.add_with_viewport(self.traps_tab)
        self. traps_tab_scroller.set_size_request(250,440)
        self.trap_boxes = []

        for trap in self.terrain.traps:
            self.trap_boxes.append(self.create_trap_box(trap))
            self.traps_tab.pack_start(self.trap_boxes[-1])

        return self.traps_tab_scroller

    def create_trap_box(self, trap):
        box = gtk.Fixed()

        box.trap_name = gtk.Label("Trap: " + str(trap.ID + 1))
        box.put(box.trap_name, 0, 0)

        box.trap_trigger = gtk.Label("Trap Type:")
        box.put(box.trap_trigger, 0, 20)

        box.trap_reset = gtk.Label("Trigger: " + trap.trigger + ". Reset: " + trap.reset + ".")
        box.put(box.trap_reset, 0, 40)

        box.trap_find = gtk.Label("Dice required:")
        box.put(box.trap_find, 0, 60)

        box.trap_disable = gtk.Label("To find: " + str(trap.findDc) + ". To disable: " + str(trap.disableDc) + ".")
        box.put(box.trap_disable, 0, 80)

        box.trap_die = gtk.Label("Dammage: " + str(trap.die) + " D " + str(fix_dice(trap.dammage)) + ".")
        box.put(box.trap_die, 0, 100)

        box.trap_padding = gtk.Label()
        box.put(box.trap_padding, 0, 120)

        return box

    def create_treasure_tab(self):

        self.treasure_tab_scroller = gtk.ScrolledWindow()
        self.treasure_tab_scroller.set_policy(gtk.POLICY_AUTOMATIC,
                                         gtk.POLICY_ALWAYS)
        self.treasure_tab_scroller.set_size_request(100,100)


        self.treasure_tab = gtk.VBox()
        self.treasure_tab_scroller.add_with_viewport(self.treasure_tab)
        self. treasure_tab_scroller.set_size_request(250,440)
        self.treasure_boxes = []

        for treasure in self.terrain.treasure:
            self.treasure_boxes.append(self.create_treasure_box(treasure))
            self.treasure_tab.pack_start(self.treasure_boxes[-1])

        return self.treasure_tab_scroller

    def create_treasure_box(self, treasure):
        box = gtk.Fixed()

        box.treasure_name = gtk.Label("Treasure: " + str(treasure.ID + 1))
        box.put(box.treasure_name, 0, 0)

        box.treasure_type = gtk.Label("treasure Type: " + treasure.type_ + ".")
        box.put(box.treasure_type, 0, 20)

        if treasure.trap != -1:
            box.treasure_trap = gtk.Label("Trapped by trap: " + str(treasure.trap.ID) + ".")
            box.put(box.treasure_trap, 0, 40)

            box.treasure_padding = gtk.Label()
            box.put(box.treasure_padding, 0, 60)

        else:
            box.treasure_padding = gtk.Label()
            box.put(box.treasure_padding, 0, 40)

        return box

        

    @property
    def top(self):
        return self.top

