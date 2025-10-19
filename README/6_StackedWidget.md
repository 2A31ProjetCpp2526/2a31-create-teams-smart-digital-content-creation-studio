# Utilisation de QStackedWidget dans AmineTemplar

Ce document explique comment `QStackedWidget` est utilisé dans le projet, où le trouver dans le code, et comment en ajouter / changer des pages (Designer + C++). Exemples et références sont fournis pour `ui->stackedWidget`, `ui->mainStackedWidget` et `ui->authStackedWidget`.

## Qu'est-ce que `QStackedWidget` ?
`QStackedWidget` est un conteneur Qt qui contient plusieurs pages (widgets) mais n'en affiche qu'une à la fois. C'est idéal pour implémenter des vues commutables (par ex. Dashboard / Profile / Projects) ou des formulaires multiples (Login / SignUp / Forgot Password).

## Où sont les `QStackedWidget` dans ce projet
- `ui->mainStackedWidget` : conteneur principal qui bascule entre la vue normale (contenu principal) et l'overlay de connexion (login overlay). (déclaré dans le UI principal `mainwindow.ui`).
- `ui->stackedWidget` : conteneur des pages principales (Dashboard, Profile, Projects, Editor, Library, Settings, Shop). Les pages sont ajoutées dans `ui_mainwindow.h` généré par Qt Designer et initialisées dans `mainwindow.cpp`.
- `ui->authStackedWidget` : conteneur des formulaires de connexion (Login / SignUp / Forgot Password). L'application ajoute dynamiquement la page login à cet `authStackedWidget` depuis `MainWindow::setupLoginForms()`.

Références rapides trouvées dans le projet :
- `mainwindow.cpp` : initialisation et utilisation :
  - `ui->stackedWidget->setCurrentIndex(0);` (ligne ~84 de `mainwindow.cpp`) — page initiale.
  - `QWidget* profilePlaceholder = ui->stackedWidget->widget(1);` (ligne ~104) — remplacement d'une page placeholder par `profileController`.
  - `ui->authStackedWidget->addWidget(loginPageWidget);` (setupLoginForms(), ligne ~126) — ajout de la page login.
  - `authStackedWidget->setCurrentIndex(0);` (setupLoginForms(), ligne ~134) — montrer la page Login par défaut.
  - `ui->mainStackedWidget->setCurrentIndex(1); ui->authStackedWidget->setCurrentIndex(0);` (dans `onLoginClicked()`) — ouvrir l'overlay de login et afficher le formulaire.

## Exemple : créer une page dans Designer
1. Ouvrez `mainwindow.ui` dans Qt Designer.
2. Localisez le `QStackedWidget` nommé `stackedWidget` (dans la zone normaleContentPage). Il contient déjà les pages `employerPage`, `profilePage`, `projectsPage`, etc.
3. Pour ajouter une nouvelle page :
   - Dans l'arbre d'objets, sélectionnez `stackedWidget` puis clic droit → "Insert Page" ou utilisez le bouton "Add Page" de l'éditeur.
   - Donnez un `objectName` clair à la nouvelle page (ex. `analyticsPage`).
   - Conceptionnez la page (ajoutez layouts, widgets, etc.).
4. Sauvegardez le `.ui`.

## Exemple : accéder et basculer en C++
- Basculer vers une page en connaissant son index :
```cpp
ui->stackedWidget->setCurrentIndex(2); // affiche la page à l'index 2
```
- Basculer en utilisan `switchToPage(int)` (méthode utilitaire du projet) :
```cpp
// depuis MainWindow
switchToPage(1); // appelle des animations puis setCurrentIndex(1)
```
- Remplacer dynamiquement une page par un widget contrôleur :
```cpp
QWidget* profilePlaceholder = ui->stackedWidget->widget(1); // récupère l'ancienne page (index 1)
if (profilePlaceholder) {
    ui->stackedWidget->removeWidget(profilePlaceholder);
    ui->stackedWidget->insertWidget(1, profileController);
    delete profilePlaceholder; // optionnel
}
```
Ceci est utilisé dans `MainWindow::setupPages()` pour remplacer des placeholders par `ProfileController` et `ShopController` (voir `mainwindow.cpp` lines ~88-120).

