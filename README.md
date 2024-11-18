Description du Projet:
Ce projet consiste à implémenter un programme permettant de gérer et de simuler des files d'attente en utilisant des listes linéaires chaînées (LLC). Il simule le fonctionnement d'un centre avec plusieurs guichets/agents qui reçoivent des clients, traitent leurs requêtes et, éventuellement, redirigent les clients vers d'autres guichets. Chaque guichet dispose de sa propre file d'attente respectant l'ordre FIFO (First In, First Out). Le projet intègre un menu principal offrant plusieurs options pour la gestion des clients et des guichets.

Fonctionnalités Principales:
Menu Principal:
-Ajout de Clients.
-Choix du guichet/agent recevant le client (le guichet d'accueil ajoute le client à la file d'attente).

Réception des Clients:
-Sélection d'un guichet/agent (A, B, C, etc.).
-Affichage de la liste des clients dans la file d'attente du guichet choisi.
Options pour :
-Traiter la requête d'un client et le supprimer de la file.
-Rediriger le client vers un autre guichet/agent tout en respectant l'ordre d'arrivée.
-Affichage Global des Files d'Attente
-Visualisation de l'ensemble des clients avec l'indication du guichet/agent auquel ils sont affectés.

Opérations en Vrac sur les Files d'Attente:
-Redirection d'une file d'attente vers plusieurs guichets vides 
-Fusion de plusieurs files vers un même guichet/agent.
-Rééquilibrage des files d'attente : Répartir les clients de manière équilibrée entre les guichets.
-Réinitialisation des numéros de tickets .

Structure des Données:
-Client : Représenté par un maillon de la liste linéaire chaînée, disposant d'un numéro de ticket unique.
-Guichet/Agent : Dispose de sa propre file d'attente implémentée sous forme de liste linéaire chaînée.

Détails Techniques
Utilisation de machines abstraites pour gérer les opérations sur les listes linéaires chaînées, les files et les piles.


Auteurs
BOUCHENNA Damia et SAADI Ahmed lors d'un tp . 
