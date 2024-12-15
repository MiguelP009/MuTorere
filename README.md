# Mu Torere AI Project

This project implements the traditional **Mu Torere** board game with artificial intelligence agents to experiment with reinforcement learning (RL). The goal is to pit a reinforcement learning agent against a random agent or another RL agent and analyze its learning process.

## Features
- **Game Simulation**: Implements the Mu Torere board game logic.
- **Reinforcement Learning Agent**: Learns optimal strategies using Q-learning.
- **Random Agent**: Provides a simple baseline for comparison.
- **Training Data Analysis**: Includes a Python tool for visualizing the learning process.

---

## Getting Started

### Prerequisites
- **C++ Compiler**: Requires GCC or any C++17-compatible compiler.
- **Python**: Requires Python 3.x for the analysis tool.
- **Libraries**:
  - Python: `pandas`, `matplotlib` (install with `pip install pandas matplotlib`).

### Running the Simulation
1. Compile and execute the C++ project:
   ```bash
   g++ -std=c++17 -o mu_torere_simulation src/*.cpp
   ./mu_torere_simulation
   ```

2. Use the Python analysis tool to visualize results (explained below).

---

## Project Structure

```plaintext
mu-torere/
├── src/                # Source files
├── include/            # Header files
├── Data/               # Folder for data (e.g., Q-values, results)
│   └── Results/        # Folder for results from simulations
├── analysis_tool.py    # Python tool for visualizing results
└── README.md           # Project documentation
```

---

## C++ Project Overview

### Core Components
1. **Game Logic**:
   - Implements the Mu Torere board game rules.
   - Detects valid moves, game over conditions, and determines the winner.

2. **Agents**:
   - `ReinforcementLearningAgent`: Learns using Q-learning.
   - `RandomAgent`: Chooses moves randomly.

3. **Training**:
   - Allows two agents to compete for thousands of games to train the RL agent.
   - Rewards and win rates are logged for post-training analysis.

4. **Save and Load Q-Values**:
   - The RL agent can save its learning (Q-values) to a file and reload them to resume training or evaluation.

---

## Python Analysis Tool

### Description
The `analysis_tool.py` script allows you to:
- List and select result files from the `Data/Results` directory.
- Visualize the total rewards and win rate over time.
- Analyze learning trends with rolling averages.

### Usage
1. Navigate to the project root directory:
   ```bash
   python analysis_tool.py
   ```

2. A window will open, allowing you to:
   - Select a result file from the `Data/Results` folder.
   - View detailed graphs of:
     - Total rewards over games.
     - Win rate trends over time.

### Example Output
- **Graph 1**: Total rewards accumulated during training.
- **Graph 2**: Win rate with a trend line to observe learning stability.

---