## Auth stacked (Login / SignUp / Forgot)
Le projet garde un `QStackedWidget` dédié aux formulaires d'authentification (`authStackedWidget`). L'exemple ci-dessous montre comment la page login est ajoutée dynamiquement :
```cpp
loginPageWidget = new QWidget();
loginUI = new Ui::LoginPage();
loginUI->setupUi(loginPageWidget);
ui->authStackedWidget->addWidget(loginPageWidget);
// stocke la référence pour manipuler plus tard
authStackedWidget = ui->authStackedWidget;
authStackedWidget->setCurrentIndex(0); // montre Login
```
Cette logique se situe dans `MainWindow::setupLoginForms()` (voir `mainwindow.cpp` lines ~120-140).

## Conseils pratiques et pièges
- Index vs objet : préférer `setCurrentWidget(widgetPointer)` ou `setCurrentIndex(index)` selon ce qui est plus lisible. N'utilisez pas d'index "magiques" sans commentaire (ex: 1 signifie Profile) — ajoutez des constantes ou commentaires.
- Initialisation : si vous remplacez des pages dynamiquement (comme `profileController`), assurez-vous que la page a été correctement construite avant de l'insérer.
- Animations : `switchToPage()` applique un fondu; si vous changez `stackedWidget` en-dehors de cette méthode, vous perdrez l'animation.
- Taille : gardez des layouts et des tailles minimales sur les widgets internes pour éviter les sauts lors du changement de page.

---
## Différence entre `QStackedWidget` et `QTabWidget`

### Résumé court
- `QStackedWidget` : conteneur de pages affichant une seule page à la fois, sans onglets visibles. Le changement se fait par code (index/widget). Bon pour des écrans complets (Dashboard, Profile, ...).
- `QTabWidget` : conteneur avec une barre d'onglets visible que l'utilisateur peut cliquer pour changer de page. Bon pour des sections liées (Info / Historique / Sécurité dans un profil).

### Comparaison détaillée
- Interface utilisateur
  - `QTabWidget` affiche une barre d'onglets (navigation visible par l'utilisateur).
  - `QStackedWidget` n'affiche pas d'onglets — navigation contrôlée par le code ou des boutons externes.

- Navigation
  - `QTabWidget` : navigation utilisateur directe (clic sur onglet).
  - `QStackedWidget` : navigation programmée (par ex. menu latéral, boutons, animations).

- Cas d'usage
  - `QTabWidget` → sections internes d'une même page, petits panneaux liés.
  - `QStackedWidget` → pages entières/écrans distincts de l'application.

- Comportement et style
  - `QTabWidget` fournit de la navigation native (Ctrl+Tab, focus clavier) et est facile à créer dans Designer.
  - `QStackedWidget` est neutre visuellement et se prête bien aux animations/transitions (fondu, slide).

### Exemples rapides
- Basculer vers l'index 2 :

```cpp
ui->stackedWidget->setCurrentIndex(2); // QStackedWidget
ui->profileTabWidget->setCurrentIndex(2); // QTabWidget
```

- Basculer vers un widget précis (préférable aux indices magiques) :

```cpp
ui->stackedWidget->setCurrentWidget(ui->analyticsPage);
```

### Astuce : utiliser `QTabWidget` sans afficher la barre d'onglets
Si vous voulez conserver la gestion de pages dans Designer (ajout/suppression facile) mais masquer la barre d'onglets pour qu'il ressemble à un `QStackedWidget` :

```cpp
ui->profileTabWidget->tabBar()->hide(); // cache la barre d'onglets
```

Cela vous permet de concevoir dans Designer tout en contrôlant la navigation par code.

### Recommandation
- Utilisez `QStackedWidget` pour des écrans/app pages complètes.
- Utilisez `QTabWidget` pour des sous-sections internes où l'utilisateur doit voir et choisir les onglets.
- Pour la flexibilité, vous pouvez cacher la `tabBar()` d'un `QTabWidget` et piloter la navigation par code si nécessaire.

---

## Guide pas-à-pas : créer et utiliser `QStackedWidget` et `QTabWidget` (Designer + C++)

Ci-dessous des étapes pratiques — copy/paste friendly — pour créer et manipuler ces widgets dans Qt Designer puis en C++.

