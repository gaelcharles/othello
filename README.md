# Othello

Salut !
Petit tutoriel pour utiliser Git et Github.
Si vous voulez suivre un très bon tutoriel fait par Github eux-mêmes (en anglais et plus complet) c'est ici https://try.github.io

## Installation
* Commencez par vous inscrire sur Github.

* Pour avoir le repository du projet sur votre ordi, commencez par installer un shell avec Git. "Git for Windows" fait très bien le café (https://git-scm.com/download/win)
Ou sinon il exsite d'autres shells, par exemple y'a babun qui est très bon, en plus le plugin Git est inclus (http://babun.github.io/)

* Déplacez-vous ou vous voulez créer le dossier "othello", avec la commande par exemple
> cd C:/Users/XXXX/Projets

* Et ensuite clonez le projet avec la commande
> git clone https://github.com/gaelcharles/othello.git

Le projet est sur l'ordi :) !

## Faire des modifications
* Commencez par créer une branche pour éviter de faire un code qui marche pas et qui écrase la version précédente du code qui marche (la branche "master" (principale) doit toujours être une version fonctionnelle).
> git checkout -b nom_de_la_branche

* Vérifiez toujours que vous êtes bien sur votre branche en faisant
> git branch

* Faites vos modifications sur CodeBlocks comme d'habitude

* Une fois un code fonctionnel, enregistrez tous vos fichiers et faites
> git status

Vous verrez alors toutes les modifications que vous avez faites. Vous pouvez choisir d'ajouter à votre branche celles que vous voulez en faisant
> git add -p

Là, git détectera tous les "blocs de code" ajoutés et vous demandera s'il faut l'ajouter ou non (y/n pour ajouter ou non)

* Si vous avez créé des nouveaux fichiers, il faut directement mettre leur noms après le add, par exemple
> git add newfile.cpp

* Une fois les fichiers ajoutés, il faut les "commit". En gros, on regroupe les modifications ajoutées en mettant un message expliquant la fonctionnalité de ce qui a été ajouté / supprimé.
> git commit -m "Le message ici entre guillemets, le plus précis possible. Par exemple : Ajout graphique des numéros des cases sur le côté du plateau"

* Maintenant, on peut "push" les modifications, l'étape supérieure.
> git push

* On retourne sur Github, et normalement il détecte qu'on a créé une nouvelle branche. On fait un "pull request" de cette branche en cliquant sur le bouton associé.
En gros, ça va créer une version parallèle du projet (sur notre branche), avec vos modifications. Les autres utilisateurs la verront, pourront lire vos ajouts / suppressions / modifications.
S'ils sont d'accord avec ce que vous avez fait, ils peuvent approuver votre Pull request. Sinon, ils peuvent ajouter un petit commentaire propre à une ou plusieurs lignes spécifiques
(ex : un commentaire sur une implémentation de fonction, en mettant "je comprend pas pourquoi tu passes tel ou tel argument en paramètre", etc.)
Bien sûr on peut juste envoyer un message à la personne ou sur la discussion FB et dire que c'est OK ou pas, ça ira plus vite.

* Quand tout le monde est OK pour que cette version devienne la nouvelle version actuelle fonctionnelle (master), on "merge" la branche sur master. Github permet de le faire directement en cliquant sur le bouton associé.

* Et les modifications sont enregistrées.

# Avantages

* Déjà, on a 2/2 pour le versioning sur la note

* On peut voir et juger chaque modification et décider d'ajouter le code ou non sans se soucier de reprendre une version précédente

* Plus de soucis d'écrasement de versions qui marchaient par une version qui marche plus

* En ligne sur internet donc si on utilises un autre ordi (cf. vacances) on y a accès quand même

* Tout le monde partage la même version.
