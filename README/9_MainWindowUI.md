# Détail complet de `mainwindow.ui`

Ce document décrit l'architecture et la structure complètes de `mainwindow.ui` (fichier principal de l'interface), explique à quoi sert chaque section/widget, comment les icônes/polices/background sont référencés, et comment le code C++ s'y connecte.

Fichier : `mainwindow.ui`
Chemin : `c:\Users\user\Documents\QT - Test\AmineTemplar\mainwindow.ui`

Résumé rapide
- `MainWindow` (QMainWindow) contient :
  - un `centralwidget` avec un `QHBoxLayout` principal
  - une `sidebarWidget` (à gauche) — navigation principale
  - un `QStackedWidget` `mainStackedWidget` (au centre) — contient `normalContentPage` et `loginOverlayPage`
  - le `normalContentPage` contient header + contenu principal (un autre `QStackedWidget` `stackedWidget` avec les pages Employer/Profile/Projects/...)
  - `loginOverlayPage` contient `authStackedWidget` (boîte de formulaire Login/SignUp/Forgot)

Structure détaillée (section par section)

1) Propriétés globales
- Taille initiale : `1200x800`
- `windowTitle` : "Amine Templar"
- `styleSheet` appliqué sur `QMainWindow` :
  - définit `background-image: url(:/images/background.jpg);` et propriétés de répétition/position/scale.
  - Explication : le background global est défini ici pour que toute la fenêtre ait une image de fond (fichier inclus via `resources.qrc` et accessible en C++ ou `.ui` via `:/images/background.jpg`).

2) `centralwidget` (QWidget)
- Layout : `QHBoxLayout` (0 margins) — deux colonnes : `sidebarWidget` + `mainStackedWidget`.

3) `sidebarWidget` (QWidget)
- Taille fixe en largeur : 280px (min/max configurés).
- Style : fond clair `#f8f9fa`, bord droit `1px solid #e9ecef`.
- Contenu :
  - `logoLabel` : titre / logo textuel en haut (Poppins 18pt), centré.
  - Boutons de navigation (`QPushButton`): `employerBtn`, `profileBtn`, `projectsBtn`, `editorBtn`, `libraryBtn`, `settingsBtn`, `shopBtn`.
    - Chaque bouton : hauteur 50px, police `Poppins`, style inline (padding, couleur, hover, pressed), `checkable=true` et `autoExclusive=true` pour comportement de groupe (simuler une sidebar active).
    - `employerBtn` contient une icône (`:/resources/icons/employer.svg` via `resources.qrc`). Les autres boutons utilisent icônes similaires déclarées dans `resources.qrc`.
  - `userProfileWidget` : encadré en bas avec avatar (`userAvatarLabel`), `usernameLabel` et `logoutBtn` (icone `:/icons/logout.svg`).

Pourquoi ici ?
- La sidebar concentre la navigation primaire ; utiliser `checkable` + `autoExclusive` permet de garder la sélection active visuellement sans logique additionnelle.
- Les icônes sont référencées via le `resource` attribué dans le `.ui` (`resources.qrc`) afin qu'elles embarquent dans l'exécutable (rcc) et soient accessibles par `:/icons/...`.

4) `mainStackedWidget` (QStackedWidget)
- Style : fond blanc translucide `rgba(255,255,255,0.95)`, border-radius 10px, margin.
- Pages :
  - `normalContentPage` : affichage normal (header + contenu)
  - `loginOverlayPage` : overlay pour les formulaires d'authentification
- Raison : `mainStackedWidget` permet de basculer entre la vue normale et l'overlay de connexion (appelé dans `MainWindow::onLoginClicked()` via `ui->mainStackedWidget->setCurrentIndex(1);`).

5) `normalContentPage`
- Contient :
  - `headerWidget` : bandeau en haut (hauteur fixe 70px) avec bouton `loginBtn` (style arrondi, bleu) — bouton lié à `MainWindow::onLoginClicked()`.
  - `stackedWidget` : QStackedWidget principal des pages (employerPage, profilePage, projectsPage, editorPage, libraryPage, settingsPage, shopPage).

6) `stackedWidget` (pages principales)
- Page par défaut : `employerPage` et à l'intérieur un `QTabWidget` `employerTabWidget` (Tabs: Display / Add / Modify / Dashboard / Statistics / Chatbot / QR Scanner). Chaque tab a son `title` et son `icon` (icônes référencées dans `resources.qrc`).
- Pourquoi `QTabWidget` ici ? Parce que les sections de la vue Employer sont liées et l'utilisateur doit pouvoir switcher rapidement entre sous-sections.
- `employerPage` contient des widgets importants : `displayTitle`, `employeeTable`, boutons d'action (`searchBtn`, `sortBtn`, `exportBtn`, `modifyBtn`, `deleteBtn`), et tous utilisent des icônes/polices référencées via `resources.qrc` et `style.qss`/inline styles.

