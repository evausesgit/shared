from enum import Enum, unique
import random


class AutoNumber(Enum):
    def __new__(cls):
        value = len(cls.__members__) + 1
        obj = object.__new__(cls)
        obj._value_ = value
        return obj


@unique
class Jour(AutoNumber):
    LUNDI    = ()
    MARDI    = ()
    MERCREDI = ()
    JEUDI    = ()
    VENDREDI = ()
    SAMEDI   = ()
    DIMANCHE = ()


@unique
class Category(AutoNumber):
    VIANDE = ()
    LAIT   = ()
    NEUTRE = ()


@unique
class Classe(AutoNumber):
    VEGETABLES = ()
    PROTEIN = ()
    FECULENT = ()


@unique
class Feature(AutoNumber):
    NONE = ()
    SHABBATH = ()
    NO_FECULENT = ()


def getCategory(jour):
    if jour == Jour.VENDREDI:
        return Category.VIANDE
    if jour == Jour.SAMEDI:
        return Category.NEUTRE

    return random.choice(list(Category))


class Aliment():
    def __init__(self, name="", category=Category.NEUTRE, features=Feature.NONE, classe=Classe.VEGETABLES):
        self.name = name
        self.category = category
        self.classe = classe
        self.features = features


Entrees = [
    Aliment('carottes rapees' , Category.NEUTRE),
    Aliment('comcombre',  Category.NEUTRE)
]

#plus tard separer legumes et assaisonement/cuisson
Legumes = [
    Aliment(*args) for args in [
        ('haricots verts ail', Category.NEUTRE),
        ('haricots plats ail', Category.NEUTRE),
        ('brocolis ail'      , Category.NEUTRE),
        ('poilees de legumes WOK', Category.NEUTRE),
        ('soupe', Category.NEUTRE),
        ('carottes rondelles', Category.NEUTRE),
        ('ratatouille', Category.NEUTRE),
        ('legumes wok', Category.NEUTRE),
        ('fondu de poireaux', Category.LAIT),
        ('epinards a la creme', Category.LAIT),
    ]
]

Feculents = [
    Aliment(name) for name in [
        'puree', 'riz', 'pates sauce tomate',
        'semoule', 'ble', 'boulgour/quinoa', 'lentille'
    ]
]

Proteins = [
    Aliment(*args) for args in [
        ('lentilles saucisses', Category.VIANDE, Feature.NO_FECULENT),
        ('pates a la bolognaise', Category.VIANDE, Feature.NO_FECULENT),
        ('cuisses poulet', Category.VIANDE, Feature.NONE),
        ('entrecotes', Category.VIANDE, Feature.NONE),
        ('steacks haches', Category.VIANDE, Feature.NONE),
        ('escalopes panees', Category.VIANDE, Feature.NONE),
        ('omelettes+fromages', Category.LAIT, Feature.NONE),
        ('gratin saumon', Category.LAIT, Feature.NO_FECULENT),
        ('pizza au thon', Category.LAIT, Feature.NO_FECULENT),
        ('pate au saumon', Category.LAIT, Feature.NO_FECULENT),
        ('hachis parmentier', Category.VIANDE, Feature.NO_FECULENT),
        ('poisson au four', Category.NEUTRE, Feature.NONE),
        ('poisson panes', Category.NEUTRE, Feature.NONE),
        ('poisson en sauce', Category.NEUTRE, Feature.NONE),
    ]
]

ProteinsShabbath = [
    Aliment(*args) for args in [
        ('couscous', Category.VIANDE, Feature.NO_FECULENT),
        ('kemounia', Category.VIANDE, Feature.NO_FECULENT),
        ('petits-pois boulettes', Category.VIANDE, Feature.NO_FECULENT)
    ]
]


class Entree:
    def __init__(self, category):
        pass


class Dessert:
    def __init__(self, category):
        pass


class Plat(object):
    def __init__(self, category, jour, prev_menus):
        self.category = category
        self.jour = jour
        self.prev_menus = prev_menus
        self.protein = self.find_protein()
        if self.jour == Jour.VENDREDI:
            assert self.protein.category == Category.VIANDE, "Oops !"

        if self.protein.features == Feature.NO_FECULENT:
            self.legume = None
            self.feculent = None
        else:
            self.legume = self.find_legume()
            self.feculent = self.find_feculent()

    def allowed(self, aliment, classe):
        """n'autorisant pas a avoir deux fois le meme aliment dans la semaine,
        il faut que chaque aliment contiennent au moins 3 choix car 7 jours, -1
        viande pour shabbath reste 6 avec categorie diff de la prec journee
        donc 1/3 lait, 1/3 neutre et 1/3 viande
	on ne melange pas le lait et la viande"""

        if self.category == Category.VIANDE:
            if aliment.category == Category.LAIT:
                return False
        if self.category == Category.LAIT:
            if aliment.category == Category.VIANDE:
                return False

        for menu in self.prev_menus:
            if classe == Classe.PROTEIN:
                if menu.plat.protein == aliment :
                    return False
            if classe == Classe.VEGETABLES:
                if menu.plat.legume == aliment:
                    return False
            if classe == Classe.FECULENT:
                if menu.plat.feculent == aliment:
                    return False

        return True

    def find_protein(self):
        if jour == Jour.VENDREDI:
            choices = ProteinsShabbath
        else:
            choices = Proteins
        return self.choose_until_allowed(choices, Classe.PROTEIN)

    def find_legume(self):
        return self.choose_until_allowed(Legumes, Classe.VEGETABLES)

    def find_feculent(self):
        return self.choose_until_allowed(Feculents, Classe.FECULENT)

    def choose_until_allowed(self, choices, kind):
        res = random.choice(choices)
        while not self.allowed(res, kind):
            res = random.choice(choices)
        return res

    def __str__(self):
        res = "%-20s\n" % (self.protein.name)
        if self.legume :
            res += "%-20s\n" % (self.legume.name)
        if self.feculent:
            res += "%-20s\n" % (self.feculent.name)
        return res


class Menu:
    def __init__(self, category, jour, prev_menus):
        self.category  = category
        self.jour = jour
        self.prev_menus = prev_menus
        self.entree = Aliment()
        self.plat = Plat(self.category, self.jour, self.prev_menus)
        self.dessert = Aliment()

    def __str__(self,):
        res = ""
        res += "="*40 + "\n"
        res += "%20s" % self.jour.name + "\n"
        res += "="*40 + "\n"
        res += str(self.plat)
        return res


def choose_menu(category, jour, menus):
    menu = Menu(category, jour, menus)
    print(menu)
    return menu


def orders():
    previous_category = None
    for jour in Jour:
        while True:
            category = getCategory(jour)
            if category != previous_category or jour == Jour.VENDREDI:
                yield jour, category
                previous_category = category
                break


if __name__ == "__main__" :
    menus = []
    for jour, category in orders():
        menus.append(choose_menu(category, jour, menus))

