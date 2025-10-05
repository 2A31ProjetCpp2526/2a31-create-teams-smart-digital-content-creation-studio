# 5. Overall (Vue d'ensemble du projet)

Ce document donne une vue d'ensemble technique et organisationnelle du projet Amine Templar.

## Architecture générale
- `MainWindow` (fichiers `mainwindow.h` / `mainwindow.cpp`) : conteneur principal de l'application. Gère la barre latérale, la navigation entre pages, et l'overlay de connexion.
- Pages et contrôleurs :
  - `Profile` : `Profile.ui` + `profilecontroller.cpp` / `profilecontroller.h`
  - `Shop` : `shopcontroller.cpp` / `shopcontroller.h` (+ `Shop.ui`)
  - D'autres pages (Editor, Library, Projects) définies dans `mainwindow.ui` et gérées par `MainWindow`.

## Structure du dépôt (principaux dossiers/fichiers)
- `*.ui` — fichiers Qt Designer décrivant l'UI (ex: `mainwindow.ui`, `Profile.ui`, `login.ui`)
- `*.cpp`, `*.h` — code C++ (ex: `mainwindow.cpp`, `profilecontroller.cpp`)
- `resources/` — icônes (`icons/*.svg`), polices (`fonts/`), images
- `build/` — dossier de build (généré), contenant les exécutables et fichiers intermédiaires
- `style.qss` — feuille de style globale

## Compilation & Build
- `CMakeLists.txt` — fichier CMake pour configurer la build (Qt 6.7.3). Le workspace contient aussi des Makefile pour debug/release.
- Pour construire localement : utiliser la configuration Qt/CMake (Qt Creator) ou exécuter `cmake` puis `cmake --build build`.

## Signal / Slot (mécanique)
- La connexion UI ↔ C++ est faite soit :
  - automatiquement par `uic` (génération de `ui_*.h` et usage de `ui->element` dans les contrôleurs),
  - soit dynamiquement via `findChild` et `connect` (ex: `loginPageWidget->findChild<QPushButton*>("loginButton")`).
- Les slots sont des méthodes members (ex: `MainWindow::validateAndLogin()`, `ProfileController::onChangePhotoClicked()`), connectées aux signaux `clicked`, `textChanged`, etc.

## Ce qui a été implémenté récemment
- Encapsulation du contenu `Profile` dans `profileContainer` (QFrame) pour éliminer les layout shifts.
- Ajout d'un onglet `QR Code` dans `Profile.ui` et d'un slot `onGenerateQRCodeClicked()` dans `profilecontroller.cpp`.
- Correction des références UI ↔ C++ (ex: `generateQRBtn`, `activityListWidget`) pour assurer la compilation.

## Bonnes pratiques et recommandations
- Toujours utiliser `QVBoxLayout`/`QHBoxLayout`/`QGridLayout` pour structurer les UI; éviter le positionnement absolu.
- Appliquer des contraintes `min/max` sur widgets critiques (boutons, tabs, avatars) pour éviter des redimensionnements imprévus.
- Limiter les effets CSS sur `:hover` aux changements d'apparence (couleur, bordure, shadow) mais pas à la taille/padding/marge.
- Charger la police globale en début d'exécution (dans `main.cpp`) pour garantir consistance de rendu.

## Qui a fait quoi
- Design UI (fichiers `.ui`) : conception via Qt Designer — éléments placés et stylés principalement dans `*.ui`.
- Logique C++ : implémentation des comportements (dialogs, validation, lecture/écriture JSON) dans `*.cpp`.
- Modifications récentes (anti-shift & QR tab) : encapsulation `profileContainer` dans `Profile.ui` et ajout/ajustement des slots correspondants dans `profilecontroller.cpp`.

---

Si vous voulez, je peux produire une version imprimable (.pdf) de ces README, ou étendre chaque README avec des extractions plus fines (par ex. la liste complète de tous les widgets UI avec numéros de ligne exacts).