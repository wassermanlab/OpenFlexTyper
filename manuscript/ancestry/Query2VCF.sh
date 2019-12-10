# AFRICAN
# father
python fmformater/flextyper_formater.py -f VCF -i build/african_father/GRCh37_Sites_Query__Results.tsv -n AfricanFatherAncestrySites
# mother
python fmformater/flextyper_formater.py -f VCF -i build/african_mother/GRCh37_Sites_Query__Results.tsv -n AfricanMotherAncestrySites
# kid
python fmformater/flextyper_formater.py -f VCF -i build/african_kid/GRCh37_Sites_Query__Results.tsv -n AfricanKidAncestrySites

# ASIAN
# father
python fmformater/flextyper_formater.py -f VCF -i build/asian_father/GRCh37_Sites_Query__Results.tsv -n AsianFatherAncestrySites
# mother
python fmformater/flextyper_formater.py -f VCF -i build/asian_mother/GRCh37_Sites_Query__Results.tsv -n AsianMotherAncestrySites
# kid
python fmformater/flextyper_formater.py -f VCF -i build/asian_kid/GRCh37_Sites_Query__Results.tsv -n AsianKidAncestrySites

# EUROPEAN
# father
python fmformater/flextyper_formater.py -f VCF -i build/european_father/GRCh37_Sites_Query__Results.tsv -n EuropeanFatherAncestrySites
# mother
python fmformater/flextyper_formater.py -f VCF -i build/european_mother/GRCh37_Sites_Query__Results.tsv -n EuropeanMotherAncestrySites
# kid
python fmformater/flextyper_formater.py -f VCF -i build/european_kid/GRCh37_Sites_Query__Results.tsv -n EuropeanKidAncestrySites



# bgzip and merge
bgzip AfricanFatherAncestrySites.vcf
tabix AfricanFatherAncestrySites.vcf.gz

bgzip AfricanMotherAncestrySites.vcf
tabix AfricanMotherAncestrySites.vcf.gz

bgzip AfricanKidAncestrySites.vcf
tabix AfricanKidAncestrySites.vcf.gz

bgzip AsianFatherAncestrySites.vcf
tabix AsianFatherAncestrySites.vcf.gz

bgzip AsianMotherAncestrySites.vcf
tabix AsianMotherAncestrySites.vcf.gz

bgzip AsianKidAncestrySites.vcf
tabix AsianKidAncestrySites.vcf.gz

bgzip EuropeanFatherAncestrySites.vcf
tabix EuropeanFatherAncestrySites.vcf.gz

bgzip EuropeanMotherAncestrySites.vcf
tabix EuropeanMotherAncestrySites.vcf.gz

bgzip EuropeanKidAncestrySites.vcf
tabix EuropeanKidAncestrySites.vcf.gz

# Merge
bcftools merge -0 \
	AfricanFatherAncestrySites.vcf.gz \
	AfricanMotherAncestrySites.vcf.gz  \
	AfricanKidAncestrySites.vcf.gz \
	AsianFatherAncestrySites.vcf.gz \
	AsianMotherAncestrySites.vcf.gz  \
	AsianKidAncestrySites.vcf.gz \
	EuropeanFatherAncestrySites.vcf.gz \
	EuropeanMotherAncestrySites.vcf.gz  \
	EuropeanKidAncestrySites.vcf.gz \
	-o AllMerged.vcf

bgzip AllMerged.vcf
tabix  AllMerged.vcf.gz

peddy AllMerged.vcf.gz All.ped
