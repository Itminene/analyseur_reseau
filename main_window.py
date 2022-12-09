from tkinter import *


#######################################################################
#
#                               Fonctions
#
#######################################################################


# Retourne la liste des champs de 'chaine' qui sont séparés par une virgule
def decoupage(chaine):
    
    champs = ''
    liste = []

    for c in chaine:
        if c == ',':
            liste.append(champs)
            champs = ''
        else:
            champs += c

    # On ajoute le dernier
    liste.append(champs)

    return liste


#######################################################################
#
# Comptage du nombre d'adresses IP différentes et création des colonnes
#
#######################################################################


# Lecture du fichier généré par l'analyse
file = open('generated_test1.txt')
content = file.read()

# Dans un premier temps on va lire toutes les adresses IP du fichier

# Ensemble d'adresses IP
IPs = set()

# IP courante
ip = ''

# Compteur d'IP (deux ip par lignes)
cpt = 0

# Parcours du fichier lu
i = 0
while i < len(content):

    if content[i] != ',':
        ip += content[i]
    else:
        IPs.add(ip)
        ip = ''
        cpt += 1

    # On a lu deux IP, on change de ligne
    if cpt >= 2:
        cpt = 0
        j = i
        while j < len(content) and content[j] != '\n':
            j += 1
        i = j+1
    else:
        i += 1

# Dictionnaire d'adresses IP : une ip correspond à une colonne
dico_ip = {}
col = 0
for ip in IPs:
    dico_ip[ip] = cpt
    cpt += 1

# On retourne au début du fichier
file.seek(0)
content = file.read()


#######################################################################
#
# Les instructions ci-dessous correspondent à la création de la fenêtre
#
#######################################################################


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

vScroll = Scrollbar(fenetre, orient='vertical', command=cnv.yview)
vScroll.grid(row=0, column=1, sticky='ns')

cnv.configure(xscrollcommand=hScroll.set, yscrollcommand=vScroll.set)

# Frame
frm = Frame(cnv)


#######################################################################
#
# Les instructions ci-dessous correspondent à la création du contenu de
# la fenêtre
#
#######################################################################


# On va créer une colonne pour chaque ip
for (ip, col) in dico_ip.items():
    label_ip = Label(frm, text=ip, bg='sky blue')
    label_ip.grid(column=col, row=0)

# On ajoute une colonne pour 'Comment'
comment = Label(frm, borderwidth=50, text="Comment")
comment.grid(column=len(dico_ip), row=0)

# On lit le fichier
ligne = ''
num_ligne = 1
i = 0
while i < len(content):
    
    
    # On lit une ligne
    while content[i] != '\n':

        ligne += content[i]
        i += 1
        
        # Fin du fichier
        if i >= len(content):
            break
    
    champs = decoupage(ligne)

    # On récupère tous les champs
    ip_src = champs[0]
    ip_dest = champs[1]
    port_src = champs[2]
    port_dest = champs[3]
    protocole = champs[4]
    msg_type = champs[5]
    infos = champs[6]

    # On regarde si la source est à droite de la destination
    src_droite = dico_ip[ip_src] > dico_ip[ip_dest]

    # Création des flèches
    cnv_src = Canvas(frm, height=50, width=200, bd=0)
    cnv_src.create_line(100, 0, 100, 50, dash=(3,5))

    cnv_dest = Canvas(frm, height=50, width=200, bd=0)
    cnv_dest.create_line(100, 0, 100, 50, dash=(3,5))

    # Cas où la source est à droite de la destination
    if src_droite:

        # Canevas pour la source
        cnv_src.create_line(100, 25, 0, 25)
        cnv_src.create_text(150, 25, text=port_src)

        # Canevas pour la destination
        cnv_dest.create_line(200, 25, 100, 25, arrow='last')
        cnv_dest.create_text(50, 25, text=port_dest)
        cnv_dest.create_text(150, 12.5, text=msg_type)

    # Cas où la source est à gauche de la destination
    else:

        # Canevas pour la source
        cnv_src.create_line(100, 25, 200, 25)
        cnv_src.create_text(50, 25, text=port_src)

        # Canevas pour la destination
        cnv_dest.create_line(0, 25, 100, 25, arrow='last')
        cnv_dest.create_text(150, 25, text=port_dest)
        cnv_dest.create_text(50, 12.5, text=msg_type)

    # On les ajoute à la fenêtre
    cnv_src.grid(column=dico_ip[ip_src], row=num_ligne, sticky='nesw')
    cnv_dest.grid(column=dico_ip[ip_dest], row=num_ligne, sticky='nesw')

    # On parcours toutes les adresses IP
    for ip in dico_ip:

        # C'est la source ou la destination : on ne les traite pas
        if ip == ip_src or ip == ip_dest:
            continue

        # Création du canevas pour l'adresse IP courante
        cnv_cur = Canvas(frm, height=50, width=200, bd=0)
        cnv_cur.create_line(100, 0, 100, 50, dash=(3,5))

        # On regarde si le canevas de l'ip courant est sur le trajet de la flèche
        # Si la source est à droite, sa colonne à la plus grande valeur
        if src_droite:
            if dico_ip[ip] < dico_ip[ip_src] and dico_ip[ip] > dico_ip[ip_dest]:

                # On fait une ligne horizontale
                cnv_cur.create_line(0, 25, 200, 25)
        else:
            if dico_ip[ip] > dico_ip[ip_src] and dico_ip[ip] < dico_ip[ip_dest]:

                # On fait une ligne horizontale
                cnv_cur.create_line(0, 25, 200, 25)

        # On ajoute le canevas courant à la fenêtre
        cnv_cur.grid(column=dico_ip[ip], row=num_ligne)

    # On crée un canevas pour le comment
    comment = protocole + ": " + infos
    cnv_type = Label(frm, text=comment)
    
    # On l'ajoute à la fenêtre
    cnv_type.grid(column=len(dico_ip), row=num_ligne)

    ligne = ''
    num_ligne += 1
    i += 1

# Recalcul des dimensions de la fenêtre
frm.update()

# Création de la window dans le Canvas
cnv.create_window(0, 0, window=frm, anchor=W)

# Boite englobante pour tout ce qui a dans le Canvas
cnv.configure(scrollregion=cnv.bbox(ALL))

# Boucle principale
fenetre.mainloop()
