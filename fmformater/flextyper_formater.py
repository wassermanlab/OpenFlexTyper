import sys
import argparse
import os
import statistics


def parse_arguments():
    """Parses inputted arguments as described"""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-f', '--format', help="format of output", type=str, required=True,
        choices=["VCF", "23_and_me", "ancestry"])
    parser.add_argument(
        '-i', '--input', help='input tsv ', type=str, required=True)
    parser.add_argument('-n', '--name',
                        help='name of save file', required=True)
    args = parser.parse_args()
    return args


def flextyper_2_vcf(data, name):
    new = open(name + ".vcf", "w+")
    new.write("##fileformat=VCFv4.2\n")
    new.write("##FORMAT=<ID=GT,Number=1,Type=String,Description=\"Genotype\">\n")
    new.write("##FORMAT=<ID=AD,Number=R,Type=Integer,Description=\"Allelic depths for the ref and alt alleles in the order listed\">\n")
    new.write("#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\tFORMAT\t" +
              name + "\n")

    amount = []
    with open(data) as f:
        for line in f:
            if not line.startswith("#"):
                ln = line.split("\t")
                ref = int(ln[9])
                alt = int(ln[10])
                if (ref == 0 and alt != 0) or (ref != 0 and alt == 0):
                    amount.append(max([ref,alt]))

    mean = statistics.mean(amount)
    std = statistics.stdev(amount)
    UB = mean + std
    LB = mean - std

    with open(data) as f:
        for line in f:
            if not line.startswith("#"):
                ln = line.split("\t")
                ln[-1] = ln[-1].rstrip()
                if int(ln[10]) > 0:
                    chrom = ln[3]
                    pos = str(int(ln[4]) + 1)  # making 1 based
                    ID = ln[7]
                    ref = ln[5]
                    alt = ln[6]
                    ref_count = str(ln[9])
                    alt_count = str(ln[10])
                    if LB < int(alt_count) < UB: # hom
                        zygosity = "1/1"
                    else:  # het
                        zygosity = "0/1"

                    output = "\t".join([chrom, pos, ID, ref, alt,
                                        ".", ".", ".",
                                        "AD:GT", zygosity+":"+ref_count + "," + alt_count])
                    new.write(output + "\n")
    new.close()


def flextyper_2_array(data, name, format):
    if format == "23_and_me":
        new = open(name+"23_and_me.txt", "w+")
        new.write("#rsid\tchromosome\tposition\tgenotype")
    if format == "ancestry":
        new = open(name+"ancestry.txt", "w+")
        new.write("#rsID\tChromosome\tPosition\tAllele 1\tAllele 2\n")
    with open(data) as f:
        for line in f:
            if not line.startswith("#"):
                ln = line.split("\t")
                ln[-1] = ln[-1].rstrip()
                chrom = ln[3]
                pos = str(int(ln[4]) + 1)  # making 1 based
                ID = ln[7]
                ref = ln[5]
                alt = ln[6]
                ref_count = int(ln[9])
                alt_count = int(ln[10])
                if alt_count > 0 or ref_count > 0:
                    if alt_count > 0 and ref_count == 0:  # homozygous alt
                        allele1 = alt
                        allele2 = alt
                    elif alt_count == 0 and ref_count > 0:  # homozygous ref
                        allele1 = ref
                        allele2 = ref
                    elif alt_count > 0 and ref_count > 0:  # het
                        allele1 = ref
                        allele2 = alt
                    if format == "23_and_me":
                        output = "\t".join([ID, chrom, pos, allele1+allele2])
                    if format == "ancestry":
                        output = "\t".join([ID, chrom, pos, allele1, allele2])
                    new.write(output + "\n")
    new.close()


def main():
    args = parse_arguments()
    format = args.format
    input = args.input
    name = args.name

    if format == "VCF":
        flextyper_2_vcf(input, name)
    if format == "23_and_me":
        flextyper_2_array(input, name, "23_and_me")
    if format == "ancestry":
        flextyper_2_array(input, name, "ancestry")


if __name__ == "__main__":
    main()
