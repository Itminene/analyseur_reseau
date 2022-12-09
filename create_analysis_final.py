from tkinter import *
import sys

# Filtre passé en paramètre du script
param = len(sys.argv)

if param == 1:
    filtre = ''
    resultat = 'resultat.txt'
elif param == 2:
    filtre = sys.argv[1]
    resultat = 'resultat.txt'
else:
    filtre = sys.argv[1]
    resultat = sys.argv[2]

if filtre == 'vide':
    filtre = ''

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

# Fonction qui crée un nouveau fichier dans lequel on a supprimé les lignes
# où le filtre n'est pas présent
# Le filtre vide recopie le fichier dans son intégralité
# Retourne -1 si le filtre est incorrect
def filtrage_v2(filtre):

    print('filtre : ' + filtre + '\n')
    dico_filtres = {'port':'', 'port.dest':'', 'port.src':'', 'ip':'', 'ip.dest':'', 'ip.src':'', 'tcp':False, 'http':False}

    # Cas où il n'y a pas de filtre
    if filtre == '':

        # Lecture du fichier généré par l'analyse
        file = open('printf.txt')
        content = file.read()

        # Ouverture du fichier à écrire
        file_filtered = open("generated_filtered.txt", 'w')

        # Recopie du fichier
        file_filtered.write(content)

        return 0

    # Cas où le filtre n'a qu'une seule valeur
    if ',' not in filtre:

        # Cas où c'est un filtre du type '=='
        if '==' in filtre:

            tab_filtre = filtre.split('==')

            if len(tab_filtre) != 2:
                print("Erreur : mauvaise syntaxe pour le filtre (1)")
                return -1

            nom_filtre = tab_filtre[0]
            val_filtre = tab_filtre[1]

            if nom_filtre not in dico_filtres or nom_filtre == 'tcp' or nom_filtre == 'http':
                print("Erreur : mauvaise syntaxe pour le filtre (2)")
                return -1

            dico_filtres[nom_filtre] = val_filtre

        # Filtre 'tcp' ou 'http'
        else:

            if filtre == 'tcp':
                dico_filtres['tcp'] = True

            if filtre == 'http':
                dico_filtres['http'] = True

            if filtre != 'tcp' and filtre != 'http':
                print("Erreur : mauvaise syntaxe pour le filtre (3)")
                return -1

    # Cas où le filtre a plusieurs valeurs
    else:

        tab_filtres = filtre.split(',')

        # Parcours du tableau
        for cur_filtre in tab_filtres:

            # Cas où c'est un filtre du type '=='
            if '==' in cur_filtre:

                tab_filtre = cur_filtre.split('==')

                if len(tab_filtre) != 2:
                    print("Erreur : mauvaise syntaxe pour le filtre (4)")
                    return -1

                nom_filtre = tab_filtre[0]
                val_filtre = tab_filtre[1]

                if nom_filtre not in dico_filtres or nom_filtre == 'tcp' or nom_filtre == 'http':
                    print("Erreur : mauvaise syntaxe pour le filtre (5)")
                    return -1

                dico_filtres[nom_filtre] = val_filtre

            # Filtre 'tcp' ou 'http'
            else:

                if cur_filtre == 'tcp':
                    dico_filtres['tcp'] = True

                if cur_filtre == 'http':
                    dico_filtres['http'] = True

                if cur_filtre != 'tcp' and cur_filtre != 'http':
                    print("Erreur : mauvaise syntaxe pour le filtre (6)")
                    return -1

    # Cas où c'est soit l'ip ou ip.X pareil pour le port
    # On ne peut pas utiliser les deux à la fois

    if dico_filtres['ip'] != '':
        dico_filtres['ip.dest'] = ''
        dico_filtres['ip.src'] = ''
    
    if dico_filtres['port'] != '':
        dico_filtres['port.dest'] = ''
        dico_filtres['port.src'] = ''

    # Lecture du fichier généré par l'analyse
    file = open('printf.txt')
    content = file.read()

    # Ouverture du fichier à écrire
    file_filtered = open("generated_filtered.txt", 'w')

    # On lit le fichier
    ligne = ''
    i = 0
    while i < len(content):

        dico_presence = {'port':True, 'port.dest':True, 'port.src':True, 'ip':True, 'ip.dest':True, 'ip.src':True, 'tcp':True, 'http':True}
    
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

        print("ip_src = " + ip_src)
        print("ip_dest = " + ip_dest)
        print("dico_filtres['ip'] = " + dico_filtres['ip'])

        print("port_src = " + port_src)
        print("port_dest = " + port_dest)
        print("dico_filtres['port'] = " + dico_filtres['port'])

        # On vérifie que chaque champ correspond au filtre correspondant
        if dico_filtres['ip'] != '':
            if ip_src != dico_filtres['ip'] and ip_dest != dico_filtres['ip']:
                print("ip est mis à false")
                dico_presence['ip'] = False
        
        if dico_filtres['ip.src'] != '':
            if ip_src != dico_filtres['ip.src']:
                print("ip_src est mis à false")
                dico_presence['ip.src'] = False

        if dico_filtres['ip.dest'] != '':
            if ip_dest != dico_filtres['ip.dest']:
                print("ip_dest est mis à false")
                dico_presence['ip.dest'] = False

        if dico_filtres['port'] != '':
            if port_src != dico_filtres['port'] and port_dest != dico_filtres['port']:
                print("port est mis à false")
                dico_presence['port'] = False
        
        if dico_filtres['port.src'] != '':
            if port_src != dico_filtres['port.src']:
                print("port_src est mis à false")
                dico_presence['port.src'] = False

        if dico_filtres['port.dest'] != '':
            if port_dest != dico_filtres['port.dest']:
                print("port_dest est mis à false")
                dico_presence['port.dest'] = False

        if dico_filtres['http']:
            if protocole != 'HTTP':
                dico_presence['http'] = False

        if dico_filtres['tcp']:
            if protocole != 'TCP':
                dico_presence['tcp'] = False

        # Réécriture de la ligne dans le cas où le champ respecte le filtre
        respecte = True
        for (cle, present) in dico_presence.items():
            if present == False:
                respecte = False
                break
        
        if respecte:
            file_filtered.write(ligne + '\n')

        ligne = ''
        i += 1

