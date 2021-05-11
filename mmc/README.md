# Generalized Min-Max Solver


It is a decision tree based min-max solver to predict best action given a state.
It takes specialized file input, whose structure is described in `FILE_STRUCTURE.md`

We discuss the minor details of the solver here.

## Details

1. The min-max solver is for a zero-sum game between 2 players with alternating turns
2. We can change value of `k` to change our strategy. Larger value of `k` means the solver puts more priority to minimizing loss, than maximizing profit.
3. We also have a  `weight` array, that defines the details about what weight we want to take on increasing depth. This is to simulate realistic scenarios, as agents usually put more weight to near-term utility than far-away.
4. We have considered deterministic game till now, because so,far I have studied only these types of games.

