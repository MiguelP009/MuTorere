import os
import pandas as pd
import matplotlib.pyplot as plt
from tkinter import Tk, filedialog, Label, Button, StringVar, OptionMenu

def plot_data(file_path):
    """Afficher les graphiques pour un fichier donné."""
    # Charger les données
    data = pd.read_csv(file_path)

    # Calcul de la tendance (moyenne glissante)
    window_size = 9000  # Taille de la fenêtre pour la moyenne glissante
    if "WinRate" in data.columns:
        data["WinRateTrend"] = data["WinRate"].rolling(window=window_size).mean()

    # Tracer les récompenses cumulées
    plt.figure(figsize=(12, 6))
    if "TotalReward" in data.columns:
        plt.subplot(2, 1, 1)
        plt.plot(data["Game"], data["TotalReward"], label="Total Reward")
        plt.xlabel("Game")
        plt.ylabel("Total Reward")
        plt.title("Total Rewards Over Time")
        plt.legend()
        plt.grid()

    # Tracer le winrate avec la tendance
    if "WinRate" in data.columns:
        plt.subplot(2, 1, 2)
        plt.plot(data["Game"], data["WinRate"], label="Win Rate (Window)", color="orange")
        plt.plot(data["Game"], data["WinRateTrend"], label="Win Rate Trend", color="blue", linestyle="--")
        plt.xlabel("Game")
        plt.ylabel("Win Rate")
        plt.title("Win Rate Over Time")
        plt.legend()
        plt.grid()

    plt.tight_layout()
    plt.show()

def select_file(directory):
    """Créer une fenêtre Tkinter pour sélectionner un fichier."""
    # Lister les fichiers disponibles dans le répertoire
    files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]

    def show_plot():
        """Afficher les graphiques pour le fichier sélectionné."""
        selected_file = selected_file_var.get()
        file_path = os.path.join(directory, selected_file)
        plot_data(file_path)

    # Initialiser Tkinter
    root = Tk()
    root.title("Sélecteur de fichier")

    # Label d'instruction
    Label(root, text="Sélectionnez un fichier pour afficher les graphiques :").pack(pady=10)

    # Menu déroulant pour sélectionner un fichier
    selected_file_var = StringVar(root)
    selected_file_var.set(files[0])  # Fichier par défaut
    OptionMenu(root, selected_file_var, *files).pack(pady=10)

    # Bouton pour afficher les graphiques
    Button(root, text="Afficher les graphiques", command=show_plot).pack(pady=10)

    # Lancer l'interface
    root.mainloop()

# Répertoire contenant les fichiers
directory = "Data/Results"

# Lancer le sélecteur de fichier interactif
select_file(directory)
