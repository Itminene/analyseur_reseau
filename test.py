from tkinter import *
import sys

param = len(sys.argv)
print(param)

filtre1 = 'port.dest==5555'
filtre2 = 'port.src==5555'
filtre3 = 'ip.src==255.255.168.88'
filtre4 = 'ip.dest==255.255.168.88'
filtre5 = 'tcp'
filtre6 = 'http'
filtre7 = 'port==80'
filtre8 = 'ip==255.255.168.88'

filtre_comp = 'port.dest==5555,port.src==80,tcp'


filtres = []
if ',' in filtre_comp:
    tmp = filtre_comp.split(',')
    for filtre in tmp:
        filtres += filtre.split('==')

print(filtres)

"""
## La fenetre, avec les options de grille qui vont bien
root = Tk()
root.grid_rowconfigure(0, weight=1)
root.grid_columnconfigure(0, weight=1)

## Le canvas
cnv = Canvas(root)
cnv.grid(row=0, column=0, sticky='nswe')

## Les scrollbars
hScroll = Scrollbar(root, orient=HORIZONTAL, command=cnv.xview)
hScroll.grid(row=1, column=0, sticky='we')

vScroll = Scrollbar(root, orient=VERTICAL, command=cnv.yview)
vScroll.grid(row=0, column=1, sticky='ns')

cnv.configure(xscrollcommand=hScroll.set, yscrollcommand=vScroll.set)

## Le Frame, dans le Canvas, mais sans pack ou grid
frm = Frame(cnv)
## Les labels et entrys dans le frame
for i in range(50):
    Label(frm, text='Label%s: ' % i).grid(row=i, column=0)
    Entry(frm).grid(row=i, column=1)
## Pour etre sur que les dimensions sont calculées
frm.update()

## Création de la window dans le Canvas
cnv.create_window(0, 0, window=frm, anchor=NW)

## La scrollregion est la boite englobante pour tout ce qu'il y a dans le Canvas
cnv.configure(scrollregion=cnv.bbox(ALL))

## C'est parti!
root.mainloop()
"""