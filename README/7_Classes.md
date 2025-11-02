# Inventaire des classes et objets du projet AmineTemplar

Ce document liste les classes (contrôleurs, widgets, structures de données) présentes dans le projet, leurs fichiers associés, leur rôle principal, et les méthodes/éléments importants à connaître. Le but est d'avoir une vue d'ensemble rapide pour la maintenance et l'extension.

> Remarque : ce fichier regroupe les classes définies manuellement (fichiers `.h/.cpp`) et les classes générées par Qt (`Ui::...`) venant des `.ui`.

---

## 1) Classes principales (implémentées manuellement)

### `MainWindow` — `mainwindow.h` / `mainwindow.cpp`
- Type : `QMainWindow`
- Rôle : point d'entrée de l'application ; gère la navigation principale (sidebar), les pages (via `ui->stackedWidget`), l'overlay de login et les animations de transition.
- Membres importants :
  - `Ui::MainWindow *ui;`
  - `ProfileController *profileController;`
  - `ShopController *shopController;`
  - `QStackedWidget *authStackedWidget;` (gestion des formulaires Login/SignUp/Forgot)
  - `int currentPageIndex;`
- Méthodes clés :
  - `setupPages()`, `setupLoginForms()`, `switchToPage(int)`, `setupAnimations()`, `setupSidebarIcons()`
  - Slots de navigation : `onDashboardClicked()`, `onProfileClicked()`, `onProjectsClicked()`, `onEditorClicked()`, `onLibraryClicked()`, `onSettingsClicked()`, `onShopClicked()`, `onLoginClicked()`
- Où il est instancié : Application bootstrap (`main.cpp`) crée `MainWindow`.

### `ProfileController` — `profilecontroller.h` / `profilecontroller.cpp`
- Type : `QWidget`
- Rôle : gère l'UI du profil utilisateur (page Profile) : données utilisateur, avatar, sécurité, historique, QR, export/import, activité, etc.
- Membres importants :
  - `Ui::Profile *ui;`
  - `QJsonObject profileData;`
  - `QTimer *autoSaveTimer;`
  - `QString avatarPath;`
- Méthodes clés :
  - `loadProfileData()`, `saveProfileData()`, `updateUIFromData()`, `updateDataFromUI()`
  - `refreshInternalTabLayout()` (méthode anti-flicker pour le `profileTabWidget`)
  - Slots : `onChangePhotoClicked()`, `onRemovePhotoClicked()`, `onGenerateAIImageClicked()`, `onGenerateQRCodeClicked()`, `onUpdatePasswordClicked()`, `onSaveProfileClicked()`, `onClearHistoryClicked()`, etc.
- Signaux : `profileUpdated()`, `avatarChanged(const QString&)`, `settingsChanged()`, `errorOccurred(const QString&)`
- Fichiers de données : constantes `PROFILE_DATA_FILE`, `AVATAR_FOLDER` définies dans l'en-tête.

### `ShopController` — `shopcontroller.h` / `shopcontroller.cpp`
- Type : `QWidget`
- Rôle : gère la page Shop (produits, panier, checkout, animations d'ajout au panier).
- Structures : `Product`, `CartItem` (définies en-tête)
- Membres importants :
  - `Ui::Shop *ui;`
  - `QVector<Product> products;`
  - `QVector<CartItem> cartItems;`
  - `double cartTotal;`
- Méthodes clés :
  - `setupProducts()`, `addToCart(const Product&, int)`, `updateCartDisplay()`, `saveCartData()`, `loadCartData()`, `onCheckout()`
- Slots : `onAddToCart1()` .. `onAddToCart6()`, `onCheckout()`, `onClearCart()`, `onCartItemDoubleClicked()`

---

## 2) Classes UI générées par Qt (issue des `.ui`)
Ces classes sont générées automatiquement et contiennent les définitions des widgets, leurs noms, et la méthode `setupUi()`.
- `Ui::MainWindow` — créé depuis `mainwindow.ui` (généré dans `build/.../ui_mainwindow.h`). Contient : `mainStackedWidget`, `stackedWidget`, `authStackedWidget`, `profileBtn`, `employerBtn`, `loginBtn`, etc.
- `Ui::Profile` — généré depuis `Profile.ui` (généré dans `build/.../ui_Profile.h`) ; contient `profileTabWidget`, `avatarLabel`, `saveProfileBtn`, `activityListWidget`, `generateQRBtn`, etc.
- `Ui::Shop` — généré depuis `Shop.ui`.
- `Ui::LoginPage` — généré depuis `login.ui` ; contient `authStackedWidget` local (mais `MainWindow` utilise sa propre instance dans l'overlay), `loginButton`, `forgotPasswordNavButton`, etc.
- `Ui::EditorPage`, `Ui::LibraryPage`, `Ui::ProjectsPage`, `Ui::SettingsPage`, etc. — générés depuis les `.ui` correspondants.

> Note : Les en-têtes générés se trouvent dans `build/.../AmineTemplar_autogen/include/ui_*.h`.

---

## 3) Autres fichiers/objets notables
- `main.cpp` : bootstrap de l'application (chargement de la police `Poppins`, application du fichier `style.qss`, création de `MainWindow`).
- `resources.qrc` (généré rcc) : référence toutes les icônes et images (`:/icons/*.svg`, `:/resources/fonts/*.ttf`).
- `style.qss` : stylesheet global appliqué via `main.cpp`.

---

## 4) Comment les classes sont instanciées et reliées (au runtime)
- `main()` crée `MainWindow` qui appelle `ui->setupUi(this)`.
- Dans `MainWindow::setupPages()` :
  - `profileController = new ProfileController(this);`
  - `shopController = new ShopController(this);`
  - Ces contrôleurs remplacent des pages placeholder dans `ui->stackedWidget` en utilisant `removeWidget()` / `insertWidget()`.
- `MainWindow::setupLoginForms()` crée dynamiquement `loginPageWidget` et appelle `ui->authStackedWidget->addWidget(loginPageWidget)`.

---

## 5) Suggestion pour README/7_Classes.md
Voulez-vous que j'ajoute pour chaque classe :
- Extrait des méthodes publiques avec numéros de ligne exacts ?
- Diagramme simple (ASCII) montrant dépendances (MainWindow -> ProfileController, ShopController) ?
- Un tableau listant les fichiers `.ui` correspondants et les widgets clés (avatarLabel, profileTabWidget, loginButton, etc.) ?

Dites-moi quelle granularité vous voulez et j'adapterai le fichier (`README/7_Classes.md`).

---

Fichier créé : `README/7_Classes.md` (c:\Users\user\Documents\QT - Test\AmineTemplar\README\7_Classes.md)

Tâche correspondante marquée complétée dans la todo list.
