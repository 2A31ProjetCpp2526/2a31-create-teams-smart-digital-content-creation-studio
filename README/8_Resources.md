# Ressources : icônes, polices et background dans AmineTemplar

Ce fichier explique précisément où sont stockées les ressources (icônes, images, polices), comment elles sont référencées dans les `.ui` et le code C++, et comment ajouter/modifier des ressources.

Fichiers importants
- `resources.qrc` — fichier Qt Resource Collection (racine) qui liste :
  - `resources/fonts/Poppins-Light.ttf`
  - `images/background.jpg`
  - `style.qss`
  - `resources/icons/*.svg` (tous les icônes utilisés dans les .ui)
  - Exemple d'entrée dans `resources.qrc` :
    <file>resources/fonts/Poppins-Light.ttf</file>

- `style.qss` — feuille de style globale appliquée via `main.cpp`. Elle contient des règles CSS-like (couleurs, fonts, background-image, hover) et s'applique globalement à l'application.
  - Exemple d'usage :
    - `background-image: url(:/images/background.jpg);` (définit le background global)
    - `font-family: "Poppins", sans-serif;`

- `main.cpp` — bootstrap :
  - Charge la police Poppins et applique la `style.qss` :
    ```cpp
    int fontId = QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-Light.ttf");
    QFile styleFile(":/style.qss");
    styleFile.open(QFile::ReadOnly);
    qApp->setStyleSheet(styleFile.readAll());
    ```
  - Il loggue si la police a été chargée correctement.

Comment les icônes sont référencées
- Dans les fichiers `.ui` :
  - Les icônes sont référencées via `iconset resource="resources.qrc"` et des chemins `:/icons/<name>.svg`.
  - Exemple : `:/icons/login.svg`, `:/icons/info.svg`, `:/icons/history.svg`.
  - Extrait dans `Profile.ui` :
    ```xml
    <iconset resource="resources.qrc">
      <normaloff>:/icons/info.svg</normaloff>
    </iconset>
    ```

- Dans le code C++ :
  - On utilise `QIcon(":/icons/login.svg")` ou `setIcon(QIcon(":/icons/logout.svg"))`.
  - Exemple dans `MainWindow` :
    ```cpp
    ui->loginBtn->setIcon(QIcon(":/resources/icons/login.svg"));
    ui->loginBtn->setIconSize(QSize(20, 20));
    ```
  - Note : parfois le `.ui` et le C++ utilisent des chemins légèrement différents (`:/icons/...` vs `:/resources/icons/...`) — `resources.qrc` inclut des alias pour que les chemins fonctionnent depuis les `.ui` sans modification.

Où trouver la liste des icônes embarquées
- Le `.qrc` est listé dans `resources.qrc` (à la racine du projet). Le binaire rcc génère `qrc_resources.cpp` dans `build/...`.
- Vous pouvez inspecter `build/.../rcc/qrc_resources.cpp` ou `AmineTemplar_autogen/.../qrc_resources.cpp` pour voir l'inclusion finale.

Police (Poppins)
- Fichier : `resources/fonts/Poppins-Light.ttf`.
- Chargement : dans `main.cpp` via `QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-Light.ttf")`. Si la police se charge, le code récupère la famille (ex: "Poppins") et l'applique via `qApp->setFont(...)` ou via `style.qss`.
- Les `.ui` définissent `font-family: 'Poppins'` pour s'assurer que le rendu est homogène.

Background global
- `style.qss` contient la règle :
  ```css
  background-image: url(:/images/background.jpg);
  ```
  Ce `url(:/images/background.jpg)` pointe vers l'image incluse dans `resources.qrc`.
- Le background est appliqué par la feuille de style globale (chargée dans `main.cpp`).

Comment ajouter une nouvelle icône / image / police
1. Placez le fichier dans le dossier correspondant (`resources/icons/`, `images/`, ou `resources/fonts/`).
2. Ouvrez `resources.qrc` et ajoutez une entrée `<file>resources/icons/my-icon.svg</file>` sous le bon prefix si nécessaire.
3. Si vous utilisez Qt Designer, ouvrez le `.ui`, éditez l'icône via la propriété `icon` et naviguez vers `:/icons/my-icon.svg` (le resource alias apparaîtra).
4. Si vous utilisez C++ : utilisez `QIcon(":/icons/my-icon.svg")` ou `QPixmap(":/images/mybg.jpg")`.
5. Rebuild le projet pour regénérer `qrc_resources.cpp`.

Astuce : alias et chemins
- `resources.qrc` peut contenir des alias ou des prefixes pour conserver des chemins courts (`:/icons/...`). Les `.ui` enregistrent généralement `resource="resources.qrc"` et utilisent `:/icons/name.svg`.
- Si vous rencontrez un widget sans icône visible, vérifiez :
  - que la ressource est listée dans `resources.qrc`,
  - que le chemin est correct (préfix/sous-dossier),
  - que `style.qss` ou un `setStyleSheet()` local ne masque pas l'icône.

Extraits utiles (emplacements)
- `resources.qrc` (racine) — contient `resources/fonts/Poppins-Light.ttf`, `images/background.jpg`, `resources/icons/*.svg`, `style.qss`.
- `main.cpp` — chargement police + style (lignes ~10–40).
- `style.qss` — règles globales (ligne `background-image: url(:/images/background.jpg);`).
- `Profile.ui`, `mainwindow.ui`, `login.ui` — utilisent `iconset resource="resources.qrc"` et `font-family: 'Poppins'`.

Voulez-vous que j'ajoute :
- Un petit script PowerShell pour automatiser l'ajout d'une icône au `resources.qrc` ? (je peux générer une commande qui ajoute l'entrée au `.qrc`).
- Que j'ajoute cette documentation comme `README/8_Resources.md` (déjà fait) dans `README/5_Overall.md` comme lien ?

Fichier créé : `README/8_Resources.md` (c:\Users\user\Documents\QT - Test\AmineTemplar\README\8_Resources.md)

Je marque la tâche correspondante complétée dans la todo list.