7) `profilePage`, `projectsPage`, `editorPage`, `libraryPage`, `settingsPage`, `shopPage`
- Pages placeholders ou avec contenus simples (Labels indiquant "Coming Soon" ou descriptions). Elles sont prévues pour être remplacées par des contrôleurs plus complets (cf. `MainWindow::setupPages()` qui remplace `profilePage` par `ProfileController` et `shopPage` par `ShopController`).

8) `loginOverlayPage`
- Conteneur centré (`loginCenteringContainer`) avec `loginFormsContainer` qui contient un `QStackedWidget` `authStackedWidget`.
- `authStackedWidget` est destiné à contenir les pages de Login / SignUp / Forgot Password (la page login est ajoutée dynamiquement depuis `MainWindow::setupLoginForms()` par `ui->authStackedWidget->addWidget(loginPageWidget);`).
- `backToMainButton` retourne à la page principale.

9) Ressources et références (icônes, fonts, background)
- `resources.qrc` est inclus via `<resources><include location="resources.qrc"/></resources>`.
- Icônes : référencées dans `.ui` en utilisant `iconset resource="resources.qrc"` puis `:/resources/icons/...` ou `:/icons/...` selon le chemin déclaré dans `resources.qrc`.
- Background : déclaré dans le `styleSheet` du `QMainWindow` avec `:/images/background.jpg`.
- Fonts : la police `Poppins` est chargée en C++ via `QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-Light.ttf")` (voir `main.cpp`) et `style.qss` applique des règles globales.

10) Connexions C++ ↔ UI
- `mainwindow.cpp` contient les `connect()` qui lient les boutons de la sidebar aux slots `onDashboardClicked()`, `onProfileClicked()`, etc.
- `MainWindow::setupPages()` remplace les placeholders par des contrôleurs :
  - `profileController = new ProfileController(this);`
  - `ui->stackedWidget->insertWidget(1, profileController);`
- `onLoginClicked()` bascule les `QStackedWidget` pour afficher l'overlay :
  - `ui->mainStackedWidget->setCurrentIndex(1);`
  - `ui->authStackedWidget->setCurrentIndex(0);`

11) Pourquoi cette architecture ?
- Séparation claire : sidebar (navigation) vs contenu (pages). Facilite le routage interne et l'extensibilité.
- Utilisation des `QStackedWidget` pour masquer/afficher des modes (contenu principal vs overlay login) et pour contenir les pages principales.
- `QTabWidget` dans `employerPage` pour organiser des sous-sections liées.
- Les contrôleurs (`ProfileController`, `ShopController`) permettent d'isoler la logique métier et l'UI complexe hors du fichier `.ui` principal.

---

Conseils pour modification et extension
- Pour ajouter une nouvelle page (ex: `analyticsPage`) :
  1. Dans `mainwindow.ui`, ajoutez un `QWidget` enfant de `stackedWidget` et donnez-lui `objectName` clair (`analyticsPage`).
  2. Concevez la page (layouts, widgets) dans Designer.
  3. Dans `mainwindow.cpp::setupPages()`, soit insérez un contrôleur dynamique (`analyticsController`) à l'index choisi, soit laissez Designer gérer la page statique.

- Pour ajouter une icône :
  1. Placez le fichier SVG/PNG dans `resources/icons/`.
  2. Ouvrez `resources.qrc` dans Designer (ou éditez le fichier) et ajoutez la nouvelle ressource.
  3. Dans `.ui`, sélectionnez le widget et assignez l'icône via la propriété `icon` (Designer) ou utilisez `setIcon(QIcon(":/resources/icons/your.svg"))` en C++.

- Pour modifier la police globale :
  1. Ajoutez la police `.ttf` dans `resources/fonts/`.
  2. Chargez-la dans `main.cpp` via `QFontDatabase::addApplicationFont()`.
  3. Mettez `style.qss` à jour pour utiliser la famille de police dans tout le projet.

---

Fichier créé : `README/9_MainWindowUI.md`

Voulez-vous que j'ajoute :
- un tableau listant chaque widget `objectName` et sa description (utile pour référence rapide) ?
- ou que j'injecte ce README dans `README/5_Overall.md` comme sommaire ?

Je peux aussi générer un fichier CSV `docs/mainwindow-ui-widgets.csv` listant `objectName,type,description,ui_file,line` si vous préférez un format machine-parsable.
## Tableau des widgets (extrait de `mainwindow.ui`)

Ci-dessous un tableau récapitulatif (colonnes : `objectName` | `class` | `brief role` | `ui line`) construit à partir de `mainwindow.ui`. Utilisez le CSV correspondant `docs/mainwindow-ui-widgets.csv` pour import dans des outils (Excel, scripts).

