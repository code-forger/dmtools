import pygtk
pygtk.require('2.0')
import gtk

import dice_gui as dice
import terrain_gui as terrain


def delete_event(widget, event, data=None):
    gtk.main_quit()
    return False

def page_changed_notebook(notebook, page, page_num):
    if page_num == 0:pass
    elif page_num == 1:pass

window = gtk.Window(gtk.WINDOW_TOPLEVEL)
window.connect("delete_event", delete_event)

notebook = gtk.Notebook()
#notebook.connect("switch-page", page_changed_notebook)
window.add(notebook)

terrain_window = terrain.TerrainGui()
notebook.append_page(terrain_window.top, gtk.Label("Terrain"))

dice_window = dice.DiceGui()
notebook.append_page(dice_window.top, gtk.Label("Dice"))

notebook.set_current_page(0)

window.show_all()

terrain_window.terrain_controller.refresh_callback(None,None)

gtk.main()
