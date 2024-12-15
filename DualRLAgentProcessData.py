import pandas as pd
import matplotlib.pyplot as plt

# Charger les données
data = pd.read_csv("dual_rl_rewards.csv")

# Tracer les récompenses cumulées pour chaque joueur
plt.figure(figsize=(10, 6))
plt.plot(data["Game"], data["TotalRewardPlayer1"], label="Player 1 (RL Agent)", color="blue")
plt.plot(data["Game"], data["TotalRewardPlayer2"], label="Player 2 (RL Agent)", color="orange")
plt.xlabel("Game")
plt.ylabel("Total Reward")
plt.title("Total Rewards Over Time for Both RL Agents")
plt.legend()
plt.grid()
plt.show()
