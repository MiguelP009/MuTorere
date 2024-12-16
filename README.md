# Mu Torere AI Project

This project implements the traditional **Mu Torere** board game with artificial intelligence agents to experiment with reinforcement learning (RL). The goal is to pit a reinforcement learning agent against a random agent, another RL agent, or a human player, and analyze its learning process.

## Features
- **Game Simulation**: Implements the Mu Torere board game logic.
- **Reinforcement Learning Agent**: Learns optimal strategies using Q-learning.
- **Random Agent**: Provides a simple baseline for comparison.
- **RealPlayerAgent**: Allows a human player to interact with the game via the console.
- **Training Data Analysis**: Includes a Python tool for visualizing the learning process.

---

## Getting Started

### Prerequisites
- **C++ Compiler**: Requires GCC or any C++17-compatible compiler.
- **Python**: Requires Python 3.x for the analysis tool.
- **Libraries**:
  - Python: `pandas`, `matplotlib` (install with `pip install pandas matplotlib`).

---

## Running the Simulation

### Compilation
Compile the C++ project:
```bash
g++ -std=c++17 -o mu_torere_simulation src/*.cpp
```

### Command-Line Options
Run the simulation with the following command:
```bash
./mu_torere_simulation [OPTIONS]
```

#### Available Options:
- **Agent Types**:
  - `--agent1 [random|rl|real]`: Type of Agent 1.
  - `--agent2 [random|rl|real]`: Type of Agent 2.
  - Example: `--agent1 rl --agent2 random`
- **Number of Games**:
  - `--games <n>`: Number of games to play (default: 1000).
  - Example: `--games 500`
- **Training**:
  - `--train`: Enables training for RL agents.
  - Example: `--train`
- **Saving and Loading Q-values**:
  - `--export-qvalues <file>`: Save Q-values to the specified file.
  - `--load-qvalues <file>`: Load Q-values from the specified file.
  - Example: `--export-qvalues qvalues.csv` or `--load-qvalues pretrained.csv`
- **Results Output**:
  - `--output-results <file>`: Save game results to the specified file.
  - Example: `--output-results results.csv`
- **Help**:
  - `--help`: Display help information about the command-line options.

---

### Examples

1. **Random agent vs RL agent (100 games)**:
   ```bash
   ./mu_torere_simulation --agent1 random --agent2 rl --games 100
   ```

2. **Train two RL agents and save Q-values**:
   ```bash
   ./mu_torere_simulation --agent1 rl --agent2 rl --games 10000 --train --export-qvalues qvalues.csv
   ```

3. **Load pretrained Q-values and play RL agent vs random agent**:
   ```bash
   ./mu_torere_simulation --agent1 rl --agent2 random --load-qvalues qvalues.csv --games 500
   ```

4. **Human player vs RL agent**:
   ```bash
   ./mu_torere_simulation --agent1 real --agent2 rl --games 1
   ```

5. **Two human players**:
   ```bash
   ./mu_torere_simulation --agent1 real --agent2 real --games 1
   ```

---

## Project Structure

```plaintext
mu-torere/
├── src/                # Source files
├── include/            # Header files
├── Data/               # Folder for data (e.g., Q-values, results)
│   └── Results/        # Folder for results from simulations
│   └── QValues/        # Folder for saved QValues
├── ProcessData.py      # Python tool for visualizing results
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
   - `RealPlayerAgent`: Allows human players to interact with the game via the console.

3. **Training**:
   - Allows two agents to compete for thousands of games to train the RL agent.
   - Rewards and win rates are logged for post-training analysis.

4. **Save and Load Q-Values**:
   - The RL agent can save its learning (Q-values) to a file and reload them to resume training or evaluation.

---

## Python Analysis Tool

### Description
The `ProcessData.py` script allows you to:
- List and select result files from the `Data/Results` directory.
- Visualize the total rewards and win rate over time.
- Analyze learning trends with rolling averages.

### Usage
1. Navigate to the project root directory:
   ```bash
   python ProcessData.py
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