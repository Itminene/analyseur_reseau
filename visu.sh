# Script principal de l'application

echo
echo "======================================================="
echo "=========== VISUALISATEUR DE TRAFIC ET FLUX ==========="
echo "======================================================="
echo
echo "  *** made by Itminene El Garah and Nathan Timba ***"
echo

quitter='q'
vide=''

# Lecture de l'entrée
echo -n "Entrez le nom du fichier à analyser (q pour quitter) : "
read entree

while [[ $entree != $quitter ]]; do

    # Test de l'existence du fichier
    if [ ! -e $entree ]; then
        echo "Fichier introuvable"
    else
        echo "Nom du fichier à analyser: $entree"
        # Instructions permettant de générer le fichier 'printf.txt'
        # make crée l'éxecutable ./analyseur
        #$main='./analyseur'
        #if [ ! -e $main ]; then
        #    make
        #fi
        # ./analyseur $entree crée le fichier

        
        # Premier affichage
        python create_analysis_final.py

        # Lecture du filtre
        filtre=''

        while [[ $filtre != $quitter ]]; do

            echo "-------------------------------------------------------"
            echo "| Filtres disponibles :                               |"
            echo "|     * tcp                                           |"
            echo "|     * http                                          |"
            echo "|     * port==<nom_du_port>                           |"
            echo "|     * port.dest==<nom_du_port>                      |"
            echo "|     * port.src==<nom_du_port>                       |"
            echo "|     * ip==<valeur_ip>                               |"
            echo "|     * ip.dest==<valeur_ip>                          |"
            echo "|     * ip.src==<valeur_ip>                           |"
            echo "-------------------------------------------------------"
            echo
            echo "- 'port' filtre les trames dont le numéro de port correspond"
            echo "à celui indique dans le filtre sans faire la distinction"
            echo "entre la source et la destination"
            echo
            echo "- 'port.dest' similaire à 'port' mais s'applique seulement aux"
            echo "aux ports destinations"
            echo
            echo "- 'port.src' similaire à 'port.dest' pour les ports sources"
            echo 
            echo "- 'ip', 'ip.dest' et 'ip.src' sont analogues aux filtres 'port',"
            echo "'port.dest' et 'port.src' pour les adresses IP"
            echo
            echo "- 'tcp' filtre les segments TCP sans HTTP"
            echo
            echo "- 'http' filtre les segments TCP encaspulant HTTP"
            echo
            echo "- Appuyez directement sur entrée si vous ne voulez pas appliquer de filtre"
            echo
            echo "- Vous pouvez faire des compositions de filtres en tapant : "
            echo
            echo "    '<filtre1>,<filtre2>,<filtre3>,...,<filtreN>'"
            echo
            echo -n "Entrez le nom du filtre ou la liste de filtres à appliquer (q pour quitter) : "
            read filtre

            if [[ $filtre != $quitter ]]; then

                if [[ $filtre == $vide ]]; then
                    filtre='vide'
                fi
                
                echo
                echo -n "Entrez le nom du fichier dans lequel sauvegarder le résultat (resultat.txt par défaut) : "
                read resultat
                python create_analysis_final.py $filtre $resultat
            fi

        done
    fi

    # Lecture de l'entrée
    echo -n "Entrez le nom du fichier à analyser (q pour quitter) : "
    read entree

done