echo -n "Generating dataset"
for i in 1 2 3 4 
do
	sleep 1
	echo -n "."
done
echo "."
g++ -std=c++14 generate_dataset.cpp
./a.out
echo -n "Generating queryset"
for i in 1 2 3 4 
do
	sleep 1
	echo -n "."
done
echo "."
g++ -std=c++14 generate_queryset.cpp
./a.out