filtrage_v2(filtre)     

#######################################################################
#
# Comptage du nombre d'adresses IP différentes et création des colonnes
#
#######################################################################


# Lecture du fichier généré par le filtrage
file = open('generated_filtered.txt')
content = file.read()

# Ouverture du fichier à écrire
file_res = open(resultat, 'w')

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
fenetre.title("Visualisateur")
fenetre.geometry("1200x800")
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
ligne_ecrite = '       '
for (ip, col) in dico_ip.items():
    label_ip = Label(frm, text=ip, bg='sky blue')
    label_ip.grid(column=col, row=0)
    
    # Instructions pour dessiner la ligne dans le fichier
    deb = col * 30 + 7
    fin = deb + 28
    i = deb
    while i <= fin:
        
        # On écrit l'ip
        if i == deb+8:
            ligne_ecrite += ip
            i += len(ip)
        else:
            ligne_ecrite += ' '
            i += 1  

# On ajoute une colonne pour 'Comment'
comment = Label(frm, borderwidth=50, text="Comment")
comment.grid(column=len(dico_ip), row=0)

# Instructions pour dessiner la ligne dans le fichier
ligne_ecrite += '         Comment\n'

# On ajoute la ligne dans le fichier à écrire
file_res.write(ligne_ecrite)

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

    # Couleur pour la flèche
    if protocole == 'TCP':
        color = 'green'
    elif protocole == 'HTTP' or protocole == 'HTTPS':
        color = 'blue'
    else:
        color = 'black'

    # Cas où la source est à droite de la destination
    if src_droite:

        # Canevas pour la source
        cnv_src.create_line(100, 25, 0, 25, fill=color)
        cnv_src.create_text(150, 25, text=port_src)

        # Canevas pour la destination
        cnv_dest.create_line(200, 25, 100, 25, arrow='last', fill=color)
        cnv_dest.create_text(50, 25, text=port_dest)
        cnv_dest.create_text(150, 12.5, text=msg_type)

    # Cas où la source est à gauche de la destination
    else:

        # Canevas pour la source
        cnv_src.create_line(100, 25, 200, 25, fill=color)
        cnv_src.create_text(50, 25, text=port_src)

        # Canevas pour la destination
        cnv_dest.create_line(0, 25, 100, 25, arrow='last', fill=color)
        cnv_dest.create_text(150, 25, text=port_dest)
        cnv_dest.create_text(50, 12.5, text=msg_type)

    # On les ajoute à la fenêtre
    cnv_src.grid(column=dico_ip[ip_src], row=num_ligne)
    cnv_dest.grid(column=dico_ip[ip_dest], row=num_ligne)

    # On parcours toutes les adresses IP
    for ip in dico_ip:

        # C'est la source ou la destination : on ne les traite pas
        if ip == ip_src or ip == ip_dest:
            continue

        # Création du canevas pour l'adresse IP courante
        cnv_cur = Canvas(frm, height=50, width=200, bd=0)
        cnv_cur.create_line(100, 0, 100, 50, dash=(3,5))

        # On regarde si le canevas de l'ip courant est sur le trajet de la flèche
        # Si la source est à droite, sa colonne a la plus grande valeur
        if src_droite:
            if dico_ip[ip] < dico_ip[ip_src] and dico_ip[ip] > dico_ip[ip_dest]:

                # On fait une ligne horizontale
                cnv_cur.create_line(0, 25, 200, 25, fill=color)
        else:
            if dico_ip[ip] > dico_ip[ip_src] and dico_ip[ip] < dico_ip[ip_dest]:

                # On fait une ligne horizontale
                cnv_cur.create_line(0, 25, 200, 25, fill=color)

        # On ajoute le canevas courant à la fenêtre
        cnv_cur.grid(column=dico_ip[ip], row=num_ligne)

    # On crée un canevas pour le comment
    comment = protocole + ": " + infos
    cnv_type = Label(frm, text=comment, fg=color)
    
    # On l'ajoute à la fenêtre
    cnv_type.grid(column=len(dico_ip), row=num_ligne)

    ligne = ''
    num_ligne += 1
    i += 1

    # Instructions pour dessiner la ligne dans le fichier

    # On dessine le premier trait vertical dans chaque colonne
    ligne_ecrite = '       '
    for col in range(len(dico_ip)):
        
        ligne_ecrite += '              '
        ligne_ecrite += '|'
        ligne_ecrite += '              '
    
    file_res.write(ligne_ecrite + '\n')


    # On va parcourir colonne par colonne
    ligne_ecrite = '       '
    for col in range(len(dico_ip)):

        # Colonne source
        if col == dico_ip[ip_src]:

            # La source est à droite de la destination
            if src_droite:
                ligne_ecrite += "--------------|"
                ligne_ecrite += port_src

                # On ajoute des espaces correspondant à la taille restante
                for k in range(14 - len(port_src)):
                    ligne_ecrite += ' '
            # La source est à gauche de la destination
            else:
                for k in range(14 - len(port_src)):
                    ligne_ecrite += ' '
                ligne_ecrite += port_src
                ligne_ecrite += "|--------------"
        
        # Colonne destination
        elif col == dico_ip[ip_dest]:

            # La source est à droite de la destination
            if src_droite:
                for k in range(14 - len(port_dest)):
                    ligne_ecrite += ' '
                ligne_ecrite += port_dest
                ligne_ecrite += "|<-------------"

            # La source est à gauche de la destination
            else:
                ligne_ecrite += "------------->|"
                ligne_ecrite += port_dest

                # On ajoute des espaces correspondant à la taille restante
                for k in range(14 - len(port_dest)):
                    ligne_ecrite += ' '
        
        # Toutes les autres colonnes
        else:

            # Cas où la source est à droite
            if src_droite:

                # La colonne est sur le trajet de la flèche
                if col > dico_ip[ip_dest] and col < dico_ip[ip_src]:
                    ligne_ecrite += '--------------|--------------'
                else:
                    ligne_ecrite += '              |              '
            
            # Cas où la source est à gauche
            else:
                
                # La colonne est sur le trajet de la flèche
                if col < dico_ip[ip_dest] and col > dico_ip[ip_src]:
                    ligne_ecrite += '--------------|--------------'
                else:
                    ligne_ecrite += '              |              '

    # Ajoute des infos dans colonne Comment
    ligne_ecrite += protocole + ": " + infos

    file_res.write(ligne_ecrite + '\n')

    # On dessine le premier trait vertical dans chaque colonne
    ligne_ecrite = '       '
    for col in range(len(dico_ip)):
        
        ligne_ecrite += '              '
        ligne_ecrite += '|'
        ligne_ecrite += '              '

    file_res.write(ligne_ecrite + '\n')


# Recalcul des dimensions de la fenêtre
frm.update()

# Création de la window dans le Canvas
cnv.create_window(0, 0, window=frm, anchor=W)

# Boite englobante pour tout ce qui a dans le Canvas
cnv.configure(scrollregion=cnv.bbox(ALL))

# Boucle principale
fenetre.mainloop()