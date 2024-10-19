# Wordle

Recreation of the popular online game "Wordle".

I'm particularly proud of some of the things I accomplished
with this project. I was able to write most of the input checking/grading
in a few hours, which was quite satisfying. The game is currently in a
"playable" state, but it isn't very fun. Additionally, this project
became too large and disorganized for me to handle without outside tools,
and it fell by the wayside.

Txt containing all valid wordle words provided here: https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93

## To Do:

- [x] Find a random word in the bank
  - [x] Count entries in list
  - [x] Generate random int in range of given entries
  - [x] Return word at given index
- [x] Get user input
  - [x] Escape if letter count != 5
  - [x] Escape if word not in bank
- [x] Compare
  - [x] strncmp() each char in input against each char in rand word
  - [x] Return enum based on outcome (i.e. "Correct Letter/Correct Position", "Correct Letter/Incorrect Position", "Incorrect Letter")
- [x] Build game loop
  - [x] Store random target word
  - [x] Get user input
  - [x] Check against valid input criteria
  - [x] Grade input against target
  - [x] Escape input loop if all graded letters are correct
  - [x] Escape input loop if num_turns == 6
- [ ] Refine
  - [ ] Improve UI
  - [ ] Split game values and buffers into separate types
  - [ ] Buffer holding all possible characters
  - [ ] Add grading check for cases where an input string has repeat characters, but only one instance of that character in the target
    - e.g. target: abore, input: boost
    - first instance of 'o' should display as IL, second instance should display as CL_CP
  - [ ] Improved entropy in get_random_word() if perceived as necessary
  - [ ] Fix stdin buffer overflow
  - [ ] Store incorrect letters to display to user