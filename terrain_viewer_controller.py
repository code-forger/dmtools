import math

import pygtk
pygtk.require('2.0')
import gtk

import terrain_generator

def parse_num(s):
    try:
        return int(s)
    except exceptions.ValueError:
        return float(s)

class TerrainViewController():
    def draw_mode_discrete_click(self, widget):
        self.terrain_view.draw_mode = "basic"
        self.terrain_view.show_terrain()

    def draw_mode_all_click(self, widget):
        self.terrain_view.draw_mode = "advanced"
        self.terrain_view.show_terrain()

    def resolution_callback(self, widget, data=None):
        text = widget.get_text()
        value = parse_num(text)
        self.terrain.resolution = value
        self.terrain_view.regen_pixelmap()

    def __init__(self, terrain_view):
        self.terrain = terrain_generator.Terrain([100,100], 6, 5, .4,4, 3, 1, 1)
        self.terrain_view = terrain_view

        self.top = gtk.Fixed()
        self.top.set_size_request(500,200)

        self.draw_mode_box = gtk.VBox(homogeneous=True)
        self.top.add(self.draw_mode_box)

        self.draw_mode_title = gtk.Label("View Mode:")
        self.draw_mode_box.pack_start(self.draw_mode_title)

        self.draw_mode_all = gtk.RadioButton(label="Show All")
        self.draw_mode_all.connect("clicked", self.draw_mode_all_click)
        self.draw_mode_box.pack_start(self.draw_mode_all)

        self.draw_mode_discrete = gtk.RadioButton(group=self.draw_mode_all,
                                                  label="Hide all.")
        self.draw_mode_discrete.connect("clicked", self.draw_mode_discrete_click)
        self.draw_mode_box.pack_start(self.draw_mode_discrete)

        self.resolution_box = gtk.VBox(homogeneous=True)
        self.top.put(self.resolution_box, 100,0)

        self.resolution_label = gtk.Label('Resolution:')
        self.resolution_box.pack_start(self.resolution_label)

        self.resolution_entry = gtk.Entry()
        self.resolution_entry.set_text(str(self.terrain.resolution))
        self.resolution_entry.connect('activate', self.resolution_callback)
        self.resolution_box.pack_start(self.resolution_entry)


    @property
    def top(self):
        return self.top