| objectName | class | brief role | ui line |
|---|---|---:|---:|
| MainWindow | QMainWindow | Application main window | 4 |
| centralwidget | QWidget | Main central widget containing layout | 25 |
| sidebarWidget | QWidget | Left sidebar navigation container | 43 |
| logoLabel | QLabel | App title/logo display | 79 |
| employerBtn | QPushButton | Sidebar button: Employer page | 125 |
| profileBtn | QPushButton | Sidebar button: Profile page | 184 |
| projectsBtn | QPushButton | Sidebar button: Projects page | 236 |
| editorBtn | QPushButton | Sidebar button: Editor page | 288 |
| libraryBtn | QPushButton | Sidebar button: Library page | 340 |
| settingsBtn | QPushButton | Sidebar button: Settings page | 392 |
| shopBtn | QPushButton | Sidebar button: Shop page | 444 |
| userProfileWidget | QWidget | User info container with avatar and logout | 496 |
| userAvatarLabel | QLabel | User avatar display | 534 |
| usernameLabel | QLabel | Displays current user's name | 572 |
| logoutBtn | QPushButton | Logout action button | 608 |
| mainStackedWidget | QStackedWidget | Top-level stacked widget (content vs login overlay) | 671 |
| normalContentPage | QWidget | Normal app content page | 682 |
| headerWidget | QWidget | Top header with login button | 700 |
| loginBtn | QPushButton | Header login button | 746 |
| stackedWidget | QStackedWidget | Main content pages container (employer, profile...) | 785 |
| employerPage | QWidget | Employer main page container | 789 |
| employerTabWidget | QTabWidget | Tabs inside employer page | 807 |
| displayTab | QWidget | Tab: Display | 848 |
| displayTitle | QLabel | Title for display tab | 873 |
| actionButtonsWidget | QWidget | Container for action buttons (search/sort/export) | 894 |
| searchBtn | QPushButton | Search action button | 912 |
| sortBtn | QPushButton | Sort action button | 953 |
| exportBtn | QPushButton | Export to PDF button | 994 |
| employeeTable | QTableWidget | Table of employees | 1051 |
| tableActionsWidget | QWidget | Container with modify/delete actions | 1129 |
| modifyBtn | QPushButton | Modify selected employee | 1160 |
| deleteBtn | QPushButton | Delete selected employee | 1201 |
| addTab | QWidget | Tab: Add | 1246 |
| addTitle | QLabel | Title for Add tab | 1268 |
| addPlaceholder | QLabel | Placeholder text for Add tab | 1288 |
| modifyTab | QWidget | Tab: Modify | 1329 |
| modifyTitle | QLabel | Title for Modify tab | 1351 |
| modifyPlaceholder | QLabel | Placeholder for Modify tab | 1371 |
| dashboardTab | QWidget | Tab: Dashboard | 1412 |
| dashboardTabTitle | QLabel | Title for Dashboard tab | 1434 |
| dashboardTabContent | QLabel | Content for Dashboard | 1454 |
| statisticsTab | QWidget | Tab: Statistics | 1495 |
| statisticsTitle | QLabel | Title for Statistics tab | 1517 |
| statisticsPlaceholder | QLabel | Placeholder for Statistics | 1537 |
| chatbotTab | QWidget | Tab: Chatbot | 1588 |
| chatbotTitle | QLabel | Title for Chatbot tab | 1610 |
| chatbotPlaceholder | QLabel | Placeholder for Chatbot | 1630 |
| qrScannerTab | QWidget | Tab: QR Scanner | 1671 |
| qrScannerTitle | QLabel | Title for QR Scanner tab | 1693 |
| qrScannerPlaceholder | QLabel | Placeholder for QR Scanner | 1713 |
| profilePage | QWidget | Profile placeholder page | 1762 |
| profilePlaceholder | QLabel | Label inside profile page | 1777 |
| projectsPage | QWidget | Projects page container | 1802 |
| projectsTitle | QLabel | Title for Projects | 1817 |
| projectsContent | QLabel | Content for Projects | 1837 |
| editorPage | QWidget | Editor page container | 1864 |
| editorTitle | QLabel | Title for Editor | 1879 |
| editorContent | QLabel | Content for Editor | 1899 |
| libraryPage | QWidget | Library page container | 1926 |
| libraryTitle | QLabel | Title for Library | 1941 |
| libraryContent | QLabel | Content for Library | 1961 |
| settingsPage | QWidget | Settings page container | 1988 |
| settingsTitle | QLabel | Title for Settings | 2003 |
| settingsContent | QLabel | Content for Settings | 2023 |
| shopPage | QWidget | Shop page container | 2050 |
| shopPlaceholder | QLabel | Label in Shop page | 2065 |
| loginOverlayPage | QWidget | Overlay page for login forms | 2094 |
| loginCenteringContainer | QWidget | Centering container for login forms | 2117 |
| backToMainButton | QPushButton | Button to return to main content | 2148 |
| loginFormsContainer | QWidget | White card containing auth forms | 2176 |
| authStackedWidget | QStackedWidget | Auth forms container (Login/SignUp/Forgot) | 2214 |
