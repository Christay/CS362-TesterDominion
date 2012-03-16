#!/bin/bash

make clean
make all
make test_dom

./playdom 44 > game.diff
diff game.diff game.static > gamediff.results
./test_dom -br > buy_card_random.results
./test_dom -pc > play_card_random.results
./test_dom -rg > random_games.results
./test_dom -cc > corner_cases.results