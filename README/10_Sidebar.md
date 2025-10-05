# 10 — Rapport détaillé : Barre latérale (Sidebar)

Date : 23/09/2025
Projet : Amine Templar (Qt 6.7.3, Widgets/C++)

Objectif : documenter la conception exacte de la barre latérale verticale (sans modifier le projet).

---

## 1) Identification générale
- Widget racine de la barre latérale : `sidebarWidget`
- Fichier source consulté : `mainwindow.ui`

## 2) Dimensions et contraintes
- Largeur fixe : **280 px** (définie par `minimumSize` et `maximumSize` dans `mainwindow.ui`).
  - `minimumSize`: 280 × 0
  - `maximumSize`: 280 × 16777215
- Hauteur : non fixe (s'étend avec le contenu / fenêtre)

## 3) Layout interne
- Layout principal : `QVBoxLayout` nommé `sidebarLayout` appliqué à `sidebarWidget`.
- Propriétés du `sidebarLayout` :
  - `spacing` = **0 px**
  - `leftMargin` = **0 px**
  - `topMargin` = **24 px**
  - `rightMargin` = **0 px**
  - `bottomMargin` = **24 px**
  - Ces marges sont les marges internes du layout (donc padding interne de la sidebar : 24 px en haut et en bas).

## 4) Ordre et éléments principaux (de haut en bas)
- `logoLabel` (QLabel) — min height = **60 px**
- `verticalSpacer_3` — sizeHint height = **40 px** (espace fixe)
- Boutons de navigation (liste ci-dessous)
- `userProfileWidget` (card en bas) — min height = **80 px**
- `loginBtn` et autres widgets (plus bas)

## 5) Boutons de navigation : liste et propriétés exactes
Les boutons principaux sont `QPushButton` et partagent un bloc de style inline très similaire. Chaque bouton a :
- Hauteur minimale : **50 px** (défini par `minimumSize` = 0 × 50)
- Largeur : occupe l'espace horizontal disponible (sidebar fixe 280 px)
- Police : `Poppins`, taille 11, weight Light (d'après `font` dans le .ui)
- Propriétés communes (extraites de `mainwindow.ui` inline stylesheet) :
  - `text-align: left;`
  - `padding: 12px 24px;` (12 px haut/bas, 24 px gauche/droite)
  - `border: none;`
  - `background-color: transparent;`
  - `color: #6c757d;` (couleur texte par défaut)
  - `font-weight: 300;` et `letter-spacing: 0.5px;`
  - `checkable = true`, `autoExclusive = true` (comportement radio)

Remarque sur marge/padding visuelle : le fichier `style.qss` global contient aussi `margin: 3px 12px` pour `QWidget#sidebarWidget QPushButton`, qui ajoute **3 px** verticalement et **12 px** horizontalement autour de chaque bouton si la feuille de style globale est chargée (cf. Section Style ci‑dessous).

Détails par bouton (extraits exacts du `mainwindow.ui`)

- `employerBtn` (texte "Employer")
  - `objectName`: `employerBtn`
  - `minimumSize`: 0 × **50 px**
  - `checkable`: true
  - `checked`: true (initialement coché)
  - `autoExclusive`: true
  - `icon`: `:/resources/icons/employer.svg` (défini dans la propriété `icon`)
  - inline stylesheet (identique au bloc commun, voir ci‑dessus)

- `profileBtn` (texte "Profile")
  - `objectName`: `profileBtn`
  - `minimumSize`: 0 × **50 px**
  - `checkable`: true, `autoExclusive`: true
  - pas d'icône explicite dans la section lue

- `projectsBtn` (texte "Projects")
  - `objectName`: `projectsBtn`
  - `minimumSize`: 0 × **50 px**
  - `checkable`: true, `autoExclusive`: true

- `editorBtn` (texte "Editor")
  - `objectName`: `editorBtn`
  - `minimumSize`: 0 × **50 px**
  - `checkable`: true, `autoExclusive`: true

- `libraryBtn` (texte "Library")
  - `objectName`: `libraryBtn`
  - `minimumSize`: 0 × **50 px**
  - `checkable`: true, `autoExclusive`: true

- `settingsBtn` (texte "Settings")
  - `objectName`: `settingsBtn`
  - `minimumSize`: 0 × **50 px**
  - `checkable`: true, `autoExclusive`: true

- `shopBtn` (texte "Shop")
  - `objectName`: `shopBtn`
  - `minimumSize`: 0 × **50 px**
  - `checkable`: true, `autoExclusive`: true

> Notes sur l'icône :
> - Seul `employerBtn` affiche explicitement un `<property name="icon">` pointant vers `:/resources/icons/employer.svg` dans le `.ui` lu.
> - Les icônes sont des fichiers SVG vectoriels (dossier `resources/icons/`), donc la taille d'affichage dépend de l'environnement Qt et de toute propriété `iconSize` si définie ailleurs (aucune `iconSize` définie dans `mainwindow.ui`).

## 6) Marges, inter-espacements et espacement réel entre boutons
- `sidebarLayout` spacing = **0 px** (donc pas d'espacement automatique du layout lui-même).
- Espacement réel entre boutons dépendra :
  - Des `spacer` (ex. `verticalSpacer_3` = 40 px) placés autour.
  - De la règle globale `style.qss`: `QWidget#sidebarWidget QPushButton { margin: 3px 12px; }` qui ajouterait **3 px vertical** entre boutons et **12 px** horizontal autour (si stylesheet global chargé).
- Par conséquent, espacement vertical effectif typique entre boutons = **3 px** (via `margin` dans `style.qss`) + toute différence due aux éléments `spacer`.

## 7) Stylesheets (règles exactes pertinentes)
### Règles inline (présentes dans `mainwindow.ui`, appliquées aux boutons individualisés)
(Extrait, identique pour chaque bouton principal) :

```css
QPushButton {
    text-align: left;
    padding: 12px 24px;
    border: none;
    background-color: transparent;
    color: #6c757d;
    font-weight: 300;
    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;
    letter-spacing: 0.5px;
}
QPushButton:hover {
    background-color: #e9ecef;
    color: #495057;
    transform: translateX(5px);
    transition: all 0.3s ease;
}
QPushButton:pressed {
    background-color: #dee2e6;
}
QPushButton[checked="true"] {
    background-color: #007bff;
    color: white;
    border-left: 4px solid #0056b3;
}
```

> Remarque importante : `transform` et `transition` sont des propriétés CSS web standard et **ne sont pas supportées** par les Qt Style Sheets (elles seront ignorées par Qt). Les autres règles (couleurs, padding, border, background) sont valides.

### Règles globales (dans `style.qss`)
(Extraits pertinents) :

```css
QWidget#sidebarWidget {
    background-color: rgba(248, 249, 250, 0.95);
    border-right: 2px solid rgba(233, 236, 239, 0.8);
    border-radius: 0 15px 15px 0;
    margin-right: 5px;
}

QWidget#sidebarWidget QPushButton {
    text-align: left;
    padding: 16px 20px;
    border: none;
    background-color: transparent;
    color: #6c757d;
    font-weight: 400;
    font-size: 14px;
    letter-spacing: 0.5px;
    border-radius: 12px;
    margin: 3px 12px;
    min-height: 20px;
}

QWidget#sidebarWidget QPushButton:hover {
    background-color: rgba(233, 236, 239, 0.7);
    color: #495057;
}

QWidget#sidebarWidget QPushButton:pressed {
    background-color: rgba(222, 226, 230, 0.8);
}

QWidget#sidebarWidget QPushButton:checked {
    background-color: rgba(0, 123, 255, 0.9);
    color: white;
    font-weight: 500;
    border-left: 4px solid #007bff;
    box-shadow: 2px 2px 12px rgba(0, 123, 255, 0.3);
}
```

- Attention : certaines propriétés (ex. `box-shadow`) peuvent avoir un support limité ou partiel dans Qt stylesheets; test visuel à l'exécution déterminera le rendu exact.

## 8) Élément utilisateur en bas
- `userProfileWidget` (objectName) : min height **80 px**
- Inline stylesheet :
  - background-color: #ffffff;
  - border: 1px solid #e9ecef;
  - border-radius: 8px;
  - margin: 0 12px;
  - padding: 8px;

## 9) Iconographie
- Icons stockées dans `resources/icons/` (SVG). Exemple visible : `:/resources/icons/employer.svg` pour `employerBtn`.
- Aucune `iconSize` explicite définie dans `mainwindow.ui` pour les boutons ; les SVG étant vectoriels, leur rendu pixel dépendra de l'espace disponible et de la manière dont Qt choisit la taille d'icône (par défaut, Qt utilisera la pixmap fournie ou la taille de l'icône affichée). Si vous désirez une taille fixe, il faut définir `button->setIconSize(QSize(w,h))` en code ou ajouter une propriété correspondante.

## 10) Conclusions & recommandations (lecture seule)
- La barre latérale a une largeur fixe claire : **280 px**. Les boutons principaux ont une hauteur de **50 px** et sont alignés à gauche avec un padding horizontal de **24 px** (inline) ou **20 px** (global style) — il y a une légère duplication entre style global et inline, l'appli runtime décidera de la règle finale selon la spécificité.
- Le fichier contient des règles CSS non supportées par Qt (`transform`, `transition`) — elles n'affecteront pas le rendu Qt et semblent être des vestiges de design web.
- Marges effectives entre boutons : typiquement **3 px** (via `margin` dans `style.qss`) plus tout espace ajouté par les `spacer` dans le `.ui`.

---

Fichier créé : `README/10_Sidebar.md` (ce document)

Si vous voulez que je :
- récupère les dimensions intrinsèques des SVG (viewBox) pour proposer une `iconSize` recommandée (par ex. 24×24 ou 20×20 px), je peux lire les fichiers SVG et l'indiquer ; ou
- génère un schéma textuel (Y offsets) indiquant les positions verticales exactes en pixels (calculées à partir des marges/min-heights/spacers), dites-moi et je l'ajoute.

