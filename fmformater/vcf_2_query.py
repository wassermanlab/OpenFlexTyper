from pybedtools import BedTool
from cyvcf2 import VCF
import datetime
import sys
import argparse


def parse_arguments():
    """Parses inputted arguments as described."""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-f', '--fasta', help="Fasta file to query", type=str, required=True)
    parser.add_argument(
        '-v', '--variants', help='variant file in a format like vcf', type=str,
        required=True)
    parser.add_argument('-n', '--filename',
                        help='name of query file generated',
                        type=str, default=datetime.datetime.now().isoformat())
    parser.add_argument('-l', '--length',
                        help='number of bp upstream and downstream',
                        type=int, default=100)
    parser.add_argument('-d', '--data_type',
                        help='where the data came from',
                        type=str, default="vcf")                    
    args = parser.parse_args()
    return args
# sampleID = args.sampleID


def get_seq(index, fasta, variant_tuple, length, dt):
    """Extracts surrounding sequence upstream and downstream of variant"""
    cut_len = length #length of upstream and downstream portion 
    var_len = len(variant_tuple[2]) 
    chro = variant_tuple[0]
    upstream_start = variant_tuple[1] - cut_len - 1
    upstream_stop = variant_tuple[1] - 1
    downstream_start = variant_tuple[1] + var_len
    downstream_stop = variant_tuple[1] + cut_len + var_len
    upstream = BedTool.seq((chro, upstream_start, upstream_stop), fasta) ## get upstream and downstream portion 
    downstream = BedTool.seq((chro, downstream_start, downstream_stop), fasta)

    seq = (
        index,
        upstream + variant_tuple[2] + downstream,
        upstream + variant_tuple[3] + downstream,
        "\t".join(map(str, variant_tuple)), 
        dt
    ) 
    return seq ## returns line 


def write_table(fasta, list_variant_tuples, table_name, length, dt):
    """writes the final table parsing each variant tuple line by line."""
    query_table = open(table_name, "w+")
    query_table.write("\t".join(["#Index", "Reference", "Alternate","Chrom", "Pos", "Ref", "Alt", "Identifier", "Data Type\n"]))
    counter = 0
    for variant in list_variant_tuples: ## for each variants tuple 
        line = get_seq(counter, fasta, variant, length, dt) 
        query_table.write("\t".join(map(str, line)))
        query_table.write("\n")
        counter = counter + 1
    query_table.close()


def extract_variants(vcf):
    """from the vcf return a list of tuble as such (CHROM, POS, REF, ALT)."""
    # returns list of tuples (CHROM, POS, REF, ALT, ID)
    variant_pos = []
    for variant in VCF(vcf): ## for each variant in the vcf
        if len(variant.ALT) > 0: ## if you have an alt
            variant_pos.append((str(variant.CHROM), variant.POS, str(
                variant.REF), str(variant.ALT[0]), str(variant.ID)))
        else: ## if there is no alt allele
            variant_pos.append((str(variant.CHROM), variant.POS, str(
                variant.REF), "", str(variant.ID)))
    return variant_pos


def main():
    args = parse_arguments()
    vcf = args.variants
    fasta = args.fasta
    table_name = args.filename
    length = args.length
    data_type = args.data_type
    variant_tuples = extract_variants(vcf)
    write_table(fasta, variant_tuples, table_name, length, data_type)


if __name__ == "__main__":
    main()
