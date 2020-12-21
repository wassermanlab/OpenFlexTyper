#Variables:
FMFORMATTER=/mnt/common/WASSERMAN_SOFTWARE/OpenFlexTyper/fmformatter/flextyper_formatter.py
ANCESTRY_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/AncestryResults/
source /mnt/common/WASSERMAN_SOFTWARE/OpenFlexTyper/opt/miniconda3/etc/profile.d/conda.sh
conda activate /mnt/common/WASSERMAN_SOFTWARE/OpenFlexTyper/opt/openFlexTyper/

cd $ANCESTRY_DIR

# AFR
# Father
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR1955420_Ancestry_FTSearch_k31s10m200u  -n AfricanFatherAncestrySites -m 5
# Mother
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR1955443_Ancestry_FTSearch_k31s10m200u -n AfricanMotherAncestrySites -m 5
# Kid
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR2304556_Ancestry_FTSearch_k31s10m200u -n AfricanKidAncestrySites -m 5

# ASIAN
# Father
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR1955507_Ancestry_FTSearch_k31s10m200u -n AsianFatherAncestrySites -m 5
# Mother
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR1955495_Ancestry_FTSearch_k31s10m200u -n AsianMotherAncestrySites -m 5
# Kid
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR2304569_Ancestry_FTSearch_k31s10m200u -n AsianKidAncestrySites -m 5

# EURO
# Father
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR1955404_Ancestry_FTSearch_k31s10m200u -n EuropeanFatherAncestrySites -m 5
# Mother
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR1955491_Ancestry_FTSearch_k31s10m200u -n EuropeanMotherAncestrySites -m 5 
# Kid
python $FMFORMATTER -f VCF -i ${ANCESTRY_DIR}ERR2304597_Ancestry_FTSearch_k31s10m200u -n EuropeanKidAncestrySites -m 5


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

conda activate /mnt/common/WASSERMAN_SOFTWARE/AnnotateVariants/opt/AnnotateVariantsEnvironment/
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


conda activate /mnt/common/WASSERMAN_SOFTWARE/OpenFlexTyper/opt/openFlexTyper/

peddy AllMerged.vcf.gz All.ped
