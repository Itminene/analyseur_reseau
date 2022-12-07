from tkinter import *

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