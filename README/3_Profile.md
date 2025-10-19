# 3. Profile

Ce document décrit en détail la page Profile du projet Amine Templar et les mesures prises pour éliminer définitivement les décalages d'interface (layout shifts).

## Fichiers clés
- `Profile.ui` — définition complète de la page Profile (tabs, avatar, boutons). (voir sections autour de 340-420 pour le `QTabWidget` initial)
- `profilecontroller.cpp` / `profilecontroller.h` — logique C++ qui pilote les interactions sur la page Profile.

## Onglets (tabs)
La barre d'onglets horizontale contient les onglets suivants (définis dans `Profile.ui`):
- `infoTab` — titre "Info" (icône `:/icons/info.svg`) (autour de `Profile.ui` ligne~370)
- `historyTab` — titre "History" (icône `:/icons/history.svg`) (autour de `Profile.ui` ligne~823)
- `securityTab` — titre "Security" (icône `:/icons/security.svg`) (autour de `Profile.ui` ligne~886)
- `transactionsTab` — titre "Transactions" (icône `:/icons/transactions.svg`) (autour de `Profile.ui` ligne~1097)
- `qrTab` — titre "QR Code" (icône `:/icons/link.svg` utilisé comme placeholder) (autour de `Profile.ui` ligne~1160)

Chaque onglet est un `QWidget` avec son propre `QVBoxLayout` explicitement défini (par ex. `infoLayout`, `historyLayout`, etc.).

## Section Photo de profil (Avatar)
- `avatarLabel` (QLabel) : élément affichant l'avatar (défini dans `Profile.ui` line 453) et stylé dans `profilecontroller.cpp`, méthode `setupCircularAvatar()` (voir `profilecontroller.cpp` lines ~100-160). Le label est contraint à `100x100` (min/max), `border-radius` défini pour le rendre circulaire.
- Boutons à côté de l'avatar :
  - `changeAvatarBtn` (QPushButton) — défini dans `Profile.ui` line 486; action implémentée dans `profilecontroller.cpp` `onChangePhotoClicked()` (voir `profilecontroller.cpp` lines ~600).
  - `removeAvatarBtn` (QPushButton) — défini dans `Profile.ui` (ligne proche de 486); action `ProfileController::onRemovePhotoClicked()` (voir `profilecontroller.cpp` lines ~660).
  - `generateAIImageBtn` (QPushButton) — défini dans `Profile.ui` line 497; action `onGenerateAIImageClicked()` (voir `profilecontroller.cpp` lines ~690).

- Champs personnels importants :
  - `firstNameEdit` (QLineEdit) — défini dans `Profile.ui` line 590

- Actions de sauvegarde :
  - `saveProfileBtn` (QPushButton) — défini dans `Profile.ui` line 763; connecté à `ProfileController::onSaveProfileClicked()` (voir `profilecontroller.cpp` implémentation lines ~820).

- Liste d'activité :
  - `activityListWidget` (QListWidget) — défini dans `Profile.ui` line 875; mise à jour via `ProfileController::addActivity()` (voir `profilecontroller.cpp` lines ~540+).

## Anti-flicker / anti-shift (corrigé)
Les actions réalisées pour éliminer définitivement les décalages sont :
- Tout le contenu de la page `Profile` a été encapsulé dans un `QFrame` nommé `profileContainer` avec un `QVBoxLayout` interne (créé dans `Profile.ui`, modifications effectuées récemment).
- Le `profileContainer` a un `background-color: #ffffff`, `border-radius: 12px` et `margin: 16px` pour conserver un cadre blanc stable autour du contenu.
- Le `QTabWidget` (`profileTabWidget`) possède des contraintes `minimumSize` (950x650) et un `tabBar` dont la hauteur est fixée via le code (dans `profilecontroller.cpp` lors du `showEvent` ou `refreshInternalTabLayout()` si nécessaire).
- Les hover styles ne modifient que la couleur/border, jamais la taille, le padding ou la margin.
- `ProfileController::refreshInternalTabLayout()` est appelé depuis `MainWindow::onProfileClicked()` (voir `mainwindow.cpp`, ligne ~??) pour forcer un recalcul de layout sécurisé à l'ouverture. (implémentation de `refreshInternalTabLayout()` dans `profilecontroller.cpp` gère `layout()->invalidate(); layout()->activate(); QApplication::processEvents();`)

## Mécanismes et slots importants (avec références)
- `ProfileController::onChangePhotoClicked()` — ouvre `QFileDialog`, valide l'image, copie l'image dans le dossier de profil et met à jour l'UI (ligne ~620 dans `profilecontroller.cpp`).
- `ProfileController::onRemovePhotoClicked()` — confirme via `QMessageBox` puis restaure l'avatar par défaut (ligne ~660).
- `ProfileController::onGenerateAIImageClicked()` — ouvre un `QDialog` modal avec une `QTextEdit` pour décrire l'image et deux boutons `Generate`/`Cancel`; simule la génération (ligne ~690).
- `ProfileController::onGenerateQRCodeClicked()` — ouvre un `QDialog` modal affichant une image QR code placeholder et boutons `Save Image`/`Close` (ligne ~740).
- `ProfileController::addActivity()` — gestion de la liste d'activité, met à jour le widget `activityListWidget` (ligne ~540+).

## Alignement, espaces et polices
- Police: `Poppins` chargée dans `main.cpp` (lignes ~10-25); utilisée partout (labels, boutons, inputs).
- Alignement: layouts `QHBoxLayout`/`QVBoxLayout`/`QGridLayout` utilisés de façon cohérente; aucun widget n'utilise de positionnement absolu.
- Espacements: les marges internes (`leftMargin`, `rightMargin`) sont réglées explicitement dans chaque layout (par ex. 16 ou 24 px selon la zone).

## Résumé: pourquoi il n'y a plus de layout shift
1. Contenu encapsulé dans `profileContainer` (QFrame blanc) — hover et modifications internes changent uniquement l'apparence interne sans impacter la taille extérieure du container.
2. Contraintes de taille (min/max) sur widgets importants (tabs, avatars, boutons) empêchent les redimensionnements inattendus.
3. Réinitialisation contrôlée du layout via `refreshInternalTabLayout()` pour éviter le recalcul asynchrone au moment de l'affichage.

---

Si vous souhaitez, je peux générer une liste complète avec numéros de ligne exacts pour chaque widget (`firstNameEdit`, `emailEdit`, `saveProfileBtn`, etc.).