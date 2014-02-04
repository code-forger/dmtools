import math

import pygtk
pygtk.require('2.0')
import gtk

import terrain_generator

class TerrainView():
    def configure_event(self, widget, event):
        x, y, width, height = widget.get_allocation()
        if self.da_pixmap == None:
            self.da_pixmap = gtk.gdk.Pixmap(widget.get_window(), width, height, depth=-1)
            self.show_terrain()
        return gtk.TRUE

    def expose_event(self, widget, event):
        x , y, width, height = event.area
        widget.window.draw_drawable(widget.get_style().fg_gc[gtk.STATE_NORMAL],
                                    self.da_pixmap, x, y, x, y, width, height)
        return gtk.FALSE

    def regen_pixelmap(self):
        self.da_pixmap = None #forces recreation of pixel map
        self.da.set_size_request(self.terrain.size[1]*self.terrain.resolution, 
                                     self.terrain.size[0]*self.terrain.resolution)
        window = self.da.get_toplevel()
        window.resize(*window.size_request())


    def __init__(self):
        self.terrain = terrain_generator.Terrain([100,100], 6, 5, .4,4, 3, 1, 1)

        self.top = gtk.Fixed()

        self.da = gtk.DrawingArea()
        self.da.set_size_request(self.terrain.size[0]*self.terrain.resolution, 
                                 self.terrain.size[1]*self.terrain.resolution)
        self.da.connect("expose_event", self.expose_event)
        self.da.connect("configure_event", self.configure_event)
        self.top.add(self.da)
        self.da_pixmap = None

        self.draw_mode = "advanced"


    def show_terrain(self):
        ax, ay, width, height = self.da.get_allocation()
        rect = self.da.get_allocation() 
        self.da_pixmap.draw_rectangle(self.da.get_style().white_gc,
                          gtk.TRUE, 0,0,width, height)
        for x in range(len(self.terrain.grid)):
            for y in range(len(self.terrain.grid[0])):
                if self.draw_mode == "basic":
                    self.draw_pixel(x,y,self.terrain.basic_grid[x][y])
                else:
                    self.draw_pixel(x,y,self.terrain.grid[x][y])

        for r in self.terrain.rooms:
            self.draw_room(r)

        self.da.queue_draw_area(0,0, width, height)

    def draw_room(self, room):
        resolution = self.terrain.resolution
        gc = gtk.gdk.GC(self.da.window)
        if room.shape == "square":
            points = []
            for a in [0, math.pi/2, math.pi, math.pi/2*3]:
                points.append((resolution*int(1 + room.pos[0] + (room.size*math.cos(room.angle+a))),
                              (resolution*int(1 + room.pos[1] + (room.size*math.sin(room.angle+a))))))
            if self.draw_mode == "basic":
                gc.set_foreground(self.da.get_colormap().alloc(65535, 65535, 65535))
                self.da_pixmap.draw_polygon(gc, True, points)
            gc.set_foreground(self.da.get_colormap().alloc(0, 0, 0))
            self.da_pixmap.draw_polygon(gc, False, points)
        else:
            if self.draw_mode == "basic":
                gc.set_foreground(self.da.get_colormap().alloc(65535, 65535, 65535))
                self.da_pixmap.draw_arc(gc, True, resolution*int(1 + room.pos[0]-room.size/2),
                                                  resolution*int(1 + room.pos[1]-room.size/2),
                                                  resolution*int(room.size), resolution*int(room.size),
                                                  0, 64*360)
            gc.set_foreground(self.da.get_colormap().alloc(0, 0, 0))
            self.da_pixmap.draw_arc(gc, False, resolution*int(1 + room.pos[0]-room.size/2),
                                               resolution*int(1 + room.pos[1]-room.size/2),
                                               resolution*int(room.size), resolution*int(room.size),
                                               0, 64*360)
        

    def draw_pixel(self, x, y, code):
        resolution = self.terrain.resolution
        gc = gtk.gdk.GC(self.da.window)
        if code == 0:
            gc.set_foreground(self.da.get_colormap().alloc(65535, 65535, 65535))
        elif code == 1:
            gc.set_foreground(self.da.get_colormap().alloc(0, 0, 0))
        elif code == 2:
            gc.set_foreground(self.da.get_colormap().alloc(65535, 0, 0))
        elif code == 4:
            gc.set_foreground(self.da.get_colormap().alloc(0, 65535, 0))
        elif code == 5:
            gc.set_foreground(self.da.get_colormap().alloc(0, 65535, 65535))
        elif code == 3:
            gc.set_foreground(self.da.get_colormap().alloc(0, 0, 65535))
        for xx in range(resolution):
            for yy in range(resolution):
                self.da_pixmap.draw_point(gc,x*resolution+xx,y*resolution+yy)

    @property
    def top(self):
        return self.top
