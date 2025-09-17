# TraceX

**TraceX** est un logiciel multiplateforme développé en C++/Qt pour la gestion et l’extraction de la traçabilité des exigences (SSS → SRS → SDD).  
Il permet de visualiser les liens entre les documents, analyser le taux de traçabilité et générer des rapports détaillés.

---

## 🛠 Fonctionnalités principales

- Import et gestion des fichiers SSS, SRS et SDD.  
- Graphe interactif des liens de traçabilité.  
- Extraction automatique des exigences et styles depuis les documents Word.  
- Génération de rapports récapitulatifs.  
- Interface claire et intuitive en Qt.  

---

## 💾 Installation

La première release officielle est disponible en **fichier ZIP** dans les releases GitHub.  
Selon votre OS, installez le fichier correspondant :  

- **Windows** : `installer.exe` à l’intérieur du ZIP  
- **macOS**   : `installer.pkg` ou `tracavilite-installer.app`  
- **Linux**   : `installer.run`

> ⚠️ Note : cette version est une bêta stable. Pour modifier ou recompiler le projet, consultez le dossier `src/` et adaptez les chemins si nécessaire (images, fichiers `.ui`, Image.qrc).

---

## 📄 Documentation

La documentation complète des fonctions et du projet est disponible en ligne via **GitHub Pages** :  
[https://somixe.github.io/TraceX/](https://somixe.github.io/TraceX/)  

---

## 🧪 Tests et exemples

Le dossier `tests/` contient :  
- `cpp/` et `h/` : fichiers source des tests  
- `examples/` : fichiers SSS, SRS, SDD pour tester le logiciel  
- `CMakeLists.txt` : pour compiler les tests séparément  

---

## 🖼️ Captures d’écran

![Interface principale](assets/images/screenshot_main.png)  
![Graphe de traçabilité](assets/images/screenshot_graph.png)

---

## 👨‍💻 Notes pour développeurs

- Code source : `src/`  
