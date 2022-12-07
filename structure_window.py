from tkinter import *

a = "bonjour"
b = "bonjour"
c = "au revoir"

print(a == b)
print(a == c)
# Fenetre
fenetre = Tk()
fenetre.title("Baby Shark")
fenetre.geometry("900x600")
fenetre.grid_rowconfigure(0, weight=1)
fenetre.grid_columnconfigure(0, weight=1)

# Canvas pour la fenetre
cnv = Canvas(fenetre)
cnv.grid(row=0, column=0, sticky='nswe')

# Scrollbars
hScroll = Scrollbar(fenetre, orient='horizontal', command=cnv.xview)
hScroll.grid(row=1, column=0, sticky='we')

vScroll = Scrollbar(fenetre, orient=VERTICAL, command=cnv.yview)
vScroll.grid(row=0, column=1, sticky='ns')

cnv.configure(xscrollcommand=hScroll.set, yscrollcommand=vScroll.set)

# Frame
frm = Frame(cnv)

# Label
ip1 = Label(frm, borderwidth=50, text="255.255.168.88")
ip2 = Label(frm, borderwidth=50, text="192.168.99.199")
ip3 = Label(frm, borderwidth=50, text="128.119.245.12")
comment = Label(frm, borderwidth=50, text="Comment")
ligne1 = Label(frm, text='TCP TCP TCP TCP TCP TCP TCP TCP TCP TCP TCP TCP TCP TCP')
ligne2 = Label(frm, text='HTTP')

# Ajout dans la fenetre
ip1.grid(column=0, row=0)
ip2.grid(column=1, row=0)
ip3.grid(column=2, row=0)
comment.grid(column=3, row=0)
ligne1.grid(column=3, row=1)
ligne2.grid(column=3, row=2)

# Canvas
canevas1 = Canvas(frm, height=50, width=200, bg='red')
canevas1.create_line(100, 0, 100, 50, dash=(3,5))
canevas1.create_line(100, 25, 200, 25)
canevas1.create_text(50, 25, text='80')

canevas2 = Canvas(frm, height=50, width=200, bg='red')
canevas2.create_line(100, 0, 100, 50, dash=(3,5))
canevas2.create_line(0, 25, 100, 25, arrow='last')
canevas2.create_text(50, 12.5, text='ACK')
canevas2.create_text(150, 25, text='60779')

canevas3 = Canvas(frm, height=50, width=200, bg='red')
canevas3.create_line(100, 0, 100, 50, dash=(3,5))

canevas4 = Canvas(frm, height=50, width=200, bg='green')
canevas4.create_line(100, 0, 100, 50, dash=(3,5))
canevas4.create_line(100, 25, 200, 25, arrow='first')
canevas4.create_text(150, 12.5, text='SYN, ACK')
canevas4.create_text(50, 25, text='80')

canevas5 = Canvas(frm, height=50, width=200, bg='green')
canevas5.create_line(100, 0, 100, 50, dash=(3,5))
canevas5.create_line(200, 25, 0, 25)

canevas6 = Canvas(frm, height=50, width=200, bg='green')
canevas6.create_line(100, 0, 100, 50, dash=(3,5))
canevas6.create_line(100, 25, 0, 25)
canevas6.create_text(150, 25, text='5555')

# Ajout dans la fenetre
canevas1.grid(column=0, row=1)
canevas2.grid(column=1, row=1)
canevas3.grid(column=2, row=1)

canevas4.grid(column=0, row=2)
canevas5.grid(column=1, row=2)
canevas6.grid(column=2, row=2)

for i in range(3,10):
    canevas7 = Canvas(frm, height=50, width=200, bg='blue')
    canevas8 = Canvas(frm, height=50, width=200, bg='blue')
    canevas9 = Canvas(frm, height=50, width=200, bg='blue')

    canevas7.grid(column=0, row=i)
    canevas8.grid(column=1, row=i)
    canevas9.grid(column=2, row=i)

# Recalcul des dimensions de la fenêtre
frm.update()

# Création de la window dans le Canvas
cnv.create_window(0, 0, window=frm, anchor=W)

# Boite englobante pour tout ce qui a dans le Canvas
cnv.configure(scrollregion=cnv.bbox(ALL))

# Boucle principale
fenetre.mainloop()