### 1) Créer un `QStackedWidget` dans Qt Designer
1. Ouvrez `mainwindow.ui` dans Qt Designer.
2. Dans la palette de widgets, trouvez `QStackedWidget` (Widgets containers) et glissez-le sur la zone où vous voulez afficher vos pages.
3. Dans l'arbre d'objets, sélectionnez le `QStackedWidget` et donnez-lui un `objectName` (ex: `stackedWidget` ou `mainStackedWidget`).
4. Pour ajouter une page :
   - Sélectionnez le `QStackedWidget` → clic droit → "Insert Page".
   - Une nouvelle page apparaît dans l'arbre sous `stackedWidget` (par ex. `page_2`).
   - Sélectionnez la nouvelle page, changez son `objectName` (ex: `analyticsPage`) et ajoutez-y layouts/widgets.
5. Répétez pour toutes les pages nécessaires puis sauvegardez.

### 2) Utiliser `QStackedWidget` en C++
- Inclure et accéder au widget créé par Designer :
```cpp
// Dans MainWindow (après ui->setupUi(this))
ui->stackedWidget->setCurrentIndex(0); // afficher la première page
// ou
ui->stackedWidget->setCurrentWidget(ui->analyticsPage); // afficher la page par référence
```
- Remplacer une page par un QWidget dynamique (pattern utilisé dans ce projet) :
```cpp
QWidget* placeholder = ui->stackedWidget->widget(1);
if (placeholder) {
    ui->stackedWidget->removeWidget(placeholder);
    ui->stackedWidget->insertWidget(1, profileController);
    delete placeholder; // facultatif
}
```
- Écouter un bouton pour basculer de page :
```cpp
connect(ui->profileBtn, &QPushButton::clicked, this, [this]() {
    ui->stackedWidget->setCurrentIndex(1);
});
```

### 3) Créer un `QTabWidget` dans Qt Designer
1. Ouvrez le `.ui` où vous voulez des onglets (ex: `Profile.ui`).
2. Dans la palette, glissez `QTabWidget` sur la zone désirée.
3. Dans l'arbre d'objets, renommez le (ex: `profileTabWidget`).
4. Pour chaque onglet : sélectionnez le `QTabWidget`, cliquez sur l'icône "Add Page" ou clic droit → "Insert Page".
5. Sélectionnez chaque page d'onglet et concevez son contenu. Donnez des noms d'objet clairs si vous voulez y accéder directement.
6. Sauvegardez le `.ui`.

### 4) Utiliser `QTabWidget` en C++
- Basculement par index :
```cpp
ui->profileTabWidget->setCurrentIndex(2);
```
- Basculement par widget (si vous avez un pointeur vers l'onglet) :
```cpp
ui->profileTabWidget->setCurrentWidget(ui->securityTab);
```
- Récupérer l'index d'un onglet :
```cpp
int idx = ui->profileTabWidget->indexOf(ui->securityTab);
```

### 5) Astuce : masquer la barre d'onglets d'un `QTabWidget` pour qu'il se comporte comme un `QStackedWidget`
Si vous préférez concevoir avec `QTabWidget` mais sans affichage d'onglets :
```cpp
ui->profileTabWidget->tabBar()->hide();
// Contrôlez la navigation via des boutons/menu
ui->profileTabWidget->setCurrentIndex(0);
```

### 6) Bonnes pratiques
- Évitez les "indices magiques" ; documentez quel index correspond à quelle page ou utilisez des constantes nommées.
- Préférez `setCurrentWidget()` si vous avez des pointeurs clairs vers les pages.
- Assurez-vous que les layouts sont complets (margins, min sizes) pour éviter les sauts de taille lors du changement de page.
- Si vous remplacez dynamiquement des pages, initialisez-les complètement avant l'insertion.

---

Fichiers / lignes utiles :
- `mainwindow.cpp` : `switchToPage(int)`, `setupPages()`, `setupLoginForms()`, `onLoginClicked()` (voir les lignes autour de 80–140). 
- `mainwindow.ui` : `QStackedWidget` noms : `mainStackedWidget`, `stackedWidget`, `authStackedWidget` (voir `mainwindow.ui` ou le header généré `build/.../ui_mainwindow.h`).

Si vous voulez, j'ajoute des extraits plus précis (avec numéros de ligne exacts) ou je modifie `README/5_Overall.md` pour y insérer un lien vers ce document. Voulez-vous que je l'ajoute aussi au README principal maintenant ?