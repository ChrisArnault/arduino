# Définition d'un serveur réseau rudimentaire
# Ce serveur attend la connexion d'un client, pour entamer un dialogue avec lui

import socket, sys
import re

HOST = 'nb-arnault4'
PORT = 5000

# 1) création du socket :
mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 2) liaison du socket à une adresse précise :
try:
    mySocket.bind((HOST, PORT))
except socket.error:
    print("La liaison du socket à l'adresse choisie a échoué.")
    sys.exit()


previous = None

while True:
    # 3) Attente de la requête de connexion d'un client :
    print("Serveur prêt, en attente de requêtes ...")
    mySocket.listen(5)

    # 4) Etablissement de la connexion :
    connexion, adresse = mySocket.accept()
    print("Client connecté, adresse IP %s, port %s" % (adresse[0], adresse[1]))

    messages = 1

    while True:
        try:
            msgClient = connexion.recv(100).decode("utf-8")
        except socket.error:
            print("disconnexion from client")
            break

        if len(msgClient) > 0:
            m = re.match(r"[(]([\d]+)[)]([\d]+)[|]([\d]+)[#]", msgClient)
            if not m is None:
                number = int(m[1])
                x = int(m[2])
                y = int(m[3])
                if not previous is None:
                    if number != (previous + 1):
                        print("Mismatch", number, previous, x, y)

                previous = number

            if messages >= 999:
                # print("from B> [{}]".format(msgClient))
                messages = 0
            else:
                messages += 1
        else:
            break


# 6) Fermeture de la connexion :
connexion.send("Au revoir !")
print("Connexion interrompue.")
connexion.close()

