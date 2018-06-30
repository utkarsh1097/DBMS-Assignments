echo -n "Generating dataset"
for i in 1 2 3 4 
do
	sleep 0.3
	echo -n "."
done
echo "."
g++ -std=c++14 -o generate_dataset generate_dataset.cpp -no-pie
./generate_dataset
rm generate_dataset
echo -n "Generating queryset"
for i in 1 2 3 4 
do
	sleep 0.3
	echo -n "."
done
echo "."
g++ -std=c++14 -o generate_queryset generate_queryset.cpp -no-pie
./generate_queryset
rm generate_queryset
