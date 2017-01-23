:title: Tron
:data-transition-duration: 1500
:css: pres.css

----

Open-source IA pour TRON:
=========================

Sommaire
---------------------------------

1. Présentation de TRON

2. Simplification pour le jeu

3. Les intelligences artificielles en bot programming

4. L'algorithme MinMax

5. L'algorithme de Voronoi

6. Application

.. note::

    Vidéo de présentation de tron

----

Présentation de TRON
========================

.. image:: lightcycle.png
    :width: 800px

.. note::

    Vidéo

----

Simplification
=====================

.. image:: simplification.png

.. note::

    Grille en 2d, avec une position et
    une trace à chaque passage
    But du jeu : ne pas se prendre la trace des autres

----

Les IA en bot programming
=========================

PIERRE

.. note::
 Tes notes ici

----


MinMax
=========

PIERRE

.. note::

    Tes notes ici

----


Diagramme de Voronoi
=====================

- Définition
- Application

.. image:: voronoi_explanation.png


.. note::

    Le diagramme de Voronoi est un découpage du plan (pavage) en cellules à partir d'un ensemble discret de points appelés « germes ». Chaque cellule enferme un seul germe, et forme l'ensemble des points du plan plus proches de ce germe que de tous les autres. (wikipédia)

    Ce diagramme est utilisé dans l'intelligence artificielle pour calculer le score de manière très simple : plus l'IA a de cellules dans son 'camp', plus elle gagne des points, son but va donc d'augmenter son nombre de points, et pour cela, réduire le nombre de point des autres joueurs

----



Application
==================

- csfml
- open-source
- demo

.. note::

    Pour réaliser l'affichange du jeu, nous avons utilisé la bibliothèque open-source 'csfml', qui est la version 'C' de sfml.
    Le code source du jeu est totalement open-source. Le but de ce projet est d'inciter n'importe qui à programmer une IA et a la tester
    Let's play !

----


Merci pour votre attention
==========================
