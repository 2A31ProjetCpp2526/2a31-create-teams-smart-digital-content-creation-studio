# 2. Employer (Page Employeur)

Ce document détaille la page Employer (employeur) du projet Amine Templar.

## Fichiers clés
- `mainwindow.ui` — contient la définition du layout principal, la barre latérale (sidebar) et l'organisation des pages (dashboard, profile, projects, ...).
- `mainwindow.cpp` — gère la logique de navigation depuis la sidebar vers les pages (méthodes `onDashboardClicked()`, `onProfileClicked()`, etc.).

## Sidebar horizontale / verticale et boutons
- Les boutons de la sidebar sont définis dans `mainwindow.ui` (rechercher `QPushButton` dans la section sidebar);
- Connexions des boutons de la sidebar : dans `mainwindow.cpp` les méthodes suivantes sont utilisées pour la navigation :
  - `onDashboardClicked()` (index 0)
  - `onProfileClicked()` (index 1)
  - `onProjectsClicked()` (index 2)
  - `onEditorClicked()` (index 3)
  - `onLibraryClicked()` (index 4)
  - `onSettingsClicked()` (index 5)
  - `onShopClicked()` (index 6)
  - Ces méthodes appellent `switchToPage(index)` qui effectue une transition en fondu via `QPropertyAnimation` (voir `mainwindow.cpp`, lignes ~140-200)

## Tabs et sections dans Employer page
- La page Employer contient typiquement des sous-tabs: `Display`, `History`, `Security`, `Transactions`, `Chatbot`, `Statistics` (les widgets correspondants sont définis dans `mainwindow.ui` ; voir sections autour de 820-900 pour le style des `QTabBar::tab`).
- Les styles des `QTabBar::tab` (padding, bordure, couleur, hover) sont définis dans `mainwindow.ui` (voir bloc autour de la ligne 820). Le style appliqué garantit la stabilité visuelle (aucune modification de taille lors du survol).

## Icônes et schéma de couleurs
- Les icônes sont référencées via `resources.qrc` (emplacement: `resources/icons/*.svg`). Exemple: `:/resources/icons/display.svg`.
- Couleurs: palette principale bleue `#007bff` pour éléments actifs, gris clair `#f8f9fa` pour fonds, `#dee2e6` pour bordures. Ces couleurs sont utilisées de manière cohérente dans `style.qss` et dans certains `styleSheet` inline.

## Éviter les layout-shifts
- L'approche utilisée pour prévenir les mouvements est :
  - Utiliser des layouts Qt (QVBoxLayout/QHBoxLayout/QGridLayout) avec tailles minimales/maximales définies pour les contrôles importants (ex: `min-height/max-height` sur tabs et boutons).
  - Ne pas utiliser `transform` ni modifications de `padding/margin` lors d'événements hover.
  - Les transitions visuelles sont gérées par opacité (`QPropertyAnimation`) plutôt que par déplacement d'éléments.

## Connexions C++
- Les actions de la sidebar sont connectées à des slots dans `mainwindow.cpp` (par exemple: `connect(sidebarBtn, &QPushButton::clicked, this, &MainWindow::onProfileClicked);`). Ces méthodes appellent `switchToPage(index)` qui met à jour `ui->stackedWidget`.

## Composants et noms d'objets (exemples)
- `ui->stackedWidget` : conteneur principal des pages (Dashboard, Profile, ...)
- `ui->mainStackedWidget` : contient la vue normale et l'overlay de connexion
- `ui->loginBtn` : bouton dans la barre (voir `mainwindow.cpp` ligne ~24 pour l'assignation d'icône)

---

Si vous voulez, je peux parcourir et lister chaque bouton de la sidebar avec ses lignes exactes dans `mainwindow.ui` et `mainwindow.cpp` — dites-moi si vous souhaitez la liste complète des objets et lignes pour la sidebar.