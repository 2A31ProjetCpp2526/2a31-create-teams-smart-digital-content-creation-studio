# 4. Style (Styles, Thèmes, Polices)

Ce document explique comment le style est appliqué dans Amine Templar et comment la stabilité visuelle est assurée.

## Fichiers clés
- `main.cpp` — chargement de la police Poppins et application de `style.qss` (lignes ~10-30).
- `style.qss` — feuille de style globale (chargée via `:/style.qss`) : définit couleurs, hover globaux, et règles communes.
- `*.ui` files (ex: `login.ui`, `Profile.ui`, `mainwindow.ui`) — certains widgets ont des `styleSheet` inline pour des cas spécifiques.

## Police
- Police Poppins chargée globalement dans `main.cpp` :
  ```cpp
  int fontId = QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-Light.ttf");
  if (fontId != -1) {
      QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
      QFont font(fontFamilies.at(0), 11, QFont::Light);
      a.setFont(font);
  }
  ```
- Résultat : tous les widgets héritent de la police Poppins par défaut (sauf override local).

## Icons & resources
- Les icônes sont stockées dans `resources/icons/*.svg` et référencées via `resources.qrc`.
- Exemple: `:/icons/info.svg`, `:/icons/login.svg`, etc.

## Style global vs style inline
- `style.qss` : règles globales (boutons, inputs, tab bars) — chargée dans `main.cpp`.
- `ui` inline `styleSheet` : utilisé pour réglages spécifiques (par ex. `loginButton` dans `login.ui` a un style inline pour garantir un rendu exact, voir `login.ui` lignes ~240-320).

## Règles pour éviter les layout shifts
- Ne jamais modifier `margin`, `padding`, `min-width`, `min-height`, ou `transform` sur les événements `:hover`.
- Autoriser uniquement les modifications suivantes sur hover : `background-color`, `color`, `border-color`, `box-shadow` (subtil), et `cursor`.
- Définir explicitement `min-height` / `max-height` pour boutons et tabs afin d'empêcher toute variation de taille.
- Encapsuler le contenu dans un `QFrame` blanc pour protéger la zone extérieure des changements de style internes.

## Exemple pratique (extrait `Profile.ui`)
- `QPushButton` styles:
  ```css
  QPushButton {
      background-color: #007bff;
      color: white;
      border-radius: 6px;
      padding: 10px 16px;
      min-height: 36px;
      max-height: 36px;
  }
  QPushButton:hover { background-color: #0056b3; }
  ```
- `QTabBar::tab` styles (voir `mainwindow.ui` ligne ~820 pour référence)

## Organisation dans Qt Designer
- Chaque zone est définie comme widget conteneur avec `QVBoxLayout`/`QHBoxLayout`/`QGridLayout`.
- Les `QFrame` sont utilisés pour contenants visuels (ex: `profileContainer`), pour appliquer background blanc, border et border-radius.

---

Pour plus de précision je peux lister les extraits exacts de `style.qss` et les correspondances ligne par ligne.