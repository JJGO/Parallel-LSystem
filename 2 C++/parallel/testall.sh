# ./test.sh naive $1 $2 $3
# ./test.sh dynamicahead $1 $2 $3
# ./test.sh connected $1 $2 $3

./test.sh naive 15 65 11
mv Results_naive.txt Results_naive65.txt
./test.sh dynamicahead 15 65 11
mv Results_dynamicahead.txt Results_dynamicahead65.txt
./test.sh connected 15 65 11
mv Results_connected.txt Results_connected65.txt

./test.sh naive 15 130 11
mv Results_naive.txt Results_naive130.txt
./test.sh dynamicahead 15 130 11
mv Results_dynamicahead.txt Results_dynamicahead130.txt
./test.sh connected 15 130 11
mv Results_connected.txt Results_connected130.txt

./test.sh naive 15 260 11
mv Results_naive.txt Results_naive260.txt
./test.sh dynamicahead 15 260 11
mv Results_dynamicahead.txt Results_dynamicahead260.txt
./test.sh connected 15 260 11
mv Results_connected.txt Results_connected260.txt