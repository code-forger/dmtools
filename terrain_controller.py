import exceptions

import pygtk
pygtk.require('2.0')
import gtk

import terrain_generator

def parse_num(s):
    try:
        return int(s)
    except exceptions.ValueError:
        return float(s)

class TerrainController():
    def refresh_callback(self, widget, data=None):
        self.terrain.generate_terrain()
        self.terrain_view.show_terrain()
        self.terrain_data.update()

    def size_callback(self, widget, data=None):
        text = widget.get_text().split(',')
        value = map(parse_num,text)
        self.terrain.size = value
        self.terrain_view.regen_pixelmap()

    def rooms_callback(self, widget, data=None):
        text = widget.get_text()
        value = parse_num(text)
        self.terrain.target_rooms = value

    def room_size_callback(self, widget, data=None):
        text = widget.get_text()
        value = parse_num(text)
        self.terrain.room_size = value

    def wander_callback(self, widget, data=None):
        text = widget.get_text()
        value = parse_num(text)
        self.terrain.variation = value

    def traps_per_room_callback(self, widget, data=None):
        text = widget.get_text()
        value = parse_num(text)
        self.terrain.traps_per_room = value

    def treasure_per_room_callback(self, widget, data=None):
        text = widget.get_text()
        value = parse_num(text)
        self.terrain.treasure_per_room = value

    def party_level_callback(self, widget, data=None):
        text = widget.get_text()
        value = parse_num(text)
        self.terrain.party_level = value

    def __init__(self, terrain_view, terrain_data):
        self.terrain_view = terrain_view
        self.terrain_data = terrain_data
        self.terrain = terrain_generator.Terrain([100,100], 6, 5, .4,4, 3, 1, 1)

        self.top = gtk.Fixed()

        self.content = gtk.VBox(homogeneous=True)
        self.content.set_border_width(2)
        self.top.add(self.content)

        def add_control(self, name, title, text):
            exec("self.%s_label = gtk.Label('%s:')"%(name,title))
            exec("self.content.pack_start(self.%s_label)"%(name))

            exec("self.%s_entry = gtk.Entry()"%(name))
            exec("self.%s_entry.set_text('%s')"%(name,text))
            exec("self.%s_entry.connect('activate', self.%s_callback)"%(name,name))
            exec("self.content.pack_start(self.%s_entry)"%(name))

            exec("self.%s_padding = gtk.Label('')"%(name))
            exec("self.content.pack_start(self.%s_padding)"%(name))

        add_control(self, "size","Grid size: x,y",str(self.terrain.size[0]) + "," +
                                                  str(self.terrain.size[1]))
        add_control(self, "rooms","Number of Rooms",str(self.terrain.target_rooms))
        add_control(self, "room_size","Size of rooms",str(self.terrain.room_size))
        add_control(self, "wander","Wander of path",str(self.terrain.variation))
        add_control(self, "traps_per_room","Traps per room",str(self.terrain.traps_per_room))
        add_control(self, "treasure_per_room","Treasure per room",str(self.terrain.treasure_per_room))
        add_control(self, "party_level","Party Level",str(self.terrain.party_level))

        self.refresh = gtk.Button("Generate")
        self.refresh.connect("clicked", self.refresh_callback)
        self.content.pack_start(self.refresh)

    @property
    def top(self):
        return self.top
