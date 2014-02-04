import pygtk
pygtk.require('2.0')
import gtk

import dice 

class DiceGui():

    def roll(self, widget, data=None):
        self.dice.roll(data)
        self.add_string_to_history("D%d: %d" % (data, self.dice.result))
        self.update()

    def reset_dice(self, widget, data=None):
        self.dice.reset()
        self.add_string_to_history("--Reset--")
        self.update()

    def clear_history(self, widget, data=None):
        for l in self.history_labels:
             l.destroy()

    def add_string_to_history(self,string):
        label = gtk.Label(string)
        self.history_labels.append(label)
        label.set_justify(gtk.JUSTIFY_LEFT)
        self.history.pack_start(label,False,False,0)
        label.show()
        bar = self.history_scroller.get_vscrollbar()
        adj = bar.get_adjustment()
        adj.set_value(adj.get_upper())

    def __init__(self):
        size = 50
        self.dice = dice.Dice()
        self.history_labels = []

        self.top = gtk.Fixed()


        self.content = gtk.HBox()
        self.top.add(self.content)
        self.content.show()

        self.history_area = gtk.VBox()
        self.history_area.show()
        self.content.add(self.history_area)

        self.history_scroller = gtk.ScrolledWindow()
        self.history_scroller.set_policy(gtk.POLICY_AUTOMATIC,
                                         gtk.POLICY_ALWAYS)
        self.history_scroller.set_size_request(100,100)
        self.history_area.pack_start(self.history_scroller)

        self.history = gtk.VBox(spacing=0)
        self.history_scroller.add_with_viewport(self.history)

        self.control_buttons = gtk.HBox(homogeneous=True)
        self.history_area.pack_start(self.control_buttons)

        self.clear_button = gtk.Button("Clear")
        self.clear_button.connect("clicked", self.clear_history)
        self.control_buttons.add(self.clear_button)

        self.reset = gtk.Button("Reset")
        self.reset.connect("clicked", self.reset_dice)
        self.control_buttons.add(self.reset)


        self.table = gtk.Table(rows=3, columns=3, homogeneous=True)
        self.content.add(self.table)

        def create_button(self,dice,pos):
            exec("self.d%d = gtk.Button('D%d')"%(dice,dice))
            exec("self.d%d.connect('clicked', self.roll, %d)"%(dice,dice))
            a,b,c,d = pos
            exec("self.table.attach(self.d%d,%d,%d,%d,%d)"%(dice,a,b,c,d))
            exec("self.d%d.set_size_request(%d,%d)"%(dice,50,50))
            exec("self.d%d.show()"%dice)


        create_button(self,2,(0,1,0,1))
        create_button(self,4,(1,2,0,1))
        create_button(self,6,(2,3,0,1))
        create_button(self,8,(2,3,1,2))
        create_button(self,10,(2,3,2,3))
        create_button(self,12,(1,2,2,3))
        create_button(self,20,(0,1,2,3))
        create_button(self,100,(0,1,1,2))


        self.result = gtk.Label("%d" % 0)
        self.table.attach(self.result,1,2,1,2)


    def update(self):
        self.result.set_text("%d" % self.dice.result)

    @property
    def top(self):
        return self.top
