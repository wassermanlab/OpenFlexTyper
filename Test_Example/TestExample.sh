# Build index
../build/flextyper index \
 -r MixedVirus_100_1.fq.gz \
 -p MixedVirus_100_2.fq.gz \
 -n 1 --gz -v 


# Search index
../build/flextyper search \
	-c setting_1.ini -v

# Print hit count
echo "Search results"
cut -f3,4 path_query_MixedVirus_100_Results.tsv