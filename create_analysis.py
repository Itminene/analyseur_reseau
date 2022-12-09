# Script qui génère un fichier txt du résultat du visualisateur

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

# Ouverture du fichier à lire
file_read = open("generated_test1.txt")
content = file_read.read()

# Ouverture du fichier à écrire
file_write = open("Resultats/resultat.txt", 'w')

# On lit le fichier
ligne = ''
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

    # On crée la ligne à écrire
    ligne_ecrite = ip_src + ":" + port_src + " ---> " + ip_dest + ":" + port_dest

    j = len(ligne_ecrite)
    while j < 51:
        
        ligne_ecrite += ' '
        j += 1

    ligne_ecrite += protocole + ": " + infos

    # On écrit le résultat dans le fichier à écrire
    file_write.write(ligne_ecrite + "\n")

    i += 1
    ligne = ''