# 1. Login / Sign Up / Forgot Password

Ce document décrit en détail l'implémentation de l'authentification (Login, Sign Up, Forgot Password) dans le projet Amine Templar (Qt 6.7.3 Widgets / C++).

IMPORTANT: toutes les références ci-dessous sont tirées du code courant du projet.

## Fichiers clés
- `login.ui` — définition des formulaires (login, signup, forgot password). (voir lignes autour de 240-320 pour le bouton Sign In, 390 pour Forgot Password)
- `mainwindow.cpp` — intégration des formulaires dans l'overlay principal, connexions signal-slot. (voir `MainWindow::setupLoginForms()` autour de la ligne 120 et `MainWindow::setupLoginFormConnections()` autour de ligne 128 et suivantes)

## Objets UI (noms exacts et lignes)
- `loginButton` (Bouton Sign In)
  - Localisation: `login.ui`, widget `QPushButton` nommé `loginButton` (ligne ~262)
  - Propriétés: `minimumSize` height 48, police Poppins 12pt, style en ligne (background-color `#007bff`, hover `#0056b3`) (voir bloc de style dans `login.ui` lignes 240-320)
  - Connexions: connecté à `MainWindow::validateAndLogin()` via `setupLoginFormConnections()` (voir `mainwindow.cpp` lignes ~288-291)

- `forgotPasswordNavButton` (navigation vers form "Forgot password?")
  - Localisation: `login.ui` (ligne ~390)
  - Connexion: connecté à `MainWindow::showForgotPasswordForm()` dans `mainwindow.cpp` (ligne ~268-271)

- `sendResetLinkButton` (bouton d'envoi du lien de réinitialisation)
  - Localisation: `login.ui` (ligne ~1034)
  - Connexion: connecté à `MainWindow::validateAndSendResetLink()` via `setupLoginFormConnections()` (voir `mainwindow.cpp` ligne ~(sendResetLinkButton connect))

- `signUpNavButton` / `signUpButton` / `backToLoginFromSignUpButton`
  - Localisations: `login.ui` (signUpNavButton ligne ~437, signUpButton ligne ~797, backToLoginFromSignUpButton ligne ~850)
  - Connexions: navigation et validation via `MainWindow::showSignUpForm()` et `MainWindow::validateAndSignUp()` (voir `mainwindow.cpp` `setupLoginFormConnections()` lignes 125-200)

## Comment ça marche (flux)
1. L'UI est définie dans `login.ui` (widgets, layouts) — aucune logique métier ici. Les boutons et champs portent des noms d'objets (`loginButton`, `loginEmailLineEdit`, `loginPasswordLineEdit`, etc.).
2. `MainWindow::setupLoginForms()` (file `mainwindow.cpp`, ligne ~120) instancie un `QWidget` (nommé `loginPageWidget`) et appelle `loginUI->setupUi(loginPageWidget)` pour charger la définition `login.ui` dans ce widget.
3. Ce widget est ajouté à `ui->authStackedWidget` (ligne ~124) et les connexions sont configurées par `MainWindow::setupLoginFormConnections()` (ligne ~160+).
4. `setupLoginFormConnections()` recherche dynamiquement (via `findChild`) les boutons par leurs noms d'objet (ex: `loginPageWidget->findChild<QPushButton*>("loginButton")`) puis connecte leurs signaux `clicked` aux slots correspondants dans `MainWindow` (ex: `validateAndLogin`). Les hover effects sont appliqués par `MainWindow::addButtonHoverEffect()`.

## Détail technique des slots (C++)
- `MainWindow::validateAndLogin()` (file `mainwindow.cpp`, ligne ~517)
  - Récupère les champs `loginEmailLineEdit` et `loginPasswordLineEdit` via `findChild`.
  - Valide les champs (non vide, format simple) — si valide, passe à l'écran principal (`showMainContent()`).
  - Ajoute des messages via `QMessageBox` pour retours utilisateurs.

- `MainWindow::showForgotPasswordForm()` (file `mainwindow.cpp`, ligne ~396)
  - Appelle `switchLoginFormWithAnimation(2)` (ou `authStackedWidget->setCurrentIndex(2)`), ce qui affiche la page Forgot Password dans le `authStackedWidget`.

- `MainWindow::validateAndSendResetLink()` (file `mainwindow.cpp`, connecté approximativement ligne ~200)
  - Valide l'e-mail de reset (champ `resetEmailLineEdit`) et affiche un message d'information si OK.

## Layouts et organisation dans `login.ui`
- Le formulaire utilise `QVBoxLayout` principal (nom `verticalLayout`).
- Le formulaire login est un `QWidget` (loginFormPage) avec un `QVBoxLayout` nommé `loginFormLayout` (marges: left=48, top=...)
- Les champs sont des `QLineEdit` placés verticalement; les boutons sont placés verticalement avec des `spacers` pour contrôler l'espacement.
- Le `authStackedWidget` (dans la fenêtre principale) permet de basculer entre Login / Sign Up / Forgot Password sans ouvrir de nouvelles fenêtres.

## Styles, polices et effets
- Police Poppins chargée dans `main.cpp` (ligne ~10-25) via `QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-Light.ttf")`.
- Styles principaux appliqués de deux façons:
  - Styles inline dans `login.ui` (ex: `loginButton` a `styleSheet` défini dans `login.ui` lignes 240-320)
  - Style global appliqué via `:/style.qss` (chargé dans `main.cpp`) pour comportements/consistance globales.
- Hover effects limités à changements de couleur (`background-color`) et `cursor` (pointeur).
- Aucun `transform` ou changement de padding/margin/size n'est appliqué lors de l'hover (garantit stabilité visuelle).

## Comportements spéciaux
- `loginButton` ouvre l'application : `validateAndLogin()` effectue contrôles et affiche le contenu principal via `showMainContent()`.
- `forgotPasswordNavButton` bascule le `authStackedWidget` sur la page Forgot Password.
- `sendResetLinkButton` simule l'envoi d'un lien (affiche un `QMessageBox`) ; l'implémentation réelle d'envoi n'est pas incluse.

## Ce qui est fait en UI vs en C++
- UI (`login.ui`): structure des formulaires, noms des widgets, styles ligne pour boutons, placeholders et propriétés de layout.
- C++ (`mainwindow.cpp`): création dynamique du widget login (`loginPageWidget`), `setupUi()`, connexions `findChild` + `connect`, logique de validation (`validateAndLogin`), navigation (switch d'indices dans `authStackedWidget`) et feedback utilisateur.

## Capture d'écran / diagramme (placeholder)
- [IMAGE] `screens/login_form.png` — capture placeholder du formulaire de login

---

Pour toute question sur un widget particulier (par exemple le champ `loginEmailLineEdit` ou la validation précise), je peux extraire les lignes exactes supplémentaires et documenter plus finement.
